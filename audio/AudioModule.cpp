#include "AudioModule.hpp"

AudioModule::AudioModule() {
	if (!buffer_up.loadFromFile("./audio/up.wav"))
		return;

	if (!buffer_down.loadFromFile("./audio/down.wav"))
		return;

	if (!buffer_left.loadFromFile("./audio/left.wav"))
		return;

	if (!buffer_right.loadFromFile("./audio/right.wav"))
		return;

	if (!buffer_eat.loadFromFile("./audio/eat.wav"))
		return;

	if (!buffer_dead.loadFromFile("./audio/dead.wav"))
		return;
}

void AudioModule::playSound(const SoundType &soundType) {

	switch (soundType) {
		case SoundType::UP:
			sound_up.setBuffer(buffer_up);
			sound_up.play();
			break;
		case SoundType::DOWN:
			sound_down.setBuffer(buffer_down);
			sound_down.play();
			break;
		case SoundType::LEFT:
			sound_left.setBuffer(buffer_left);
			sound_left.play();
			break;
		case SoundType::RIGHT:
			sound_right.setBuffer(buffer_right);
			sound_right.play();
			break;
		case SoundType::EAT:
			sound_eat.setBuffer(buffer_eat);
			sound_eat.play();
			break;
		case SoundType::DEAD:
			sound_dead.setBuffer(buffer_dead);
			sound_dead.play();
			break;
	}
}

AudioModule::~AudioModule() {

}
