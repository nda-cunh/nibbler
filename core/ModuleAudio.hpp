#include "../include/IAudioModule.hpp"
#include <iostream>
#include <dlfcn.h>

class ModuleAudio : public IAudioModule { 
	public:
		ModuleAudio() {
			handler = dlopen("./libaudio.so", RTLD_LAZY);
			if (handler == NULL)
				throw std::runtime_error("can't load libaudio.so");
			auto func = (IAudioModule*(*)())dlsym(handler, "load");
			if (func == NULL)
				throw std::runtime_error("can't dlsym \"load\" function");
			audio = func();
		};

		~ModuleAudio() {
			auto func = (void(*)(IAudioModule*))dlsym(handler, "unload");
			if (func != NULL)
				func(audio);
			if (dlclose(handler) != 0)
				std::cerr << "dlclose have an error" << std::endl;
		}

		void playSound(const SoundType &soundType) {
			audio->playSound(soundType);
		}
	private:
		IAudioModule *audio;
		void* handler;
};
