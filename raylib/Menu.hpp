#ifndef MENU_HPP
#define MENU_HPP

# include <vector>
# include <map>
# include "Button.hpp"
# include "Timer.hpp"
# include "GameOver.hpp"
# include "../include/IPlugin.hpp"

class Menu {
	const int		_TILE_SIZE;
	int				_WIDTH;
	int				_HEIGHT;
	Timer			_last_click;
	int				_speed;

	Button			_play_1p;
	Button			_play_2p;
	Button			_speed_up;
	Button			_speed_down;

	/* ---- Init Activities ---- */
	void	init_buttons();

	public:
		/* ---- Constructors & Coplien ---- */
		Menu();
		Menu(const Menu &);
		Menu(int width, int height, int tile_size);
		~Menu();

		Menu	&operator=(const Menu &);

		void	setSpeed( int );
		Event	checkCollision(Activity act, float x, float y, bool click = true);
		void	checkHover(Activity act, float x, float y);
		void	draw(const Activity &act);
};

#endif
