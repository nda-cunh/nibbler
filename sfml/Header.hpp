#ifndef _HEADER_HPP_
#define _HEADER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include "config.h"

class Header : public sf::RectangleShape
{
	std::shared_ptr<sf::Font>		_font;
	std::shared_ptr<sf::Texture>	_texture;
	std::shared_ptr<sf::Texture>	_texture_snakes;

	sf::Text	_text_score;
	sf::Sprite	_icon_score;
	sf::Sprite	_icon_snake;
	sf::Text	_text_best;
	sf::Sprite	_icon_best;

	public:
		/* ---- Constructors & Coplien ---- */
		Header();
		Header( const Header & );
		~Header();

		Header	&operator=( const Header & );

		/* ---- Init ---- */
		void create (int width, int height);

		/* ---- Accessors ---- */
		void setScore		(int n);
		void setBestScore	(int n);

		/* ---- Draw method ---- */
		void draw_self (sf::RenderWindow &surface);
};

#endif
