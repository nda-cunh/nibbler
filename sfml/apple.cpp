#include "apple.hpp"

Apple::Apple () {
	Aapple.time_ms(500);
	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("./sfml/food.png");
	this->setTexture(*texture);
	this->setOrigin({static_cast<float>(texture->getSize().x / 2.0), static_cast<float>(texture->getSize().y / 2.0)});
}

void Apple::init(int x, int y) {
	this->tileX = x;
	this->tileY = y;
}

void Apple::draw_food(sf::RenderWindow &window, Position &position) {
	auto size = texture->getSize();
	if (Aapple.isElapsed())
		is_up = !is_up;

	if (is_up && this->getScale().x <= 1.5)
		this->scale({1.0001, 1.0001});
	else if (this->getScale().x >= 0.8)
		this->scale({0.9999, 0.9999});
	this->setPosition(position.x * tileX + size.x / 2, position.y * tileY + size.y / 2);
	window.draw(*this);
}

