#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/IGame.hpp"
#include <memory>


class Game : public IGame {
	private:
		sf::RenderWindow *window;
	public:
		~Game () {
		}
		Game () {
		}

		void open(){
			window = new sf::RenderWindow(sf::VideoMode(500, 500), "Hello SFML");
		}

		void close(){
			delete window;
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

Game *game = NULL;

extern "C" {
	IGame *get_ptr () {
		game = new Game();
		return game;
	}
	
	void destroy_ptr() {
		delete game;
	}
}
