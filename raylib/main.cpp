#include "utils.hpp"
#include "../include/IPlugin.hpp"
#include "Game.hpp"

class Plugin : public IPlugin {
	private:
		int 	width;
		int 	height;
		Game	_game;

	public:
		virtual ~Plugin() {
			CloseWindow();
		}
		void open(int x, int y) {
			width = (x + 2) * TILE_SIZE;
			height = (y + 3) * TILE_SIZE;
			_game = Game(x, y);
			SetTraceLogLevel(LOG_ERROR);
			SetTargetFPS(120);
			InitWindow(width, height, "nibbler - raylib");
		}

		void close() { 
			CloseWindow();
		}

		Event poll_event() {
			if (WindowShouldClose())
				return CLOSE;

			int key = 42;
			while (key != 0) {
				key = GetKeyPressed();
				switch (key) {
					case KEY_LEFT:
						return LEFT;
					case KEY_RIGHT:
						return RIGHT;
					case KEY_UP:
						return UP;
					case KEY_DOWN:
						return DOWN;
					case KEY_ENTER:
						return ENTER;
					case KEY_ESCAPE:
						return CLOSE;
					case KEY_F1:
						return F1;
					case KEY_F2:
						return F2;
					case KEY_F3:
						return F3;
					default:
						break;
				}
			}
			return NONE;
		}

		void update_snake(const std::deque<Position> &snake, Direction direction) {
			(void) direction;
			_game.setSnake(snake);
		}

		void update_food(Position &pos)  {
			_game.setFood(pos);
		}

		void update_score(int n){
			_game.setScore(n);
		}

		void update_bestscore(int n) {
			_game.setBestScore(n);
		}

		void update_gameover() {
			Position beg = {static_cast<int>(0.2 * width), static_cast<int>(0.4 * height)};
			DrawRectangle(0, 0, width, height, GetColor(0x00000084));
			DrawRectangle(beg.x, beg.y, width - 2 * beg.x, 6 * TILE_SIZE, GetColor(0x131313FF));
			DrawText("Game Over", beg.x + TILE_SIZE * 1.8, beg.y + TILE_SIZE, 42, WHITE);
			DrawText("Press [Enter]", beg.x + TILE_SIZE * 2.7, beg.y + TILE_SIZE * 4, 22, WHITE);
		}

		void clear() {
			BeginDrawing();
			ClearBackground(BLACK);
		}

		void display() {
			_game.draw();
			EndDrawing();
		}
};

extern "C" {
	Plugin *game = NULL;

	IPlugin *load() {
		try {
			if (game == NULL)
				game = new Plugin();
		} catch (...) {
			return NULL;
		}
		return game;
	}

	void unload() { delete game; }
}
