#ifndef _APPLE_HPP_
#define _APPLE_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/IPlugin.hpp"


class Apple : sf::Sprite{
	std::shared_ptr<sf::Texture> _texture;
	bool	_is_up;
	int		_tileX;
	int		_tileY;

	public:
		/* ---- Constructors & Coplien ---- */
		Apple ();
		Apple (const Apple &);
		~Apple();

		Apple	&operator=(const Apple &);

		/* ---- Public methods ---- */
		void update_food(sf::RenderTexture &window, Position &position);
};

#endif
