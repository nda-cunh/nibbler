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
	snake_p1 = rhs.snake_p1;
	snake_p2 = rhs.snake_p2;
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
		case sf::Keyboard::A:
			return A_LEFT;
		case sf::Keyboard::D:
			return D_RIGHT;
		case sf::Keyboard::W:
			return W_UP;
		case sf::Keyboard::S:
			return S_DOWN;
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

Event	Plugin::handle_mouse_event(const sf::Event &event, const Activity &act) {
	if (event.mouseButton.button != sf::Mouse::Left)
		return NONE;
	sf::Vector2i	pos = sf::Mouse::getPosition(*this->window);

	switch (act) {
		case Activity::ON_GAME_OVER:
			return gameover.collides(pos.x - 40, pos.y - 120);
			break;
		case Activity::ON_MENU:
			return menu.collides(pos.x, pos.y);
			break;
		default:
			break;
	}
	return NONE;
}

void	Plugin::handle_mouse_move(const sf::Event &e, const Activity &act) {
	sf::Vector2f	game_shift = game.getPosition();
	sf::Vector2i	pos = sf::Mouse::getPosition(*this->window);

	switch (act) {
		case Activity::ON_GAME_OVER:
			gameover.collides(pos.x - game_shift.x, pos.y - game_shift.y);
			break;
		case Activity::ON_MENU:
			menu.collides(pos.x, pos.y);
			break;
		default:
			break;
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
			case sf::Event::MouseMoved:
				handle_mouse_move(event, act);
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

void Plugin::update_snake(const std::deque<Position> &p1, const std::deque<Position> &p2) {
	snake_p1.update_snake(*texture_game, p1);
	if (p2.size() > 0)
		snake_p2.update_snake(*texture_game, p2);
}

void Plugin::update_food(Position &position) {
	apple.update_food (*texture_game, position);
}

void Plugin::update_score(int score_p1, int score_p2) {
	gameover.setScore(score_p1); 
	header.setScore(score_p1);
}

void Plugin::update_speed(int speed) {
	this->menu.setSpeed(speed);
}

void Plugin::Plugin::update_bestscore(int best_score_p1, int best_score_p2) {
	gameover.setBestScore(best_score_p1); 
	header.setBestScore(best_score_p1);
}

void Plugin::clear () {
	texture_game->clear();
	window->clear(sf::Color(87, 138, 52));
	background.draw_self(*texture_game);
	header.draw_self(*window);
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
	if (act == Activity::ON_MENU)
		menu.draw(*window);
	window->display();
}
