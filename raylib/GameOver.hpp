#ifndef MENU_HPP
#define MENU_HPP

# include "Button.hpp"
# include "../include/IPlugin.hpp"

class GameOver {
	const int	TILE_SIZE;
	Vector2		_size;
	Button		_button_restart;
	Button		_button_quit;

	/* ---- Init Activities ---- */
	void	init_buttons(int width, int height);

	public:
		/* ---- Constructors & Coplien ---- */
		GameOver();
		GameOver(const GameOver &);
		GameOver(int width, int height, int tile_size);
		~GameOver();

		GameOver	&operator=(const GameOver &);

		/* ---- Methods ---- */
		Event	checkCollision(Activity act, float x, float y);
		void	checkHover(Activity act, float x, float y);
		void	draw() const;
};

#endif
