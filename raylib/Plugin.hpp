#ifndef PLUGIN_RAYLIB_HPP
#define PLUGIN_RAYLIB_HPP

#include "../include/IPlugin.hpp"
#include "Game.hpp"
#include "Menu.hpp"

class Plugin : public IPlugin {
	const int	TILE_SIZE = 32;
	int 	width;
	int 	height;
	Game	_game;
	Menu	_menu;

	public:

		/* ---- Coplien ---- */
		Plugin();
		Plugin(const Plugin &);
		virtual ~Plugin(); 

		Plugin &operator=(const Plugin &rhs);

		/* ---- Plugin ---- */
		void open(int x, int y); 
		void close(); 

		/* ---- Event ---- */
		Event poll_event(Activity current_activity);

		/* ---- Data ---- */
		void update_snake(const std::deque<Position> &snake, Direction direction); 
		void update_food(Position &pos) ; 
		void update_score(int n);
		void update_bestscore(int n); 
		void update_gameover(); 

		/* ---- Display ---- */
		void clear(); 
		void display(const Activity act); 
};

#endif
