#include "Game.hpp"

/* ____ CONSTRUCTORS ____ */
Game::Game()	{}

Game::~Game()	{}

Game::Game(const int width, const int height, ModuleAudio *audio, Activity act) :
	_mode(act),
	_score{0, 0},
	_best_score{0, 0},
	_speed(0.075),
	_is_over(false),
	_size({width, height}),
	_foods(std::vector<Position>()),
	_snake{Snake(), Snake()},
	_audio(audio)
{ 
	_snake[0].create(width, height);
	_snake[1].create(width, height);
	if (act == ON_GAME_2P) {
		_snake[0].create(width, height, -1);
		_snake[1].create(width, height, 1);
	}
	// for (int i = 0; i < width*height; ++i)
	generateFood();
}

/* ____ ACCESSORS ____ */
bool	Game::over() const {
	return _is_over;
}

int		Game::getScore( unsigned int idx ) const {
	return _score[idx];
}

int		Game::getBestScore( unsigned int idx ) const {
	return _best_score[idx];
}

void 		Game::increaseSpeed	( void ) {
	if (this->_speed <= 0.05)
		return ;
	_speed -= 0.0125;
}

void 		Game::decreaseSpeed	( void ) {
	if (this->_speed >= 0.1)
		return ;
	_speed += 0.0125;
}

double		Game::getSpeed( void ) const {
	return _speed;
}

int			Game::getLevelSpeed( void ) const {
	int speed_level = 5 - (_speed - 0.05) / 0.0125 + 1;
	return speed_level;
}

const std::deque<Position> &Game::getSnakePositions( unsigned int idx ) const {
	return _snake[idx].getPositions(); 
}

const std::vector<Position> &Game::getFoodPositions( void ) const {
	return _foods;
}
		

/* ____ METHODS ____ */
void Game::moveSnake (const Direction &dir, int idx) {
	const Direction	snake_dir = _snake[idx].getDirection();
	const Position	new_head_pos = _snake[idx].move(dir);
	const auto		snake_pos = _snake[idx].getPositions();
	const auto		other_snake_pos = _snake[idx ^ 1].getPositions();
	const auto		food_it = FIND(_foods, new_head_pos);


	// Check if snake is out of bounds or if it collides with itself
	if ((new_head_pos.x >= _size.x || new_head_pos.x < 0) || 
		(new_head_pos.y >= _size.y || new_head_pos.y < 0) ||
		COUNT(snake_pos, new_head_pos) > 1 ||
		(this->_mode == ON_GAME_2P && COUNT(other_snake_pos, new_head_pos) > 0))
	{
		_is_over = true;
		_audio->playSound(IAudioModule::DEAD);
		return ;
	}
					
	if (dir != snake_dir &&
		((dir == Up && snake_dir != Down)    || 
		 (dir == Down && snake_dir != Up)    ||
		 (dir == Left && snake_dir != Right) ||
		 (dir == Right && snake_dir != Left))) {
		switch (dir) {
			case Up:
				_audio->playSound(IAudioModule::UP);
				break;
			case Down:
				_audio->playSound(IAudioModule::DOWN);
				break;
			case Left:
				_audio->playSound(IAudioModule::LEFT);
				break;
			case Right:
				_audio->playSound(IAudioModule::RIGHT);
				break;
		}
	}


	if (food_it == _foods.end())
		_snake[idx].loseTail();
	else {
		if (++_score[idx] > _best_score[idx])
			++_best_score[idx];
		_audio->playSound(IAudioModule::EAT);
		_foods.erase(food_it);
		generateFood();
		generateFood();
	}
}

Game	Game::newGame( Activity act ) const {
	Game	new_game = Game(_size.x, _size.y, _audio, act);

	new_game._best_score[0] = _best_score[0];
	new_game._speed = _speed;
	return new_game;
}

void	Game::generateFood() {
	const auto 		snake_pos = getSnakePositions();
	auto freePos = std::vector<Position>();

	// Generate all available positions
	for (int i = 0; i < _size.x; ++i) {
		for (int j = 0; j < _size.y; ++j) {
			if (FIND(snake_pos, Position({i, j})) != snake_pos.end())
				continue;
			else if (FIND(_foods, Position({i, j})) != _foods.end())
				continue;
			freePos.push_back({i, j});
		}
	}

	// No empty spaces in map
	if (freePos.size() == 0)
		return ;

	int rand_idx =  std::rand() % freePos.size();
	_foods.push_back(freePos[rand_idx]);
}

/* ____ COPLIEN ____ */
Game::Game(const Game &src) {
	*this = src;
}

Game &Game::operator=(const Game &rhs) {
	if (this == &rhs)
		return *this;
	_score[0] = rhs._score[0];
	_score[1] = rhs._score[1];
	_best_score[0] = rhs._best_score[0];
	_best_score[1] = rhs._best_score[1];
	_speed = rhs._speed;
	_mode = rhs._mode;
	_is_over = rhs._is_over;
	_size = rhs._size;
	_foods = rhs._foods;
	_snake[0] = rhs._snake[0];
	_snake[1] = rhs._snake[1];
	_audio = rhs._audio;
	return *this;
}
