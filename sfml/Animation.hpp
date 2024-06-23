#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Timer.hpp"
#include "../include/utils.hpp"


class Animation {
	std::vector<Rect>	_frames;
	sf::Texture			_tex;
	int					_idx;
	double				_freq;
	double				_speed;
	Timer				_timer;

	public:
		/* ---- Constructors & Coplien ---- */
		Animation();
		Animation(const Animation &);
		~Animation();

		Animation &operator=(const Animation &);

		/* ---- Accessors ---- */
		void setFreq(double freq);
		void setTexture(const sf::Texture &);
		void setSpeed(double speed);

		void addFrames(const std::vector<Rect> &v);
		void addFrames(sf::Rect<int> first_frame, sf::Vector2<int> delta, int nb_frame);

		sf::Sprite	getFrame(float x, float y);
};

#endif
