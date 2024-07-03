#ifndef _GAMEOVER_HPP_
#define _GAMEOVER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.hpp"
#include "config.h"

class GameOver : public sf::Sprite
{
	private:
		std::unique_ptr<sf::RenderTexture>	surface;
		std::unique_ptr<sf::Texture> 		texture_gameover;
		std::unique_ptr<sf::Texture> 		texture_gameover_2p;

		// Texts
		sf::Font	_font;
		sf::Text	_text_score[2];
		sf::Text	_text_best[2];

		sf::Sprite	sprite_gameover[2];
		bool		_is_multiplayer;
		// Buttons
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
		void setBestScore(const int n, int idx);
		void setScore(const int n, int idx);
		void setGameMode(bool is_multiplayer);

		/* ---- Draw update ---- */
		void update();
};

#endif
