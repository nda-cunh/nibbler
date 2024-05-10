#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/IPlugin.hpp"
#include <memory>
#include <cmath>

class Animation : sf::Clock {
	public:
		Animation (int ms) {
			this->ms = ms;
			this->restart();
		}
		bool isElapsed () {
			auto t = this->getElapsedTime().asMilliseconds();
			if (t >= ms) {
				this->restart();
				return true;
			}
			return false;
		}
	private:
		sf::Int32 ms; 
};




class Snake {
	public:
		Snake () {
			texture_snake.loadFromFile("./sfml/snake.png");
			tounge.setTexture(texture_snake);
			eyes.setTexture(texture_snake);
		}
		void create (int x, int y) {
			tileX = x;
			tileY = y;
		}
		void draw_snake(sf::RenderWindow &window, const std::deque<Position> &snake, Direction direction) {

			// sf::RenderTexture head;
			// head.create(tileX, tileY);
			
			// eyes.setTextureRect({1, 15, 28, 28});
			// head.draw(eyes);
			// head.setSmooth(true);
			// head.display();
			// sf::Sprite sprite;
			// sprite.setTexture(head.getTexture());

			// window.draw(sprite);
			/* Draw Langue */
			/*
			auto boca = sf::Vector2f(snake[0].x * tileX, snake[0].y * tileY);

			switch (direction) {
				case Up:
					tounge.setRotation(-95.0f);
					boca.x += tileX/2;
					break;
				case Down:
					boca.x += tileX/2;
					boca.y += tileY;
					tounge.setRotation(95.f);
					break;
				case Left:
					boca.y += tileY/2;
					tounge.setRotation(180.f);
					break;
				case Right:
					boca.y += tileY/2;
					boca.x += tileX;
					tounge.setRotation(0.f);
					break;
				default:
					break;
			}
			tounge.setOrigin(10, 10);
			tounge.setTextureRect({884,129, 45, 21});
			tounge.setPosition(boca);
			window.draw(tounge);
			*/
			

			/* Draw Body */
			Position last = snake[0];
			auto color = sf::Color(78, 125, 246, 255);
				double size = tileX / 2.0 - 4;
			for (auto i : snake) {
				draw_segment (window, i, last, size, color);
				color.b -= 3;
				last = i;
				size -= 0.2;
			}


		}
	protected:
		inline void draw_segment(sf::RenderWindow& window, const Position begin, const Position end, double size, sf::Color color) {
			sf::CircleShape circle(size);
			circle.setFillColor(color);
			double diff = (tileX / 2.0) - size;

			Position b = {begin.x * tileX, begin.y * tileY};
			Position e = {end.x * tileX, end.y * tileY};
			while (b.x != e.x) {
				circle.setPosition(b.x + diff, b.y + diff);
				window.draw(circle);
				if (e.x > b.x)
					b.x++;
				else
					b.x--;
			}
			while (b.y != e.y) {
				circle.setPosition(b.x + diff, b.y + diff);
				window.draw(circle);
				if (e.y > b.y)
					b.y++;
				else
					b.y--;
			}
		}
	private:
		sf::Texture texture_snake;
		sf::Sprite tounge;
		sf::Sprite eyes;
		int tileX;
		int tileY;
};











class Plugin : public IPlugin {
	private:
		sf::RenderWindow *window;
		sf::Sprite Sdamier;
		sf::RenderTexture Tdamier;
		sf::Texture Tapple;
		sf::Sprite Sapple;
		Animation Aapple;
		Snake snake;
		int tileX;
		int tileY;
	public:
		Plugin() : Aapple(500){
		
		}
		void open(int x, int y){
			sf::ContextSettings settings;
			settings.antialiasingLevel = 8;

			window = new sf::RenderWindow(sf::VideoMode(800, 800), "Hello SFML", sf::Style::Default, settings);
			// window->setFramerateLimit(60);//TODO use real time
			tileX = 800 /x;
			tileY = 800 /y;
			snake.create(tileX, tileY);
			init_background();
			draw_background();
			
			// Tapple.setSmooth(true);
			Tapple.loadFromFile("./sfml/food.png");
			Sapple.setTexture(Tapple);
			Sapple.setOrigin({static_cast<float>(Tapple.getSize().x / 2.0), static_cast<float>(Tapple.getSize().y / 2.0)});
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
			static bool is_up = true;
			if (Aapple.isElapsed())
				is_up = !is_up;

			if (is_up && Sapple.getScale().x <= 1.5) {
				Sapple.scale({1.0001, 1.0001});
			}
			else if (Sapple.getScale().x >= 0.8)
				Sapple.scale({0.9999, 0.9999});
			auto size = Tapple.getSize();
			Sapple.setPosition(position.x * tileX + size.x/2, position.y * tileY + size.y/2);
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
