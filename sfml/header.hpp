#ifndef _HEADER_HPP_
#define _HEADER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

class Header : public sf::RectangleShape
{
	 public:
		Header();
		void create (int width, int height);
		void draw_self (sf::RenderWindow &surface);
		void update_score (int n);
		void update_best_score (int n);
	 private:
		std::shared_ptr<sf::Font>		font;
		std::shared_ptr<sf::Texture>	texture;
		sf::Sprite	food;
		sf::Text	text_score;
		sf::Text	text_best;
		sf::Sprite	best_score;
		
};

#endif
