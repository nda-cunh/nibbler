#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include "RenderTexture.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <cairo/cairo.h>
#include <string>

class Text : public RenderTexture {
	public:
		Text();
		void set_text(const std::string &text); 
		void set_font(const std::string &font);
		void set_color(int r, int g, int b);
		void draw (SDL_Renderer *renderer, int x, int y) override;
		void draw (SDL_Surface *surface, int x, int y) override;
		void draw (RenderTexture &texture, int x, int y) override;
		~Text();

	private:
		void cairo_draw();
		SDL_Colour color;
		std::string text;
		cairo_surface_t *cairo_surface;
		cairo_t *cairo_context;
		std::string font;

};

#endif
