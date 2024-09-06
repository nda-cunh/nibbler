#ifndef MENU_HPP
#define MENU_HPP

# include <vector>
# include <map>
# include "Button.hpp"
# include "Timer.hpp"
# include "../include/IPlugin.hpp"

class GameOver {
	const int	TILE_SIZE;
	Timer		_last_click;
	int			_speed;
	Vector2		_size;
	Button		_button_restart;
	Button		_button_quit;

	/* ---- Init Activities ---- */
	void	init_game_over(int width, int height);

	public:
		/* ---- Constructors & Coplien ---- */
		GameOver();
		GameOver(const GameOver &);
		GameOver(int width, int height, int tile_size);
		~GameOver();

		GameOver	&operator=(const GameOver &);

		void	setSpeed( int );
		Event	checkCollision(Activity act, float x, float y);
		void	checkHover(Activity act, float x, float y);
		void	draw() const;
};

#endif
