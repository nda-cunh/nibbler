#ifndef _MENU_HPP_
#define _MENU_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

class Menu : public sf::RectangleShape
{
	 public:
		Menu();
		void create (int width, int height);
		void draw_self (sf::RenderWindow &surface);
		void draw_score (int n);
	 private:
		std::shared_ptr<sf::Font> font;
		std::shared_ptr<sf::Texture> texture;
		sf::Sprite food;
		sf::Text text;
		sf::Sprite best_score;
		
};

#endif
