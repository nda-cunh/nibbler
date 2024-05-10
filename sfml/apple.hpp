#ifndef _APPLE_HPP_
#define _APPLE_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "animation.hpp"
#include "../include/IPlugin.hpp"


class Apple : sf::Sprite{
	public:
		Apple ();

		void init(int x, int y);

		void draw_food(sf::RenderTexture &window, Position &position);

	private:
		bool is_up;
		int tileX;
		int tileY;
		std::shared_ptr<sf::Texture> texture;
		Animation Aapple;
};

#endif
