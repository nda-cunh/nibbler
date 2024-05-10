#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/IPlugin.hpp"
#include <memory>
#include <cmath>
#include "snake.hpp"
#include "apple.hpp"

class Plugin : public IPlugin {
	private:
		sf::RenderWindow *window;
		sf::Sprite Sdamier;
		sf::RenderTexture Tdamier;
		Snake snake;
		Apple apple;
		int tileX;
		int tileY;
	public:
		Plugin(){
		
		}
		void open(int x, int y){
			sf::ContextSettings settings;
			settings.antialiasingLevel = 8;

			window = new sf::RenderWindow(sf::VideoMode(800, 800), "Hello SFML", sf::Style::Default, settings);
			// window->setFramerateLimit(60);//TODO use real time
			tileX = 800 /x;
			tileY = 800 /y;
			apple.init(tileX, tileY);
			snake.init(tileX, tileY);
			init_background();
			draw_background();
			
		}

		void init_background() {
			Tdamier.create(800, 800);
			float width = tileX;
			float height = tileY;
			int num_tiles_x = window->getSize().x / width;
			int num_tiles_y = window->getSize().y / height;

			sf::RectangleShape rectangle({width, height});
			for (int i = 0; i < num_tiles_x; ++i) {
				for (int j = 0; j < num_tiles_y; ++j) {
					if ((i + j) % 2 == 0) {
						rectangle.setFillColor(sf::Color(162, 209, 73)); // couleur de rectangle1
					} else {
						rectangle.setFillColor(sf::Color(170, 215, 81)); // couleur de rectangle2
					}
					rectangle.setPosition(i * width, j * height);
					Tdamier.draw(rectangle);
				}
			}
			Tdamier.display();
			Sdamier.setTexture(Tdamier.getTexture());
		}

		void close(){
			window->close();
			delete window;
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
			window->draw(Sdamier);
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
