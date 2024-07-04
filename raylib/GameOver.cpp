# include "GameOver.hpp"

/* ____ CONSTRUCTOR & COPLIEN ____ */
GameOver::GameOver() : 
	_TILE_SIZE(0),
	_last_click()
{
	init_buttons();
	_last_click.reset();
}

GameOver::GameOver(const GameOver &other) :
	_TILE_SIZE(other._TILE_SIZE),
	_WIDTH(other._WIDTH),
	_HEIGHT(other._HEIGHT)
{
	*this = other;
	_last_click.reset();
}

GameOver::GameOver(int width, int height, int tile_size):
	_TILE_SIZE(tile_size),
	_WIDTH(width),
	_HEIGHT(height),
	_last_click()
{
	init_buttons();
	_last_click.reset();
}

GameOver::~GameOver() {}

GameOver	&GameOver::operator=(const GameOver &rhs) {
	if (this == &rhs)
		return *this;
	_last_click = rhs._last_click;
	_menu = rhs._menu;
	_WIDTH = rhs._WIDTH;
	_HEIGHT = rhs._HEIGHT;
	_try_again = rhs._try_again;
	return *this;
}


/* ____ INIT ACTIVITIES ____ */

void	GameOver::init_buttons() {
	Vector2		beg = {0.2f * _WIDTH, 0.4f * _HEIGHT};
	Vector2		size = {(_WIDTH - 2.f * beg.x) / 2.1f, _TILE_SIZE * 1.2f};

	_try_again.setTxt("Try Again");
	_try_again.setTxtSize(20);
	_try_again.setTxtColor(WHITE);
	_try_again.setBgColor(GetColor(0x578a34ff));
	_try_again.setClickEvent(CLICK_1P);
	_try_again.setRect(beg.x, _HEIGHT - 0.8f * beg.y, size.x, size.y);
	_try_again.centerText();

	_menu.setTxt("Menu");
	_menu.setTxtSize(20);
	_menu.setTxtColor(WHITE);
	_menu.setBgColor(GetColor(0x578a34ff));
	_menu.setClickEvent(CLICK_MENU);
	_menu.setRect(_WIDTH - beg.x - size.x, _HEIGHT - 0.8f * beg.y,
			size.x, size.y);
	_menu.centerText();
}

Event	GameOver::checkCollision(Activity act, float x, float y, bool click) {
	Event	e = NONE;

	if (CheckCollisionPointRec({x, y}, _try_again.getRect()))
		e = ENTER;
	else if (CheckCollisionPointRec({x, y}, _menu.getRect()))
		e = CLICK_MENU;

	if (e != NONE)
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	else
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);

	if (click)
		_last_click.reset();
	return e;
}

void	GameOver::checkHover(Activity act, float x, float y) {
	checkCollision(act, x, y, false);
}

void	GameOver::draw(const Activity &act) {
	auto min = std::min(_WIDTH, _HEIGHT);

	// Background
	DrawRectangleRec({0, 0, _WIDTH * 1.f, _HEIGHT * 1.f},
					GetColor(0x00000082));

	// Game Over Text
	DrawRectangleRec({0.2f * _WIDTH, 0.4f * _HEIGHT,
			0.6f * _WIDTH, 0.2f * _HEIGHT},
			GetColor(0x578a34ff));
	DrawText("Game Over", 0.3f * _WIDTH, 0.48f * _HEIGHT,
			0.08 * min, WHITE);

	_try_again.draw();
	_menu.draw();
}
