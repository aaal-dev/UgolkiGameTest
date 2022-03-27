#include "event.hpp"

Event::Event(){}

Event::~Event(){}

sf::Event& Event::get() {
	return event;
}

void Event::pollEvents() {
	switch (event.type) {
		case sf::Event::Closed: {
			closeWindow = true;;
			break;
		}
		case sf::Event::MouseMoved: {
			mousePosX = event.mouseMove.x;
			mousePosY = event.mouseMove.y;
			break;
		}
		case sf::Event::MouseButtonReleased: {
			if (event.mouseButton.button == sf::Mouse::Button::Left) {
				mouseLBPressed = true;
			}
			break;
		}
		case sf::Event::KeyPressed: {
			switch (event.key.code) {
				case sf::Keyboard::Key::Left: {
					keyLeftPressed = true;
					break;
				}
				case sf::Keyboard::Key::Right: {
					keyRightPressed = true;
					break;
				}
				case sf::Keyboard::Key::Up: {
					keyUpPressed = true;
					break;
				}
				case sf::Keyboard::Key::Down: {
					keyDownPressed = true;
					break;
				}
				default:
					break;
			}
			break;
		}
		default: {
			break;
		}
	}
}