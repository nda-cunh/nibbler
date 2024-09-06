# include "GameOver.hpp"
#include <raylib.h>

/* ____ CONSTRUCTOR & COPLIEN ____ */
GameOver::GameOver() : TILE_SIZE(32) {}

GameOver::GameOver(const GameOver &other): TILE_SIZE(other.TILE_SIZE) {
	*this = other;
}

GameOver::GameOver(int width, int height, int tile_size): TILE_SIZE(tile_size) {
	this->init_game_over(width, height);
	_size = {static_cast<float>(width), static_cast<float>(height)};
	_last_click.reset();
}

GameOver::~GameOver() {}

GameOver	&GameOver::operator=(const GameOver &rhs) {
	if (this == &rhs)
		return *this;
	_size = rhs._size;
	_last_click = rhs._last_click;
	_button_quit = rhs._button_quit;
	_button_restart = rhs._button_restart;
	return *this;
}

/* ____ SETTER ____ */

void	GameOver::setSpeed(int ) {
}

/* ____ INIT ACTIVITIES ____ */

void	GameOver::init_game_over(int width, int height) {
	Vector2		beg = {0.2f * width, 0.4f * height};
	Vector2	size = {(width - 2.f * beg.x) / 2.1f, TILE_SIZE * 1.2f};

	_button_restart.setTxt("Try Again");
	_button_restart.setTxtSize(20);
	_button_restart.setTxtColor(WHITE);
	_button_restart.setBgColor(GetColor(0x578a34ff));
	_button_restart.setClickEvent(CLICK_1P);
	_button_restart.setRect(beg.x, height - 0.8f * beg.y,
			size.x, size.y);
	_button_restart.centerText();

	_button_quit.setTxt("Quit");
	_button_quit.setTxtSize(20);
	_button_quit.setTxtColor(WHITE);
	_button_quit.setBgColor(GetColor(0x578a34ff));
	_button_quit.setClickEvent(Event::CLOSE);
	_button_quit.setRect(width - beg.x - size.x,
			height - 0.8f * beg.y, size.x, size.y);
	_button_quit.centerText();
}

Event	GameOver::checkCollision(Activity , float x, float y) {
	if (CheckCollisionPointRec({x, y}, _button_restart.getRect()))
		return _button_restart.getEvent();
	else if (CheckCollisionPointRec({x, y}, _button_quit.getRect()))
		return _button_quit.getEvent();
	return NONE;
}

void	GameOver::checkHover(Activity, float x, float y) {
	bool	has_hover = false;

	if (CheckCollisionPointRec({x, y}, _button_restart.getRect()))
		has_hover = true;
	else if (CheckCollisionPointRec({x, y}, _button_quit.getRect()))
		has_hover = true;

	if (has_hover)
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	else
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void	GameOver::draw() const{

	// Darker background
	DrawRectangle(0, 0, _size.x, _size.y, GetColor(0x00000084));

	// Draw Game Over
	{
		int width = _size.x, height = _size.y;
		auto beg = Vector2{0.2f * width, 0.4f * height};
		int txt_size = 0.07 * std::min(height, width);
		Rectangle	rect = {beg.x, beg.y,
			width - 2.f * beg.x, height - 2.f * beg.y};
		Vector2	offset;

		offset.x = (rect.width - 9 * txt_size / 1.5) / 2.f;
		offset.y = (rect.height - txt_size) / 2.f;

		DrawRectangleRounded(rect,
				0.3f, 10, GetColor(0x578a34ff));
		DrawText("GAME OVER", beg.x + offset.x, beg.y + offset.y,
				txt_size, WHITE);
	}

	// Draw Buttons
	_button_restart.draw();
	_button_quit.draw();
}
