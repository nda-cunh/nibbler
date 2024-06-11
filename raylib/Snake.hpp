#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <deque>
#include "utils.hpp"
#include "../include/IPlugin.hpp"

class Snake {
	int							TILE_SIZE;
	const std::deque<Position>	*_positions;

	public:
		/* ---- Constructors & Coplien ---- */
		Snake();
		Snake(const Snake &);
		Snake(std::deque<Position> *snake, int tile_size);
		~Snake();

		Snake	&operator=(const Snake &);

		void update(const std::deque<Position> *snake);
		void draw();
};

#endif
