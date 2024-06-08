#include "Plugin.hpp"
#include <stdexcept>

/* ____ CONSTRUCTORS ____ */
Plugin::Plugin (std::string so, int x, int y) {
	handler = dlopen(so.c_str(), RTLD_LAZY);
	if (handler == NULL)
		throw std::runtime_error("can't load " + so);
	auto func = (IPlugin*(*)())dlsym(handler, "load");
	if (func == NULL)
		throw std::runtime_error("can't dlsym \"load\" function");
	game = func();
	this->open(x, y);
}

Plugin::~Plugin(){
	this->close();
	auto func = (IPlugin*(*)())dlsym(handler, "unload");
	if (func != NULL)
		func();
	if (dlclose(handler) != 0)
		std::cerr << "dlclose have an error" << std::endl;
}

/* ____ LIB LOADING RELATED METHODS ____ */
void Plugin::open (int x, int y) {
	game->open(x, y);
}

void Plugin::close() {
	game->close();
}

/* ____ API RELATED METHODS ____ */
Event Plugin::poll_event() {
	return game->poll_event();
}

void Plugin::clear() {
	game->clear();
}

void Plugin::display() {
	game->display();
}

void Plugin::update_snake(const std::deque<Position> &queue, Direction direction) {
	game->update_snake(queue, direction);
}

void Plugin::update_food(Position &position) {
	game->update_food(position);
}

void Plugin::update_score(int n) {
	game->update_score(n);
}

void Plugin::update_bestscore(int n) {
	game->update_bestscore(n);
}

void Plugin::update_gameover() {
	game->update_gameover();
}

