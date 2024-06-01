#ifndef GAME_HPP
#define GAME_HPP

#include "utils.hpp"
#include "Snake.hpp"

class Game {
	private:
		Position		_size;
		Position		_food;
		Snake			_snake;
		bool			_on_menu;
		int				_score;
		int				_best_score;


		void	draw_background();
		void	draw_score();
		void	draw_food();
		void	draw_best_score();

	public:
		Game();
		Game(int w, int h);
		~Game();

		void setSnake(const std::deque<Position> &snake);
		void setFood(Position pos);
		void setScore(int score);
		void setBestScore(int score);
		void setOnMenu(bool b);
		bool getOnMenu() const;
		void draw();
};
#endif
