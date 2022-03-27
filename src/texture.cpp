#include "texture.hpp"

Texture::Texture(){}

Texture::~Texture(){}

void Texture::create(std::string const &filepath) {
	texture = std::make_unique<sf::Texture>();
	texture->loadFromFile(filepath);
}

const sf::Texture& Texture::get() const {
	return *texture;
}