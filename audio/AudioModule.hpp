#ifndef _AUDIOMODULE_HPP_
#define _AUDIOMODULE_HPP_

#include <string>
#include <SFML/Audio.hpp>
#include "../include/IAudioModule.hpp"

/**
 * This class is used to play sounds
 */
class AudioModule : public IAudioModule {
	public:
        AudioModule(const AudioModule& other);
        AudioModule& operator=(const AudioModule& other);

		/**
		 *  Construct a new Audio Module object
		 */
		AudioModule();

		/**
		 *  Play a sound
		 */
		void playSound(const SoundType &soundType) override;

		/**
		 *  Destroy the Audio Module object
		 */
		~AudioModule() override;

	private:
		sf::Sound sound_up;
		sf::Sound sound_down;
		sf::Sound sound_left;
		sf::Sound sound_right;
		sf::Sound sound_eat;
		sf::Sound sound_dead;

		sf::SoundBuffer buffer_up;
		sf::SoundBuffer buffer_down;
		sf::SoundBuffer buffer_left;
		sf::SoundBuffer buffer_right;
		sf::SoundBuffer buffer_eat;
		sf::SoundBuffer buffer_dead;
};

#endif
