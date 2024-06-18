#include "Plugin.hpp"


/* ____ COPLIEN ____ */

Plugin::Plugin() {}

Plugin::Plugin(const Plugin &o) {
	*this = o;
}

Plugin &Plugin::operator=(const Plugin &rhs){
	if (this == &rhs)
		return *this;
	this->width = rhs.width;
	this->height = rhs.height;
	this->_game = rhs._game;
	this->_menu = rhs._menu;
	return *this;
}

Plugin::~Plugin() {
	CloseWindow();
}


/* ____ PLUGIN ____ */
void Plugin::open(int x, int y) {
	width = (x + 2) * TILE_SIZE;
	height = (y + 3) * TILE_SIZE;
	_game = Game(x, y, TILE_SIZE);
	_menu = Menu(width, height, TILE_SIZE);
	SetTraceLogLevel(LOG_ERROR);
	InitWindow(width, height, "nibbler - raylib");
}

void Plugin::close() { 
}


/* ____ EVENT ____ */

Event Plugin::poll_event(Activity current_activity) {
	if (WindowShouldClose())
		return CLOSE;

	int key = 42;
	while (key != 0) {
		if (IsMouseButtonPressed(0)) {
			Activity	act = _menu.checkCollision(current_activity,
					GetMouseX(), GetMouseY());

			switch (act) {
				case ON_MENU:
					return CLICK_MENU;
				case ON_GAME:
					return CLICK_1P;
				default:
					break;
			}
		}
		key = GetKeyPressed();
		switch (key) {
			case KEY_LEFT:
				return LEFT;
			case KEY_RIGHT:
				return RIGHT;
			case KEY_UP:
				return UP;
			case KEY_DOWN:
				return DOWN;
			case KEY_ENTER:
				return ENTER;
			case KEY_ESCAPE:
				return CLOSE;
			case KEY_F1:
				return F1;
			case KEY_F2:
				return F2;
			case KEY_F3:
				return F3;
			case KEY_KP_ADD:
				return SPEED_UP;
			case KEY_KP_SUBTRACT:
				return SPEED_DOWN;
			default:
				break;
		}
	}
	return NONE;
}


/* ____ DATA ____ */

void Plugin::update_snake(const std::deque<Position> &snake, Direction direction) {
	(void) direction;
	_game.setSnake(snake);
}

void Plugin::update_food(Position &pos)  {
	_game.addFood(pos);
}

void Plugin::update_score(int n){
	_game.setScore(n);
}

void Plugin::update_bestscore(int n) {
	_game.setBestScore(n);
}

void Plugin::update_speed(int) {
}


/* ____ DISPLAY ____ */

void Plugin::clear() {
	_game.setIsOver(false);
	BeginDrawing();
	ClearBackground(BLACK);
}

void Plugin::display(const Activity act) {
	if (act != ON_MENU)
		_game.draw();

	_menu.draw(act);
	EndDrawing();
	_game.resetFood();
}
