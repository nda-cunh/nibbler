#ifndef _IAUDIOMODULE_HPP_
#define _IAUDIOMODULE_HPP_

enum SoundType {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	EAT,
	DEAD
};

class IAudioModule {
public:
	virtual ~IAudioModule() = default;
	virtual void playSound(const SoundType &soundType) = 0;
};


#endif
