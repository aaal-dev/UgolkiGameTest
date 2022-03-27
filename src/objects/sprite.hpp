#pragma once

#include <cmath>
#include <memory>
#include <string>

#include "SFML/Graphics.hpp"

#include "drawable.hpp"
#include "../texture.hpp"

class Sprite : public Drawable
{
public:
	void create(Texture const *texture, float x, float y);
	void update(unsigned int deltaTime);
	const sf::Drawable& get() const override;
	bool isMouseInside(unsigned int x, unsigned int y);
	void move(float offsetX, float offsetY);
	void rotate(float angle);
	float getRotation() const;
	void scale(float factor);
	void setColor(sf::Color const &color);
	void setPosition(unsigned int x, unsigned int y);
	unsigned int getId() const;
	
private:
	std::unique_ptr<sf::Sprite> sprite;
	std::unique_ptr<sf::Texture> texture;
	unsigned int id;
	
public:
	Sprite();
	Sprite(unsigned int id);
	virtual ~Sprite();

};

