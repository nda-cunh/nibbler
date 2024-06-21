#include "Button.hpp"

////////////////////////////////////////////////
/// Constructors and Destructor
////////////////////////////////////////////////

Button::Button () {
	background_color_hover = {76, 158, 249, 255};
	background_color = {76, 191, 248, 255};
	size_font = 21;
	color = {255, 255, 255, 255};
	x = 0;
	y = 0;
}


Button::Button (const std::string &str, int width, int height) : Button (){
	int w, h;

	x = 0;
	y = 0;
	this->text = str;
	create (width, height);
	get_text_size(w, h);
	if (w > width)
		width = w;
	if (h > height)
		height = h;
	if (surface->w < width || surface->h < height)
		create(width, height);
}

Button::~Button () {
}

/**
 * create the surface and the cairo context
 */
void Button::create (int width, int height) {
	surface = std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ARGB8888), SDL_FreeSurface);
	if (surface == NULL)
		throw std::runtime_error("SDL_CreateRGBSurface failed");
	cairo_surface = std::shared_ptr<cairo_surface_t>(cairo_image_surface_create_for_data(static_cast<unsigned char*>(surface->pixels), CAIRO_FORMAT_ARGB32, surface->w, surface->h, surface->pitch), cairo_surface_destroy);
	cairo_context = std::shared_ptr<cairo_t>(cairo_create(cairo_surface.get()), cairo_destroy);

}

////////////////////////////////////////////////
/// Methods
////////////////////////////////////////////////

/**
 * clear the surface
 */
void Button::clear() {
	cairo_set_operator(cairo_context.get(), CAIRO_OPERATOR_CLEAR);
	cairo_paint(cairo_context.get());
	cairo_set_operator(cairo_context.get(), CAIRO_OPERATOR_OVER);
	cairo_set_antialias(cairo_context.get(), CAIRO_ANTIALIAS_GRAY);
}

/**
 * draw the background of the surface
 */
void Button::update_background () {
	// set the color of the background if hover or not
	if (is_hover)
		cairo_set_source_rgb(cairo_context.get(),
				background_color_hover.r / 255.0,
				background_color_hover.g / 255.0,
				background_color_hover.b / 255.0);
	else
		cairo_set_source_rgb(cairo_context.get(),
				background_color.r / 255.0,
				background_color.g / 255.0,
				background_color.b / 255.0);

	// draw the background
	cairo_rectangle(cairo_context.get(), 0, 0, surface->w, surface->h);
	cairo_fill(cairo_context.get());
}

/**
 * draw the text on the surface
 */
void Button::update_text () {
	cairo_font_extents_t font_extents;
	cairo_text_extents_t extents;
	double px;
	double py;

	// set property of the text
	cairo_select_font_face(cairo_context.get(), "Coolvetica", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cairo_context.get(), size_font);
	cairo_set_source_rgb(cairo_context.get(), color.r / 255.0, color.g / 255.0, color.b / 255.0);

	// get the size of the text
	cairo_text_extents(cairo_context.get(), text.c_str(), &extents);
	cairo_font_extents(cairo_context.get(), &font_extents);

	px = (surface->w - extents.width) / 2.0;
	py = (surface->h + font_extents.ascent - font_extents.descent) / 2.0;

	// draw the text
	cairo_move_to(cairo_context.get(), px, py);
	cairo_show_text(cairo_context.get(), text.c_str());
}

/**
 * get the size max of the text and return it
 */
void Button::get_text_size (int &width, int &height) {
	cairo_text_extents_t extents;
	cairo_font_extents_t font_extents;

	// set property of the text
	cairo_select_font_face(cairo_context.get(), "Coolvetica", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cairo_context.get(), size_font);

	// get the size of the text
	cairo_text_extents(cairo_context.get(), text.c_str(), &extents);
	cairo_font_extents(cairo_context.get(), &font_extents);
	width = extents.width;
	height = extents.height;
}

/**
 * draw the text on the screen
 */
void Button::draw (SDL_Renderer *renderer) {
	clear();
	update_background();
	update_text();

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface.get());
	SDL_Rect rect = {x, y, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

bool Button::collide (int x, int y) {
	if (x >= this->x && x <= this->x + surface->w && y >= this->y && y <= this->y + surface->h)
		return true;
	return false;
}


////////////////////////////////////////////////
/// Setters and Getters
////////////////////////////////////////////////

void Button::set_color (int r, int g, int b) {
	color.r = r;
	color.g = g;
	color.b = b;
}

int Button::get_width () {
	return surface->w;
}

int Button::get_height () {
	return surface->h;
}

void Button::set_position (int x, int y) {
	this->x = x;
	this->y = y;
}

void Button::set_size_font (const int size_font) {
	this->size_font = size_font;
}

void Button::set_background_color (int r, int g, int b) {
	background_color.r = r;
	background_color.g = g;
	background_color.b = b;
}

void Button::set_background_color_hover (int r, int g, int b) {
	background_color_hover.r = r;
	background_color_hover.g = g;
	background_color_hover.b = b;
}

void Button::hover () {
	is_hover = true;
}

void Button::unhover () {
	is_hover = false;
}
