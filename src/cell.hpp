#pragma once

#include <memory>
#include <string>

#include "SFML/Graphics.hpp"

#include "objects/drawable.hpp"
#include "objects/sprite.hpp"

class Cell
{
public:
	unsigned int index {0};
	unsigned int row {0};
	unsigned int column {0};
	unsigned int posX {0};
	unsigned int posY {0};
	unsigned int offX {0};
	unsigned int offY {0};
	unsigned int width {0};
	unsigned int height {0};
	bool ocupated {false};
	bool hovered {false};
	bool choosed {false};
	bool stacked {false};
	
	void add(Drawable *obj);
	Drawable* get() const;
	void update(unsigned int deltaTime);
	
	bool isMouseInside(unsigned int x, unsigned int y);
	void move(float offsetX, float offsetY);
	void rotate(float angle);
	void scale(float factor);
	void setHovered();
	void loseHover();
	void setChoosed();
	void loseChoice();
	
	void moveTo(Cell *cell);
	
	void setSize(unsigned int width, unsigned int height);
	void setOrigin(unsigned int offX, unsigned int offY);
	void setPosition(unsigned int posX, unsigned int posY);
	
	unsigned int getId() const;
	bool hasPlayer(unsigned int playerIndex) const;
	
private:
	Drawable *obj {nullptr};

	bool _moveLeft {false};
	bool _moveRight {false};
	bool _moveUp {false};
	bool _moveDown {false};
	
	
public:
	Cell();
	virtual ~Cell();

};

