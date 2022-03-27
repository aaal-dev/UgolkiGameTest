#include "game.hpp"

Game::Game(){}

Game::~Game(){}

bool Game::init() {
	time.init();
	window.create("DominiGameTest", 800, 600); 
	if (!window.isOpen()) return false;
	
	rubikOne.create("font/RubikOne.ttf");
	
	window.addScene(std::move(createIntroScene()));
	window.addScene(std::move(createPlayScene()));
	window.addScene(std::move(createGameoverScene()));
	window.changeSceneTo("intro");
	return true;
}

void Game::run() {
	while (window.isOpen()) {
		window.pollEvents();
		update(time.getDeltaTime());
		window.draw();
	}
}

void Game::stop() {
	
}

void Game::update(unsigned int deltaTime) {
	window.update(deltaTime);
}

std::unique_ptr<IntroScene> Game::createIntroScene() {
	auto intro = std::make_unique<IntroScene>();
	intro->name = "intro";
	// Создаю фиксированные объекты в стартовой сцене
	{
		// Задний фон
		auto texture = std::make_unique<Texture>();
		texture->create("img/intro/bg.png");
		auto sprite = std::make_unique<Sprite>(0);
		sprite->create(texture.get(), 400, 300);
		intro->addFixed(std::move(sprite), std::move(texture));
		
		// Текстовая надпись
		auto text = std::make_unique<Text>();
		text->setFont(&rubikOne);
		text->create(L"Выбери свой путь", 400, 160);
		text->setSize(48);
		text->setColor(sf::Color::Black);
		intro->addFixed(std::move(text));
	}
	
	// Создаю динамические объекты в стартовой сцене
	{
		{
			// Создаю текстуру вида игрока №1  
			auto texture = std::make_unique<Texture>();
			texture->create("img/intro/star.png");
			
			// Создаю спрайт вида игрока №1
			auto player1 = std::make_unique<Sprite>(1);
			player1->name = "Player1";
			player1->create(texture.get(), 280, 400);
			
			// Добавляю спрайт в список динамических объектов сцены
			intro->addDynamic(std::move(player1), std::move(texture));
		}
		{
			// Создаю текстуру вида игрока №2
			auto texture = std::make_unique<Texture>();
			texture->create("img/intro/star2.png");
			
			// Создаю спрайт вида игрока №2
			auto player2 = std::make_unique<Sprite>(2);
			player2->name = "Player2";
			player2->create(texture.get(), 520, 400);
			
			// Добавляю спрайт в список динамических объектов сцены
			intro->addDynamic(std::move(player2), std::move(texture));
		}
	}
	return intro;
}

std::unique_ptr<PlayScene> Game::createPlayScene() {
	auto game = std::make_unique<PlayScene>();
	game->name = "game";
	// Создаю фиксированные объекты в игровой сцене
	{
		// Задний фон
		auto texture = std::make_unique<Texture>();
		texture->create("img/game/bg.png");
		auto sprite = std::make_unique<Sprite>(0);
		sprite->create(texture.get(), 400, 300);
		game->addFixed(std::move(sprite), std::move(texture));
	}
	
	// Создаю динамические объекты в игровой сцене
	{
		
		// Создаю ячейки для динамических объектов в сцене
		for (unsigned int i = 0; i < 8; ++i) {
			for (unsigned int j = 0; j < 8; ++j) {
				auto cell = std::make_unique<Cell>();
				cell->setSize(60, 60);
				cell->setPosition(176 + j * 64, 76 + i * 64);
				cell->index = j + 8 * i;
				cell->row = i;
				cell->column = j;
				game->addCell(std::move(cell));
			}
		}
		{
			// Создаю текстуру вида игрока №1 
			auto texture = std::make_unique<Texture>();
			texture->create("img/game/star.png");

			// Создаю спрайты вида игрока №1 и расстовляю их по ячейкам
			for (unsigned int i = 0; i < 3; ++i) {
				for (unsigned int j = 0; j < 3; ++j) {
					unsigned int index = j + 8 * i;
					auto cell = game->cells[index].get();
					
					auto player1 = std::make_unique<Sprite>(1);
					player1->name = "Player1";
					player1->create(texture.get(), cell->posX, cell->posY);
					
					// Добавляю спрайт в ячейку
					cell->add(player1.get());
					
					// Добавляю спрайт в список динамических объектов сцены
					game->addDynamic(std::move(player1));
				}
			}
			
			// Добаляю текстуру в сцену
			game->addTexture(std::move(texture));
		}
		{
			// Создаю текстуру вида игрока №2
			auto texture = std::make_unique<Texture>();
			texture->create("img/game/star2.png");
			
			// Создаю спрайты вида игрока №2 и расстовляю их по ячейкам
			for (unsigned int i = 5; i < 8; ++i) {
				for (unsigned int j = 5; j < 8; ++j) {
					unsigned int index = j + 8 * i;
					auto cell = game->cells[index].get();
					
					auto player2 = std::make_unique<Sprite>(2);
					player2->name = "Player2";
					player2->create(texture.get(), cell->posX, cell->posY);
					
					// Добавляю спрайт в ячейку
					cell->add(player2.get());
					
					// Добавляю спрайт в список динамических объектов сцены
					game->addDynamic(std::move(player2));
				}
			}
			
			// Добаляю текстуру в сцену
			game->addTexture(std::move(texture));
		}
	}
	return game;
}

std::unique_ptr<GameOverScene> Game::createGameoverScene() {
	auto gameover = std::make_unique<GameOverScene>();
	gameover->name = "gameover";
	// Создаю фиксированные объекты в стартовой сцене
	{
		// Задний фон
		auto texture = std::make_unique<Texture>();
		texture->create("img/intro/bg.png");
		auto sprite = std::make_unique<Sprite>(0);
		sprite->create(texture.get(), 400, 300);
		gameover->addFixed(std::move(sprite), std::move(texture));
		
		// Текстовая надпись
		auto text = std::make_unique<Text>();
		text->setFont(&rubikOne);
		text->create(L"Победил!", 400, 160);
		text->setSize(48);
		text->setColor(sf::Color::Black);
		gameover->addFixed(std::move(text));
	}
	
	// Создаю динамические объекты в стартовой сцене
	{
		{
			// Создаю текстуру вида игрока №1  
			auto texture = std::make_unique<Texture>();
			texture->create("img/intro/star.png");
			
			// Создаю спрайт вида игрока №1
			auto player1 = std::make_unique<Sprite>(1);
			player1->name = "Player1";
			player1->create(texture.get(), 400, 400);
			
			// Добавляю спрайт в список динамических объектов сцены
			gameover->addDynamic(std::move(player1), std::move(texture));
		}
		{
			// Создаю текстуру вида игрока №2
			auto texture = std::make_unique<Texture>();
			texture->create("img/intro/star2.png");
			
			// Создаю спрайт вида игрока №2
			auto player2 = std::make_unique<Sprite>(2);
			player2->name = "Player2";
			player2->create(texture.get(), 400, 400);
			
			// Добавляю спрайт в список динамических объектов сцены
			gameover->addDynamic(std::move(player2), std::move(texture));
		}
	}
	return gameover;
}