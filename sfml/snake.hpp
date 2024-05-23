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
		inline void draw_body(sf::RenderTexture& window, const std::deque<Position> &positions);
	 private:
		sf::RenderTexture texture_head;
		sf::Texture texture_snake;
		sf::Sprite tounge;
		sf::Sprite eyes_left;
		sf::Sprite eyes_right;
		sf::Sprite mouth;
		Sprite		s_eyes_left;
		Sprite		s_eyes_right;
		Sprite		s_tongue;
		Sprite		s_mouth;
};

#endif
