#include <raylib.h>
#include <memory>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <cairo/cairo.h>
#include "Text.hpp"
#include "../include/IPlugin.hpp"



class Plugin : public IPlugin {
	private:
		SDL_Window* win;
		SDL_Renderer* renderer;
		
		Text text_score;
		Text text_bestscore;

		const int tile_size = 32;
		int width;
		int height;
		int x;
		int y;
	public:
		Plugin() {
			SDL_Init(SDL_INIT_VIDEO);
		}

		virtual ~Plugin() {
			SDL_DestroyWindow(win);
			SDL_DestroyRenderer(renderer);
			SDL_Quit();
		}

		SDL_Texture* get_background() {
			SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);


			return SDL_CreateTextureFromSurface(renderer, surface);
		}

		void open(int x, int y) {
			this->x = x;
			this->y = y;
			width = x * tile_size;
			height = y * tile_size;
			win = SDL_CreateWindow("Nibbler - SDL2", 0, 0, width, height, 0);
			renderer = SDL_CreateRenderer(win, 0, 0);
			SDL_DisplayMode dm;
			if (SDL_GetDesktopDisplayMode(0, &dm) < 0) {
				printf("Erreur lors de l'obtention des dimensions de l'écran : %s\n", SDL_GetError());
			}


			// Calcul des coordonnées de la fenêtre
			SDL_SetWindowPosition(win, (dm.w - width) / 2, (dm.h - height) / 2);
		}

		void close() {
			SDL_DestroyWindow(win);
		}

		Event poll_event(Activity) {
			SDL_Event event;
			Event e = NONE;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT:
						e = CLOSE;
						break;
					case SDL_KEYDOWN:
						switch (event.key.keysym.scancode) {
							case SDL_SCANCODE_LEFT:
								e = LEFT;
								break;
							case SDL_SCANCODE_RIGHT:
								e = RIGHT;
								break;
							case SDL_SCANCODE_UP:
								e = UP;
								break;
							case SDL_SCANCODE_DOWN:
								e = DOWN;
								break;
							case SDL_SCANCODE_RETURN:
								e = ENTER;
								break;
							case SDL_SCANCODE_ESCAPE:
								e = CLOSE;
								break;
							case SDL_SCANCODE_F1:
								e = F1;
								break;
							case SDL_SCANCODE_F2:
								e = F2;
								break;
							case SDL_SCANCODE_F3:
								e = F3;
								break;
							default:
								e = NONE;
								break;
						}
						break;
					default:
						e = NONE;
						break;
				}
			}
			return e;
		}


		void update_snake(const std::deque<Position> &queue, Direction) {
			SDL_Rect rect = {
				0,
				0,
				tile_size,
				tile_size
			};
			for (const auto &pos : queue) {
				rect.x = pos.x * tile_size,
					rect.y = pos.y * tile_size,
					SDL_SetRenderDrawColor(renderer, 81, 128, 243, 255); // Vert plus foncé
				SDL_RenderFillRect(renderer, &rect);
			}
			rect.x = queue[0].x * tile_size,
				rect.y = queue[0].y * tile_size,
				SDL_SetRenderDrawColor(renderer, 49, 94, 255, 255); // Vert
			SDL_RenderFillRect(renderer, &rect);
		}

		void update_food(Position &position) {
			// Dessin de la pomme
			SDL_Rect rect = {
				position.x * tile_size,
				position.y * tile_size,
				tile_size,
				tile_size
			};
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
			SDL_RenderFillRect(renderer, &rect);
		}


		void update_score(int score) {
			text_score.set_text("Score: " + std::to_string(score));
			text_score.draw(renderer, 10, 10);
		}


		void update_bestscore(int score) {
			text_bestscore.set_text("Best Score: " + std::to_string(score));
			text_bestscore.draw(renderer, 220, 10);
		}

		void update_gameover() {
		}

		void clear () {
			SDL_RenderClear(renderer);
			for (int i = 0; i < x; i++) {
				for (int j = 0; j < y; j++) {
					if ((i + j) % 2 == 0) {
						SDL_SetRenderDrawColor(renderer, 162, 209, 73, 255);
					} else {
						SDL_SetRenderDrawColor(renderer, 170, 215, 81, 255);
					}
					SDL_Rect rect = {i * tile_size, j * tile_size, tile_size, tile_size};
					SDL_RenderFillRect(renderer, &rect);
				}
			}
		}

		void display (Activity) {
			// Dessin du damier
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
