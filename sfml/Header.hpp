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

	bool		_is_multiplayer;
	sf::Text	_text_score[2];
	sf::Text	_text_best[2];
	sf::Sprite	_icon_score[2];
	sf::Sprite	_icon_best[2];
	sf::Sprite	_icon_snake[2];

	public:
		/* ---- Constructors & Coplien ---- */
		Header();
		Header( const Header & );
		~Header();

		Header	&operator=( const Header & );

		/* ---- Init ---- */
		void create (int width, int height);

		/* ---- Accessors ---- */
		void setScore		(int n, int idx);
		void setBestScore	(int n, int idx);
		void setGameMode	(bool is_multiplayer);

		/* ---- Draw method ---- */
		void draw_self (sf::RenderWindow &surface);
};

#endif
