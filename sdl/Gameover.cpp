#include "Gameover.hpp"

////////////////////////////////////////////////
/// Constructors and Destructor
////////////////////////////////////////////////

Gameover::Gameover () : RenderTexture("./sdl/snake_sdl.bmp"),
	x_gameover(0),
	y_gameover(0),
	score(0),
	best_score(0),
	text(),
	button_retry(),
	button_menu()
{
}

void Gameover::createGameOver (int width, int height) {
	text.set_text(std::to_string(score));
	x_gameover = (- (this->get_width()/2.0) + width/2.0);
	y_gameover = (- (this->get_height()/2.0) + height/2.0);
	
	button_retry = std::make_shared<Button> ("Try Again", (this->get_width() / 3.0) *2, 50);
	button_menu = std::make_shared<Button> ("Menu", this->get_width() / 3.0 - 10, 50);
	
	button_retry->set_position (x_gameover, y_gameover + this->get_height() + 10);
	button_menu->set_position (x_gameover + button_retry->get_width() + 10, y_gameover + this->get_height() + 10);
}

Gameover::~Gameover () {

}

////////////////////////////////////////////////
/// Methods
////////////////////////////////////////////////

/**
 * Update the score and best score
 */
void Gameover::update_score (int score) {
	this->score = score;
}

void Gameover::update_bestscore (int best_score) {
	this->best_score = best_score;
}

/**
 * Draw the gameover screen
 */
void Gameover::draw (SDL_Renderer* renderer, int , int ) {
	// draw the gameover screen
	RenderTexture::draw (renderer, x_gameover, y_gameover);

	// Draw Score Text
	text.set_text(std::to_string(score));
	text.draw(renderer, x_gameover + 72, y_gameover + 150);

	// Draw BestScore Text
	text.set_text(std::to_string(best_score));
	text.draw(renderer, x_gameover + 217, y_gameover + 150);

	// Draw Buttons
	button_retry->draw(renderer);
	button_menu->draw(renderer);
}

void Gameover::onHover (int px, int py) {
	button_retry->unhover();
	button_menu->unhover();
	if (button_retry->collide(px, py))
		button_retry->hover();
	else if (button_menu->collide(px, py))
		button_menu->hover();
}

Event Gameover::onClick (int px, int py) {
	if (button_retry->collide(px, py))
		return Event::ENTER;
	else if (button_menu->collide(px, py))
		return Event::CLICK_MENU;
	return Event::NONE;
} 

////////////////////////////////////////////////
/// Setters and Getters
////////////////////////////////////////////////

void Gameover::get_position (int &x, int &y) {
	x = this->x_gameover;
	y = this->y_gameover;
}
