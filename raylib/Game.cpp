#include "Game.hpp"
#include "utils.hpp"
#include <raylib.h>
#include "Score.hpp"

/* ____ CONSTRUCTORS & COPLIEN ____ */
Game::Game() : 
	_size({1, 1}),
	_food({}),
	_snake(Snake(NULL)),
	_score(0),
	_best_score(0),
	_is_over(false) {}

Game::Game(const Game &o) {
	*this = o;
}

Game::Game(int w, int h) : 
	_size({(w +2.f) * TILE_SIZE, (h + 3.f) * TILE_SIZE}),
	_food({}),
	_snake(Snake(NULL)),
	_score(0),
	_best_score(0),
	_is_over(false) {}

Game::~Game() {}

Game	&Game::operator=(const Game &rhs) {
	if (this == &rhs)
		return *this;
	_size = rhs._size;
	_food = rhs._food;
	_snake = rhs._snake;
	_score = rhs._score;
	_best_score = rhs._best_score;
	_is_over = rhs._is_over;
	return *this;
}

/* ____ ACCESSORS ____ */

void Game::setScore(int score) { _score = score; }
void Game::setIsOver(bool is_over) { _is_over = is_over; }
void Game::setSnake(const std::deque<Position> &snake) { _snake.update(&snake); }
void Game::resetFood( void ) { _food.clear(); }
void Game::addFood(Position pos) { _food.push_back(pos); }
void Game::setBestScore(int score) { _best_score = score; }


/* ____ DRAW METHODS ____ */

void	Game::draw_background() {
	Color	colors[2] = {
		GetColor(0xA2D149FF),
		GetColor(0xAAD751FF)
	};

	ClearBackground(GetColor(0x578a34ff));
	for (int x = 1; x < _size.x / TILE_SIZE - 1; x++) {
		bool	is_dark = (x & 1);
		for (int y = 2; y < _size.y / TILE_SIZE - 1; y++) {
			is_dark = !is_dark;
			DrawRectangle(x * TILE_SIZE, y * TILE_SIZE,
					TILE_SIZE, TILE_SIZE,
					colors[static_cast<int>(is_dark)]);
		}
	}
}

void Game::draw_food() {
	for (auto food = _food.begin(); food != _food.end(); food++) {
		Vector2	pos= {TILE_SIZE * (food->x + 1.f) + SHIFT,
						TILE_SIZE * (food->y + 2.f) + SHIFT};
		float	side = TILE_SIZE - 2* SHIFT;

		DrawRectangleRounded({pos.x, pos.y, side, side}, 0.4, 20, RED);
	}
}

void Game::draw_score() {
	static Score	displayer(WHITE, {3 * TILE_SIZE + 2 * 30, TILE_SIZE / 4});

	displayer.draw(_score);
}

void Game::draw_best_score() {
	static Score	displayer(GOLD, {11 * TILE_SIZE - 30, TILE_SIZE / 4});

	displayer.draw(_best_score);
}

void Game::draw() {
	this->draw_background();
	Position	head_pos = _snake.draw();

	// Hide out of border head
	if (!CheckCollisionPointRec(
				{static_cast<float>(head_pos.x),
				static_cast<float>(head_pos.y)},
				{0, 0, _size.x/TILE_SIZE-2.f, _size.y/TILE_SIZE-3.f}))
		DrawRectangle(TILE_SIZE * (head_pos.x + 1),
				TILE_SIZE * (head_pos.y + 2),
				TILE_SIZE, TILE_SIZE, GetColor(0x578a34ff));

	// Draw scores
	this->draw_score();
	this->draw_best_score();

	// Draw food
	this->draw_food();
}
