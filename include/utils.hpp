#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>

struct Position {
	int x;
	int y;
	bool operator==(const Position o) const {
		return this->x == o.x && this->y == o.y;
	}
	bool operator==(Position o) {
		return this->x == o.x && this->y == o.y;
	}
};

struct Rect {
	int	x;
	int y;
	int w;
	int h;
};

#endif
