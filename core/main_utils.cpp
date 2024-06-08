#include "./main_utils.h"
#include "Timer.hpp"
#include <memory>
#include <deque>
#include <stack>
#include <thread>

// File: game_loop.cpp

// updateAndDisplayGameState(...)
static void display(const Game &game, Plugin &plugin, const Direction &dir) {
	plugin.clear();
	plugin.update_snake(game.getSnakePositions(), dir);

	for (auto pos : game.getFoodPositions())
		plugin.update_food(pos);

	plugin.update_score(game.getScore());
	plugin.update_bestscore(game.getBestScore());
	if (game.over())
		plugin.update_gameover();
	plugin.display();
}

// runGameLoop(...)
void	main_plugin_loop(int width, int height) {
	std::unique_ptr<Plugin> plugin;
	Game		game(width, height);
	Event		event = DOWN;
	LIBS		lib = SFML;
	const auto	lib_names = std::map<LIBS, std::string>({
			{SFML, "./libsfml.so"},
			{SFML_BIS, "./libsfml_bis.so"},
			{SDL, "./libsdl.so"},
			{RAYLIB, "./libraylib.so"}
			});
	Direction	direction = Down;
	Timer		timer;
	

	const int FPS = 120;
	const int frameDelay = 1000 / FPS;

	std::chrono::time_point<std::chrono::high_resolution_clock> frameStart;
	int frameTime;

	plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);

	while (event != CLOSE) {
		/* Event Handling */
		frameStart = std::chrono::high_resolution_clock::now();

		// Event last = event;
		event = plugin->poll_event();
		// if (last == event)
			// break;
		// printf("%d\n", event);
		// if (event == NONE)
			// break;
		switch (event) {
			case RIGHT:
				direction = Right;
				break;
			case LEFT:
				direction = Left;
				break;
			case UP:
				direction = Up;
				break;
			case DOWN:
				direction = Down;
				break;
			case CLOSE:
				return;
			case ENTER:
				if (!game.over())
					break;
				game = game.newGame();
				event = DOWN;
				direction = Down;
				break;
			case F1:
				if (lib == SFML)
					break;
				lib = SFML;
				plugin.reset();
				plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
				break;
			case F2:
				if (lib == RAYLIB)
					break;
				lib = RAYLIB;
				plugin.reset();
				plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
				break;
			case F3:
				if (lib == SDL)
					break;
				lib = SDL;
				plugin.reset();
				plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
				break;
			default:
				break;
		}

		/* Move Snakes */
		if (timer.elapsed() > 0.08) {
			if (!game.over())
				game.moveSnake(direction);
			timer.reset();
		}
		frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - frameStart).count();
		if (frameDelay > frameTime) {
			std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay - frameTime));

		}
		display(game, *plugin, game.getSnakeDirection());	

	}
}
