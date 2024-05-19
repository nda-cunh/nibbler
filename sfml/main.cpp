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
		sf::Event event;
	public:
		virtual ~Plugin() {}
		void open(int x, int y){
			sf::ContextSettings settings;
			settings.antialiasingLevel = 8;
			settings.stencilBits = 8;
			window = std::make_shared<sf::RenderWindow>(sf::VideoMode(TILE * x + 80, TILE * y + 160), "Hello SFML", sf::Style::Default ^ sf::Style::Resize, settings);
			menu.create(window->getSize().x, 80);
			window->setFramerateLimit(120);
			texture_game = std::make_shared<sf::RenderTexture>();
			texture_game->create(TILE*x, TILE*y);
			game.setTexture(texture_game->getTexture());
			game.setPosition(40, 120);
			background.init(window->getSize());
		}

		void close(){
			window->close();
		}
		
		Event poll_event(){

			window->pollEvent(event);
			if (event.type == sf::Event::Closed)
				return CLOSE;
			else if (event.type == sf::Event::KeyPressed) {
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
					case sf::Keyboard::Escape:
						return CLOSE;
					case sf::Keyboard::F1:
						return F1;
					case sf::Keyboard::F2:
						return F2;
					case sf::Keyboard::F3:
						return F3;
					default:
						return NONE;
				}
			}
			return NONE;
		}

		void update_snake(const std::deque<Position> &queue, Direction direction) {
			snake.update_snake(*texture_game, queue, direction);
		}

		void update_food(Position &position) {
			apple.update_food (*texture_game, position);
		}

		void update_score(int n) {
			menu.update_score(n);
		}

		void update_bestscore(int n) {
			menu.update_best_score(n);
		}

		void update_gameover() {

		}

		void clear () {
			window->clear(sf::Color(87, 138, 52));
			background.draw_self(*texture_game);
			menu.draw_self(*window);
		}

		void display () {

			texture_game->display();
			window->draw(game);
			window->display();
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
