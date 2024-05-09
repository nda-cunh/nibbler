#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/IPlugin.hpp"
#include <memory>
#include <cmath>


class Plugin : public IPlugin {
	private:
		sf::RenderWindow *window;
		sf::Sprite Sdamier;
		sf::RenderTexture Tdamier;
		sf::Texture Tapple;
		sf::Sprite Sapple;
		int tileX;
		int tileY;
	public:
		void open(int x, int y){
			window = new sf::RenderWindow(sf::VideoMode(800, 800), "Hello SFML");
			window->setFramerateLimit(60);
			tileX = 800 /x;
			tileY = 800 /y;
			init_background();
			draw_background();
			
			Tapple.loadFromFile("/nfs/homes/nda-cunh/Desktop/nibbler/sfml/food.png");
			Sapple.setTexture(Tapple);
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
	
		void draw_segment(const Position begin, const Position end, double size) {
			sf::CircleShape circle(size);
			circle.setPointCount(7);
			circle.setFillColor(sf::Color(78, 125, 246, 255));
			double diff = (tileX / 2.0) - size;

			Position b = {begin.x * tileX, begin.y * tileY};
			Position e = {end.x * tileX, end.y * tileY};
			while (b.x != e.x) {
				circle.setPosition(b.x + diff, b.y + diff);
				window->draw(circle);
				if (e.x > b.x)
					b.x++;
				else
					b.x--;
			}
			while (b.y != e.y) {
				circle.setPosition(b.x + diff, b.y + diff);
				window->draw(circle);
				if (e.y > b.y)
					b.y++;
				else
					b.y--;
			}
		}

		void draw_snake(std::deque<Position> snake) {

			Position last = snake[0];
			double size = tileX / 2.0;
			for (auto i : snake) {
				draw_segment(i, last, size);
				last = i;
				size -= 0.2;
			}
		}

		void draw_food(Position &position) {

			Sapple.setPosition(position.x * tileX, position.y * tileY);
			window->draw(Sapple);
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
