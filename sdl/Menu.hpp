#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "Button.hpp"
#include "Text.hpp"
#include "../include/IPlugin.hpp"

class Menu
{
	public:
		Menu() {
			text_title.set_text("SupraSnake");
			text_title.set_size_font(64);
		}
		
		~Menu() {

		}

		void create (int width, int height) {
			this->width = width;
			this->height = height;
			button_play = std::make_shared<Button> ("Play", width / 2.0, 80);
			button_play->set_size_font(42);
			button_play->set_color(0, 0, 0);
		}

		void draw (SDL_Renderer *renderer) {
			// draw a black screen on the menu	
			SDL_Rect rect;
			rect = {0, 0, width, height};
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect);
			text_title.draw(renderer, width / 2.0 - text_title.get_width() /2.0, 25);
			button_play->set_position(width / 2.0 - button_play->get_width() / 2.0, 150);
			button_play->draw(renderer);
		}

		Event collide_click (int x, int y) {
			if (button_play->collide(x, y)) {
				return Event::CLICK_1P;
			}
			return NONE;
		}

		void collide_hover (int x, int y) {
			button_play->unhover();
			if (button_play->collide(x, y)) {
				button_play->hover();
			}
		}

	private:
		Text text_title;
		std::shared_ptr<Button> button_play;
		int width;
		int height;
};

#endif
