#include "window.hpp"

Window::Window(){}

Window::~Window(){}

void Window::create(std::string const &title, unsigned int width, unsigned int height) {
	window = std::make_unique<sf::RenderWindow> (sf::VideoMode(width, height), 
			title, sf::Style::Titlebar | sf::Style::Close);
	window->setVerticalSyncEnabled(true);
}

bool Window::isOpen() const {
	return window->isOpen();
}

void Window::close() {
	window->close();
}

void Window::pollEvents() {
	while (window->pollEvent(event.get())) {
		event.pollEvents();
	}
	if (event.closeWindow)
		close();
	if (event.playerChoosed) {
		event.playerChoosed = false;
		changeSceneTo("game");
	}
	if (event.gameIsEnded) {
		changeSceneTo("gameover");
	}
}

void Window::update(unsigned int deltaTime) {
	currentScene->update(deltaTime);
}

void Window::draw() {
	window->clear();
	
	for (auto const &obj : currentScene->fixedObjs) {
		window->draw(obj->get());
	}
	
	for (auto const &obj : currentScene->dynamicObjs) {
		window->draw(obj->get());
	}
	
	window->display();
}

void Window::addScene(std::unique_ptr<Scene> scene) {
	scenes.insert({scene->name, std::move(scene)});
}

void Window::changeSceneTo(std::string const &name) {
	currentScene = scenes[name].get();
	currentScene->setEvent(&event);
}