# include "Snake.hpp"

/* ____ CONSTRUCTORS ____ */
Snake::Snake() :
	_positions(std::deque<Position>()),
	_dir(Up)
{ }

Snake::~Snake() {}

Snake::Snake(const int width, const int height) :
	_positions(std::deque<Position>()),
	_dir (Down)
{
	for (int j = 4; j > 0; j--)
		_positions.push_front({width / 2, height / 2 - j});
}

/* ____ COPLIEN ____ */
Snake::Snake(const Snake &src) {
	*this = src;
}

Snake &Snake::operator=(const Snake &src) {
	if (this != &src) {
		_positions = src._positions;
		_dir = src._dir;
	}
	return *this;
}


/* ____ ACCESSORS ____ */
const std::deque<Position>	&Snake::getPositions( void )  const { return _positions; }

const Direction	&Snake::getDirection( void )  const { return _dir; }


/* ____ METHODS ____ */
void	Snake::loseTail( void ) { _positions.pop_back(); }
void	Snake::loseHead( void ) { _positions.pop_front(); }

const Position	Snake::move(const Direction &new_dir) {
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

bool	Snake::isCompatibleDir(const Direction &e) const {
	if (_dir == Up || _dir == Down)
		return (e == Left || e == Right);
	else if (_dir == Left  || _dir == Right)
		return (e == Up || e == Down);
	return false;
}
