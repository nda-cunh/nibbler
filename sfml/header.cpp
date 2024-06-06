#include "header.hpp"

Header::Header () {

}

void Header::create(int width, int height) {
	this->setSize({(float)width, (float)height});
	this->setFillColor({74,117,44});
	texture = std::make_shared<sf::Texture>();
	font = std::make_shared<sf::Font>();
	if (font->loadFromFile("./sfml/Answer.ttf") == false)
		throw std::runtime_error("can't load Answer.bmp");
	text_score.setFont(*font);
	text_best.setFont(*font);
	if (texture->loadFromFile("./sfml/trophies.bmp") == false)
		throw std::runtime_error("can't load trophies.bmp");
	food.setTexture(*texture);
	best_score.setTexture(*texture);
	food.setTextureRect({0, 0, 80, 80});
	best_score.setTextureRect({80, 0, 80, 80});
	food.setScale({0.75, 0.75});
	best_score.setScale({0.75, 0.75});
	food.setPosition({20, 10});
	best_score.setPosition({140, 10});
	text_best.setPosition({200, 20});
	text_score.setPosition({80, 20});
}

void Header::update_score(int n) {
	char buffer[8];
	sprintf(buffer, "%d", n);
	if (buffer != text_score.getString())
		text_score.setString(std::string(buffer));
}

void Header::update_best_score(int n) {
	char buffer[8];
	sprintf(buffer, "%d", n);
	if (buffer != text_best.getString())
		text_best.setString(std::string(buffer));
}

void Header::draw_self (sf::RenderWindow &surface) {
	surface.draw(*this);
	surface.draw(best_score);
	surface.draw(food);
	surface.draw(text_best);
	surface.draw(text_score);
}
