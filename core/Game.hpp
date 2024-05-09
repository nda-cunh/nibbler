#ifndef GAME_HPP
#define GAME_HPP

#include "../include/utils.hpp"
#include "Snake.hpp"
#include <algorithm>
#include <vector>
#include <random>

class Game {
	public:
		int		_score;
		bool	_is_over;

		Game(const int width, const int height): _snake(Snake(width, height)) {
			_size = {width, height};
			_is_over = false;
			_score = 0;
			_foods = std::vector<Position>();
			generateFood();
		}
		~Game() {
		}

		std::deque<Position> getSnakePositions( void ) { return _snake.getPositions(); }

		Position &getFoodPositions( void ) { return _foods[0]; }

		void moveSnake(const Direction &dir) {
			const Position new_head_pos = _snake.move(dir);
			const auto		snake_pos = _snake.getPositions();
			const auto		food_it = std::find(_foods.begin(), _foods.end(), new_head_pos);

			if (new_head_pos.x >= _size.x || new_head_pos.x < 0)
				_is_over = true;
			else if (new_head_pos.y >= _size.y || new_head_pos.y < 0)
				_is_over = true;
			else if (std::count(snake_pos.begin(), snake_pos.end(), new_head_pos) > 1)
				_is_over = true;

			if (food_it == _foods.end())
				_snake.loseTail();
			else {
				_score++;
				_foods.erase(food_it);
				generateFood();
			}
		}
	private:
		Position				_size;
		std::vector<Position>	_foods;
		Snake					_snake;

		void	generateFood() {
			const auto 		snake_pos = getSnakePositions();
			int rand_x = std::rand() % _size.x;
			int rand_y = std::rand() % _size.y;
			Position	rand_pos = {rand_x, rand_y};

			while (true) {
				rand_pos = {std::rand() % _size.x, std::rand() % _size.y};
				if (std::find(snake_pos.begin(), snake_pos.end(), rand_pos) != snake_pos.end())
					continue ;
				else if (std::find(_foods.begin(), _foods.end(), rand_pos) != _foods.end())
					continue ;
				else
					break;
			}
			_foods.push_back(rand_pos);
		}
};
#endif
