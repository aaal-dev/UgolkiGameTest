#pragma once

#include <memory>
#include <string>
#include <vector>

#include "SFML/Graphics.hpp"

#include "cell.hpp"
#include "objects/drawable.hpp"
#include "event.hpp"
#include "font.hpp"
#include "scenes/introscene.hpp"
#include "scenes/gameoverscene.hpp"
#include "scenes/playscene.hpp"
#include "objects/sprite.hpp"
#include "objects/text.hpp"
#include "texture.hpp"
#include "time.hpp"
#include "window.hpp"

class Game
{
public:
	bool init();
	void run();
	void stop();
	
private:
	unsigned int lastTime {0};
	Time time;
	Window window;
	
	Font rubikOne;
	
	void update(unsigned int deltaTime);
	
	std::unique_ptr<IntroScene> createIntroScene();
	std::unique_ptr<PlayScene> createPlayScene();
	std::unique_ptr<GameOverScene> createGameoverScene();
	
	
public:
	Game();
	virtual ~Game();

};

