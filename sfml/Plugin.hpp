#ifndef PLUGIN_SFML_HPP
#define PLUGIN_SFML_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <stdexcept>
#include "../include/IPlugin.hpp"
#include "Snake.hpp"
#include "Apple.hpp"
#include "config.h"
#include "Background.hpp"
#include "Header.hpp"
#include "Gameover.hpp"

class Plugin : public IPlugin {
	std::shared_ptr<sf::RenderWindow>	window;
	std::shared_ptr<sf::RenderTexture>	texture_game;
	sf::RectangleShape 					dark_background;
	// Background
	Background	background;
	Header		header;
	// Activities
	GameOver	gameover;
	sf::Sprite	game;
	// Items
	Snake		snake;
	Apple		apple;


	/* ---- Event ---- */
	Event	handle_keyboard_event(sf::Event	event) ;
	Event	handle_mouse_event(const sf::Event &event, const Activity &act);
	void	handle_mouse_move(const Activity &act);

	void	update_game_mode(const Activity act);

	public:
		/* ---- Coplien ---- */
		Plugin();
		Plugin( const Plugin & );
		virtual ~Plugin();

		Plugin &operator=(const Plugin &rhs);

		/* ---- Plugin ---- */
		void open(int x, int y);
		void close();

		/* ---- Event ---- */
		Event poll_event(Activity act);

		/* ---- Data ---- */
		void update_snake(const std::deque<Position> &p1);
		void update_food(Position &position) ;
		void update_score(int score);
		void update_bestscore(int bestscore);
		void update_speed(int n);

		/* ---- Display ---- */
		void clear () ;
		void display (const Activity act) ;
};
#endif
