#include "game.hpp"

int main()
{
	Game game;
	if (!game.init())
		return 0;
	game.run();
	return 0;
}
