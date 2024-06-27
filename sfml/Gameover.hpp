#ifndef _GAMEOVER_HPP_
#define _GAMEOVER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.hpp"
#include "config.h"

class GameOver : public sf::Sprite
{
	std::unique_ptr<sf::RenderTexture>	surface;
	std::unique_ptr<sf::Texture> 		texture_gameover;
	sf::Sprite	sprite_gameover;
	sf::Text	_text_score;
	sf::Text	_text_best;
	sf::Font	_font;

	Button		_button_menu;
	Button		_button_retry;

	public:
		/* ---- Constructors & Coplien ---- */
		GameOver();
		GameOver( const GameOver & );
		~GameOver();

		GameOver &operator=(const GameOver &);

		/* ---- Mouse event ---- */
		Event collides(int x, int y);

		/* ---- Accessors ---- */
		void setPosition(const float x, const float y);
		void setBestScore(const int n);
		void setScore(const int n);

		/* ---- Draw update ---- */
		void update();
};

#endif
