#ifndef MENU_HPP
#define MENU_HPP

# include <vector>
# include <map>
# include "Button.hpp"
# include "Timer.hpp"

class Menu {
	private:
		std::map<Activity, std::vector<Button>> _buttons;
		Activity		_current_activity;
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
		void	draw(const Activity &act);
};

#endif
