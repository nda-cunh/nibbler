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
	CLICK_MENU,
	CLICK_1P,
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
		virtual ~IPlugin() = default;
		virtual void open(int, int) = 0;
		virtual void close() = 0;
		virtual void update_snake(const std::deque<Position> &snake, Direction direction) = 0;
		virtual void update_food(Position &position) = 0;
		virtual void update_score(int n) = 0;
		virtual void update_bestscore(int n) = 0;
		virtual void update_gameover() = 0;
		virtual void clear () = 0;
		virtual void display (const Activity) = 0;
		virtual Event poll_event(const Activity) = 0;
};
#endif
