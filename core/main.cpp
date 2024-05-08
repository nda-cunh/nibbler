#include <iostream>
#include <string>
#include <dlfcn.h>
#include <unistd.h>
#include <time.h>

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

enum Direction {
	Left,
	Right,
	Up,
	Down
};

int	main(int ac, char **av)
{
	Plugin plugin("lib_nibbler_sfml.so");
	int x = 20; 
	int y = 20; 
	bool is_running = true;

	Direction direction = Up;
	clock_t tick = clock();
	Event event;
	while (is_running) {

		/* Event Part */
		auto event = plugin.poll_event();
		if (event == RIGHT)
			direction = Right;
		else if (event == LEFT)
			direction = Left;
		else if (event == UP)
			direction = Up;
		else if (event == DOWN)
			direction = Down;
		else if (event == CLOSE)
			is_running = false;
		// std::cout << event << std::endl;

		if (tick + 10000 < clock()) {
			if (direction == Left)
				x -= 5;
			if (direction == Right)
				x += 5;
			if (direction == Up)
				y -= 5;
			if (direction == Down)
				y += 5;
			tick = clock();
		}

		plugin.rect(x, y);
		plugin.iteration();
	}
	

	return (0);
}
