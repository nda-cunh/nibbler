#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include <SFML/Graphics.hpp>
#include "../include/IPlugin.hpp"
#include "config.h"

class Snake
{
	 public:
		Snake();
		void draw_snake(sf::RenderWindow &window, const std::deque<Position> &snake, Direction direction);
	protected:
		inline void draw_segment(sf::RenderWindow& window, const Position begin, const Position end, double size, sf::Color color);
	 private:
		sf::Texture texture_snake;
		sf::Sprite tounge;
		sf::Sprite eyes;
};

#endif
