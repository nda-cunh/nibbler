#include "AudioModule.hpp"

AudioModule::AudioModule () {
	// Load all sound from file
	
	if (!buffer_up.loadFromFile("./audio/up.wav"))
		throw std::runtime_error("Error loading up.wav");

	if (!buffer_down.loadFromFile("./audio/down.wav"))
		throw std::runtime_error("Error loading down.wav");

	if (!buffer_left.loadFromFile("./audio/left.wav"))
		throw std::runtime_error("Error loading left.wav");

	if (!buffer_right.loadFromFile("./audio/right.wav"))
		throw std::runtime_error("Error loading right.wav");

	if (!buffer_eat.loadFromFile("./audio/eat.wav"))
		throw std::runtime_error("Error loading eat.wav");

	if (!buffer_dead.loadFromFile("./audio/dead.wav"))
		throw std::runtime_error("Error loading dead.wav");

	// Set the sound buffer to the sound object
	sound_right.setBuffer(buffer_right);
	sound_left.setBuffer(buffer_left);
	sound_down.setBuffer(buffer_down);
	sound_dead.setBuffer(buffer_dead);
	sound_eat.setBuffer(buffer_eat);
	sound_up.setBuffer(buffer_up);
}

void AudioModule::playSound (const SoundType &soundType) {

	switch (soundType) {
		case SoundType::UP:
			sound_up.play();
			break;

		case SoundType::DOWN:
			sound_down.play();
			break;

		case SoundType::LEFT:
			sound_left.play();
			break;

		case SoundType::RIGHT:
			sound_right.play();
			break;

		case SoundType::EAT:
			sound_eat.play();
			break;

		case SoundType::DEAD:
			sound_dead.play();
			break;
	}
}


AudioModule& AudioModule::operator= (const AudioModule& other) {
	if (this == &other)
		return *this;
	buffer_up = other.buffer_up;
	buffer_down = other.buffer_down;
	buffer_left = other.buffer_left;
	buffer_right = other.buffer_right;
	buffer_eat = other.buffer_eat;
	buffer_dead = other.buffer_dead;
	return *this;
}

AudioModule::AudioModule (const AudioModule& other) {
	*this = other;
}

AudioModule::~AudioModule() {

}
