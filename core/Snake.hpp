#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <deque>
#include "../include/utils.hpp"
# include "../include/IPlugin.hpp"

class Snake {
	public:
		Snake() {}
		~Snake() {
			this->_positions.clear();
		}

		void create(const int &width, const int &height) {
			for (int j = 4; j > 0; j--)
				_positions.push_front({width / 2, height / 2 - j});
			_dir = Down;
		}

		const std::deque<Position>	&getPositions( void )  const { return _positions; }

		void	loseTail( void ) { _positions.pop_back(); }

		const Position	move(const Direction &new_dir) {
			if (this->isCompatibleDir(new_dir))
				_dir = new_dir;
			Position	head_pos = _positions[0];
			
			switch (_dir) {
				case Left:
					head_pos = {head_pos.x - 1, head_pos.y};
					break;
				case Right:
					head_pos = {head_pos.x + 1, head_pos.y};
					break;
				case Up:
					head_pos = {head_pos.x, head_pos.y - 1};
					break;
				case Down:
					head_pos = {head_pos.x, head_pos.y + 1};
					break;
			}
			_positions.push_front(head_pos);
			return head_pos;
		}

	private:
		std::deque<Position>	_positions;
		Direction				_dir;

		bool	isCompatibleDir(const Direction &e) const {
			if (_dir == Up || _dir == Down)
				return (e == Left || e == Right);
			else if (_dir == Left  || _dir == Right)
				return (e == Up || e == Down);
			return false;
		}
};
#endif
