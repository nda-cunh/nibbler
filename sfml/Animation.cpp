#include "Animation.hpp"

/* ____ CONSTRUCTORS & COPLIEN ____ */
Animation::Animation() {
	_idx = 0;
	_timer = Timer();
	_freq = 2.0;
	_speed = 0.1;
}

Animation::Animation(const Animation &other) {
	*this = other;
}

Animation::~Animation() {}


Animation &Animation::operator=(const Animation &rhs) {
	if (this == &rhs)
		return *this;
	_frames = rhs._frames;
	_tex = rhs._tex;
	_idx = rhs._idx;
	_freq = rhs._freq;
	_speed = rhs._speed;
	_timer = rhs._timer;
	return *this;
}


/* ____ ACCESSORS ____ */

void Animation::setTexture(const sf::Texture &tex) { _tex = tex; }

/* Freq is the time between 2 animations */
void Animation::setFreq(double freq) { _freq = freq; }

/* Speed is the time between 2 animations frame */
void Animation::setSpeed(double speed) { _speed = speed; }

void Animation::addFrames(const std::vector<Rect> &v) {
	for (auto it = v.begin(); it != v.end(); it++)
		_frames.push_back(*it);
}

void Animation::addFrames(sf::Rect<int> first_frame, sf::Vector2<int> delta, int nb_frame) {
	Rect	r = {first_frame.left, first_frame.top,
		first_frame.width, first_frame.height};

	while (nb_frame--) {
		_frames.push_back(r);
		r.x += delta.x;
		r.y += delta.y;
	}
}

void Animation::clear( void ) {
	_frames.clear();
}

sf::Sprite	Animation::getFrame(float x, float y) {
	sf::Sprite		sprite(_tex);
	double			time_spent = _timer.elapsed();
	unsigned int	tmp_idx = static_cast<int>(time_spent / _speed);

	if (time_spent > _freq) {
		_idx = 0;
		_timer.reset();
	} else if (tmp_idx < _frames.size()) {
		_idx = tmp_idx;
	}

	Rect	r = _frames[_idx];
	sf::IntRect	sf_r = {r.x, r.y, r.w, r.h};

	sprite.setTextureRect(sf_r);
	sprite.setPosition(x, y);
	return sprite;
}
