#ifndef GAME_HPP
#define GAME_HPP

#include "Snake.hpp"

class Game {
	int				TILE_SIZE;
	Vector2			_size;
	std::deque<Position>	_food;
	Snake					_snake;
	int						_score;
	int						_best_score;
	bool					_is_over;


	/* ---- Private Draw Methods ---- */
	void	draw_background();
	void	draw_score();
	void	draw_food();
	void	draw_best_score();

	public:
		/* ---- Constructors & Coplien ---- */
		Game();
		Game(const Game &);
		Game(int w, int h, int tile_size);
		~Game();

		Game	&operator=(const Game &);

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
