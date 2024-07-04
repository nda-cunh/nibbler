# include "Menu.hpp"

/* ____ CONSTRUCTOR & COPLIEN ____ */
Menu::Menu() :
	_TILE_SIZE(32)
{
	init_buttons();
}

Menu::Menu(const Menu &other):
	_TILE_SIZE(other._TILE_SIZE)
{
	*this = other;
}

Menu::Menu(int width, int height, int tile_size):
	_TILE_SIZE(tile_size),
	_WIDTH(width),
	_HEIGHT(height)
{
	init_buttons();
	_last_click.reset();
}

Menu::~Menu() {}

Menu	&Menu::operator=(const Menu &rhs) {
	if (this == &rhs)
		return *this;
	_last_click = rhs._last_click;
	_WIDTH = rhs._WIDTH;
	_HEIGHT = rhs._HEIGHT;
	_play_1p = rhs._play_1p;
	_play_2p = rhs._play_2p;
	_speed_up = rhs._speed_up;
	_speed_down = rhs._speed_down;
	return *this;
}

/* ____ SETTER ____ */

void	Menu::setSpeed(int speed) {
	_speed = speed;
}

/* ____ INIT ACTIVITIES ____ */

void	Menu::init_buttons() {
	Vector2		beg = {0.2f * _WIDTH, 0.13f * _HEIGHT};
	int			min = std::min(_WIDTH, _HEIGHT);

	_play_1p.setTxt("Play 1P");
	_play_1p.setTxtColor(BLACK);
	_play_1p.setTxtSize(0.08 * min);
	_play_1p.setRect(beg.x, 0.35 * _HEIGHT, _WIDTH * 3 / 5, 0.12 * _HEIGHT);
	_play_1p.setBgColor(GetColor(0x12CC12FF));
	_play_1p.setClickEvent(CLICK_1P);
	_play_1p.centerText();

	_play_2p.setTxt("Play 2P");
	_play_2p.setTxtColor(BLACK);
	_play_2p.setTxtSize(0.08 * min);
	_play_2p.setRect(beg.x, 0.55 * _HEIGHT, _WIDTH * 3 / 5, 0.12 * _HEIGHT);
	_play_2p.setBgColor(GetColor(0x12CC12FF));
	_play_2p.setClickEvent(CLICK_1P);
	_play_2p.centerText();

	beg = {0.3f * _WIDTH, 0.9f * _HEIGHT};

	_speed_down.setTxt("-");
	_speed_down.setTxtSize(0.07 * min);
	_speed_down.setTxtColor(BLACK);
	_speed_down.setRect(beg.x, beg.y, 0.07 * min, 0.07 * min);
	_speed_down.setBgColor(GetColor(0x12CC12FF));
	_speed_down.setOffSet(0.02 * min, 0.005 * min);
	_speed_down.setClickEvent(SPEED_DOWN);

	beg.x = _WIDTH - beg.x - 0.08 * min;

	_speed_up.setTxt("+");
	_speed_up.setTxtSize(0.07 * min);
	_speed_up.setTxtColor(BLACK);
	_speed_up.setRect(beg.x, beg.y, 0.07 * min, 0.07 * min);
	_speed_up.setBgColor(GetColor(0x12CC12FF));
	_speed_up.setOffSet(0.02 * min, 0.005 * min);
	_speed_up.setClickEvent(SPEED_UP);
}


Event	Menu::checkCollision(Activity act, float x, float y, bool click) {
	Event	e = NONE;

	if (CheckCollisionPointRec({x, y}, _play_1p.getRect()))
		e = CLICK_1P;
	else if (CheckCollisionPointRec({x, y}, _play_2p.getRect()))
		e = CLICK_2P;
	else if (CheckCollisionPointRec({x, y}, _speed_down.getRect()))
		e = SPEED_DOWN;
	else if (CheckCollisionPointRec({x, y}, _speed_up.getRect()))
		e = SPEED_UP;


	if (e != NONE)
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	else
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);

	if (click)
		_last_click.reset();

	return e;
}

void	Menu::checkHover(Activity act, float x, float y) {
	checkCollision(act, x, y, false);
}

void	Menu::draw(const Activity &act) {
	int			min = std::min(_WIDTH, _HEIGHT);

	ClearBackground(BLACK);
	DrawText("SupraSnake", _WIDTH / 2 - 0.3 * _WIDTH, 0.13 * _HEIGHT,
			0.11 * min, GetColor(0x12CC12FF));
	_play_1p.draw();
	_play_2p.draw();
	_speed_down.draw();
	_speed_up.draw();

	DrawText("Speed",
			_WIDTH / 2 - 0.1 * _WIDTH, 0.8 * _HEIGHT,
			0.07 * min, GetColor(0x12CC12FF));

	DrawText(std::string(6, 'o').c_str(),
			_WIDTH / 2 - 0.1 * _WIDTH, 0.9 * _HEIGHT,
			0.06 * min, GetColor(0x13131384));

	DrawText(std::string(_speed, 'o').c_str(),
			_WIDTH / 2 - 0.1 * _WIDTH, 0.9 * _HEIGHT,
			0.06 * min, GetColor(0x12CC12FF));
}
