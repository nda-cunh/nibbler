#ifndef MENU_HPP
#define MENU_HPP
 
# include "../include/IPlugin.hpp"
# include <vector>
# include <map>
# include "Button.hpp"
# include "Timer.hpp"

class Menu {
	std::map<Activity, std::vector<Button>> _buttons;
	Timer			_last_click;

	/* ---- Init Activities ---- */
	void	init_game_over(int width, int height);
	void	init_menu(int width, int height);

	public:
		/* ---- Constructors & Coplien ---- */
		Menu();
		Menu(const Menu &);
		Menu(int width, int height);
		~Menu();

		Menu	&operator=(const Menu &);

		Event		checkCollision(Activity act, float x, float y);
		void		draw(const Activity &act, sf::RenderTarget &win);
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

#endif
