#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <deque>
#include "utils.hpp"
#include "../include/IPlugin.hpp"

class Snake {
	const std::deque<Position>	*_positions;

	public:
		/* ---- Constructors & Coplien ---- */
		Snake();
		Snake(const Snake &);
		explicit Snake(std::deque<Position> *snake);
		~Snake();

		Snake	&operator=(const Snake &);

		void update(const std::deque<Position> *snake);
		Position	draw() const;
};

#endif
