#include "gameover.hpp"

GameOver::GameOver() {
	font.loadFromFile("./sfml/Answer.ttf");
	t_score.setFont(font);
	t_score_max.setFont(font);
	texture_gameover = std::make_unique<sf::Texture>();
	surface = std::make_unique<sf::RenderTexture>();

	texture_gameover->loadFromFile("./sfml/gameover.png");
	auto size = texture_gameover->getSize();
	surface->create(size.x, size.y);
	this->setTexture(surface->getTexture());
	
	this->setOrigin(size.x / 2, size.y / 2);
	sprite_gameover.setTexture(*texture_gameover);
	t_score.setPosition(90, 175);
	t_score.setFillColor(sf::Color::White);
	t_score_max.setPosition(215, 175);
	t_score_max.setFillColor(sf::Color::White);
}

void GameOver::update() {
	surface->clear({0,0,0,0});
	surface->draw(sprite_gameover);
	surface->draw(t_score);
	surface->draw(t_score_max);
	surface->display();
}

		
void GameOver::update_score_max(const int n) {
	char buffer[16];
	sprintf(buffer, "%d", n);
	t_score_max.setString(std::string(buffer));
}

void GameOver::update_score(const int n) {
	char buffer[16];
	sprintf(buffer, "%d", n);
	t_score.setString(std::string(buffer));
}
