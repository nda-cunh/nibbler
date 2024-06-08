/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nda-cunh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 04:18:12 by nda-cunh          #+#    #+#             */
/*   Updated: 2024/06/08 04:59:09 by nda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raylib.h>
#include <memory>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cairo/cairo.h>

#include "../include/IPlugin.hpp"
#include "SDL_surface.h"



class Plugin : public IPlugin {
	private:
		SDL_Window* win;
		SDL_Renderer* renderer;
		
		// Text Score
		SDL_Surface *surface_score;
		cairo_surface_t *cairo_surface_score;
		cairo_t *cairo_context_score;
		
		// Best Score
		SDL_Surface *surface_best;
		cairo_surface_t *cairo_surface_best;
		cairo_t *cairo_context_best;

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
			// Free Font score
			cairo_destroy(cairo_context_score);
			cairo_surface_destroy(cairo_surface_score);
			SDL_FreeSurface(surface_score);
			
			// Free Best Score Font
			cairo_destroy(cairo_context_best);
			cairo_surface_destroy(cairo_surface_best);
			SDL_FreeSurface(surface_best);

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
			

			surface_score = SDL_CreateRGBSurfaceWithFormat(0, 250, 50, 32, SDL_PIXELFORMAT_ARGB8888);
			cairo_surface_score = cairo_image_surface_create_for_data(
					(unsigned char *)surface_score->pixels,
					CAIRO_FORMAT_ARGB32,
					surface_score->w,
					surface_score->h,
					surface_score->pitch
					);
			cairo_context_score = cairo_create(cairo_surface_score);
			

			surface_best = SDL_CreateRGBSurfaceWithFormat(0, 250, 50, 32, SDL_PIXELFORMAT_ARGB8888);
			cairo_surface_best = cairo_image_surface_create_for_data(
					(unsigned char *)surface_best->pixels,
					CAIRO_FORMAT_ARGB32,
					surface_best->w,
					surface_best->h,
					surface_best->pitch
					);
			cairo_context_best = cairo_create(cairo_surface_best);

		}

		void close() {
			SDL_DestroyWindow(win);
		}

		Event poll_event() {
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
					SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // Vert plus foncé
				SDL_RenderFillRect(renderer, &rect);
			}
			rect.x = queue[0].x * tile_size,
				rect.y = queue[0].y * tile_size,
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Vert
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
			// Effacement de la surface
			cairo_set_operator(cairo_context_score, CAIRO_OPERATOR_CLEAR);
			cairo_paint(cairo_context_score);
			cairo_set_operator(cairo_context_score, CAIRO_OPERATOR_OVER);

			// Affichage du score
			char score_text[32];
			sprintf(score_text, "Score: %d", score);
			cairo_select_font_face(cairo_context_score, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
			cairo_set_font_size(cairo_context_score, 32);
			cairo_set_source_rgb(cairo_context_score, 0, 0, 0); // Blanc
			cairo_move_to(cairo_context_score, 10, 50);
			cairo_show_text(cairo_context_score, score_text);

			// Copie de la surface Cairo dans le rendu SDL
			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface_score);
			SDL_Rect dest_rect = {0, 0, surface_score->w, surface_score->h};
			SDL_RenderCopy(renderer, texture, NULL, &dest_rect);

			// Libération des ressources
			SDL_DestroyTexture(texture);
		}


		void update_bestscore(int score) {
			// Effacement de la surface
			cairo_set_operator(cairo_context_best, CAIRO_OPERATOR_CLEAR);
			cairo_paint(cairo_context_best);
			cairo_set_operator(cairo_context_best, CAIRO_OPERATOR_OVER);

			// Affichage du score
			char score_text[32];
			sprintf(score_text, "Best Score: %d", score);
			cairo_select_font_face(cairo_context_best, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
			cairo_set_font_size(cairo_context_best, 32);
			cairo_set_source_rgb(cairo_context_best, 0, 0, 0);
			cairo_move_to(cairo_context_best, 10, 50);
			cairo_show_text(cairo_context_best, score_text);

			// Copie de la surface Cairo dans le rendu SDL
			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface_best);
			SDL_Rect dest_rect = {width - 250, 0, surface_best->w, surface_best->h};
			SDL_RenderCopy(renderer, texture, NULL, &dest_rect);

			// Libération des ressources
			SDL_DestroyTexture(texture);
		}

		void update_gameover() {
		}

		void clear () {
			SDL_RenderClear(renderer);
			for (int i = 0; i < x; i++) {
				for (int j = 0; j < y; j++) {
					if ((i + j) % 2 == 0) {
						SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					} else {
						SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
					}
					SDL_Rect rect = {i * tile_size, j * tile_size, tile_size, tile_size};
					SDL_RenderFillRect(renderer, &rect);
				}
			}
		}

		void display () {
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
