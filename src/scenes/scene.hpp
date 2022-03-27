#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>

#include "../objects/drawable.hpp"
#include "../cell.hpp"
#include "../event.hpp"
#include "../texture.hpp"

class Scene
{
public:
	std::string name;
	std::vector<std::unique_ptr<Texture>> textures;
	std::vector<std::unique_ptr<Drawable>> fixedObjs;
	std::vector<std::unique_ptr<Drawable>> dynamicObjs;
	
	void addTexture(std::unique_ptr<Texture> texture);
	virtual void setEvent(Event* event);
	virtual void update(unsigned int deltaTime) = 0;
	
protected:
	Event* event;
	
public:
	Scene();
	virtual ~Scene();

};

