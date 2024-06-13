#ifndef _AUDIOMODULE_HPP_
#define _AUDIOMODULE_HPP_

#include <string>
#include <SFML/Audio.hpp>
#include "../include/IAudioModule.hpp"

class AudioModule : public IAudioModule {
	public:
		AudioModule() {
			if (!buffer_up.loadFromFile("up.wav"))
				return;

			if (!buffer_down.loadFromFile("down.wav"))
				return;

			if (!buffer_left.loadFromFile("left.wav"))
				return;

			if (!buffer_right.loadFromFile("right.wav"))
				return;

			if (!buffer_eat.loadFromFile("eat.wav"))
				return;

			if (!buffer_dead.loadFromFile("dead.wav"))
				return;
		}

		void playSound(const SoundType &soundType) {

			switch (soundType) {
				case SoundType::UP:
					sound.setBuffer(buffer_up);
					break;
				case SoundType::DOWN:
					sound.setBuffer(buffer_down);
					break;
				case SoundType::LEFT:
					sound.setBuffer(buffer_left);
					break;
				case SoundType::RIGHT:
					sound.setBuffer(buffer_right);
					break;
				case SoundType::EAT:
					sound.setBuffer(buffer_eat);
					break;
				case SoundType::DEAD:
					sound.setBuffer(buffer_dead);
					break;
			}
			sound.play();
		}
		~AudioModule() {}

	private:
		sf::Sound sound;
		sf::SoundBuffer buffer_up;
		sf::SoundBuffer buffer_down;
		sf::SoundBuffer buffer_left;
		sf::SoundBuffer buffer_right;
		sf::SoundBuffer buffer_eat;
		sf::SoundBuffer buffer_dead;
};

#endif
