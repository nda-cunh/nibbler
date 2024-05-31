#include "../include/IPlugin.hpp"
#include <cstdio>
#include <raylib.h>

#define BG_COLOR GetColor(0x42424242)
#define TILE_SIZE 32
#define SHIFT 0.1 * TILE_SIZE

class Plugin : public IPlugin {
	private:
		int width;
		int height;

	public:
		virtual ~Plugin() {}
		void open(int x, int y) {
			width = (x + 2) * TILE_SIZE;
			height = (y + 3) * TILE_SIZE;
			SetTraceLogLevel(LOG_ERROR);
			SetTargetFPS(120);
			InitWindow(width, height, "nibbler - raylib");
		}

		void close() { CloseWindow(); }

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
			auto pos = snake.begin();
			auto color = GetColor(0x21AA21FF);
			
			DrawRectangle(TILE_SIZE * (pos->x + 1) + SHIFT, TILE_SIZE * (pos->y + 2) + SHIFT,
					TILE_SIZE - 2.0 * SHIFT, TILE_SIZE - 2.0 * SHIFT, color);
			color = GetColor(0x126612FF);
			for (++pos; pos != snake.end(); ++pos) {
				DrawRectangle(TILE_SIZE * (pos->x + 1) + SHIFT, TILE_SIZE * (pos->y + 2) + SHIFT,
						TILE_SIZE - 2.0 * SHIFT, TILE_SIZE - 2.0 * SHIFT, color);
			}
		}

		void update_food(Position &pos)  {
			DrawRectangle((pos.x + 1) * TILE_SIZE + SHIFT,
					(pos.y + 2) * TILE_SIZE + SHIFT,
					TILE_SIZE - 2.0 * SHIFT, TILE_SIZE - 2.0 * SHIFT, GetColor(0xFF2222FF));
		}

		void update_score(int n) {
			auto beg = width * 0.10;
			char score[10] = "";
			sprintf(score, "SCORE %3d", n);
			DrawText(score, beg, 0.5 * TILE_SIZE, 32, WHITE);
		}

		void update_bestscore(int n) {
			auto beg = width * 0.5;
			char score[10] = "";
			sprintf(score, "BEST %3d", n);
			DrawText(score, beg, 0.5 * TILE_SIZE, 32,
					GetColor(0xFFD700FF));
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

			bool	is_dark = true;
			Color	colors[2] = {
				GetColor(0xDBD1B4FF),
				GetColor(0xC2B280FF)
			};
			for (int x = 1; x < this->width / TILE_SIZE - 1; x++) {
				is_dark = (x % 2 == 1);
				for (int y = 2; y < this->height / TILE_SIZE - 1; y++) {
					is_dark = !is_dark;
					DrawRectangle(x * TILE_SIZE, y * TILE_SIZE,
							TILE_SIZE, TILE_SIZE,
							colors[static_cast<int>(is_dark)]);
				}
			}
		}

		void display() { EndDrawing(); }
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
