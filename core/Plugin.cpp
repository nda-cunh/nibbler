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
	 try {
        this->close();
        auto func = (void(*)(IPlugin*))dlsym(handler, "unload");
        if (func != nullptr) {
            func(game);
        } else {
            std::cerr << "can't dlsym \"unload\" function" << std::endl;
        }
        dlclose(handler);
    } catch (const std::exception& e) {
        std::cerr << "Error in Plugin destructor: " << e.what() << std::endl;
    }
}
		
Plugin::Plugin(const Plugin &other) {
	*this = other;
}

Plugin &Plugin::operator=(const Plugin &other) {
	if (&other != this) {
		game = other.game;
		handler = other.handler;
	}
	return (*this);
}

/* ____ LIB LOADING RELATED METHODS ____ */
void Plugin::open (int x, int y) {
	game->open(x, y);
}

void Plugin::close() {
	game->close();
}

/* ____ API RELATED METHODS ____ */
Event Plugin::poll_event(Activity current_activity) {
	return game->poll_event(current_activity);
}

void Plugin::clear() {
	game->clear();
}

void Plugin::display(const Activity act) {
	game->display(act);
}

void Plugin::update_snake(const std::deque<Position> &p1, const std::deque<Position> &p2) {
	game->update_snake(p1, p2);
}

void Plugin::update_food(Position &position) {
	game->update_food(position);
}

void Plugin::update_score(int score_p1, int score_p2) {
	game->update_score(score_p1, score_p2);
}

void Plugin::update_bestscore(int best_score_p1, int best_score_p2) {
	game->update_bestscore(best_score_p1, best_score_p2);
}

void Plugin::update_speed(int n) {
	game->update_speed(n);
}

