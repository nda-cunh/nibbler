#ifndef PLUGIN_RAYLIB_HPP
#define PLUGIN_RAYLIB_HPP

#include "../include/IPlugin.hpp"
#include "Game.hpp"
#include "Menu.hpp"

class Plugin : public IPlugin {
	const int	TILE_SIZE = 32;
	int 	width;
	int 	height;

	Activity	_game_mode;
	Game		_game;
	Menu		_menu;
	GameOver	_gameover;

	void update_game_mode(const Activity act);

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
		void update_snake(const std::deque<Position> &snake, const std::deque<Position> &snake2 = {}); 
		void update_food(Position &pos) ; 
		void update_score(int score_p1, int score_p2 = 0);
		void update_bestscore(int best_score_p1, int best_score_p2 = 0); 
		void update_speed(int n); 

		/* ---- Display ---- */
		void clear(); 
		void display(const Activity act); 
};

#endif
