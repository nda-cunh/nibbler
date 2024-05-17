#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include <SFML/Graphics.hpp>
#include "../include/IPlugin.hpp"
#include "Sprite.hpp"
#include "config.h"

class Snake
{
	 public:
		Snake();
		void update_snake(sf::RenderTexture &window, const std::deque<Position> &snake, Direction direction);
	protected:
		inline void draw_segment(sf::RenderTexture& window, const Position begin, const Position end, double size, sf::Color color);
		inline void draw_head(sf::RenderTexture& window, const Position &pos, Direction dir);
	 private:
		sf::Texture texture_snake;
		sf::Sprite tounge;
		sf::Sprite eyes;
		Sprite		s_eyes;
		Sprite		s_tongue;
};

#endif
