#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <stdexcept>
#include "../include/IPlugin.hpp"
#include "snake.hpp"
#include "apple.hpp"
#include "config.h"
#include "background.hpp"
#include "header.hpp"
#include "gameover.hpp"
#include "Menu.hpp"

class Plugin : public IPlugin {
	private:
		std::shared_ptr<sf::RenderWindow> window;
		std::shared_ptr<sf::RenderTexture> texture_game;
		sf::Sprite game;
		Snake snake;
		Apple apple;
		Menu	menu;
		Header header;
		Background background;
		GameOver gameover;
		sf::RectangleShape dark_background;
	public:
		virtual ~Plugin() {}
		void open(int x, int y){
			sf::ContextSettings settings;
			window = std::make_shared<sf::RenderWindow>(sf::VideoMode(TILE * x + 80, TILE * y + 160), "Nibbler", sf::Style::Default ^ sf::Style::Resize, settings);
			header.create(window->getSize().x, 80);
			texture_game = std::make_shared<sf::RenderTexture>();
			texture_game->create(TILE * x, TILE * y);
			game.setTexture(texture_game->getTexture());
			game.setPosition(40, 120);
			background.init(window->getSize());
			gameover.setPosition(TILEf * x / 2.0, TILEf * y / 2.0);
			dark_background.setFillColor({0,0,0,150});
			dark_background.setSize({TILEf*x, TILEf*y});
			menu = Menu(TILE * x + 80, TILE * y + 160);
		}

		void close(){
			window->close();
		}
		
		Event	handle_keyboard_event(sf::Event	event) {
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

		Event	handle_mouse_event(const sf::Event &event, const Activity &act) {
			if (event.mouseButton.button != sf::Mouse::Left)
				return NONE;
			sf::Vector2i position = sf::Mouse::getPosition(*this->window);
			Activity	act2 = menu.checkCollision(act, position.x, position.y);

			switch (act2) {
				case ON_MENU:
					return CLICK_MENU;
				case ON_GAME:
					return CLICK_1P;
				default:
					return NONE;
			}
		}

		Event poll_event(Activity act){
			sf::Event event;
			Event e = NONE;
			while (window->pollEvent(event)) {
				// Handle the event
				switch (event.type) {
					case sf::Event::Closed:
						return CLOSE;
					case sf::Event::KeyPressed:
						e = handle_keyboard_event(event);
						break;
					case sf::Event::MouseButtonPressed:
						e = handle_mouse_event(event, act);
						break;
					default:
						e = NONE;
						break;
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
			gameover.setScore(n); 
			header.setScore(n);
		}

		void update_bestscore(int n) {
			gameover.setBestScore(n); 
			header.setBestScore(n);
		}

		void clear () {
			texture_game->clear();
			window->clear(sf::Color(87, 138, 52));
			background.draw_self(*texture_game);
			header.draw_self(*window);
		}

		void update_gameover() {
			// texture_game->draw(dark_background);
			// texture_game->draw(gameover);
		}

		void display (const Activity act) {
			gameover.update();

			if (act == Activity::ON_GAME_OVER) {
				texture_game->draw(dark_background);
				texture_game->draw(gameover);
			}

			texture_game->display();
			game.setTexture(texture_game->getTexture());

			window->draw(game);
			menu.draw(act, *window);
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
