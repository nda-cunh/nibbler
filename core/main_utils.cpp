#include "./main_utils.h"
#include "Timer.hpp"
#include <memory>

// File: game_loop.cpp

// updateAndDisplayGameState(...)
static void display(const Game &game, Plugin &plugin, Direction &dir) {
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

enum Lib_magik {
	LIB_1,
	LIB_2,
	LIB_3
};


// runGameLoop(...)
void	main_plugin_loop(int width, int height) {
	std::unique_ptr<Plugin> plugin;
	Game		game(width, height);
	Event		event = DOWN;
	Direction	direction = Down;
	Timer		timer;

	Lib_magik lib;
	lib = LIB_1;
	plugin = std::make_unique<Plugin>("./libsfml.so", width, height);

	while (event != CLOSE) {
		/* Event Handling */
		event = plugin->poll_event();
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
				continue;
			case ENTER:
				if (!game.over())
					break;
				game = Game(width, height);
				event = DOWN;
				direction = Down;
				break;
			case F1:
				if (lib == LIB_1)
					break;
				lib = LIB_1;
				plugin.reset();
				plugin = std::make_unique<Plugin>("./libsfml.so", width, height);
				break;
			case F2:
				if (lib == LIB_2)
					break;
				lib = LIB_2;
				plugin.reset();
				plugin = std::make_unique<Plugin>("./libsfml_bis.so", width, height);
				break;
			default:
				break;
		}

		/* Move Snakes */
		if (!game.over() && timer.elapsed() > 0.1) {
			game.moveSnake(direction);
			timer.reset();
		}

		display(game, *plugin, direction);	
	}
}






