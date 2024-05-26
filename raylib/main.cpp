#include <raylib.h>
#include <memory>
#include <stdexcept>
#include "../include/IPlugin.hpp"

class Plugin : public IPlugin {
	private:
		int width;
		int height;
	public:
		virtual ~Plugin() {}
		void open(int x, int y){
			width = x * 32;
			height = y * 32;
			InitWindow(width, height, "nibbler - raylib");
		}

		void close(){
			CloseWindow();
		}
		
		Event poll_event(){


			int key = 42;
			while (key != 0) {
				key = GetKeyPressed();
				switch(key) {
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

		void update_snake(const std::deque<Position> &queue, Direction direction) {
		}

		void update_food(Position &position) {
		}

		void update_score(int n) {
		}

		void update_bestscore(int n) {
		}

		void update_gameover() {
		}

		void clear () {
			BeginDrawing();
			ClearBackground(RAYWHITE);
		}

		void display () {
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
	
	void unload() {
		delete game;
	}
}
