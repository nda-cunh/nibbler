#include "Plugin.hpp"

extern "C" {
	IPlugin *load() {
		return new Plugin();
	}

	void unload(Plugin *game) {
		delete game;
	}
}
