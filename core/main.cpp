#include <iostream>
#include <string>
#include <dlfcn.h>
#include <unistd.h>

#include "../include/IGame.hpp"

class Plugin : public IPlugin {
	private:
		IPlugin* game;
		void* handler;
	public:
		~Plugin(){
			this->close();
			auto func = (IPlugin*(*)())dlsym(handler, "unload");
			func();
			dlclose(handler);
		}
		Plugin (std::string so) {
			handler = dlopen(so.c_str(), RTLD_LAZY);
			auto func = (IPlugin*(*)())dlsym(handler, "load");
			game = func();
			this->open();
		}

		void open () {
			game->open();
		}
		void close() {
			game->close();
		}

		/* API du jeu */
		Event poll_event() {
			return game->poll_event();
		}
		void rect (int x, int y) {
			game->rect(x, y);
		}
		void iteration() {
			game->iteration();
		}
};

int	main(int ac, char **av)
{
	Plugin plugin("lib_nibbler_sfml.so");
	int x = 20; 
	int y = 20; 
	bool is_running = true;

	Event event;
	while (is_running) {

		/* Event Part */
		auto event = plugin.poll_event();
		if (event == RIGHT)
			x++;
		else if (event == LEFT)
			x--;
		else if (event == UP)
			y--;
		else if (event == DOWN)
			y++;
		else if (event == CLOSE)
			is_running = false;
		// std::cout << event << std::endl;

		plugin.rect(x, y);
		plugin.iteration();
	}
	

	return (0);
}
