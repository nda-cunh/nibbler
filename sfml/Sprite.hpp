#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include "Timer.hpp"
#include "../include/utils.hpp"


class Sprite {
	private:
		int					_idx;
		double				_freq;
		double				_speed;
		std::vector<Rect>	_frames;
		Timer				_timer;
	public:
		Sprite();
		~Sprite();

		void setFrames(std::vector<Rect> v);
		void setFreq(double freq);
		void setSpeed(double speed);
		Rect getFrame();
};

#endif
