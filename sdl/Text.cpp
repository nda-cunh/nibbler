#include "Text.hpp"


Text::Text () {
	font = "Answer";
	size_font = 32;
	x = 0;
	y = 0;
	create (1, 1);
}

void Text::create (int width, int height) {
	surface = std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ARGB8888), SDL_FreeSurface);
	if (surface == NULL)
		throw std::runtime_error("SDL_CreateRGBSurface failed");
	cairo_surface = std::shared_ptr<cairo_surface_t>(cairo_image_surface_create_for_data(static_cast<unsigned char*>(surface->pixels), CAIRO_FORMAT_ARGB32, surface->w, surface->h, surface->pitch), cairo_surface_destroy);
	cairo_context = std::shared_ptr<cairo_t>(cairo_create(cairo_surface.get()), cairo_destroy);

}

void Text::update () {
	bool update = false;
	int w, h;
	get_text_size(w, h);
	if (w > surface->w)
		update = true;
	if (h > surface->h)
		update = true;

	if (update)
		create(w, h);
}

Text::Text (std::string str) : Text(){
	this->text = str;

	update();
}


Text::~Text () {
}

void Text::clear() {
	cairo_set_operator(cairo_context.get(), CAIRO_OPERATOR_CLEAR);
	cairo_paint(cairo_context.get());
	cairo_set_operator(cairo_context.get(), CAIRO_OPERATOR_OVER);
	cairo_set_antialias(cairo_context.get(), CAIRO_ANTIALIAS_GRAY);
}

void Text::update_text () {
	cairo_select_font_face(cairo_context.get(), font.c_str(), CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cairo_context.get(), size_font);
	cairo_set_source_rgb(cairo_context.get(), 1.0, 1.0, 1.0);

	cairo_text_extents_t extents;
	cairo_text_extents(cairo_context.get(), text.c_str(), &extents);

	double x = (surface->w - extents.width) / 2.0;
	double y = (surface->h + extents.height) / 2.0;
	cairo_move_to(cairo_context.get(), x, y);
	cairo_show_text(cairo_context.get(), text.c_str());
	cairo_set_antialias(cairo_context.get(), CAIRO_ANTIALIAS_BEST);
}

void Text::set_font (std::string font) {
	if (this->font != font) {
		this->font = font;
		update();
	}
}

void Text::set_size_font (int size) {
	if (size != size_font) {
		size_font = size;
		update();
	}
}

// get the size max of the text and return it
void Text::get_text_size (int &width, int &height) {
	cairo_select_font_face(cairo_context.get(), font.c_str(), CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cairo_context.get(), size_font);
	cairo_text_extents_t extents;
	cairo_text_extents(cairo_context.get(), text.c_str(), &extents);
	cairo_font_extents_t font_extents;
	cairo_font_extents(cairo_context.get(), &font_extents);

	width = extents.width;
	height = font_extents.height + font_extents.descent;
}

void Text::draw (SDL_Renderer *renderer, int px, int py) {
	clear();
	update_text();

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface.get());
	SDL_Rect rect = {px, py, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

void Text::draw (SDL_Renderer *renderer) {
	clear();
	update_text();

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface.get());
	SDL_Rect rect = {x, y, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

int Text::get_width () {
	return surface->w;
}

int Text::get_height () {
	return surface->h;
}

void Text::set_position (int x, int y) {
	this->x = x;
	this->y = y;
}

void Text::set_text (std::string str) {
	if (str != this->text) {
		this->text = str;
		update();
	}
}
