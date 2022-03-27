#include "text.hpp"

Text::Text(){
	type = DrawableType::TEXT;
}

Text::~Text(){}

void Text::create(std::wstring const &line, float x, float y) {
	text = std::make_unique<sf::Text>();
	text->setFont(font->get());
	text->setString(line);
	text->setPosition(x, y);
	sf::FloatRect bounds = text->getLocalBounds();
	text->setOrigin(bounds.width * .5f, bounds.height * .5f);
	text->setFillColor(sf::Color::White);
}

const sf::Drawable& Text::get() const {
	return *text.get();
}

void Text::setFont(Font *font) {
	this->font = font;
}

void Text::setSize(unsigned int size) {
	text->setCharacterSize(size);
	sf::FloatRect bounds = text->getLocalBounds();
	text->setOrigin(bounds.width * .5f, bounds.height * .5f);
}

void Text::setColor(sf::Color const &color) {
	text->setFillColor(color);
}