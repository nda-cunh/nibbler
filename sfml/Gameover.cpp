#include "Gameover.hpp"


/* ____ CONSTRUCTORS & COPLIEN ____ */

GameOver::GameOver() : _is_multiplayer(false){
	surface = std::make_unique<sf::RenderTexture>();

	texture_gameover = std::make_unique<sf::Texture>();
	if (texture_gameover->loadFromFile("./sfml/gameover.bmp") == false)
		throw std::runtime_error("can't load gameover.bmp");

	texture_gameover_2p = std::make_unique<sf::Texture>();
	if (texture_gameover_2p->loadFromFile("./sfml/gameover_2P.bmp") == false)
		throw std::runtime_error("can't load gameover_2P.bmp");

	if (_font.loadFromFile("./sfml/coolvetica.otf") == false)
		throw std::runtime_error("can't load coolvetica.otf");
	
	{
		_text_score[0].setFont(_font);
		_text_score[0].setPosition(100, 160);
		_text_score[0].setFillColor(sf::Color(0xe0e6fbff));
		_text_score[1].setFont(_font);
		_text_score[1].setPosition(100, 195);
		_text_score[1].setFillColor(sf::Color(0xf8dc92ff));

		_text_best[0].setFont(_font);
		_text_best[0].setPosition(226, 160);
		_text_best[0].setFillColor(sf::Color(0xe0e6fbff));
		_text_best[1].setFont(_font);
		_text_best[1].setPosition(226, 195);
		_text_best[1].setFillColor(sf::Color(0xf8dc92ff));
	}

	{
		auto size = texture_gameover->getSize();

		surface->create(size.x, size.y + 60);
		this->setTexture(surface->getTexture());
		this->setOrigin(size.x / 2.0, size.y / 2.0);
		sprite_gameover[0].setTexture(*texture_gameover);
		sprite_gameover[1].setTexture(*texture_gameover_2p);
	}

}

GameOver::GameOver(const GameOver &other) { *this = other; }

GameOver::~GameOver() {
}

GameOver &GameOver::operator=( const GameOver &rhs ) {
	if (&rhs == this)
		return *this;
	for (int i = 0; i < 2; i++) {
		_text_score[i] = rhs._text_score[i];
		_text_best[i] = rhs._text_best[i];
		sprite_gameover[i] = rhs.sprite_gameover[i];
	}
	_font = rhs._font;
	_button_menu = rhs._button_menu;
	_button_retry = rhs._button_retry;
	return *this;
}


/* ____ MOUSE EVENT ____ */

Event	GameOver::collides(int x, int y) {
	x -= this->getPosition().x;
	x += this->getOrigin().x;
	y -= this->getPosition().y;
	y += this->getOrigin().y;

	// Reset hover state
	_button_menu.setHover(false);
	_button_retry.setHover(false);

	// Check if the mouse is hovering over a button
	if (_button_menu.getRect().contains(x, y)) {
		_button_menu.setHover(true);
		return CLICK_MENU;
	} else if (_button_retry.getRect().contains(x, y)) {
		_button_retry.setHover(true);
		return ENTER;
	}
	return NONE;
}


/* ____ ACCESSORS ____ */

inline static void	centerTextHorizontally(sf::Text &text) {
	auto center = text.getGlobalBounds().getSize() / 2.f;
	auto localBounds = center + text.getLocalBounds().getPosition();

	text.setOrigin({localBounds.x, 0});
}

void GameOver::setBestScore(const int n, int idx) {
	std::string	n_str = std::to_string(n);

	if (n_str == _text_best[idx].getString())
		return ;
	// Set the score text
	_text_best[idx].setString(n_str);
	centerTextHorizontally(_text_best[idx]);
}

void GameOver::setScore(const int n, int idx) {
	std::string	n_str = std::to_string(n);

	if (n_str == _text_score[idx].getString())
		return ;
	// Set the score text
	_text_score[idx].setString(n_str);
	centerTextHorizontally(_text_score[idx]);
}

void GameOver::setGameMode(bool is_multiplayer) {
	_is_multiplayer = is_multiplayer;
}


void GameOver::setPosition(const float x, const float y) {
	const auto	size = texture_gameover->getSize();
	const auto	spacing = 20;
	auto		y_begin = size.y + 10;
	const float	big_ratio = 3.f / 5.f, small_ratio = 2.f / 5.f;

	if (y * 2 / TILEf <= 13)
		y_begin = size.y - 70;

	_button_retry.setTxtSize(25);
	_button_retry.setRect(spacing, y_begin,
			size.x * big_ratio - 2.f * spacing, 50);
	_button_retry.setBgColor(sf::Color(0x4dc1f9ff));
	_button_retry.setTxtColor(sf::Color::White);
	_button_retry.setClickEvent(CLICK_1P);
	_button_retry.setTxt("Try Again");

	_button_menu.setTxtSize(25);
	_button_menu.setRect(size.x * big_ratio, y_begin,
			size.x * small_ratio - spacing, 50);
	_button_menu.setBgColor(sf::Color(0x4dc1f9ff));
	_button_menu.setTxtColor(sf::Color::White);
	_button_menu.setClickEvent(CLICK_MENU);
	_button_menu.setTxt("Menu");
	sf::Sprite::setPosition(x, y);
}


/* ____ DRAW UPDATE ____ */

void GameOver::update() {
	surface->clear({0,0,0,0});
	
	surface->draw(sprite_gameover[_is_multiplayer]);
	surface->draw(_text_score[0]);
	surface->draw(_text_best[0]);
	if (_is_multiplayer) {
		surface->draw(_text_score[1]);
		surface->draw(_text_best[1]);
	}
	_button_menu.draw(*surface.get());
	_button_retry.draw(*surface.get());
	surface->display();
}
