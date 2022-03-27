#include "gameoverscene.hpp"

GameOverScene::GameOverScene(){}

GameOverScene::~GameOverScene(){}

void GameOverScene::addFixed(std::unique_ptr<Drawable> obj) {
	fixedObjs.push_back(std::move(obj));
}

void GameOverScene::addFixed(std::unique_ptr<Drawable> obj, std::unique_ptr<Texture> texture) {
	fixedObjs.push_back(std::move(obj));
	textures.push_back(std::move(texture));
}

void GameOverScene::addDynamic(std::unique_ptr<Drawable> obj, std::unique_ptr<Texture> texture) {
	dynamicObjs.push_back(std::move(obj));
	textures.push_back(std::move(texture));
}

void GameOverScene::update(unsigned int deltaTime) {
	for (auto const &obj : dynamicObjs) {
		if (obj->type == DrawableType::SPRITE) {
			auto sprite = static_cast<Sprite*>(obj.get());
			if (sprite->getId() == event->winnerIndex) {
				sprite->rotate(1.f);
			} else {
				sprite->setColor(sf::Color::Transparent);
			}
			sprite->update(deltaTime);
		}
	}
	event->mouseLBPressed = false;
}
