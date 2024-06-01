#include "Snake.hpp"
#include "utils.hpp"
#include <vector>

Snake::Snake() : _positions(NULL) {}
Snake::Snake(std::deque<Position> *snake) : _positions(snake) {}
Snake::~Snake() {}

void Snake::update(const std::deque<Position> *snake) {
	_positions = snake;
}

void Snake::draw() {
	auto pos = _positions->begin();
	auto prev = pos;
	Color color;
	
	color = GetColor(0x218821FF);
	for (++pos; pos != _positions->end(); ++pos) {
		DrawCircleV({TILE_SIZE * (pos->x + 1.5f), TILE_SIZE * (pos->y + 2.5f)}, TILE_SIZE * 0.5f - SHIFT, color);

		if (prev->x != pos->x) {
			if (prev->x < pos->x)
				DrawRectangle((prev->x + 1.5f) * TILE_SIZE,
						(prev->y + 2) * TILE_SIZE + SHIFT,
						TILE_SIZE,
						TILE_SIZE - 2 * SHIFT,
						color);
			else
				DrawRectangle((pos->x + 1.5f) * TILE_SIZE,
						(pos->y + 2) * TILE_SIZE + SHIFT,
						TILE_SIZE,
						TILE_SIZE - 2 * SHIFT,
						color);
		} else {
			if (prev->y < pos->y)
				DrawRectangle((prev->x + 1) * TILE_SIZE + SHIFT,
						(prev->y + 2.5f) * TILE_SIZE,
						TILE_SIZE - 2 * SHIFT,
						TILE_SIZE,
						color);
			else
				DrawRectangle((pos->x + 1) * TILE_SIZE + SHIFT,
						(pos->y + 2.5f) * TILE_SIZE,
						TILE_SIZE - 2 * SHIFT,
						TILE_SIZE,
						color);
		}
		++prev;
	}
	pos = _positions->begin();
	color = GetColor(0x126612FF);
	DrawCircleV({TILE_SIZE * (pos->x + 1.5f), TILE_SIZE * (pos->y + 2.5f)}, TILE_SIZE * 0.5f - SHIFT, color);
}



































