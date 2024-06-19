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
#include "Gameover.hpp"
#include "Menu.hpp"

class Plugin : public IPlugin {
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
			SDL_DisplayMode dm;
			this->x = x;
			this->y = y;
			width = x * tile_size;
			height = y * tile_size;

			////////////////////////////////////////
			///	Window
			////////////////////////////////////////
			win = SDL_CreateWindow("Nibbler - SDL2", 0, 0, width + tile_size * 2, height + tile_size * 2 * 2, SDL_WINDOW_HIDDEN);
			if (win == NULL)
				throw std::runtime_error("SDL_CreateWindow failed");
			if (SDL_GetDesktopDisplayMode(0, &dm) < 0) {
				printf("Erreur lors de l'obtention des dimensions de l'écran : %s\n", SDL_GetError());
				throw std::runtime_error("SDL_GetDesktopDisplayMode failed");
			}
			SDL_SetWindowPosition(win, (dm.w - width) / 2, (dm.h - height) / 2);
			SDL_ShowWindow(win);

			////////////////////////////////////////
			///	Renderer
			////////////////////////////////////////
			renderer = SDL_CreateRenderer(win, 0, 0);
			if (renderer == NULL)
				throw std::runtime_error("SDL_CreateRenderer failed");

			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

			////////////////////////////////////////
			///	Damier
			////////////////////////////////////////
			damier.create(width, height, tile_size, x, y);

			////////////////////////////////////////
			///	RenderTexture (Game)
			////////////////////////////////////////
			render_game.create(width, height);

			////////////////////////////////////////
			///	Menu
			////////////////////////////////////////

			int w;
			int h;
			SDL_GetWindowSize(win, &w, &h);
			
			menu.create(w, h);

			////////////////////////////////////////
			/// Gameover 
			////////////////////////////////////////
			
			gameover.create(w, h);

			////////////////////////////////////////
			/// Buttons
			////////////////////////////////////////
			button_retry = std::make_shared<Button> ("Try Again", (gameover.get_width() / 3.0) *2, 50);
			button_menu = std::make_shared<Button> ("Menu", gameover.get_width() / 3.0 - 10, 50);

			int gameover_x, gameover_y;
			gameover.get_position(gameover_x, gameover_y);
			
			button_retry->set_position (gameover_x, gameover_y + gameover.get_height() + 10);
			button_menu->set_position (gameover_x + button_retry->get_width() + 10, gameover_y + gameover.get_height() + 10);
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
						// survol des boutons
					case SDL_MOUSEMOTION:
						int x, y;
						SDL_GetMouseState(&x, &y);
						button_retry->unhover();
						button_menu->unhover();
						if (button_retry->collide(x, y)) {
							button_retry->hover();
						} else if (button_menu->collide(x, y)) {
							button_menu->hover();
						}
						break;
					case SDL_MOUSEBUTTONUP:
						switch (event.button.button) {
							case SDL_BUTTON_LEFT:
							// get the position of the mouse and test if it's in the button_retry
								int x, y;
								SDL_GetMouseState(&x, &y);
								if (button_retry->collide(x, y)) {
									return ENTER;
								} else if (button_menu->collide(x, y)) {
									return CLICK_MENU;
								}
								break;
							default:
								e = NONE;
								break;
						}
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
							case SDL_SCANCODE_MINUS:
								e = SPEED_DOWN;
								break;
							case SDL_SCANCODE_KP_PLUS:
								e = SPEED_UP;
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
			text_score.draw(renderer, tile_size * 2.5 - text_score.get_width() / 2.0, tile_size * 1 - text_score.get_height() / 2.0);
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
			text_bestscore.draw(renderer, tile_size * 7.5 - text_score.get_width() / 2.0, tile_size * 1 - text_score.get_height() / 2.0);
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

			switch (activity) {
				case ON_MENU:
					menu.draw(renderer);
					break;
				case ON_GAME:
					break;
				case ON_GAME_OVER:
					SDL_Rect rect; 
					int w, h;
					SDL_GetWindowSize(win, &w, &h);
					rect = {0, 0, w, h};
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
					SDL_RenderFillRect(renderer, &rect);

					// Draw the gameover screen
					gameover.update_score(score, best_score);
					gameover.draw(renderer, score, best_score);

					button_retry->draw(renderer);
					button_menu->draw(renderer);
					break;
				default:
					break;
			}

			SDL_RenderPresent(renderer);
		}

	private:
		SDL_Window* win;
		SDL_Renderer* renderer;

		Damier damier;
		Menu menu;

		Gameover gameover;
		RenderTexture render_game;

		Text text_score;
		Text text_bestscore;

		int score = 0;
		int best_score = 0;
		const int tile_size = 32;
		int width;
		int height;
		int x;
		int y;
		std::shared_ptr<Button> button_retry;
		std::shared_ptr<Button> button_menu;
};

extern "C" {
	IPlugin *load() {
		return new Plugin();
	}

	void unload(IPlugin *game) {
		delete game;
	}
}
