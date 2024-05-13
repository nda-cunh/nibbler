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

// runGameLoop(...)
void	main_plugin_loop(int width, int height) {
	std::unique_ptr<Plugin> plugin;
	Game		game(width, height);
	Event		event = DOWN;
	LIBS		lib = SFML;
	const auto	lib_names = std::map<LIBS, std::string>({
			{SFML, "./libsfml.so"},
			{SFML_BIS, "./libsfml_bis.so"}
	});
	Direction	direction = Down;
	Timer		timer;

	plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);

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
				if (lib == SFML_BIS)
					break;
				lib = SFML_BIS;
				plugin.reset();
				plugin = std::make_unique<Plugin>(lib_names.at(lib), width, height);
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






