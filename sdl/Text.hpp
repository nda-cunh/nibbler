#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include <stdexcept>
#include <SDL2/SDL.h>
#include <cairo/cairo.h>
#include <memory>

class Text {
	public:
		Text ();
		~Text ();
		Text (std::string str);

		void create (int width, int height);
		void draw (SDL_Renderer *renderer);
		void draw (SDL_Renderer *renderer, int x, int y);
		int get_width ();
		int get_height ();
		void set_position (int x, int y);
		void set_text (std::string str);
		void set_font (std::string font);
		void set_size_font (int size);
		void update ();


	private: 
		void clear();
		void update_text ();
		void get_text_size (int &width, int &height);
		std::shared_ptr<SDL_Surface> surface;
		std::shared_ptr<cairo_surface_t> cairo_surface;
		std::shared_ptr<cairo_t> cairo_context;
		std::string text;
		std::string font;
		int size_font;
		int x;
		int y;
};

#endif
