#include "introscene.hpp"

IntroScene::IntroScene(){}

IntroScene::~IntroScene(){}

void IntroScene::addFixed(std::unique_ptr<Drawable> obj) {
	fixedObjs.push_back(std::move(obj));
}

void IntroScene::addFixed(std::unique_ptr<Drawable> obj, std::unique_ptr<Texture> texture) {
	fixedObjs.push_back(std::move(obj));
	textures.push_back(std::move(texture));
}

void IntroScene::addDynamic(std::unique_ptr<Drawable> obj, std::unique_ptr<Texture> texture) {
	dynamicObjs.push_back(std::move(obj));
	textures.push_back(std::move(texture));
}

void IntroScene::update(unsigned int deltaTime) {
	for (auto const &obj : dynamicObjs) {
		if (obj->type == DrawableType::SPRITE) {
			auto sprite = static_cast<Sprite*>(obj.get());
			if (sprite->isMouseInside(event->mousePosX, event->mousePosY)) {
				if (event->mouseLBPressed) {
					event->playerIndex = sprite->getId();
					event->playerChoosed = true;
				} else {
					sprite->rotate(1.f);
				}
			} else {
//				cell->loseHover();
			}
			sprite->update(deltaTime);
		}
	}
	event->mouseLBPressed = false;
}