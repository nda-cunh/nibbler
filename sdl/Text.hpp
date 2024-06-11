#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <cairo/cairo.h>
#include <string>

class Text
{
	public:
		Text() {
			surface = SDL_CreateRGBSurfaceWithFormat(0, 250, 50, 32, SDL_PIXELFORMAT_ARGB8888);
			cairo_surface = cairo_image_surface_create_for_data(
					(unsigned char *)surface->pixels,
					CAIRO_FORMAT_ARGB32,
					surface->w,
					surface->h,
					surface->pitch
					);
			cairo_context = cairo_create(cairo_surface);
			this->text = "";
		}


		void set_text(const std::string &text) {
			this->text = text;
		}

		void draw (SDL_Renderer *renderer, int x, int y) {
			// Effacement de la surface
			cairo_set_operator(cairo_context, CAIRO_OPERATOR_CLEAR);
			cairo_paint(cairo_context);
			cairo_set_operator(cairo_context, CAIRO_OPERATOR_OVER);

			// Affichage du score
			cairo_select_font_face(cairo_context, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
			cairo_set_font_size(cairo_context, 32);
			cairo_set_source_rgb(cairo_context, 0, 0, 0); // Blanc
			cairo_move_to(cairo_context, 10, 50);
			cairo_show_text(cairo_context, text.c_str());

			// Copie de la surface Cairo dans le rendu SDL
			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_Rect dest_rect = {x, y, surface->w, surface->h};
			SDL_RenderCopy(renderer, texture, NULL, &dest_rect);

			// Libération des ressources
			SDL_DestroyTexture(texture);
		}

		~Text() {
			cairo_destroy(cairo_context);
			cairo_surface_destroy(cairo_surface);
			SDL_FreeSurface(surface);
		}

	private:
		std::string text;
		SDL_Surface *surface;
		cairo_surface_t *cairo_surface;
		cairo_t *cairo_context;

};
