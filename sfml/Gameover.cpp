#include "Gameover.hpp"


/* ____ CONSTRUCTORS & COPLIEN ____ */

GameOver::GameOver() {
	{
		texture_gameover = std::make_unique<sf::Texture>();
		surface = std::make_unique<sf::RenderTexture>();

		if (texture_gameover->loadFromFile("./sfml/gameover.bmp") == false)
			throw std::runtime_error("can't load gameover.bmp");

		auto size = texture_gameover->getSize();

		surface->create(size.x, size.y + 60);
		this->setTexture(surface->getTexture());
		this->setOrigin(size.x / 2, size.y / 2);
		sprite_gameover.setTexture(*texture_gameover);
	}
	{
		if (_font.loadFromFile("./sfml/coolvetica.otf") == false)
			throw std::runtime_error("can't load coolvetica.otf");

		_text_score.setFont(_font);
		_text_score.setPosition(90, 175);
		_text_score.setFillColor(sf::Color::White);

		_text_best.setFont(_font);
		_text_best.setPosition(215, 175);
		_text_best.setFillColor(sf::Color::White);
	}
	{
		const auto	size = texture_gameover->getSize();
		const auto	spacing = 10;
		const auto	y_begin = size.y + 10;
		const float	big_ratio = 3.f / 5.f, small_ratio = 2.f / 5.f;

		_button_retry.setTxtSize(25);
		_button_retry.setRect(10, y_begin,
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

	}
}

GameOver::GameOver(const GameOver &other) { *this = other; }

GameOver::~GameOver() {
	texture_gameover.release();
	surface.release();
}

GameOver &GameOver::operator=( const GameOver &rhs ) {
	if (&rhs == this)
		return *this;
	sprite_gameover = rhs.sprite_gameover;
	_text_best = rhs._text_best;
	_text_score = rhs._text_score;
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
		return CLICK_1P;
	}
	return NONE;
}


/* ____ ACCESSORS ____ */

void GameOver::setBestScore(const int n) {
	std::string	n_str = std::to_string(n);

	if (n_str != _text_best.getString())
		_text_best.setString(n_str);
}

void GameOver::setScore(const int n) {
	std::string	n_str = std::to_string(n);

	if (n_str != _text_score.getString())
		_text_score.setString(n_str);
}


/* ____ DRAW UPDATE ____ */

void GameOver::update() {
	surface->clear({0,0,0,0});
	surface->draw(sprite_gameover);
	surface->draw(_text_score);
	surface->draw(_text_best);
	_button_menu.draw(*surface.get());
	_button_retry.draw(*surface.get());
	surface->display();
}
