#include "Snake.hpp"
#include <raylib.h>

/* ____ CONSTRUCTORS & COPLIEN ____ */

Snake::Snake() : _positions(NULL) {}

Snake::Snake(const Snake &o) : _positions(NULL) {
	*this = o;
}

Snake::Snake(std::deque<Position> *snake) {
	_positions = snake;
}

Snake::~Snake() {}

Snake	&Snake::operator=(const Snake &rhs) {
	if (this == &rhs)
		return *this;
	_positions = rhs._positions;
	return *this;
}

void Snake::update(const std::deque<Position> *snake) {
	_positions = snake;
}


/* ____ DRAW ____ */

Rectangle getRect(const Position &a, const Position &b) {
	Position	first = a;
	Vector2		begin;
	Vector2		size;

	if (a.x > b.x || a.y > b.y)
		first = b;

	if (a.x != b.x) {
		size = {TILE_SIZE * 1.f, TILE_SIZE - 2 * SHIFT};
		begin = {(first.x + 1.5f) * TILE_SIZE,
			(first.y + 2) * TILE_SIZE + SHIFT};
	} else {
		size = {TILE_SIZE * 1.f - 2.f * SHIFT, TILE_SIZE * 1.f};
		begin = {(first.x + 1) * TILE_SIZE + SHIFT,
			(first.y + 2.5f) * TILE_SIZE};
	}
	return {begin.x, begin.y, size.x, size.y};
}

Position	Snake::draw() const{
	if (_positions == NULL)
		return {0, 0};
	auto pos  = _positions->begin();
	auto prev = pos;
	Rectangle	rect;
	Color 		color;

	/* Draw body */
	color = GetColor(0x315ec9ff);
	for (++pos; pos != _positions->end(); ++pos) {
		rect= getRect(*pos, *prev);
		DrawRectangleRounded(rect, 0.5f, 10, color);
		++prev;
	}

	/* Draw head */
	pos = _positions->begin();
	color = GetColor(0x4e7cf6ff);
	DrawCircleV({TILE_SIZE * (pos->x + 1.5f), TILE_SIZE * (pos->y + 2.5f)},
			TILE_SIZE * 0.5f - SHIFT, color);
	return *pos;
}
