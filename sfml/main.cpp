#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/IPlugin.hpp"
#include <memory>
#include <cmath>
#include "snake.hpp"
#include "apple.hpp"
#include "config.h"
#include "background.hpp"

class Plugin : public IPlugin {
	private:
		std::shared_ptr<sf::RenderWindow> window;
		Snake snake;
		Apple apple;
		Background background;
	public:
		virtual ~Plugin() {}
		void open(int x, int y){
			sf::ContextSettings settings;
			settings.antialiasingLevel = 8;

			window = std::make_shared<sf::RenderWindow>(sf::VideoMode(TILE * x, TILE * y), "Hello SFML", sf::Style::Default, settings);
			// window->setFramerateLimit(60);//TODO use real time
			background.init(window->getSize());
			draw_background();
		}

		void close(){
			window->close();
		}
		
		Event poll_event(){
			sf::Event event;

			window->pollEvent(event);
			if (event.type == sf::Event::Closed)
				return CLOSE;
			switch(event.key.code) {
				case sf::Keyboard::Left :
					return LEFT;
				case sf::Keyboard::Right:
					return RIGHT;
				case sf::Keyboard::Up:
					return UP;
				case sf::Keyboard::Down:
					return DOWN;
				case sf::Keyboard::Enter:
					return ENTER;
				default:
					return NONE;
			}
			return NONE;
		}

		void draw_snake(const std::deque<Position> &queue, Direction direction) {
			snake.draw_snake(*window, queue, direction);
		}

		void draw_food(Position &position) {
			apple.draw_food (*window, position);
		}

		void draw_score(int n) {

		}

		void draw_gameover() {

		}


		void draw_background() {
			background.draw_self(*window);
		}

		void iteration () {
			window->display();
			window->clear();
			draw_background();
		}
};


extern "C" {
	Plugin *game = NULL;

	IPlugin *load() {
		if (game == NULL)
			game = new Plugin();
		return game;
	}
	
	void unload() {
		delete game;
	}
}
