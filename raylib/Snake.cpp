#include "Snake.hpp"
#include "utils.hpp"
#include <vector>


/* ____ CONSTRUCTORS ____ */

Snake::Snake() : _positions(NULL) {}
Snake::Snake(std::deque<Position> *snake) : _positions(snake) {}
Snake::~Snake() {}

void Snake::update(const std::deque<Position> *snake) {
	_positions = snake;
}

static inline Rectangle getRect(const Position &a, const Position &b) {
	Position	first = a;
	Vector2		begin;
	Vector2		size;

	if (a.x > b.x || a.y > b.y)
		first = b;

	if (a.x != b.x) {
		size = {TILE_SIZE, TILE_SIZE - 2 * SHIFT};
		begin = {(first.x + 1.5f) * TILE_SIZE,
			(first.y + 2) * TILE_SIZE + (float)SHIFT};
	} else {
		size = {TILE_SIZE - 2 * SHIFT, TILE_SIZE};
		begin = {(first.x + 1) * TILE_SIZE + (float)SHIFT,
			(first.y + 2.5f) * TILE_SIZE};
	}
	return {begin.x, begin.y, size.x, size.y};
}

void Snake::draw() {
	auto pos = _positions->begin();
	auto prev = pos;
	Rectangle	rect;
	Color color;
	
	/* Draw body */
	color = GetColor(0x218821FF);
	for (++pos; pos != _positions->end(); ++pos) {
		rect= getRect(*pos, *prev);
		DrawRectangleRounded(rect, 0.4f, 10, color);
		++prev;
	}

	/* Draw head */
	pos = _positions->begin();
	color = GetColor(0x126612FF);
	DrawCircleV({TILE_SIZE * (pos->x + 1.5f), TILE_SIZE * (pos->y + 2.5f)},
			TILE_SIZE * 0.5f - SHIFT, color);
}



































