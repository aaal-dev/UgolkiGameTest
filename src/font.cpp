#include "font.hpp"

Font::Font(){}

Font::~Font(){}

void Font::create(std::string const &filepath) {
	font = std::make_unique<sf::Font>();
	font->loadFromFile(filepath);
}

sf::Font& Font::get() const {
	return *font.get();
}

