#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include <stdexcept>
#include <SDL2/SDL.h>
#include <cairo/cairo.h>
#include <memory>

class Button {
	public:
		Button ();
		~Button ();
		Button (std::string str, int width, int height);

		void create (int width, int height);
		void clear();
		void update_background ();
		void update_text ();
		void get_text_size (int &width, int &height);
		void draw (SDL_Renderer *renderer);
		bool collide (int x, int y);
		int get_width ();
		int get_height ();
		void set_position (int x, int y);
		void set_size_font (int size_font);
		void set_color (int r, int g, int b);
		void set_background_color (int r, int g, int b);
		void set_background_color_hover (int r, int g, int b);
		void hover ();
		void unhover ();

	private: 
		std::shared_ptr<SDL_Surface> surface;
		std::shared_ptr<cairo_surface_t> cairo_surface;
		std::shared_ptr<cairo_t> cairo_context;
		std::string text;
		SDL_Colour color;
		SDL_Colour background_color;
		SDL_Colour background_color_hover;

		int size_font;
		bool is_hover = false;
		int x;
		int y;
};

#endif
