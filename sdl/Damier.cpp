#include "Damier.hpp"

////////////////////////////////////////////////
/// Constructors and Destructor
////////////////////////////////////////////////

Damier::Damier() : tile_size(0), x(0), y(0) { }

Damier::Damier (const Damier &d): RenderTexture(){
	this->x = d.x;
	this->y = d.y;
	this->tile_size = d.tile_size;
	this->RenderTexture::operator=(d);
}

Damier &Damier::operator= (const Damier &d) {
	this->x = d.x;
	this->y = d.y;
	this->tile_size = d.tile_size;
	this->RenderTexture::operator=(d);
	return *this;
}

Damier::~Damier() { }

void Damier::create (int width, int height, int tile_size, int x, int y) {
	this->x = x;
	this->y = y;
	this->tile_size = tile_size;
	this->RenderTexture::create(width, height);
	init_damier();
}

////////////////////////////////////////////////
/// Methods
////////////////////////////////////////////////

/**
 * Initialize the damier on the surface
 */
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
