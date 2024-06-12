#include "Damier.hpp"

Damier::Damier() {
	this->x = 0;
	this->y = 0;
	this->tile_size = 0;
}

void Damier::create (int width, int height, int tile_size, int x, int y) {
	this->x = x;
	this->y = y;
	this->tile_size = tile_size;
	this->RenderTexture::create(width, height);
	init_damier();
}

Damier::~Damier() {
}

void Damier::init_damier () {
	this->clear();
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			if ((i + j) % 2 == 0) {
				SDL_Rect rect = {i * tile_size, j * tile_size, tile_size, tile_size};
				this->draw_rect(&rect, 162, 209, 73);
			} else {
				SDL_Rect rect = {i * tile_size, j * tile_size, tile_size, tile_size};
				this->draw_rect(&rect, 170, 215, 81);
			}
		}
	} 
}
