#pragma once

#include <memory>
#include <string>

#include "SFML/Graphics.hpp"

#include "drawable.hpp"
#include "../font.hpp"

class Text : public Drawable
{
public:
	void create(std::wstring const &line, float x, float y);
	const sf::Drawable& get() const override;
	void setFont(Font *font);
	void setSize(unsigned int size);
	void setColor(sf::Color const &color);
	
private:
	std::unique_ptr<sf::Text> text;
	Font *font;
	
public:
	Text();
	virtual ~Text();

};

