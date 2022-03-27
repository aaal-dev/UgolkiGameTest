#include "playscene.hpp"

PlayScene::PlayScene(){}

PlayScene::~PlayScene(){}

void PlayScene::addFixed(std::unique_ptr<Drawable> obj) {
	fixedObjs.push_back(std::move(obj));
}

void PlayScene::addFixed(std::unique_ptr<Drawable> obj, std::unique_ptr<Texture> texture) {
	fixedObjs.push_back(std::move(obj));
	textures.push_back(std::move(texture));
}

void PlayScene::addDynamic(std::unique_ptr<Drawable> obj) {
	dynamicObjs.push_back(std::move(obj));
}

void PlayScene::addDynamic(std::unique_ptr<Drawable> obj, std::unique_ptr<Texture> texture) {
	dynamicObjs.push_back(std::move(obj));
	textures.push_back(std::move(texture));
}

void PlayScene::addCell(std::unique_ptr<Cell> cell) {
	if (cell->get()) {
		rowCapacity[cell->row]++;
		columnCapacity[cell->column]++;
	}
	cells.push_back(std::move(cell));
}

void PlayScene::update(unsigned int deltaTime) {
	(this->*playerMove)(deltaTime);
	checkWhoIsWin();
}

void PlayScene::setEvent(Event *event) {
	this->event = event;
	changeCPUMoveDirection(event->playerIndex);
	changePlayer(event->playerIndex);
	
}

bool PlayScene::isCloseEnough(unsigned int index) {
	if (cells[index]->row == cells[hoveredIndex]->row && 
			!cells[hoveredIndex]->ocupated) 
	{
		return index-1 == hoveredIndex || index+1 == hoveredIndex;
	}
	if (cells[index]->column == cells[hoveredIndex]->column &&
			!cells[hoveredIndex]->ocupated) 
	{
		return 
			cells[index]->row-1 == cells[hoveredIndex]->row || 
			cells[index]->row+1 == cells[hoveredIndex]->row;
	}
	return false;
}

void PlayScene::changePlayer(unsigned int playerIndex) {
	if (playerIndex == 1)
		playerMove = &PlayScene::humanMove;
	else if (playerIndex == 2)
		playerMove = cpuMove;
}

void PlayScene::changeCPUMoveDirection(unsigned int playerIndex) {
	if (playerIndex == 1)
		cpuMove = &PlayScene::cpuMoveLeftUp;
	else if (playerIndex == 2)
		cpuMove = &PlayScene::cpuMoveRightDown;
}

void PlayScene::humanMove(unsigned int deltaTime) {
	for (auto const &cell : cells) {
		if (cell->ocupated) {
			if (cell->getId() == event->playerIndex) {
				if (cell->choosed) { // Если спрайт в ячейке выбран
					
					// Управление с клавиатуры
					if (event->keyLeftPressed) {
						if (isLeftCellReachableFrom(cell.get())) {
							moveLeftFrom(cell.get());
							changePlayer(2);
						}
						event->keyLeftPressed = false;
					} else if (event->keyRightPressed) {
						if (isRightCellReachableFrom(cell.get())) {
							moveRigthFrom(cell.get());
							changePlayer(2);
						}
						event->keyRightPressed = false;
					} else if (event->keyUpPressed) {
						if (isUpCellReachableFrom(cell.get())) {
							moveUpFrom(cell.get());
							changePlayer(2);
						}
						event->keyUpPressed = false;
					} else if (event->keyDownPressed) {
						if (isDownCellReachableFrom(cell.get())) {
							moveDownFrom(cell.get());
							changePlayer(2);
						}
						event->keyDownPressed = false;
						
					// Управление мышью
					} else if (event->mouseLBPressed) {
						if (cell->isMouseInside(event->mousePosX, event->mousePosY)) {
							cell->loseChoice();
						} else {
							if (isCloseEnough(cell->index)) {
								cell->moveTo(cells[hoveredIndex].get());
								event->mouseLBPressed = false;
								changePlayer(2);
							} else {
								cell->loseChoice();
							}
						}
					}
				} else {
					if (cell->isMouseInside(event->mousePosX, event->mousePosY)) {
						if (event->mouseLBPressed) {
							cell->setChoosed();
						} else {
							cell->setHovered();
						}
						hoveredIndex = cell->index;
					} else {
						cell->loseHover();
					}
				}

			}
		} else {
			if (cell->isMouseInside(event->mousePosX, event->mousePosY)) {
				hoveredIndex = cell->index;
			}
		}
		if (cell->ocupated) {
			if (cell->getId() == event->playerIndex) {
				cell->update(deltaTime);
			}
		}
	} 

	event->mouseLBPressed = false;
	event->keyLeftPressed = false;
	event->keyRightPressed = false;
	event->keyUpPressed = false;
	event->keyDownPressed = false;
	
}

void PlayScene::cpuMoveLeftUp(unsigned int deltaTime) {
	for (auto it = cells.rbegin(); it != cells.rend(); ++it) { 
		auto cell = it->get();
		if (cell->ocupated) {
			if (cell->getId() != event->playerIndex) {
				if (randomMove()) {
					if (isLeftCellReachableFrom(cell)) {
						moveLeftFrom(cell);
						changePlayer(1);
						break;
					}
				} else {
					if (isUpCellReachableFrom(cell)) {
						moveUpFrom(cell);
						changePlayer(1);
						break;
					}
				}
			}
		}
		if (cell->ocupated) {
			cell->update(deltaTime);
		}
	}
}

void PlayScene::cpuMoveRightDown(unsigned int deltaTime){
	for (auto it = cells.begin(); it != cells.end(); ++it) { 
		auto cell = it->get();
		if (cell->ocupated) {
			if (cell->getId() != event->playerIndex) {
				if (randomMove()) {
					if (isRightCellReachableFrom(cell)) {
						moveRigthFrom(cell);
						changePlayer(1);
						break;
					}
				} else {
					if (isDownCellReachableFrom(cell)) {
						moveDownFrom(cell);
						changePlayer(1);
						break;
					}
				}
			}
		}
		if (cell->ocupated) {
			cell->update(deltaTime);
		}
	}
}

bool PlayScene::randomMove() {
	return rand() % 2 == 0;
}

void PlayScene::moveLeftFrom(Cell *cell) {
	if (cell->column <= 4) {
		columnCapacity[cell->column-1]++;
		columnCapacity[cell->column]--;
	}
	cell->moveTo(cells[cell->index - 1].get());
}

void PlayScene::moveRigthFrom(Cell *cell) {
	if (cell->column >= 5) {
		columnCapacity[cell->column+1]++;
		columnCapacity[cell->column]--;
	}
	cell->moveTo(cells[cell->index + 1].get());
}

void PlayScene::moveUpFrom(Cell *cell) {
	if (cell->row <= 4) {
		rowCapacity[cell->row-1]++;
		rowCapacity[cell->row]--;
	}
	cell->moveTo(cells[cell->index - 8].get());
}

void PlayScene::moveDownFrom(Cell *cell) {
	if (cell->row >= 5) {
		rowCapacity[cell->row+1]++;
		rowCapacity[cell->row]--;
	}
	cell->moveTo(cells[cell->index + 8].get());
}

bool PlayScene::isLeftCellReachableFrom(Cell *cell) {
	if (cell->column <= 4 && columnCapacity[cell->column-1] == 3) {
		return false;
	}
	return cell->column > 0 && !cells[cell->index - 1]->ocupated;
}

bool PlayScene::isRightCellReachableFrom(Cell *cell) {
	if (cell->column >= 5 && columnCapacity[cell->column+1] == 3) {
		return false;
	}
	return cell->column < 7 && !cells[cell->index + 1]->ocupated;
}

bool PlayScene::isUpCellReachableFrom(Cell *cell) {
	if (cell->row <= 4 && rowCapacity[cell->row-1] == 3) {
		return false;
	}
	return cell->row > 0 && !cells[cell->index - 8]->ocupated;
}

bool PlayScene::isDownCellReachableFrom(Cell *cell) {
		if (cell->row >= 5 && rowCapacity[cell->row+1] == 3) {
		return false;
	}
	return cell->row < 7 && !cells[cell->index + 8]->ocupated;
}

void PlayScene::checkWhoIsWin() {
	if(event->playerIndex == 1) {
		if (cells[0]->hasPlayer(2) &&
			cells[1]->hasPlayer(2) &&
			cells[2]->hasPlayer(2) &&
			cells[8]->hasPlayer(2) &&
			cells[9]->hasPlayer(2) &&
			cells[10]->hasPlayer(2) &&
			cells[16]->hasPlayer(2) &&
			cells[17]->hasPlayer(2) &&
			cells[18]->hasPlayer(2))
		{
			event->gameIsEnded = true;
			event->winnerIndex = 2;
		} else if
			(cells[45]->hasPlayer(1) &&
			cells[46]->hasPlayer(1) &&
			cells[47]->hasPlayer(1) &&
			cells[53]->hasPlayer(1) &&
			cells[54]->hasPlayer(1) &&
			cells[55]->hasPlayer(1) &&
			cells[61]->hasPlayer(1) &&
			cells[62]->hasPlayer(1) &&
			cells[63]->hasPlayer(1)) 
		{
			event->gameIsEnded = true;
			event->winnerIndex = 1;
		}
	} else if(event->playerIndex == 2) {
		if (cells[0]->hasPlayer(2) &&
			cells[1]->hasPlayer(2) &&
			cells[2]->hasPlayer(2) &&
			cells[8]->hasPlayer(2) &&
			cells[9]->hasPlayer(2) &&
			cells[10]->hasPlayer(2) &&
			cells[16]->hasPlayer(2) &&
			cells[17]->hasPlayer(2) &&
			cells[18]->hasPlayer(2)) 
		{
			event->gameIsEnded = true;
			event->winnerIndex = 1;
		} else if
			(cells[45]->hasPlayer(1) &&
			cells[46]->hasPlayer(1) &&
			cells[47]->hasPlayer(1) &&
			cells[53]->hasPlayer(1) &&
			cells[54]->hasPlayer(1) &&
			cells[55]->hasPlayer(1) &&
			cells[61]->hasPlayer(1) &&
			cells[62]->hasPlayer(1) &&
			cells[63]->hasPlayer(1)) 
		{
			event->gameIsEnded = true;
			event->winnerIndex = 2;
		}
	}
}