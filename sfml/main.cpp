#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <stdexcept>
#include "../include/IPlugin.hpp"
#include "snake.hpp"
#include "apple.hpp"
#include "config.h"
#include "background.hpp"
#include "menu.hpp"
#include "gameover.hpp"

class Plugin : public IPlugin {
	private:
		std::shared_ptr<sf::RenderWindow> window;
		std::shared_ptr<sf::RenderTexture> texture_game;
		sf::Sprite game;
		Snake snake;
		Apple apple;
		Menu menu;
		Background background;
		GameOver gameover;
		sf::RectangleShape dark_background;
	public:
		virtual ~Plugin() {}
		void open(int x, int y) {
			window = std::make_shared<sf::RenderWindow>(sf::VideoMode(TILE * x + 80, TILE * y + 160), "Nibbler", sf::Style::Default ^ sf::Style::Resize);
			menu.create(window->getSize().x, 80);
			texture_game = std::make_shared<sf::RenderTexture>();
			texture_game->create(TILE * x, TILE * y);
			game.setTexture(texture_game->getTexture());
			game.setPosition(40, 120);
			background.init(window->getSize());
			gameover.setPosition(TILEf * x / 2.0, TILEf * y / 2.0);
			dark_background.setFillColor({0,0,0,150});
			dark_background.setSize({TILEf*x, TILEf*y});

		}

		void close(){
			window->close();
		}
		
		Event poll_event(Activity act){
			(void) act;
			sf::Event event;
			Event e = NONE;
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					e = CLOSE;
				} else if (event.type == sf::Event::KeyPressed) {
					switch (event.key.code) {
						case sf::Keyboard::Left:
							e = LEFT;
							break;
						case sf::Keyboard::Right:
							e = RIGHT;
							break;
						case sf::Keyboard::Up:
							e = UP;
							break;
						case sf::Keyboard::Down:
							e = DOWN;
							break;
						case sf::Keyboard::Enter:
							e = ENTER;
							break;
						case sf::Keyboard::Escape:
							e = CLOSE;
							break;
						case sf::Keyboard::F1:
							e = F1;
							break;
						case sf::Keyboard::F2:
							e = F2;
							break;
						case sf::Keyboard::F3:
							e = F3;
							break;
						default:
							e = NONE;
							break;
					}
				}
			}
			return e;
		}


		void update_snake(const std::deque<Position> &queue, Direction direction) {
			snake.update_snake(*texture_game, queue, direction);
		}

		void update_food(Position &position) {
			apple.update_food (*texture_game, position);
		}

		void update_score(int n) {
			gameover.update_score(n); 
			menu.update_score(n);
		}

		void update_bestscore(int n) {
			gameover.update_score_max(n); 
			menu.update_best_score(n);
		}

		void clear () {
			texture_game->clear();
			window->clear(sf::Color(87, 138, 52));
			background.draw_self(*texture_game);
			menu.draw_self(*window);
		}

		void update_gameover() {
			texture_game->draw(dark_background);
			texture_game->draw(gameover);
		}

		void display (const Activity act) {
			(void) act;
			gameover.update();
			texture_game->display();
			game.setTexture(texture_game->getTexture());

			window->draw(game);
			window->display();
		}
};


extern "C" {
	Plugin *game = NULL;

	IPlugin *load() {
		try {
			if (game == NULL)
				game = new Plugin();
		} catch (...) {
			return NULL;
		}
		return game;
	}
	
	void unload() {
		delete game;
	}
}
