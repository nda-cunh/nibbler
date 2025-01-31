#include "Background.hpp"

/* ____ CONSTRUCTOR & COPLIEN ____ */
Background::Background(){}

Background::Background( const Background &other ){
	*this = other;
}

Background::~Background(){}

Background &Background::operator=( const Background &rhs ){
	if (this == &rhs)
		return *this;
	texture = rhs.texture;
	return *this;
}


/* ____ INIT METHOD ____ */

void Background::init(sf::Vector2u size){
	texture = std::make_shared<sf::RenderTexture>();
	texture->create(size.x, size.y);
	int num_tiles_x = size.x / TILE;
	int num_tiles_y = size.y / TILE;

	sf::RectangleShape rectangle({TILE, TILE});
	for (int i = 0; i < num_tiles_x; ++i) {
		for (int j = 0; j < num_tiles_y; ++j) {
			if ((i + j) % 2 == 0) {
				rectangle.setFillColor(sf::Color(162, 209, 73)); // couleur de rectangle1
			} else {
				rectangle.setFillColor(sf::Color(170, 215, 81)); // couleur de rectangle2
			}
			rectangle.setPosition(i * TILE, j * TILE);
			texture->draw(rectangle);
		}
	}
	texture->display();
	this->setTexture (texture->getTexture());
}


/* ____ DISPLAY METHOD ____ */

void Background::draw_self(sf::RenderTexture &window){
	window.draw(*this);
}
