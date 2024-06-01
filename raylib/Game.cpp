#include "Game.hpp"
#include <raylib.h>

/* ____ CONSTRUCTORS ____ */
Game::Game() {
	this->_size = {1, 1};
	this->_on_menu = false;
}

Game::Game(int w, int h) {
	this->_size = {(w + 2) * TILE_SIZE, (h + 3) * TILE_SIZE};
	this->_on_menu = false;
}


Game::~Game() {}


/* ____ ACCESSORS ____ */

void Game::setSnake(const std::deque<Position> &snake) { _snake.update(&snake); }
void Game::setFood(Position pos) { _food = pos; }
void Game::setScore(int score) { _score = score; }
void Game::setBestScore(int score) { _best_score = score; }
void Game::setOnMenu(bool b) { _on_menu = b; }
bool Game::getOnMenu() const { return _on_menu; }


/* ____ DRAW METHODS ____ */

void Game::init_background() {
	bool is_dark = true;
	Color colors[2] = {
		GetColor(0xDBD1B4FF),
		GetColor(0xC2B280FF)
	};
	_background = LoadRenderTexture(_size.x, _size.y);

	BeginTextureMode(_background);
	{
		ClearBackground(BLACK);
		for (int x = 1; x < _size.x / TILE_SIZE - 1; x++) {
			is_dark = (x % 2 == 1);
			for (int y = 1; y < _size.y / TILE_SIZE - 2; y++) {
				is_dark = !is_dark;
				DrawRectangle(x * TILE_SIZE, y * TILE_SIZE,
						TILE_SIZE, TILE_SIZE,
						colors[static_cast<int>(is_dark)]);
			}
		}
	}
	EndTextureMode();
}

void	Game::draw_background() {
	if (!IsRenderTextureReady(this->_background))
		this->init_background();
	DrawTexture(_background.texture, 0, 0, RAYWHITE);
}

void Game::draw_food() {
	DrawCircleV(
			{TILE_SIZE * (_food.x + 1.5f), TILE_SIZE * (_food.y + 2.5f)},
			TILE_SIZE * 0.5f - SHIFT, GetColor(0xFF2222FF));
}

void Game::draw_score() {
	auto beg = this->_size.x * 0.10;
	char score[10] = "";
	sprintf(score, "SCORE %3d", _score);
	DrawText(score, beg, 0.5 * TILE_SIZE, 32, WHITE);
}

void Game::draw_best_score() {
	auto beg = this->_size.x * 0.5;
	char score[10] = "";
	sprintf(score, "BEST %3d", _best_score);
	DrawText(score, beg, 0.5 * TILE_SIZE, 32,
			GetColor(0xFFD700FF));
}

void Game::draw() {
	this->draw_background();
	this->draw_score();
	this->draw_best_score();
	this->_snake.draw();
	this->draw_food();
}
