#ifndef GAME_HPP
#define GAME_HPP

#include "utils.hpp"
#include "Snake.hpp"

class Game {
	private:
		RenderTexture2D	_background;
		Position		_size;
		Position		_food;
		Snake			_snake;
		bool			_on_menu;
		int				_score;
		int				_best_score;


		/* ---- Private Draw Methods ---- */
		void	init_background();
		void	draw_background();
		void	draw_score();
		void	draw_food();
		void	draw_best_score();

	public:
		/* ---- Constructors ---- */
		Game();
		Game(int w, int h);
		~Game();

		/* ---- Accessors ---- */
		void setSnake(const std::deque<Position> &snake);
		void setFood(Position pos);
		void setScore(int score);
		void setBestScore(int score);
		void setOnMenu(bool b);
		bool getOnMenu() const;

		/* ---- Draw Methods ---- */
		void draw();
};
#endif
