#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <deque>
#include "../include/IPlugin.hpp"

class Snake {
	const std::deque<Position>	*_positions;

	public:
		/* ---- Constructors ---- */
		Snake();
		Snake(std::deque<Position> *snake);
		~Snake();

		void update(const std::deque<Position> *snake);
		void draw();
};

#endif
