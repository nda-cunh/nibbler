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
		/* ---- Constructors ---- */
		~Plugin();
		Plugin (std::string so, int x, int y);

		/* ---- Lib loading related methods ---- */
		void open (int x, int y);
		void close();

		/* ---- API related methods ---- */
		Event poll_event();
		void clear();
		void display();
		void update_snake(const std::deque<Position> &queue, Direction direction);
		void update_food(Position &position);
		void update_score(int n);
		void update_bestscore(int n);
		void update_gameover();
};
#endif
