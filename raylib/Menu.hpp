#ifndef MENU_HPP
#define MENU_HPP

# include <vector>
# include <map>
# include "Button.hpp"
# include "Timer.hpp"

class Menu {
	const int		TILE_SIZE;
	std::map<Activity, std::vector<Button>> _buttons;
	Activity		_current_activity;
	Timer			_last_click;

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

		Activity	checkCollision(Activity act, float x, float y);
		void		draw(const Activity &act);
};

#endif
