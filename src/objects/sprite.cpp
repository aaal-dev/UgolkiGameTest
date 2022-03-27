#include "sprite.hpp"

Sprite::Sprite() {
	type = DrawableType::SPRITE;
}

Sprite::Sprite(unsigned int id) : id(id) {
	type = DrawableType::SPRITE;
}

Sprite::~Sprite(){}

void Sprite::create(Texture const *texture, float x, float y) {
	sprite = std::make_unique<sf::Sprite>();
	sprite->setTexture(texture->get());
	auto size = texture->get().getSize();
	sprite->setOrigin(size.x * .5f, size.y * .5f);
	sprite->setPosition(x, y);
}

void Sprite::update(unsigned int deltaTime) {

}

const sf::Drawable& Sprite::get() const {
	return *sprite.get();
}

bool Sprite::isMouseInside(unsigned int x, unsigned int y) {
	return sprite->getGlobalBounds().contains(x, y);
}

void Sprite::move(float offsetX, float offsetY) {
	sprite->move(offsetX, offsetY);
}

void Sprite::rotate(float angle) {
	sprite->rotate(angle);
}

float Sprite::getRotation() const {
	return sprite->getRotation();
}

void Sprite::scale(float factor) {
	sprite->setScale(factor, factor);
}

void Sprite::setColor(sf::Color const &color) {
	sprite->setColor(color);
}

void Sprite::setPosition(unsigned int x, unsigned int y) {
	sprite->setPosition(x, y);
}

unsigned int Sprite::getId() const {
	return id;
}