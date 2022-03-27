#pragma once

#include "scene.hpp" // Base class: Scene

class PlayScene : public Scene
{
public:
	std::vector<std::unique_ptr<Cell>> cells;
	
	std::unordered_map<unsigned int, unsigned int> rowCapacity;
	std::unordered_map<unsigned int, unsigned int> columnCapacity;
	
	unsigned int hoveredIndex {0};
	
	void addFixed(std::unique_ptr<Drawable> obj);
	void addFixed(std::unique_ptr<Drawable> obj, std::unique_ptr<Texture> texture);
	
	void addDynamic(std::unique_ptr<Drawable> obj);
	void addDynamic(std::unique_ptr<Drawable> obj, std::unique_ptr<Texture> texture);
	
	void addCell(std::unique_ptr<Cell> cell);
	
	virtual void update(unsigned int deltaTime) override;
	virtual void setEvent(Event* event) override;
	
private:
	void (PlayScene::*playerMove)(unsigned int);
	void (PlayScene::*cpuMove)(unsigned int);
	
	unsigned int playerIndex {0};
	
	bool isCloseEnough(unsigned int index);
	void setUpdateFunc(std::string const &name);
	
	void changePlayer(unsigned int playerIndex);
	void changeCPUMoveDirection(unsigned int playerIndex);
	void humanMove(unsigned int deltaTime);
	//void cpuMove(unsigned int deltaTime);
	void cpuMoveLeftUp(unsigned int deltaTime);
	void cpuMoveRightDown(unsigned int deltaTime);
	bool randomMove();
	
	void moveLeftFrom(Cell *cell);
	void moveRigthFrom(Cell *cell);
	void moveUpFrom(Cell *cell);
	void moveDownFrom(Cell *cell);
	
	bool isLeftCellReachableFrom(Cell *cell);
	bool isRightCellReachableFrom(Cell *cell);
	bool isUpCellReachableFrom(Cell *cell);
	bool isDownCellReachableFrom(Cell *cell);
	
	void checkWhoIsWin();
	
public:
	PlayScene();
	virtual ~PlayScene();

};

