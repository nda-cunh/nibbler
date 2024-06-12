#include "Plugin.hpp"

extern "C" {
	Plugin *game = NULL;

	IPlugin *load() {
		try {
			if (game == NULL)
				game = new Plugin();
		} catch (...) {
			return NULL;
		}
		return game;
	}

	void unload() {
		delete game;
	}
}
