#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "SFML/Graphics.hpp"

#include "event.hpp"
#include "scenes/scene.hpp"
#include "objects/sprite.hpp"

class Window
{
public:
	bool changeScene {false};
	void create(std::string const &title, unsigned int width, unsigned int height);
	bool isOpen() const;
	void close();
	
	void pollEvents();
	void update(unsigned int deltaTime);
	void draw();
	
	void addScene(std::unique_ptr<Scene> scene);
	void changeSceneTo(std::string const &name);

private:
	std::unique_ptr<sf::RenderWindow> window;
	Scene *currentScene;
	Event event;
	std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
	
public:
	Window();
	virtual ~Window();

};

