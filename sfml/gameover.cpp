#include "gameover.hpp"


/* ____ CONSTRUCTORS & COPLIEN ____ */

GameOver::GameOver() {
	{
		texture_gameover = std::make_unique<sf::Texture>();
		surface = std::make_unique<sf::RenderTexture>();

		if (texture_gameover->loadFromFile("./sfml/gameover.bmp") == false)
			throw std::runtime_error("can't load gameover.bmp");

		auto size = texture_gameover->getSize();

		surface->create(size.x, size.y);
		this->setTexture(surface->getTexture());
		this->setOrigin(size.x / 2, size.y / 2);
		sprite_gameover.setTexture(*texture_gameover);
	}
	{
		if (_font.loadFromFile("./sfml/Answer.ttf") == false)
			throw std::runtime_error("can't load Answer.ttf");

		_text_score.setFont(_font);
		_text_score.setPosition(90, 175);
		_text_score.setFillColor(sf::Color::White);

		_text_best.setFont(_font);
		_text_best.setPosition(215, 175);
		_text_best.setFillColor(sf::Color::White);
	}
}

GameOver::GameOver(const GameOver &other) { *this = other; }

GameOver::~GameOver() {}

GameOver &GameOver::operator=( const GameOver &rhs ) {
	if (&rhs == this)
		return *this;
	sprite_gameover = rhs.sprite_gameover;
	_text_best = rhs._text_best;
	_text_score = rhs._text_score;
	_font = rhs._font;
	return *this;
}


/* ____ ACCESSORS ____ */

void GameOver::setBestScore(const int n) {
	std::string	n_str = std::to_string(n);

	if (n_str != _text_best.getString())
		_text_best.setString(n_str);
}

void GameOver::setScore(const int n) {
	std::string	n_str = std::to_string(n);

	if (n_str != _text_score.getString())
		_text_score.setString(n_str);
}


/* ____ DRAW UPDATE ____ */

void GameOver::update() {
	surface->clear({0,0,0,0});
	surface->draw(sprite_gameover);
	surface->draw(_text_score);
	surface->draw(_text_best);
	surface->display();
}
