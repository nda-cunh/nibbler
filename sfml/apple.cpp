#include "apple.hpp"
#include "config.h"

Apple::Apple () {
	Aapple.time_ms(500);
	texture = std::make_shared<sf::Texture>();
	if (texture->loadFromFile("./sfml/food.bmp") == false)
		throw std::runtime_error("can't load food.bmp");
	this->setTexture(*texture);
	this->setOrigin({static_cast<float>(texture->getSize().x / 2.0), static_cast<float>(texture->getSize().y / 2.0)});
}

void Apple::update_food(sf::RenderTexture &window, Position &position) {
	auto size = texture->getSize();
	if (Aapple.isElapsed())
		is_up = !is_up;

	// if (is_up && this->getScale().x <= 1.5)
		// this->scale({1.0001, 1.0001});
	// else if (this->getScale().x >= 0.8)
		// this->scale({0.9999, 0.9999});
	this->setPosition(position.x * TILE + size.x / 2, position.y * TILE + size.y / 2);
	window.draw(*this);
}

