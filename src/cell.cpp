#include "cell.hpp"

Cell::Cell(){}

Cell::~Cell(){}

void Cell::add(Drawable *obj) {
	ocupated = true;
	this->obj = obj;
}

Drawable* Cell::get() const {
	return obj;
}

void Cell::update(unsigned int deltaTime) {
	auto sprite = static_cast<Sprite*>(obj);
	if (hovered) {
		sprite->rotate(1.2f);
	}
	if (choosed) {
		sprite->rotate(1.2f);
		sprite->scale(1.1f + (.1f * sin(sprite->getRotation() * 0.01745)));
		sprite->setColor(sf::Color(255, 200, 200, 255));
		if (_moveLeft) {
			sprite->move(-64.f, 0.f);
			_moveLeft =false;
		} else if (_moveRight) {
			sprite->move(64.f, 0.f);
			_moveRight = false;
		} else if (_moveUp) {
			sprite->move(0.f, -64.f);
			_moveUp = false;
		} else if (_moveDown) {
			sprite->move(0.f, 64.f);
			_moveDown = false;
		}
	} else {
		sprite->scale(1.f);
		sprite->setColor(sf::Color::White);
	}
}

bool Cell::isMouseInside(unsigned int x, unsigned int y) {
	return (x < posX + offX) && (x > posX - offX) && 
			(y < posY + offY) && (y > posY - offY);
}

//void Cell::move(float offsetX, float offsetY) {
//	sprite->move(offsetX, offsetY);
//}
//
//void Cell::rotate(float angle) {
//	sprite->rotate(angle);
//}
//
//void Cell::scale(float factor) {
//	sprite->setScale(factor, factor);
//}

void Cell::setHovered() {
	hovered = true;
}

void Cell::loseHover() {
	hovered = false;
}

void Cell::setChoosed() {
	choosed = true;
}

void Cell::loseChoice() {
	choosed = false;
}

void Cell::moveTo(Cell *cell) {
	if (!cell->ocupated) {
		auto sprite = static_cast<Sprite*>(obj);
		sprite->setPosition(cell->posX, cell->posY);
		cell->ocupated = ocupated;
		cell->choosed = choosed;
		cell->add(sprite);
		ocupated = false;
		choosed = false;
		hovered = false;
		obj = nullptr;
	}
}

void Cell::setSize(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	this->offX = width / 2;
	this->offY = height / 2;
}

void Cell::setOrigin(unsigned int offX, unsigned int offY) {
	this->offX = offX;
	this->offY = offY;
}

void Cell::setPosition(unsigned int posX, unsigned int posY) {
	this->posX = posX;
	this->posY = posY;
}

unsigned int Cell::getId() const {
	auto sprite = static_cast<Sprite*>(obj);
	return sprite->getId();
}

bool Cell::hasPlayer(unsigned int playerIndex) const {
	return this->ocupated && getId() == playerIndex;
}