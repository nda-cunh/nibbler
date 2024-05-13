#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/IPlugin.hpp"
#include <memory>

# define TILE_SIZE	30
# define BORDER		3

class Plugin : public IPlugin {
	private:
		sf::RenderWindow 	*window;
		Position			_size;

	public:
		virtual ~Plugin () {
		}
		Plugin () {
		}

		void open(int w, int h){
			_size = {w, h};
			window = new sf::RenderWindow(sf::VideoMode((w + 2) * TILE_SIZE, (h + 2) * TILE_SIZE), "Hello SFML");
			window->setFramerateLimit(60);
		}

		void close(){
			window->clear();
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
			if (event.key.code == sf::Keyboard::Enter)
				return ENTER;
			if (event.type == sf::Event::Closed)
				return CLOSE;
			if (event.key.code == sf::Keyboard::Escape)
				return CLOSE;
			if (event.key.code == sf::Keyboard::F1)
				return F1;
			if (event.key.code == sf::Keyboard::F2)
				return F2;
			if (event.key.code == sf::Keyboard::F3)
				return F3;
			return NONE;
		}

		void rect(int x, int y, const sf::Color &c = sf::Color::White) {
			auto rec = sf::RectangleShape(sf::Vector2f(TILE_SIZE - BORDER * 2, TILE_SIZE - BORDER * 2));
			rec.setPosition((x + 1) * TILE_SIZE + BORDER, (y + 1) * TILE_SIZE + BORDER);
			rec.setFillColor(c);
			window->draw(rec);
			}
		
		
		void update_snake(const std::deque<Position> &positions, Direction d) {
			(void) d;
			auto p = positions.begin();
			
			for (++p; p != positions.end(); p++) {
				this->rect(p->x, p->y, sf::Color::Green);
			}
			this->rect(positions.begin()->x, positions.begin()->y, sf::Color::Blue);
		}

		void update_food(Position &pos) {
			this->rect(pos.x, pos.y, sf::Color::Red);
		}

		void update_score(int n) {
			sf::Font	font;
			if (font.loadFromFile("./sfml_bis/pixel_emulator.ttf")) {
				sf::Text	text;
				char		score_str[20];

				score_str[sprintf(score_str, " Score %3d", n)] = 0;

				// select the font
				text.setFont(font); // font is a sf::Font

				// set the string to display
				text.setString(score_str);

				// set the character size
				text.setCharacterSize(20); // in pixels, not points!

				// set the color
				text.setFillColor(sf::Color::White);

				window->draw(text);
			}
		}

		void update_bestscore(int n) {
			sf::Font	font;
			if (font.loadFromFile("./sfml_bis/pixel_emulator.ttf")) {
				sf::Text	text;
				char		score_str[20];

				score_str[sprintf(score_str, "           Best %3d", n)] = 0;

				// select the font
				text.setFont(font); // font is a sf::Font

				// set the string to display
				text.setString(score_str);

				// set the character size
				text.setCharacterSize(20); // in pixels, not points!

				// set the color
				text.setFillColor(sf::Color::White);

				window->draw(text);
			}
		}

		void update_gameover() {
			for (int i = 0; i < _size.x; i++)
				for (int j = 0; j < _size.y; j++)
					this->rect(i, j, sf::Color(206, 0, 56, 60));
		}

		void clear() {
			window->clear();
			for (int i = 0; i < _size.x; i++)
				for (int j = 0; j < _size.y; j++)
					this->rect(i, j, sf::Color(21, 21, 21));
		}

		void display () {
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
