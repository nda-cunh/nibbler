#include "Plugin.hpp"

extern "C" {
	IPlugin *load() {
		return new Plugin();
	}

	void unload(IPlugin *game) {
		delete game;
	}
}
