#include "Game.hpp"
#include "Button.hpp"
#include <raylib.h>

/* ____ CONSTRUCTORS & COPLIEN ____ */
Game::Game(){
	this->_size = {1, 1};
}

Game::Game(const Game &o): TILE_SIZE(o.TILE_SIZE) {
	*this = o;
}

Game::Game(int w, int h, int tile_size) : TILE_SIZE(tile_size) {
	_background = RenderTexture();
	this->_size = {(w + 2) * TILE_SIZE, (h + 3) * TILE_SIZE};
	_snake = Snake(NULL, TILE_SIZE);
}

Game::~Game() {
	if (_background.id != 0)
		UnloadTexture(_background.texture);
}

Game	&Game::operator=(const Game &rhs) {
	if (this == &rhs)
		return *this;
	TILE_SIZE = rhs.TILE_SIZE;
	_background = rhs._background;
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

void Game::init_background(bool is_multiplayer) {
	bool is_dark = true;
	Color colors[2] = {
		GetColor(0xA2D149FF),
		GetColor(0xAAD751FF)
	};

	if (_background.id != 0)
		UnloadTexture(_background.texture);
	
	_background = LoadRenderTexture(_size.x, _size.y);

	BeginTextureMode(_background);
	{
		ClearBackground(GetColor(0x578a34ff));
		for (int x = 1; x < _size.x / TILE_SIZE - 1; x++) {
			is_dark = (x % 2 == 1);
			for (int y = 1; y < _size.y / TILE_SIZE - 2; y++) {
				is_dark = !is_dark;
				DrawRectangle(x * TILE_SIZE, y * TILE_SIZE,
						TILE_SIZE, TILE_SIZE,
						colors[static_cast<int>(is_dark)]);
			}
		}
		if (is_multiplayer) {
			Rectangle	rec = {_size.x * 0.45f, TILE_SIZE * 21.7f,
					TILE_SIZE * 1.f - 2.f * SHIFT, TILE_SIZE * 1.f};
			Vector2		pos_circle = {_size.x * 0.45f + TILE_SIZE * 0.5f - SHIFT,
					TILE_SIZE * 21.4f};

			DrawRectangleRounded(rec, 0.5f, 10, GetColor(0x315ec9ff));
			DrawCircleV(pos_circle,
					TILE_SIZE * 0.5f - SHIFT, GetColor(0x4e7cf6ff));
			rec.x = _size.x * 0.55f;
			DrawRectangleRounded(rec, 0.5f, 10, GetColor(0x315e00ff));
			pos_circle.x = rec.x + TILE_SIZE * 0.5f - SHIFT;
			DrawCircleV(pos_circle,
					TILE_SIZE * 0.5f - SHIFT, GetColor(0x4e7c00ff));
		}
	}
	EndTextureMode();
}

void	Game::draw_background() {
	static bool	first_display = true;

	if (first_display) {
		this->init_background();
		first_display = false;
	}
	DrawTexture(_background.texture, 0, 0, RAYWHITE);
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
	const static float	txt_size = 0.07 * std::min(_size.x, _size.y);
	char score[10] = "";

	sprintf(score, "SCORE %3d", _score);
	// DrawText(score, TILE_SIZE, 0.5 * TILE_SIZE, txt_size, WHITE);
}

void Game::draw_best_score() {
	const static float	txt_size = 0.07 * std::min(_size.x, _size.y);
	auto beg = this->_size.x * 0.5;
	char score[10] = "";

	sprintf(score, "BEST %3d", _best_score);
	// DrawText(score, beg, 0.5 * TILE_SIZE, txt_size,
			// GetColor(0xFFD700FF));
}

void Game::draw() {
	this->draw_background();
	this->draw_score();
	this->draw_best_score();
	this->_snake.draw();
	this->draw_food();
}
