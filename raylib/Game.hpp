#ifndef GAME_HPP
#define GAME_HPP

#include "utils.hpp"
#include "Snake.hpp"

class Game {
	private:
		RenderTexture2D			_background;
		Position				_size;
		std::deque<Position>	_food;
		Snake					_snake;
		int						_score;
		bool					_is_over;
		int						_best_score;


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
		void addFood(Position pos);
		void resetFood();
		void setScore(int score);
		void setIsOver(bool is_over);
		void setBestScore(int score);

		/* ---- Draw Methods ---- */
		void draw();
};
#endif
