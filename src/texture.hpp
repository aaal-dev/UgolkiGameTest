#pragma once

#include <memory>
#include <string>


#include "SFML/Graphics.hpp"

class Texture
{
public:
	void create(std::string const &filepath);
	const sf::Texture& get() const;
	
private:
	std::unique_ptr<sf::Texture> texture;
	
public:
	Texture();
	virtual ~Texture();

};

