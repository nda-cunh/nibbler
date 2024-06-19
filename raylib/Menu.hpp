#ifndef MENU_HPP
#define MENU_HPP

# include <vector>
# include <map>
# include "Button.hpp"
# include "Timer.hpp"
# include "../include/IPlugin.hpp"

class Menu {
	const int		TILE_SIZE;
	std::map<Activity, std::vector<Button>> _buttons;
	Timer			_last_click;
	int				_speed;

	/* ---- Init Activities ---- */
	void	init_game_over(int width, int height);
	void	init_menu(int width, int height);

	public:
		/* ---- Constructors & Coplien ---- */
		Menu();
		Menu(const Menu &);
		Menu(int width, int height, int tile_size);
		~Menu();

		Menu	&operator=(const Menu &);

		void	setSpeed( int );
		Event	checkCollision(Activity act, float x, float y);
		void	checkHover(Activity act, float x, float y);
		void	draw(const Activity &act);
};

#endif
