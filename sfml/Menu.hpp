#ifndef MENU_HPP
#define MENU_HPP
 
# include "../include/IPlugin.hpp"
# include <vector>
# include <map>
# include "Button.hpp"
# include "Timer.hpp"
# include "config.h"

class Menu {
	std::unique_ptr<sf::Font>	_font;
	int			_speed;
	Timer		_last_click;
	Button		_button_1p;
	// Button		_button_2p;
	Button		_speed_down;
	Button		_speed_up;
	Position	_size;

	/* ---- Init Activities ---- */
	void	init_menu(int width, int height);

	public:
		/* ---- Constructors & Coplien ---- */
		Menu();
		Menu(const Menu &);
		Menu(int width, int height);
		~Menu();

		Menu	&operator=(const Menu &);

		/* ---- Accessors ---- */
		void		setSpeed(int speed);

		/* ---- Public methods ---- */
		Event	collides(int x, int y);
		void	draw(sf::RenderTarget &win);
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
