#include "AudioModule.hpp"

extern "C" {
	IAudioModule *create() {
		return new AudioModule();
	}
	void destroy(IAudioModule *module) {
		delete module;
	}
}
