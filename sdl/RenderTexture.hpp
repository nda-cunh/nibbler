#ifndef _RENDERTEXTURE_HPP
#define _RENDERTEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <stdexcept>
#include <string>

class RenderTexture
{
	public:
		RenderTexture() {
		}

		void create(int width, int height) {
			surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ARGB8888);
			if (surface == NULL)
				throw std::runtime_error("SDL_CreateRGBSurface failed");
		}
		
		// create from texture bmp
		void create(std::string path) {
			surface = SDL_LoadBMP(path.c_str());
			if (surface == NULL)
				throw std::runtime_error("SDL_LoadBMP failed");
		}

		void clear() {
			SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
		}

		virtual void draw(RenderTexture &texture, int x, int y) {
			SDL_Rect rect = {x, y, texture.surface->w, texture.surface->h};
			SDL_BlitSurface(texture.surface, NULL, surface, &rect);
		}

		virtual void draw(SDL_Renderer*renderer, int x, int y) {
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_Rect rect = {x, y, surface->w, surface->h};
			SDL_RenderCopy(renderer, texture, NULL, &rect);
			SDL_DestroyTexture(texture);
		}

		virtual void draw (SDL_Surface *surface, int x, int y) {
			SDL_Rect rect = {x, y, surface->w, surface->h};
			SDL_BlitSurface(surface, NULL, this->surface, &rect);
		}

		void draw_rect(SDL_Rect *rect, int red, int green, int blue) {
			SDL_FillRect(surface, rect, SDL_MapRGB(surface->format, red, green, blue));
		}

		~RenderTexture() {
			SDL_FreeSurface(surface);
		}

		int get_width() {
			return surface->w;
		}

		int get_height() {
			return surface->h;
		}
	protected:
		SDL_Surface *surface;

};

#endif
