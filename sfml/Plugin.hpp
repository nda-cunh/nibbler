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
		void open(int x, int y) override;
		void close() override;

		/* ---- Event ---- */
		Event poll_event(Activity act) override;

		/* ---- Data ---- */
		void update_snake(const std::deque<Position> &p1) override;
		void update_food(Position &position) override ;
		void update_score(int score) override;
		void update_bestscore(int bestscore) override;

		/* ---- Display ---- */
		void clear ()  override;
		void display (const Activity act)  override;
};
#endif
