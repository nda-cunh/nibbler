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
		Activity				_mode;
		int						_score[2];
		int						_best_score[2];
		double					_speed;
		bool					_is_over;
		Position				_size;
		std::vector<Position>	_foods;
		Snake					_snake[2];
		ModuleAudio				*_audio;

		void	generateFood();
	
	public:
		/* ---- Constructors ---- */
		Game();
		Game(const int width, const int height, ModuleAudio *audio, Activity act = ON_MENU);
		~Game();
		void setAudio(ModuleAudio *audio);
		/* ---- Coplien  ---- */
		Game(const Game &src);
		Game &operator=(const Game &src);

		/* ---- Accessors ---- */
		bool		over() const;
		int			getScore( unsigned int idx = 0 ) const;
		int			getBestScore( unsigned int idx = 0 ) const;
		void 		increaseSpeed	( void );
		void 		decreaseSpeed	( void );
		double		getSpeed( void ) const;
		int			getLevelSpeed( void ) const;
		const std::deque<Position>	&getSnakePositions( unsigned int idx = 0) const;
		const std::vector<Position>	&getFoodPositions ( void ) const;

		/* ---- Methods ---- */
		void moveSnake	(const Direction &dir, int idx = 0);
		Game newGame	( Activity act ) const;
};
#endif
