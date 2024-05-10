#ifndef _BACKGROUND_HPP
#define _BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/IPlugin.hpp"
#include "config.h"
#include <memory>

class Background : public sf::Sprite
{
	 public:
		void init(sf::Vector2u size);
		void draw_self(sf::RenderWindow &window);
	 private:
		std::shared_ptr<sf::RenderTexture> texture;
};

#endif
