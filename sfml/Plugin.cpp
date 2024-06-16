# include "Plugin.hpp"

/* ____ COPLIEN ____ */
Plugin::Plugin() {}

Plugin::Plugin(const Plugin &other) {
	*this = other;
}

Plugin::~Plugin() {}

Plugin	&Plugin::operator=(const Plugin &rhs){
	if (this == &rhs)
		return *this;
	window = rhs.window;
	texture_game = rhs.texture_game;
	dark_background = rhs.dark_background;
	background = rhs.background;
	gameover = rhs.gameover;
	header = rhs.header;
	game = rhs.game;
	menu = rhs.menu;
	snake = rhs.snake;
	apple = rhs.apple;
	return *this;
}


/* ____ PLUGIN ____ */

void Plugin::open(int x, int y){
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

void Plugin::close(){
	window->close();
}


/* ____ EVENT ____ */

Event	Plugin::handle_keyboard_event(sf::Event	event) {
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
		case sf::Keyboard::Subtract:
			return SPEED_DOWN;
		case sf::Keyboard::Add:
			return SPEED_UP;
		default:
			return NONE;
	}
}

Event	Plugin::handle_mouse_event(const sf::Event &event, const Activity &act) {
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

Event Plugin::poll_event(Activity act){
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


/* ____ DATA ____ */

void Plugin::update_snake(const std::deque<Position> &queue, Direction direction) {
	snake.update_snake(*texture_game, queue, direction);
}

void Plugin::update_food(Position &position) {
	apple.update_food (*texture_game, position);
}

void Plugin::update_score(int n) {
	gameover.setScore(n); 
	header.setScore(n);
}

void Plugin::Plugin::update_bestscore(int n) {
	gameover.setBestScore(n); 
	header.setBestScore(n);
}

void Plugin::clear () {
	texture_game->clear();
	window->clear(sf::Color(87, 138, 52));
	background.draw_self(*texture_game);
	header.draw_self(*window);
}

void Plugin::update_gameover() {
	// texture_game->draw(dark_background);
	// texture_game->draw(gameover);
}


/* ____ DISPLAY ____ */

void Plugin::display (const Activity act) {
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
