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
	W_UP,
	A_LEFT,
	S_DOWN,
	D_RIGHT,
	CLICK_MENU,
	CLICK_1P,
	CLICK_2P,
	ENTER, // enter-key
	CLOSE, // Alt+F4 or cross window
	F1,
	F2,
	F3,
	SPEED_UP,
	SPEED_DOWN
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
		virtual void update_snake(const std::deque<Position> &p1, const std::deque<Position> &p2 = {}) = 0;
		virtual void update_food(Position &position) = 0;
		virtual void update_score(int score_p1, int score_p2 = 0) = 0;
		virtual void update_speed(int n) = 0;
		virtual void update_bestscore(int best_score_p1, int best_score_p2 = 0) = 0;
		virtual void clear () = 0;
		virtual void display (const Activity) = 0;
		virtual Event poll_event(const Activity) = 0;
};
#endif
