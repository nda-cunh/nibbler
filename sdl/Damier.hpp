#ifndef DAMIER_HPP
#define DAMIER_HPP

#include "RenderTexture.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>

class Damier : public RenderTexture {
	public:
		Damier();
		Damier &operator= (const Damier &d);
		Damier (const Damier &d);

		void create (int width, int height, int tile_size, int x, int y) ;
		~Damier();

	private:
		void init_damier ();
		int tile_size;
		int x;
		int y;

};

#endif
