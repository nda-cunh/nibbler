#include <iostream>
#include <string>
#include <dlfcn.h>
#include <unistd.h>
#include <time.h>

#include "../include/IPlugin.hpp"

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
		Plugin (std::string so, int x, int y) {
			handler = dlopen(so.c_str(), RTLD_LAZY);
			auto func = (IPlugin*(*)())dlsym(handler, "load");
			game = func();
			this->open(x, y);
		}

		void open (int x, int y) {
			game->open(x, y);
		}
		void close() {
			game->close();
		}

		/* API du jeu */
		Event poll_event() {
			return game->poll_event();
		}
		void iteration() {
			game->iteration();
		}
		void draw_snake(std::deque<Position> queue) {
			game->draw_snake(queue);
		}
		void draw_food(Position &position) {
			game->draw_food(position);
		}
		void draw_score(int n) {
			game->draw_score(n);
		}
		void draw_gameover() {
			game->draw_gameover();
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
	Plugin plugin("lib_nibbler_sfml.so", 20, 20);
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

		plugin.iteration();
	}
	

	return (0);
}
