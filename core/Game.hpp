#ifndef GAME_HPP
#define GAME_HPP

#include "../include/utils.hpp"
#include "Snake.hpp"
#include <algorithm>
#include <vector>
#include <random>

class Game {
	public:
		Game() {}

		Game(const int width, const int height){
			_snake.create(width, height);
			_size = {width, height};
			_is_over = false;
			_score = 0;
			_foods = std::vector<Position>();
			generateFood();
		}
		~Game() {
		}

		bool	over() const { return _is_over; }
		int		getScore() const { return _score; }
		const std::deque<Position> &getSnakePositions( void ) const { return _snake.getPositions(); }

		const std::vector<Position> &getFoodPositions( void ) const { return _foods; }

		void moveSnake(const Direction &dir) {
			const Position new_head_pos = _snake.move(dir);
			const auto		snake_pos = _snake.getPositions();
			const auto		food_it = std::find(_foods.begin(), _foods.end(), new_head_pos);

			// Check for any lose
			if (new_head_pos.x >= _size.x || new_head_pos.x < 0)
				_is_over = true;
			else if (new_head_pos.y >= _size.y || new_head_pos.y < 0)
				_is_over = true;
			else if (std::count(snake_pos.begin(), snake_pos.end(), new_head_pos) > 1)
				_is_over = true;
			else if (food_it == _foods.end())
				_snake.loseTail();
			else {
				_score++;
				_foods.erase(food_it);
				generateFood();
				generateFood();
			}
		}

	private:
		int						_score;
		bool					_is_over;
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
				// Food generated on snake
				if (std::find(snake_pos.begin(), snake_pos.end(), rand_pos) != snake_pos.end())
					continue ;
				// Food generated on another food
				else if (std::find(_foods.begin(), _foods.end(), rand_pos) != _foods.end())
					continue ;
				else
					break;
			}
			_foods.push_back(rand_pos);
		}
};
#endif
