#ifndef _RENDERTEXTURE_HPP
#define _RENDERTEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <stdexcept>
#include <string>
#include <memory>

class RenderTexture
{
	public:
		RenderTexture();
		RenderTexture(const RenderTexture &other);
		RenderTexture &operator=(const RenderTexture &other);

		void create(int width, int height);
		void create(const std::string &path);
		void clear();
		virtual void draw(RenderTexture &texture, int x, int y);
		virtual void draw(SDL_Renderer*renderer, int x, int y);
		virtual void draw (SDL_Surface *surface, int x, int y);
		virtual void draw_rect(SDL_Rect *rect, int red, int green, int blue);
		~RenderTexture();
		int get_width();
		int get_height();
	protected:
		std::shared_ptr<SDL_Surface> surface;


};

#endif
