#include "./main_utils.h"
#include "Timer.hpp"

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

// runGameLoop(...)
void	main_plugin_loop(int width, int height) {
	Plugin		plugin("libsfml.so", width, height);
	Game		game(width, height);
	Event		event = DOWN;
	Direction	direction = Down;
	Timer		timer;

	while (event != CLOSE) {

		/* Event Handling */
		event = plugin.poll_event();
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
			default:
				break;
		}

		/* Move Snakes */
		if (!game.over() && timer.elapsed() > 0.1) {
			game.moveSnake(direction);
			timer.reset();
		}

		display(game, plugin, direction);	
	}
}

