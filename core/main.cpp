#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include "Plugin.hpp"
#include "Game.hpp"
#include "../include/utils.hpp"

#define WIDTH 20
#define HEIGHT 20

void	init_new_game(Direction &direction, Game &game, Event &event) {
	direction = Down;
	game = Game(WIDTH, HEIGHT);
	event = DOWN;
}

// TODO handle params and arg error
int	main(  void )
{
	Plugin		plugin("lib_nibbler_sfml.so", WIDTH, HEIGHT);
	clock_t		tick = clock();
	Direction	direction;
	Event		event;
	Game		game(WIDTH, HEIGHT);

	init_new_game(direction, game, event);
	while (true) {

		/* Event Part */
		auto event = plugin.poll_event();
		if (event == RIGHT)
			direction = Right;
		else if (event == LEFT)
			direction = Left;
		else if (event == UP)
			direction = Up;
		else if (event == DOWN)
			direction = Down;
		else if (event == ENTER) {
			init_new_game(direction, game, event);
			continue;
		} else if (event == CLOSE)
			break;
		// std::cout << event << std::endl;

		if (tick + 100000 < clock() && !game._is_over) {
			game.moveSnake(direction);
			tick = clock();
		}
		plugin.draw_snake(game.getSnakePositions());
		plugin.draw_food(game.getFoodPositions());

		if (game._is_over) {
			plugin.draw_gameover();
		}
		plugin.iteration();
	}
	

	return (0);
}
