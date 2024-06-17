#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include "Text.hpp"
#include <cairo/cairo.h>
#include <memory>

class Button {
	public:
		Button () {}

		void create (int width, int height) {
			surface = std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ARGB8888), SDL_FreeSurface);
			if (surface == NULL)
				throw std::runtime_error("SDL_CreateRGBSurface failed");
			cairo_surface = std::shared_ptr<cairo_surface_t>(cairo_image_surface_create_for_data(static_cast<unsigned char*>(surface->pixels), CAIRO_FORMAT_ARGB32, surface->w, surface->h, surface->pitch), cairo_surface_destroy);
			cairo_context = std::shared_ptr<cairo_t>(cairo_create(cairo_surface.get()), cairo_destroy);

		}

		// void collide (int x, int y) {
			// if (x >= 0 && x <= surface->w && y >= 0 && y <= surface->h)
				// std::cout << "Collide" << std::endl;
		// }

		Button (std::string str, int width, int height) {
			this->text = str;

			create (width, height);
			int w, h;
			get_text_size(w, h);
			if (w > width)
				width = w;
			if (h > height)
				height = h;

			if (surface->w < width || surface->h < height)
				create(width, height);
		}

		~Button () {
		}

		void clear() {
			cairo_set_operator(cairo_context.get(), CAIRO_OPERATOR_CLEAR);
			cairo_paint(cairo_context.get());
			cairo_set_operator(cairo_context.get(), CAIRO_OPERATOR_OVER);
			cairo_set_antialias(cairo_context.get(), CAIRO_ANTIALIAS_GRAY);
		}

		void update_background () {
			// draw a cyan rectangle
			if (is_hover)
				cairo_set_source_rgb(cairo_context.get(), 0.30, 0.62, 0.98);
			else
				cairo_set_source_rgb(cairo_context.get(), 30.3 / 100.0, 75.1 / 100.0, 97.6  /100.0);
			cairo_rectangle(cairo_context.get(), 0, 0, surface->w, surface->h);
			cairo_fill(cairo_context.get());

		}

		void update_text () {
			cairo_select_font_face(cairo_context.get(), "Answer", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
			cairo_set_font_size(cairo_context.get(), 21);
			cairo_set_source_rgb(cairo_context.get(), 1.0, 1.0, 1.0);

			cairo_text_extents_t extents;
			cairo_text_extents(cairo_context.get(), text.c_str(), &extents);

			double x = (surface->w - extents.width) / 2.0;
			double y = (surface->h + extents.height) / 2.0;
			cairo_move_to(cairo_context.get(), x, y);
			cairo_show_text(cairo_context.get(), text.c_str());
		}

		// get the size max of the text and return it
		void get_text_size (int &width, int &height) {
			cairo_select_font_face(cairo_context.get(), "Answer", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
			cairo_set_font_size(cairo_context.get(), 21);
			cairo_text_extents_t extents;
			cairo_text_extents(cairo_context.get(), text.c_str(), &extents);
			width = extents.width;
			height = extents.height;
		}

		void draw (SDL_Renderer *renderer) {
			clear();
			update_background();
			update_text();

			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface.get());
			SDL_Rect rect = {x, y, surface->w, surface->h};
			SDL_RenderCopy(renderer, texture, NULL, &rect);
			SDL_DestroyTexture(texture);
		}

		bool collide (int x, int y) {
			if (x >= this->x && x <= this->x + surface->w && y >= this->y && y <= this->y + surface->h)
				return true;
			return false;
		}

		int get_width () {
			return surface->w;
		}

		int get_height () {
			return surface->h;
		}

		void set_position (int x, int y) {
			this->x = x;
			this->y = y;
		}

		void hover () {
			is_hover = true;
		}

		void unhover () {
			is_hover = false;
		}

	private: 
		std::shared_ptr<SDL_Surface> surface;
		std::shared_ptr<cairo_surface_t> cairo_surface;
		std::shared_ptr<cairo_t> cairo_context;
		std::string text;
		int x;
		int y;
		bool is_hover = false;
};

#endif
