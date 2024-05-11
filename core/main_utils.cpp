#include "./main_utils.h"
#include "Timer.hpp"

static void display(const Game &game, Plugin &plugin, Direction &dir) {
	plugin.clear();
	plugin.draw_snake(game.getSnakePositions(), dir);

	for (auto pos : game.getFoodPositions())
		plugin.draw_food(pos);

	plugin.draw_score(game.getScore());
	if (game.over())
		plugin.draw_gameover();
	plugin.display();
}

void	main_plugin_loop(int width, int height) {
	Plugin		plugin("lib_nibbler_sfml.so", width, height);
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

