#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "Button.hpp"
#include "Text.hpp"
#include "../include/IPlugin.hpp"

class Menu
{
	public:

		Menu();
		~Menu();
		void create (int width, int height);
		void draw (SDL_Renderer *renderer);
		Event collide_click (int x, int y);
		void collide_hover (int x, int y);
		void update_speed (int speed);

	private:
		Text text_title;
		std::shared_ptr<Button> button_play;
		std::shared_ptr<Button> button_plus;
		std::shared_ptr<Button> button_minus;
		int speed;
		int width;
		int height;
};

#endif
