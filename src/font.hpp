#pragma once

#include <memory>
#include <string>

#include "SFML/Graphics.hpp"

class Font
{
public:
	void create(std::string const &filepath);
	sf::Font& get() const;
	
private:
	std::unique_ptr<sf::Font> font;
	
public:
	Font();
	virtual ~Font();

};

