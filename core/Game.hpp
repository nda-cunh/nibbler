#ifndef GAME_HPP
#define GAME_HPP

#include "../include/utils.hpp"
#include "Snake.hpp"
#include <algorithm>
#include <vector>
#include <random>
#include "ModuleAudio.hpp"

#define FIND(cont, elem) std::find(cont.begin(), cont.end(), elem)
#define COUNT(cont, elem) std::count(cont.begin(), cont.end(), elem)

class Game {
	private:
		int						_score;
		int						_best_score;
		bool					_is_over;
		Position				_size;
		std::vector<Position>	_foods;
		Snake					_snake;
		ModuleAudio				*_audio;

		void	generateFood();
	
	public:
		/* ---- Constructors ---- */
		Game();
		Game(const int width, const int height, ModuleAudio *audio);
		~Game();
		void setAudio(ModuleAudio *audio);
		/* ---- Coplien  ---- */
		Game(const Game &src);
		Game &operator=(const Game &src);

		/* ---- Accessors ---- */
		bool		over() const;
		int			getScore() const;
		int			getBestScore() const;
		const Direction				&getSnakeDirection( void ) const;
		const std::deque<Position>	&getSnakePositions( void ) const;
		const std::vector<Position>	&getFoodPositions ( void ) const;

		/* ---- Methods ---- */
		void moveSnake	(const Direction &dir);
		Game newGame	( ) const;
};
#endif
