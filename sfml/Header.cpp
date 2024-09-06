#include "Header.hpp"


/* ____ CONSTRUCTORS & COPLIEN ____ */

Header::Header () : _is_multiplayer(false) {
	_font = nullptr;
	_texture = nullptr;
	_texture_snakes = nullptr;
}
Header::Header (const Header &other): sf::RectangleShape() { *this = other; }
Header::~Header () {}


Header &Header::operator=(const Header &rhs) {
	if (this == &rhs)
		return *this;

	for (int i = 0; i < 2; ++i) {
		_icon_score[i] = rhs._icon_score[i];
		_text_score[i] = rhs._text_score[i];
		_text_best[i] = rhs._text_best[i];
		_icon_best[i] = rhs._icon_best[i];
	}
	return *this;
} 

#include <iostream>

/* ____ INIT ____ */

void Header::create(int width, int height) {
	this->setSize({(float)width, (float)height});
	this->setFillColor({74,117,44});

	_font = std::make_shared<sf::Font>();
	if (_font->loadFromFile("./sfml/coolvetica.otf") == false)
		throw std::runtime_error("can't load coolvetica.otf");
	_texture = std::make_shared<sf::Texture>();
	if (_texture->loadFromFile("./sfml/trophies.bmp") == false)
		throw std::runtime_error("can't load trophies.bmp");
	_texture_snakes = std::make_shared<sf::Texture>();
	if (_texture_snakes->loadFromFile("./sfml/snakes.bmp") == false)
		throw std::runtime_error("can't load snakes.bmp");

	const float	w = this->getSize().x;
	const float shift_x = w * 0.58f;
	const sf::Vector2f	score_pos = {w / 12, 10}, best_pos = {w * 3 / 12, 10};

	// Texts
	_text_score[0].setFont(*_font);
	_text_score[0].setOrigin({-20, -10});
	_text_score[0].setPosition(score_pos);
	_text_score[1].setFont(*_font);
	_text_score[1].setOrigin({-20, -10});
	_text_score[1].setPosition(best_pos + sf::Vector2f{shift_x, 0});

	_text_best[0].setFont(*_font);
	_text_best[0].setOrigin({-20, -10});
	_text_best[0].setPosition(best_pos);
	_text_best[1].setFont(*_font);
	_text_best[1].setOrigin({-20, -10});
	_text_best[1].setPosition(score_pos + sf::Vector2f{shift_x, 0});

	// Icons
	_icon_score[0].setTexture(*_texture);
	_icon_score[0].setPosition(score_pos);
	_icon_score[0].setScale({0.45, 0.45});
	_icon_score[0].setTextureRect({0, 0, 80, 80});
	_icon_score[1].setTexture(*_texture);
	_icon_score[1].setPosition(best_pos + sf::Vector2f{shift_x, 0});
	_icon_score[1].setScale({0.45, 0.45});
	_icon_score[1].setTextureRect({0, 0, 80, 80});

	_icon_best[0].setTexture(*_texture);
	_icon_best[0].setPosition(best_pos);
	_icon_best[0].setScale({0.45, 0.45});
	_icon_best[0].setTextureRect({80, 0, 80, 80});
	_icon_best[1].setTexture(*_texture);
	_icon_best[1].setPosition(score_pos + sf::Vector2f{shift_x, 0});
	_icon_best[1].setScale({0.45, 0.45});
	_icon_best[1].setTextureRect({80, 0, 80, 80});

	// Snakes
	_icon_snake[0].setTexture(*_texture_snakes);
	_icon_snake[0].setPosition({w * 0.5f - 40, 10});
	_icon_snake[0].setOrigin({40, 10});
	_icon_snake[0].setTextureRect({0, 0, 80, 80});

	_icon_snake[1].setTexture(*_texture_snakes);
	_icon_snake[1].setPosition({w * 0.5f + 40, 10});
	_icon_snake[1].setOrigin({40, 10});
	_icon_snake[1].setTextureRect({80, 0, 80, 80});
}


/* ____ ACCESSORS ____ */


void Header::setScore(int n, int idx) {
	std::string	n_str = std::to_string(n);

	if (n_str == _text_score[idx].getString())
		return ;
	_text_score[idx].setString(n_str);
}

void Header::setBestScore(int n, int idx) {
	std::string	n_str = std::to_string(n);

	if (n_str == _text_best[idx].getString())
		return ;
	_text_best[idx].setString(n_str);
}

void Header::setGameMode(bool is_multiplayer) {
	_is_multiplayer = is_multiplayer;
}


/* ____ DRAW METHOD ____ */

void Header::draw_self (sf::RenderWindow &surface) {
	surface.draw(*this);

	for (int i = 0; i < 1 + _is_multiplayer; ++i) {
		surface.draw(_icon_best[i]);
		surface.draw(_icon_score[i]);
		surface.draw(_text_best[i]);
		surface.draw(_text_score[i]);
		if (_is_multiplayer)
			surface.draw(_icon_snake[i]);
	}
}
