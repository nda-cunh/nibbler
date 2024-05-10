#include "animation.hpp"

Animation::Animation () {
	this->restart();
}

void Animation::time_ms (int ms) {
	this->ms = ms;
}

bool Animation::isElapsed () {
	auto t = this->getElapsedTime().asMilliseconds();
	if (t >= ms) {
		this->restart();
		return true;
	}
	return false;
}
