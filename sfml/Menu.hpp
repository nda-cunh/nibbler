#ifndef MENU_HPP
#define MENU_HPP

# include <vector>
# include <map>
# include "Button.hpp"
# include "Timer.hpp"

class Menu {
	private:
		std::map<Activity, std::vector<Button>> _buttons;
		Timer			_last_click;
	
		void	init_game_over(int width, int height);
		void	init_menu(int width, int height);
	public:
		Menu();
		Menu(int width, int height);
		~Menu();
		Menu(const Menu &);

		Menu	&operator=(const Menu &);
		Activity	checkCollision(Activity act, float x, float y);
		void	draw(const Activity &act, sf::RenderTarget &win);
};

inline std::ostream& operator << (std::ostream& os, sf::Rect<float> rect)
{
	os << "[x: "<< rect.getPosition().x;
	os << ", y: "<< rect.getPosition().y;
	os << ", w: "<< rect.getSize().x;
	os << ", h: "<< rect.getSize().y;
	os << "]";
	return os;
}

#endifPressed
