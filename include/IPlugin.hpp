#ifndef IPLUGIN_HPP
#define IPLUGIN_HPP
#include <deque>
#include "utils.hpp"

enum Event {
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ENTER, // enter-key
	CLOSE, // Alt+F4 or cross window
	F1,
	F2,
	F3,
};

enum Direction {
	Up,
	Down,
	Left,
	Right
};

class IPlugin {
	public:
		virtual void open(int, int) = 0;
		virtual void close() = 0;
		virtual void draw_snake(const std::deque<Position> &snake, Direction direction) = 0;
		virtual void draw_food(Position &position) = 0;
		virtual void draw_score(int n) = 0;
		virtual void draw_gameover() = 0;
		virtual void clear () = 0;
		virtual void display () = 0;
		virtual Event poll_event() = 0;
};
#endif
