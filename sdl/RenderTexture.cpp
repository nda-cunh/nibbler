#include "RenderTexture.hpp"

RenderTexture::RenderTexture() {
}

RenderTexture &RenderTexture::operator=(const RenderTexture &other) {
	surface = SDL_ConvertSurface(other.surface, other.surface->format, 0);
	if (surface == NULL)
		throw std::runtime_error("SDL_ConvertSurface failed");
	return *this;
}

RenderTexture::RenderTexture(const RenderTexture &other) {
	surface = SDL_ConvertSurface(other.surface, other.surface->format, 0);
	if (surface == NULL)
		throw std::runtime_error("SDL_ConvertSurface failed");
}


void RenderTexture::create(int width, int height) {
	surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ARGB8888);
	if (surface == NULL)
		throw std::runtime_error("SDL_CreateRGBSurface failed");
}

// create from texture bmp
void RenderTexture::create(std::string path) {
	surface = SDL_LoadBMP(path.c_str());
	if (surface == NULL)
		throw std::runtime_error("SDL_LoadBMP failed");
}

void RenderTexture::clear() {
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
}

void RenderTexture::draw(RenderTexture &texture, int x, int y) {
	SDL_Rect rect = {x, y, texture.surface->w, texture.surface->h};
	SDL_BlitSurface(texture.surface, NULL, surface, &rect);
}

void RenderTexture::draw(SDL_Renderer*renderer, int x, int y) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect rect = {x, y, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

void RenderTexture::draw (SDL_Surface *surface, int x, int y) {
	SDL_Rect rect = {x, y, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, this->surface, &rect);
}

void RenderTexture::draw_rect(SDL_Rect *rect, int red, int green, int blue) {
	SDL_FillRect(surface, rect, SDL_MapRGB(surface->format, red, green, blue));
}

RenderTexture::~RenderTexture() {
	SDL_FreeSurface(surface);
}

int RenderTexture::get_width() {
	return surface->w;
}

int RenderTexture::get_height() {
	return surface->h;
}
