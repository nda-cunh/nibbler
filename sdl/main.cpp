#include <raylib.h>
#include <memory>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "../include/IPlugin.hpp"

class Plugin : public IPlugin {
	private:
		SDL_Window* win;
		SDL_Renderer* renderer;
		int width;
		int height;
	public:
		virtual ~Plugin() {
			SDL_DestroyWindow(win);
			SDL_DestroyRenderer(renderer);
			SDL_Quit();
		}
		void open(int x, int y){
			width = x * 32;
			height = y * 32;
			win = SDL_CreateWindow("Nibbler - SDL2", 0, 0, 500, 500, 0);
			renderer = SDL_CreateRenderer(win, 0, 0);
			SDL_DisplayMode dm;
			if (SDL_GetDesktopDisplayMode(0, &dm) < 0) {
				printf("Erreur lors de l'obtention des dimensions de l'écran : %s\n", SDL_GetError());
			}

			// Calcul des coordonnées de la fenêtre
			SDL_SetWindowPosition(win, (dm.w - width) / 2, (dm.h - height) / 2);
		}

		void close(){
			SDL_DestroyWindow(win);
		}
		
		Event poll_event(){

			SDL_Event event;


			int key = 42;
			while (key > 0) {
				key = SDL_PollEvent(&event);
				auto truc = event.key.keysym;
				switch (truc.scancode) {
					case SDL_SCANCODE_LEFT:
						return LEFT;
					case SDL_SCANCODE_RIGHT:
						return RIGHT;
					case SDL_SCANCODE_UP:
						return UP;
					case SDL_SCANCODE_DOWN:
						return DOWN;
					case SDL_SCANCODE_KP_ENTER:
						return ENTER;
					case SDL_SCANCODE_ESCAPE:
						return CLOSE;
					case SDL_SCANCODE_F1:
						return F1;
					case SDL_SCANCODE_F2:
						return F2;
					case SDL_SCANCODE_F3:
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
			SDL_RenderClear(renderer);
		}

		void display () {
			SDL_RenderPresent(renderer);
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
