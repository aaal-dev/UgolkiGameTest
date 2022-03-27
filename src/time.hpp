#pragma once

#include "SFML/Graphics.hpp"
class Time
{
public:
	void init();
	unsigned int getTime();
	unsigned int getDeltaTime();
	
private:
	sf::Clock clock;
	unsigned int lastTime{0};
	unsigned int deltaTime{0};
	
public:
	Time();
	virtual ~Time();

};

