#include "Text.hpp"

/*
 * Constructor
 *
 * Create a text surface with a size of 250x50 pixels
 */
Text::Text()
{
	create(250, 50);
	cairo_surface = cairo_image_surface_create_for_data((unsigned char *)surface->pixels,
			CAIRO_FORMAT_ARGB32, surface->w, surface->h, surface->pitch);
	cairo_context = cairo_create(cairo_surface);
	this->text = "";
	this->font = "Answer";
	this->color = {255, 255, 255, 255};
}

/* Destructor */
Text::~Text()
{
	cairo_destroy(cairo_context);
	cairo_surface_destroy(cairo_surface);
}

/*
 * Set the font to use
 * @param font The font to use
 */
void Text::set_font(const std::string &font)
{
	this->font = font;
}

/*
 * Set the text to display
 * @param text The text to display
 */
void Text::set_text(const std::string &text)
{
	this->text = text;
}

void Text::set_color(int r, int g, int b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

void Text::cairo_draw()
{
	cairo_set_operator(cairo_context, CAIRO_OPERATOR_CLEAR);
	cairo_paint(cairo_context);
	cairo_set_operator(cairo_context, CAIRO_OPERATOR_OVER);
	cairo_set_antialias(cairo_context, CAIRO_ANTIALIAS_GRAY);
	cairo_select_font_face(cairo_context, font.c_str(), CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cairo_context, 32);
	cairo_set_source_rgb(cairo_context, color.r, color.g, color.b);
	cairo_move_to(cairo_context, 10, 50);
	cairo_show_text(cairo_context, text.c_str());
}

/*
 * Draw the text on the renderer
 * @param renderer The renderer to draw on
 * @param x The x position of the text
 * @param y The y position of the text
 */
void Text::draw(SDL_Renderer *renderer, int x, int y)
{
	cairo_draw();
	RenderTexture::draw(renderer, x, y);
}

void Text::draw(SDL_Surface *surface, int x, int y)
{
	cairo_draw();
	RenderTexture::draw(surface, x, y);
}

void Text::draw(RenderTexture &texture, int x, int y)
{
	cairo_draw();
	RenderTexture::draw(texture, x, y);
}
