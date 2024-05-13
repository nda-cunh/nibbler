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
	text_score.setFont(*font);
	text_best.setFont(*font);
	texture->loadFromFile("./sfml/trophies.png");
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

void Menu::update_score(int n) {
	char buffer[8];
	sprintf(buffer, "%d", n);
	if (buffer != text_score.getString())
		text_score.setString(std::string(buffer));
}

void Menu::update_best_score(int n) {
	char buffer[8];
	sprintf(buffer, "%d", n);
	if (buffer != text_best.getString())
		text_best.setString(std::string(buffer));
}

void Menu::draw_self (sf::RenderWindow &surface) {
	surface.draw(*this);
	surface.draw(best_score);
	surface.draw(food);
	surface.draw(text_best);
	surface.draw(text_score);
}
