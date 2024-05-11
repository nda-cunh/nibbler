# ifndef PLUGIN_HPP
# define PLUGIN_HPP

#include <dlfcn.h>
#include <string>
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
		void clear() {
			game->clear();
		}
		void display() {
			game->display();
		}
		void draw_snake(const std::deque<Position> &queue, Direction direction) {
			game->draw_snake(queue, direction);
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
#endif
