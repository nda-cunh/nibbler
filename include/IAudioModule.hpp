#ifndef _IAUDIOMODULE_HPP_
#define _IAUDIOMODULE_HPP_


class IAudioModule {
	public:
		enum SoundType {
			UP,
			DOWN,
			LEFT,
			RIGHT,
			EAT,
			DEAD
		};
		virtual ~IAudioModule() = default;
		virtual void playSound(const SoundType &soundType) = 0;
};


#endif
