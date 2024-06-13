#include "AudioModule.hpp"

extern "C" {
	IAudioModule *load() {
		return new AudioModule();
	}
	void unload (IAudioModule *module) {
		delete module;
	}
}
