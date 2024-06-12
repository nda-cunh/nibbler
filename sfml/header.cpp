#include "header.hpp"


/* ____ CONSTRUCTORS & COPLIEN ____ */

Header::Header () {}
Header::Header (const Header &other) { *this = other; }
Header::~Header () {}


Header &Header::operator=(const Header &rhs) {
	if (this == &rhs)
		return *this;

	_icon_score = rhs._icon_score;
	_text_score = rhs._text_score;
	_text_best = rhs._text_best;
	_icon_best = rhs._icon_best;
	return *this;
} 


/* ____ INIT ____ */

void Header::create(int width, int height) {
	this->setSize({(float)width, (float)height});
	this->setFillColor({74,117,44});

	{
		_font = std::make_shared<sf::Font>();
		if (_font->loadFromFile("./sfml/Answer.ttf") == false)
			throw std::runtime_error("can't load Answer.bmp");
		_text_score.setFont(*_font);
		_text_score.setPosition({80, 20});

		_text_best.setFont(*_font);
		_text_best.setPosition({200, 20});
	}
	{
		_texture = std::make_shared<sf::Texture>();
		if (_texture->loadFromFile("./sfml/trophies.bmp") == false)
			throw std::runtime_error("can't load trophies.bmp");
		_icon_score.setTexture(*_texture);
		_icon_score.setPosition({20, 10});
		_icon_score.setScale({0.75, 0.75});
		_icon_score.setTextureRect({0, 0, 80, 80});

		_icon_best.setTexture(*_texture);
		_icon_best.setPosition({140, 10});
		_icon_best.setScale({0.75, 0.75});
		_icon_best.setTextureRect({80, 0, 80, 80});
	}
}


/* ____ ACCESSORS ____ */

void Header::setScore(int n) {
	std::string	n_str = std::to_string(n);

	if (n_str != _text_score.getString())
		_text_score.setString(n_str);
}

void Header::setBestScore(int n) {
	std::string	n_str = std::to_string(n);

	if (n_str != _text_best.getString())
		_text_best.setString(n_str);
}


/* ____ DRAW METHOD ____ */

void Header::draw_self (sf::RenderWindow &surface) {
	surface.draw(*this);
	surface.draw(_icon_best);
	surface.draw(_icon_score);
	surface.draw(_text_best);
	surface.draw(_text_score);
}
