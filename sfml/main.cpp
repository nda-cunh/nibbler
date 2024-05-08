#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/IGame.hpp"
#include <memory>


class Plugin : public IPlugin {
	private:
		sf::RenderWindow *window;
	public:
		~Plugin () {
		}
		Plugin () {
		}

		void open(){
			window = new sf::RenderWindow(sf::VideoMode(500, 500), "Hello SFML");
		}

		void close(){
			delete window;
		}
		
		Event poll_event(){
			sf::Event event;

			window->pollEvent(event);
			if (event.key.code == sf::Keyboard::Left)
				return LEFT;
			if (event.key.code == sf::Keyboard::Right)
				return RIGHT;
			if (event.key.code == sf::Keyboard::Up)
				return UP;
			if (event.key.code == sf::Keyboard::Down)
				return DOWN;
			if (event.type == sf::Event::Closed)
				return CLOSE;
			return NONE;
		}

		void rect(int x, int y){
			auto rec = sf::RectangleShape(sf::Vector2f(50, 50));
			rec.setPosition(x, y);
			window->draw(rec);
		}

		void iteration () {
			window->display();
			window->clear();
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
