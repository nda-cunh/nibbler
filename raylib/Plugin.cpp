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
	this->_gameover = rhs._gameover;
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
	_gameover = GameOver(width, height, TILE_SIZE);
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
			Event	e;

			if (current_activity == ON_GAME_OVER)
				e = _gameover.checkCollision(current_activity,
					GetMouseX(), GetMouseY());
			else if (current_activity == ON_MENU)
				e = _menu.checkCollision(current_activity,
						GetMouseX(), GetMouseY());

			if (e != NONE)
				return e;
		} else {
			auto pos = GetMousePosition();
			if (current_activity == ON_GAME_OVER)
				_gameover.checkHover(current_activity, pos.x, pos.y);
			else if (current_activity == ON_MENU)
				_menu.checkHover(current_activity, pos.x, pos.y);
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

void Plugin::update_snake(const std::deque<Position> &snake, const std::deque<Position> &snake2) {
	(void) snake2;
	_game.setSnake(snake);
}

void Plugin::update_food(Position &pos)  {
	_game.addFood(pos);
}

void Plugin::update_score(int score_p1, int score_p2){
	(void) score_p2;
	_game.setScore(score_p1);
}

void Plugin::update_bestscore(int best_score_p1, int best_score_p2) {
	(void) best_score_p2;
	_game.setBestScore(best_score_p1);
}

void Plugin::update_speed(int speed) {
	_menu.setSpeed(speed);
}


void Plugin::update_game_mode(const Activity act) {
	const bool is_multiplayer = act == Activity::ON_GAME_2P;

	if (act == this->_game_mode)
		return ;
	if (act != ON_GAME_OVER) {
		this->_game_mode = act;
		this->_game.init_background(is_multiplayer);
	}
}


/* ____ DISPLAY ____ */

void Plugin::clear() {
	_game.setIsOver(false);
	BeginDrawing();
	ClearBackground(BLACK);
}

void Plugin::display(const Activity act) {
	if (act == ON_MENU)
		_menu.draw(act);
	else {
		update_game_mode(act);
		_game.draw();
		if (act == ON_GAME_OVER)
			_gameover.draw(act);
	}
	EndDrawing();
	_game.resetFood();
}
