#include "apple.hpp"
#include "config.h"

Apple::Apple () {
	texture = std::make_shared<sf::Texture>();
	if (texture->loadFromFile("./sfml/food.bmp") == false)
		throw std::runtime_error("can't load food.bmp");
	this->setTexture(*texture);
	this->setOrigin({static_cast<float>(texture->getSize().x / 2.0), static_cast<float>(texture->getSize().y / 2.0)});
}

void Apple::update_food(sf::RenderTexture &window, Position &position) {
	auto size = texture->getSize();

	this->setPosition(position.x * TILE + size.x / 2.0, position.y * TILE + size.y / 2.0);
	window.draw(*this);
}

