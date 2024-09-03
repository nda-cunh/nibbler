#include "../include/IAudioModule.hpp"
#include <iostream>
#include <dlfcn.h>

class ModuleAudio : public IAudioModule { 
	public:
		/* ---- Constructors ---- */
		ModuleAudio();
		ModuleAudio(const ModuleAudio&);
		~ModuleAudio();

		/* ---- Coplien  ---- */
		ModuleAudio& operator=(const ModuleAudio&);

		/* ---- Methods ---- */
		void playSound(const SoundType &soundType);

	private:
		IAudioModule *audio;
		void* handler;
};
