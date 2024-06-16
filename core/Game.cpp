#include "Game.hpp"

/* ____ CONSTRUCTORS ____ */
Game::Game()	{}

Game::~Game()	{}

Game::Game(const int width, const int height) {
	_snake.create(width, height);
	_size = {width, height};
	_is_over = false;
	_score = 0;
	_best_score = 0;
	_foods = std::vector<Position>();
	_speed = 0.09;
	// for (int i = 0; i < width*height; ++i)
	generateFood();
}

/* ____ ACCESSORS ____ */
bool	Game::over() const {
	return _is_over;
}

int		Game::getScore() const {
	return _score;
}

int		Game::getBestScore() const {
	return _best_score;
}

void 		Game::increaseSpeed	( void ) {
	if (this->_speed < 0.05)
		return ;
	_speed -= 0.01;
}

void 		Game::decreaseSpeed	( void ) {
	if (this->_speed > 0.1)
		return ;
	_speed += 0.01;
}

double		Game::getSpeed( void ) const {
	return this->_speed;
}

const std::deque<Position> &Game::getSnakePositions( void ) const {
	return _snake.getPositions(); 
}

const std::vector<Position> &Game::getFoodPositions( void ) const {
	return _foods;
}

const Direction &Game::getSnakeDirection( void ) const {
	return _snake.getDirection();
}
		
void Game::setAudio(ModuleAudio *audio) {
	this->_audio = audio;
}

/* ____ METHODS ____ */
void Game::moveSnake(const Direction &dir) {
	const Position	new_head_pos = _snake.move(dir);
	const auto		snake_pos = _snake.getPositions();
	const auto		food_it = FIND(_foods, new_head_pos);


	// Check for any lose
	if (new_head_pos.x >= _size.x || new_head_pos.x < 0)
		_is_over = true;
	else if (new_head_pos.y >= _size.y || new_head_pos.y < 0)
		_is_over = true;
	else if (COUNT(_snake.getPositions(), new_head_pos) > 1)
		_is_over = true;
	else if (food_it == _foods.end())
		_snake.loseTail();
	else {
		if (++_score > _best_score)
			++_best_score;
		_audio->playSound(IAudioModule::EAT);
		_foods.erase(food_it);
		generateFood();
		generateFood();
	}

	if (_is_over) {
		_audio->playSound(IAudioModule::DEAD);
	}
}

Game	Game::newGame( void ) const {
	Game	new_game = Game(_size.x, _size.y);

	new_game._best_score = _best_score;
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

Game &Game::operator=(const Game &src) {
	if (this != &src) {
		_score = src._score;
		_best_score = src._best_score;
		_is_over = src._is_over;
		_size = src._size;
		_foods = src._foods;
		_snake = src._snake;
		_audio = src._audio;
	}
	return *this;
}
