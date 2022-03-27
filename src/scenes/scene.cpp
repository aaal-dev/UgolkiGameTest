#include "scene.hpp"

Scene::Scene(){
	srand(time(NULL));
}

Scene::~Scene(){}

void Scene::addTexture(std::unique_ptr<Texture> texture) {
	textures.push_back(std::move(texture));
}

void Scene::setEvent(Event *event) {
	this->event = event;
}

//void Scene::setUpdateFunc(std::string const &name) {
//	if (name == "intro")
//		move = &Scene::choosing;
//	else if (name == "game")
//		changeFunc();
//}



