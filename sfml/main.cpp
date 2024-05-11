#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/IPlugin.hpp"
#include <memory>
#include "snake.hpp"
#include "apple.hpp"
#include "config.h"
#include "background.hpp"
#include "menu.hpp"

class Plugin : public IPlugin {
	private:
		std::shared_ptr<sf::RenderWindow> window;
		std::shared_ptr<sf::RenderTexture> texture_game;
		sf::Sprite game;
		Snake snake;
		Apple apple;
		Menu menu;
		Background background;
	public:
		virtual ~Plugin() {}
		void open(int x, int y){
			sf::ContextSettings settings;
			settings.antialiasingLevel = 8;

			window = std::make_shared<sf::RenderWindow>(sf::VideoMode(TILE * x + 80, TILE * y + 160), "Hello SFML", sf::Style::Default, settings);
			menu.create(window->getSize().x, 80);
			window->setFramerateLimit(60);
			texture_game = std::make_shared<sf::RenderTexture>();
			texture_game->create(TILE*x, TILE*y);
			game.setTexture(texture_game->getTexture());
			game.setPosition(40, 120);
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
			snake.draw_snake(*texture_game, queue, direction);
		}

		void draw_food(Position &position) {
			apple.draw_food (*texture_game, position);
		}

		void draw_score(int n) {
			menu.draw_score(n);
		}

		void draw_gameover() {

		}


		void draw_background() {
			background.draw_self(*texture_game);
			menu.draw_self(*window);
		}

		void iteration () {
			texture_game->display();
			window->draw(game);
			window->display();
			window->clear(sf::Color(87, 138, 52));
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
