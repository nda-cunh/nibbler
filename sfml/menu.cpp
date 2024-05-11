#include "menu.hpp"

Menu::Menu () {

}

void Menu::create(int width, int height) {
	printf("menu create\n");
	this->setSize({(float)width, (float)height});
	this->setFillColor({74,117,44});
	texture = std::make_shared<sf::Texture>();
	font = std::make_shared<sf::Font>();
	font->loadFromFile("./sfml/Answer.ttf");
	text.setFont(*font);
	texture->loadFromFile("./sfml/trophies.png");
	food.setTexture(*texture);
	best_score.setTexture(*texture);
	food.setTextureRect({0, 0, 80, 80});
	best_score.setTextureRect({80, 0, 80, 80});
	food.setScale({0.75, 0.75});
	best_score.setScale({0.75, 0.75});
	food.setPosition({20, 10});
	best_score.setPosition({140, 10});
	text.setPosition({80, 20});
}

void Menu::draw_score(int n) {
	char buffer[8];
	sprintf(buffer, "%d", n);
	text.setString(std::string(buffer));
}

void Menu::draw_self (sf::RenderWindow &surface) {
	surface.draw(*this);
	surface.draw(best_score);
	surface.draw(food);
	surface.draw(text);
}
