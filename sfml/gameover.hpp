#ifndef _GAMEOVER_HPP_
#define _GAMEOVER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

class GameOver : public sf::Sprite
{
	 public:
		GameOver();
		void update();
		void update_score_max(const int n);
		void update_score(const int n);
	 private:
		sf::Font font;
		sf::Text t_score;
		sf::Text t_score_max;
		sf::Sprite sprite_gameover;
		std::unique_ptr<sf::Texture> texture_gameover;
		std::unique_ptr<sf::RenderTexture> surface;
};

#endif
