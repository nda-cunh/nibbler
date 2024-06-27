#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include <SFML/Graphics.hpp>
#include "../include/IPlugin.hpp"
#include "Animation.hpp"
#include "config.h"

class Snake
{
	sf::RenderTexture	texture_head;
	sf::Texture 		texture_snake;
	Animation				s_eyes_left;
	Animation				s_eyes_right;
	Animation				s_tongue;
	Animation				s_mouth;

	/* ---- Private Methods ---- */
	inline void draw_head(sf::RenderTexture& window, const std::deque<Position> &snake);
	inline void draw_body(sf::RenderTexture& window, const std::deque<Position> &positions);

	public:
		/* ---- Constructors & Coplien ---- */
		Snake();
		Snake(const Snake &);
		~Snake();

		Snake	&operator=(const Snake &);

		/* ---- Public Methods ---- */
		void update_snake(sf::RenderTexture &window, const std::deque<Position> &snake);
};

#endif
