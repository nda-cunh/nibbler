#ifndef _GAMEOVER_HPP_
#define _GAMEOVER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

class GameOver : public sf::Sprite
{
	std::unique_ptr<sf::RenderTexture>	surface;
	std::unique_ptr<sf::Texture> 		texture_gameover;
	sf::Sprite	sprite_gameover;
	sf::Text	_text_score;
	sf::Text	_text_best;
	sf::Font	_font;

	public:
		/* ---- Constructors & Coplien ---- */
		GameOver();
		GameOver( const GameOver & );
		~GameOver();

		GameOver &operator=(const GameOver &);

		/* ---- Accessors ---- */
		void setBestScore(const int n);
		void setScore(const int n);

		/* ---- Draw update ---- */
		void update();
};

#endif
