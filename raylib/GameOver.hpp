#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

# include <vector>
# include <map>
# include "Button.hpp"
# include "Timer.hpp"
# include "../include/IPlugin.hpp"

class GameOver {
	const int		_TILE_SIZE;
	int				_WIDTH;
	int				_HEIGHT;
	Timer			_last_click;

	// Button			_game_over;
	Button			_try_again;
	Button			_menu;

	void	init_buttons();
	public:
		/* ---- Constructors & Coplien ---- */
		GameOver();
		GameOver(const GameOver &);
		GameOver(int width, int height, int tile_size);
		~GameOver();

		GameOver	&operator=(const GameOver &);

		Event	checkCollision(Activity act, float x, float y, bool click = true);
		void	checkHover(Activity act, float x, float y);
		void	draw(const Activity &act);
};

#endif
