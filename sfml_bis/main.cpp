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
		~Plugin () {
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
			return NONE;
		}

		void rect(int x, int y, const sf::Color &c = sf::Color::White) {
			auto rec = sf::RectangleShape(sf::Vector2f(TILE_SIZE - BORDER * 2, TILE_SIZE - BORDER * 2));
			rec.setPosition((x + 1) * TILE_SIZE + BORDER, (y + 1) * TILE_SIZE + BORDER);
			rec.setFillColor(c);
			window->draw(rec);
		}
		
		
		void draw_snake(const std::deque<Position> &positions, Direction d) {
			auto p = positions.begin();
			
			for (++p; p != positions.end(); p++) {
				this->rect(p->x, p->y, sf::Color::Green);
			}
			this->rect(positions.begin()->x, positions.begin()->y, sf::Color::Blue);
		}

		void draw_food(Position &pos) {
			this->rect(pos.x, pos.y, sf::Color::Red);
		}

		void draw_score(int n) {


		}

		void draw_gameover() {
			sf::Text	text;
			// Load the font from the URL
			sf::Font font;
			font.loadFromFile("./sfml_bis/game_paused.otf");
			text.setFont(font); // font is a sf::Font
			text.setString("Game Over!");
			text.setCharacterSize(100); // in pixels, not points!
			text.setFillColor(sf::Color::White);
			text.setStyle(sf::Text::Bold);
			text.setPosition({100, 20});
			sf::Text	text2;
			// Load the font from the URL
			text2.setFont(font); // font is a sf::Font
			text2.setString("Press [ Enter ]\n To play again");
			text2.setCharacterSize(50); // in pixels, not points!
			text2.setFillColor(sf::Color::White);
			text2.setStyle(sf::Text::Bold);
			text2.setPosition({150, 400});

			window->draw(text);
			window->draw(text2);
		}

		void clear() {
			window->clear();
		}

		void display () {
			window->display();
			for (int i = 0; i < _size.x; i++)
				for (int j = 0; j < _size.y; j++)
					this->rect(i, j, sf::Color(21, 21, 21));
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
