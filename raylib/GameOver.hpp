#ifndef MENU_HPP
#define MENU_HPP

# include "Button.hpp"
# include "../include/IPlugin.hpp"

class GameOver {
	Vector2		_size;
	Button		_button_restart;
	Button		_button_quit;

	/* ---- Init Activities ---- */
	void	init_buttons(int width, int height);

	public:
		/* ---- Constructors & Coplien ---- */
		GameOver();
		GameOver(const GameOver &);
		GameOver(int width, int height);
		~GameOver();

		GameOver	&operator=(const GameOver &);

		/* ---- Methods ---- */
		Event	checkCollision(float x, float y);
		void	checkHover(float x, float y);
		void	draw() const;
};

#endif
