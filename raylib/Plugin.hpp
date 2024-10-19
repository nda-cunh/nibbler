#ifndef PLUGIN_RAYLIB_HPP
#define PLUGIN_RAYLIB_HPP

#include "../include/IPlugin.hpp"
#include "Game.hpp"
#include "GameOver.hpp"

class Plugin : public IPlugin {
	int 	_width;
	int 	_height;
	Game	_game;
	GameOver	_game_over;


	/* ---- Event ---- */
	Event	check_mouse_events(const Activity &act);

	public:
		/* ---- Coplien ---- */
		Plugin();
		Plugin(const Plugin &);
		virtual ~Plugin() override; 

		Plugin &operator=(const Plugin &rhs);

		/* ---- Plugin ---- */
		void open(int x, int y) override; 
		void close() override; 

		/* ---- Event ---- */
		Event poll_event(Activity current_activity) override;

		/* ---- Data ---- */
		void update_snake(const std::deque<Position> &snake) override; 
		void update_food(Position &pos) override; 
		void update_score(int n) override;
		void update_bestscore(int n) override;

		/* ---- Display ---- */
		void clear() override; 
		void display(const Activity act) override; 
};

#endif
