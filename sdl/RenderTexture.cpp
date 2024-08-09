#include "RenderTexture.hpp"


////////////////////////////////////////////////
/// Constructors and Destructor
////////////////////////////////////////////////

RenderTexture::RenderTexture() { }


RenderTexture::RenderTexture(const RenderTexture &other) {
	surface.reset(SDL_ConvertSurface(other.surface.get(), other.surface.get()->format, 0));
	if (surface.get() == NULL)
		throw std::runtime_error("SDL_ConvertSurface failed");
}

RenderTexture &RenderTexture::operator=(const RenderTexture &other) {
	surface.reset(SDL_ConvertSurface(other.surface.get(), other.surface.get()->format, 0));
	if (surface.get() == NULL)
		throw std::runtime_error("SDL_ConvertSurface failed");
	return *this;
}

RenderTexture::~RenderTexture() { }


/**
 * Create a rendertexture with a width and height
 */
void RenderTexture::create(int width, int height) {
	surface = std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ARGB8888), SDL_FreeSurface);
	if (surface.get() == NULL)
		throw std::runtime_error("SDL_CreateRGBSurface failed");
}

/**
 * Create a rendertexture from a bmp file
 */
void RenderTexture::create(const std::string &path) {
	surface = std::shared_ptr<SDL_Surface>(SDL_LoadBMP(path.c_str()), SDL_FreeSurface);
	if (surface.get() == NULL)
		throw std::runtime_error("SDL_LoadBMP failed");
}

////////////////////////////////////////////////
/// Methods
////////////////////////////////////////////////

void RenderTexture::clear() {
	SDL_FillRect(surface.get(), NULL, SDL_MapRGB(surface->format, 0, 0, 0));
}

void RenderTexture::draw(RenderTexture &texture, int x, int y) {
	SDL_Rect rect = {x, y, texture.surface->w, texture.surface->h};
	SDL_BlitSurface(texture.surface.get(), NULL, surface.get(), &rect);
}

void RenderTexture::draw(SDL_Renderer*renderer, int x, int y) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface.get());
	SDL_Rect rect = {x, y, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

void RenderTexture::draw (SDL_Surface *surface, int x, int y) {
	SDL_Rect rect = {x, y, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, this->surface.get(), &rect);
}

void RenderTexture::draw_rect(SDL_Rect *rect, int red, int green, int blue) {
	SDL_FillRect(surface.get(), rect, SDL_MapRGB(surface->format, red, green, blue));
}

////////////////////////////////////////////////
///	Setters and Getters
////////////////////////////////////////////////

int RenderTexture::get_width() {
	return surface->w;
}

int RenderTexture::get_height() {
	return surface->h;
}
