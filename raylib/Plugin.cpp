#include "Plugin.hpp"
#include "utils.hpp"

/* ____ COPLIEN ____ */

Plugin::Plugin() {}

Plugin::Plugin(const Plugin &o) {
	*this = o;
}

Plugin &Plugin::operator=(const Plugin &rhs){
	if (this == &rhs)
		return *this;
	this->_width = rhs._width;
	this->_height = rhs._height;
	this->_game = rhs._game;
	this->_game_over = rhs._game_over;
	return *this;
}

Plugin::~Plugin() {
	CloseWindow();
}


/* ____ PLUGIN ____ */
void Plugin::open(int x, int y) {
	_width = (x + 2) * TILE_SIZE;
	_height = (y + 3) * TILE_SIZE;
	_game = Game(x, y);
	_game_over = GameOver(_width, _height);
	SetTraceLogLevel(LOG_ERROR);
	InitWindow(_width, _height, "nibbler - raylib");
}

void Plugin::close() { 
}


/* ____ EVENT ____ */

Event	Plugin::check_mouse_events(const Activity &act){
	auto	pos = GetMousePosition();
	Event	e = NONE;

	if (act != ON_GAME_OVER)
		return e;
	else if (IsMouseButtonPressed(0))
		e = _game_over.checkCollision(pos.x, pos.y);
	else
		_game_over.checkHover(pos.x, pos.y);
	return e;
}


Event Plugin::poll_event(Activity current_activity) {
	if (WindowShouldClose())
		return CLOSE;

	int key = 42;
	while (key != 0) {
		Event mouse_event = check_mouse_events(current_activity);
		if (mouse_event != NONE)
			return mouse_event;
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
	_game.draw();
	if (act == ON_GAME_OVER)
		_game_over.draw();
	EndDrawing();
	_game.resetFood();
}
