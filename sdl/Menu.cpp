#include "Menu.hpp"

////////////////////////////////////////////////
/// Constructors and Destructor
////////////////////////////////////////////////

Menu::Menu() {
	text_title.set_text("SupraSnake");
	text_title.set_size_font(72);
	text_speed_value.set_text("0");
	text_speed.set_text("Speed");
	text_speed.set_size_font(30);
	speed = 0;
	width = 0;
	height = 0;
}

Menu::~Menu() {

}

void Menu::create (int width, int height) {
	this->width = width;
	this->height = height;
	button_play = std::make_shared<Button> ("Play", width / 2.0, 80);
	button_play->set_size_font(42);
	button_play->set_color(0, 0, 0);
	button_minus = std::make_shared<Button> ("-", 40, 40);
	button_minus->set_size_font(20);
	button_minus->set_color(0, 0, 0);
	button_plus = std::make_shared<Button> ("+", 40, 40);
	button_plus->set_size_font(20);
	button_plus->set_color(0, 0, 0);

	button_play->set_position(width / 2.0 - button_play->get_width() / 2.0, 150);
	button_minus->set_position(0, height - 84);
	button_plus->set_position(42, height - 42);
	text_speed_value.set_position(10, (height - 42) + 5);
	text_speed.set_position(42, (height - 84));
}

////////////////////////////////////////////////
/// Methods
////////////////////////////////////////////////

void Menu::draw (SDL_Renderer *renderer) {
	SDL_Rect rect;

	// draw a black screen on the menu
	rect = {0, 0, width, height};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
	text_title.draw(renderer, width / 2.0 - text_title.get_width() /2.0, 25);

	button_play->draw(renderer);
	button_minus->draw(renderer);
	button_plus->draw(renderer);
	text_speed_value.draw(renderer);
	text_speed.draw(renderer);
}

Event Menu::collide_click (int x, int y) {
	if (button_play->collide(x, y))
		return Event::CLICK_1P;
	else if (button_minus->collide(x, y))
		return Event::SPEED_DOWN;
	else if (button_plus->collide(x, y))
		return Event::SPEED_UP;
	return NONE;
}

void Menu::collide_hover (int x, int y) {
	button_play->unhover();
	button_minus->unhover();
	button_plus->unhover();

	if (button_play->collide(x, y))
		button_play->hover();
	else if (button_minus->collide(x, y))
		button_minus->hover();
	else if (button_plus->collide(x, y))
		button_plus->hover();
}
// 
////////////////////////////////////////////////
/// Setters and Getters
////////////////////////////////////////////////

void Menu::update_speed (int speed) {
	this->speed = speed;
	text_speed_value.set_text(std::to_string(speed));
}
