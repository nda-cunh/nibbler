#include "apple.hpp"
#include "config.h"


/* ____ CONSTRUCTORS & COPLIEN ____ */

Apple::Apple () {
	_texture = std::make_shared<sf::Texture>();
	if (_texture->loadFromFile("./sfml/food.bmp") == false)
		throw std::runtime_error("can't load food.bmp");
	this->setTexture(*_texture);
	this->setOrigin({_texture->getSize().x / 2.0f, _texture->getSize().y / 2.0f});
}

Apple::Apple (const Apple &other){ *this = other; }

Apple::~Apple() {}

Apple	&Apple::operator=(const Apple &rhs) { 
	if (this == &rhs)
		return *this;
	_is_up = rhs._is_up;
	_tileX = rhs._tileX;
	_tileY = rhs._tileY;
	_texture = rhs._texture;
	return *this;
}


/* ____ PUBLIC METHODS ____ */

void Apple::update_food(sf::RenderTexture &window, Position &position) {
	auto size = _texture->getSize();

	this->setPosition(position.x * TILE + size.x / 2.0,
			position.y * TILE + size.y / 2.0);
	window.draw(*this);
}

