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

enum Direction {
	Left,
	Right,
	Up,
	Down
};

std::ostream &operator<<(std::ostream &o, const enum Direction d) {
	const std::string names[4] = {"Left", "Right", "Up", "Down"};
	o << names[d];
	return o;
}
#endif
