#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <deque>
#include "../include/utils.hpp"
# include "../include/IPlugin.hpp"

class Snake {
	public:
		/* ---- Constructors ---- */
		Snake();
		~Snake();

		/* ---- Coplien ---- */
		Snake(const Snake &src);
		Snake &operator=(const Snake &src);

		void create(const int &width, const int &height, int idx = 0);

		/* ---- Accessors ---- */
		const std::deque<Position>	&getPositions( void )  const;
		const Direction &getDirection( void ) const;

		/* ---- Methods ---- */
		void			loseTail( void );
		void			loseHead( void );
		const Position	move(const Direction &new_dir);

	private:
		std::deque<Position>	_positions;
		Direction				_dir;

		bool	isCompatibleDir(const Direction &e) const;
};

#endif
