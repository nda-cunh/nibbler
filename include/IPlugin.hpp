#include <deque>

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

struct Position {
	int x;
	int y;
};

class IPlugin {
	public:
		virtual void open(int, int) = 0;
		virtual void close() = 0;
		virtual void draw_snake(std::deque<Position>) = 0;
		virtual void draw_food(Position &position) = 0;
		virtual void draw_score(int n) = 0;
		virtual void draw_gameover() = 0;
		virtual void iteration () = 0;
		virtual Event poll_event() = 0;
};
