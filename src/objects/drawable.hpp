#pragma once

#include <memory>
#include <string>

#include "SFML/Graphics.hpp"

enum class DrawableType {
	SPRITE,
	TEXT
};

class Drawable
{
public:
	std::string name;
	DrawableType type;
	
	virtual const sf::Drawable& get() const = 0;
	
public:
	Drawable() {}
	virtual ~Drawable() {}

};

