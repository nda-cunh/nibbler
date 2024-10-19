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
		Plugin() {};
		Plugin(const Plugin &other);
		Plugin &operator=(const Plugin &other);
		/* ---- Constructors ---- */
		virtual ~Plugin() override;
		Plugin (const std::string &so, int x, int y);

		/* ---- Lib loading related methods ---- */
		void open (int x, int y) override;
		void close() override;

		/* ---- API related methods ---- */
		Event poll_event(Activity current_activity) override;
		void clear() override;
		void display(const Activity) override;
		void update_snake(const std::deque<Position> &queue) override;
		void update_food(Position &position) override;
		void update_score(int n) override;
		void update_bestscore(int n) override;
};
#endif
