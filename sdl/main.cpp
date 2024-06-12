#include <memory>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <cairo/cairo.h>
#include "Text.hpp"
#include "RenderTexture.hpp"
#include "../include/IPlugin.hpp"
#include "Damier.hpp"
#include "Button.hpp"

class Plugin : public IPlugin {
	private:
		SDL_Window* win;
		SDL_Renderer* renderer;
		
		Text text_score;
		Text text_bestscore;

		Damier damier;

		RenderTexture render_game;
		RenderTexture gameover;

		int score = 0;
		int best_score = 0;
		const int tile_size = 32;
		int width;
		int height;
		int x;
		int y;
	public:
		Plugin () {
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

		void open (int x, int y) {
			this->x = x;
			this->y = y;
			width = x * tile_size;
			height = y * tile_size;
			win = SDL_CreateWindow("Nibbler - SDL2", 0, 0, width + tile_size * 2, height + tile_size * 2 * 2, SDL_WINDOW_HIDDEN);
			if (win == NULL)
				throw std::runtime_error("SDL_CreateWindow failed");
			renderer = SDL_CreateRenderer(win, 0, 0);
			if (renderer == NULL)
				throw std::runtime_error("SDL_CreateRenderer failed");
			
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			gameover.create("./sdl/snake_sdl.bmp");

			damier.create(width, height, tile_size, x, y);

			render_game.create(width, height);

			SDL_DisplayMode dm;
			if (SDL_GetDesktopDisplayMode(0, &dm) < 0) {
				printf("Erreur lors de l'obtention des dimensions de l'écran : %s\n", SDL_GetError());
				throw std::runtime_error("SDL_GetDesktopDisplayMode failed");
			}
			SDL_SetWindowPosition(win, (dm.w - width) / 2, (dm.h - height) / 2);
			SDL_ShowWindow(win);
		}

		void close () {
			SDL_DestroyWindow(win);
		}

		Event poll_event (Activity) {
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


		void update_snake (const std::deque<Position> &queue, Direction) {
			SDL_Rect rect = { 0, 0, tile_size, tile_size };

			for (const auto &pos : queue) {
				rect.x = pos.x * tile_size,
				rect.y = pos.y * tile_size,
				render_game.draw_rect(&rect, 81, 128, 243);
			}
			rect.x = queue[0].x * tile_size,
			rect.y = queue[0].y * tile_size,
			render_game.draw_rect (&rect, 49, 94, 255);
		}

		void update_food (Position &position) {
			SDL_Rect rect = {
				position.x * tile_size,
				position.y * tile_size,
				tile_size,
				tile_size
			};
			render_game.draw_rect (&rect, 255, 0, 0);
		}

		void update_score (int score) {
			this->score = score;
			SDL_Rect rect = {tile_size, tile_size / 2, tile_size, tile_size};
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect);

			text_score.set_text(std::to_string(score));
			text_score.draw(renderer, tile_size * 2, -5);
		}

		void update_gameover () {
		}

		void update_bestscore (int score) {

			this->best_score = score;
			//draw a rect yellow for the best score
			SDL_Rect rect = {190, tile_size / 2, tile_size, tile_size};
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			SDL_RenderFillRect(renderer, &rect);

			text_bestscore.set_text(std::to_string(score));
			text_bestscore.draw(renderer, 190 + tile_size, -5);
		}

		void clear () {
			SDL_SetRenderDrawColor(renderer, 87, 138, 52, 255);
			SDL_RenderClear(renderer);

			SDL_Rect rect = {0, 0, width + tile_size * 2, tile_size * 2};
			SDL_SetRenderDrawColor(renderer, 74, 117, 44, 255);
			SDL_RenderFillRect(renderer, &rect);
			render_game.clear();
			
			render_game.draw(damier, 0, 0);
		}

		void display (Activity activity) {
			render_game.draw (renderer, tile_size, tile_size*3);
			if (activity == ON_GAME_OVER) {
				// draw a transparent black rect when the game is over
				int w, h;
				SDL_GetWindowSize(win, &w, &h);
				SDL_Rect rect = {0, 0, w, h};
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
				SDL_RenderFillRect(renderer, &rect);
				// draw the gameover in renderer
				int x_gameover = (w - gameover.get_width()) / 2.0;
				int y_gameover = (h - gameover.get_height()) / 2.0;
				gameover.draw (renderer, x_gameover, y_gameover);
				text_score.set_text(std::to_string(score));
				text_score.draw(renderer, x_gameover + 64, y_gameover + 120);
				text_bestscore.set_text(std::to_string(best_score));
				text_bestscore.draw(renderer, x_gameover + 208, y_gameover + 120);

			}
			// Button button;
			// button.create(200, 200, "Hello World !!!");
			// button.draw(renderer, 10, 10);

			// Text textator;
			// textator.set_text("Hello World !!!");
			// textator.draw(renderer, 10, 10);

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
