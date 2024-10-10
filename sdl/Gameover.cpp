#include "Gameover.hpp"

////////////////////////////////////////////////
/// Constructors and Destructor
////////////////////////////////////////////////

Gameover::Gameover () : RenderTexture() {
	create("./sdl/snake_sdl.bmp");
	score = 0;
	best_score = 0;
	x_gameover = 0;
	y_gameover = 0;
}

Gameover::Gameover(const Gameover &g) : RenderTexture(g) {
	*this = g;
}

Gameover	&Gameover::operator= (const Gameover &g) {
	if (this != &g) {
		score = g.score;
		best_score = g.best_score;
		x_gameover = g.x_gameover;
		y_gameover = g.y_gameover;
		text = g.text;
	}
	return *this;
}

void Gameover::createGameOver (int width, int height, int tile_y) {
	text.set_text(std::to_string(score));
	x_gameover = (- (this->get_width()/2.0) + width/2.0);
	y_gameover = (- (this->get_height()/2.0) + height/2.0);
	button_retry = std::make_shared<Button> ("Try Again", ((get_width() / 3.0) * 2) - 10 , 50);
	button_quit = std::make_shared<Button> ("Quit", ((get_width() / 3.0) * 1) - 10 , 50);
	printf("%d\n", (height/ 32));
	if (tile_y < 12) {
		button_retry->set_position (x_gameover, y_gameover + get_height() - 60);
		button_quit ->set_position (x_gameover + ((get_width() / 3.0)* 2), y_gameover + get_height() - 60);
	}
	else {
		button_retry->set_position (x_gameover, y_gameover + get_height() + 10);
		button_quit ->set_position (x_gameover + ((get_width() / 3.0)* 2), y_gameover + get_height() + 10);
	}
}

void Gameover::hover (int x, int y) {
	button_retry->unhover();
	if (button_retry->collide(x, y))
		button_retry->hover();
	button_quit->unhover();
	if (button_quit->collide(x, y))
		button_quit->hover();
}

int Gameover::collide (int x, int y) {
	if (button_retry->collide (x, y))
		return 1;
	if (button_quit->collide (x, y))
		return 2;
	return 0;
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
void Gameover::draw (SDL_Renderer* renderer, int px, int py) {
	(void) px;
	(void) py;

	// draw the gameover screen
	RenderTexture::draw (renderer, x_gameover, y_gameover);

	// Draw Score Text
	text.set_text(std::to_string(score));
	text.draw(renderer, x_gameover + 72, y_gameover + 150);

	// Draw BestScore Text
	text.set_text(std::to_string(best_score));
	text.draw(renderer, x_gameover + 217, y_gameover + 150);

	// Draw Retry Button
	button_retry->draw(renderer);
	button_quit->draw(renderer);

}

////////////////////////////////////////////////
/// Setters and Getters
////////////////////////////////////////////////

void Gameover::get_position (int &x, int &y) {
	x = this->x_gameover;
	y = this->y_gameover;
}
