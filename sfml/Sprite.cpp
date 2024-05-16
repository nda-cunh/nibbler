#include "Sprite.hpp"

Sprite::Sprite() {
	_idx = 0;
	_timer = Timer();
}

Sprite::~Sprite() {}

void Sprite::setFrames(std::vector<Rect> v) {
	_frames = v;
	_freq = 2.0;
	_speed = 0.1;
}

/* Freq is the time between 2 animations */
void Sprite::setFreq(double freq) { _freq = freq; }

/* Speed is the time between 2 animations frame */
void Sprite::setSpeed(double speed) { _speed = speed; }

Rect Sprite::getFrame( void ) {
	double			time_spent = _timer.elapsed();
	unsigned int	tmp_idx = static_cast<int>(time_spent / _speed);

	if (time_spent > _freq) {
		_idx = 0;
		_timer.reset();
	} else if (tmp_idx < _frames.size()) {
		_idx = tmp_idx;
	}
	return _frames[_idx];
}
