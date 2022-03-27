#pragma once

#include "scene.hpp" // Base class: Scene

class GameOverScene : public Scene
{
public:
	void addFixed(std::unique_ptr<Drawable> obj);
	void addFixed(std::unique_ptr<Drawable> obj, std::unique_ptr<Texture> texture);
	
	void addDynamic(std::unique_ptr<Drawable> obj, std::unique_ptr<Texture> texture);
	
	virtual void update(unsigned int deltaTime) override;
	
	GameOverScene();
	virtual ~GameOverScene();

};

