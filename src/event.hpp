#pragma once

#include "SFML/Graphics.hpp"

class Event
{
public:
	sf::Event& get();
	void pollEvents();
	
	int mousePosX {0};
	int mousePosY {0};
	
	bool mouseLBPressed {false};
	bool mouseRBPressed {false};
	
	bool keyLeftPressed {false};
	bool keyRightPressed {false};
	bool keyUpPressed {false};
	bool keyDownPressed {false};
	
	bool closeWindow {false};
	
	bool playerChoosed {false};
	bool gameIsEnded {false};
	
	unsigned int playerIndex {0};
	unsigned int winnerIndex {0};
	
private:
	sf::Event event;

public:
	Event();
	virtual ~Event();

};

