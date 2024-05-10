#include "snake.hpp"

Snake::Snake () {
	texture_snake.loadFromFile("./sfml/snake.png");
	tounge.setTexture(texture_snake);
	eyes.setTexture(texture_snake);
}

void Snake::init (int x, int y) {
	tileX = x;
	tileY = y;
}

void Snake::draw_snake(sf::RenderWindow &window, const std::deque<Position> &snake, Direction direction) {

	// sf::RenderTexture head;
	// head.create(tileX, tileY);
	
	// eyes.setTextureRect({1, 15, 28, 28});
	// head.draw(eyes);
	// head.setSmooth(true);
	// head.display();
	// sf::Sprite sprite;
	// sprite.setTexture(head.getTexture());

	// window.draw(sprite);
	/* Draw Langue */
	/*
	auto boca = sf::Vector2f(snake[0].x * tileX, snake[0].y * tileY);

	switch (direction) {
		case Up:
			tounge.setRotation(-95.0f);
			boca.x += tileX/2;
			break;
		case Down:
			boca.x += tileX/2;
			boca.y += tileY;
			tounge.setRotation(95.f);
			break;
		case Left:
			boca.y += tileY/2;
			tounge.setRotation(180.f);
			break;
		case Right:
			boca.y += tileY/2;
			boca.x += tileX;
			tounge.setRotation(0.f);
			break;
		default:
			break;
	}
	tounge.setOrigin(10, 10);
	tounge.setTextureRect({884,129, 45, 21});
	tounge.setPosition(boca);
	window.draw(tounge);
	*/
	

	/* Draw Body */
	Position last = snake[0];
	auto color = sf::Color(78, 125, 246, 255);
		double size = tileX / 2.0 - 4;
	for (auto i : snake) {
		draw_segment (window, i, last, size, color);
		color.b -= 3;
		last = i;
		size -= 0.2;
	}


}
void Snake::draw_segment(sf::RenderWindow& window, const Position begin, const Position end, double size, sf::Color color) {
	sf::CircleShape circle(size);
	circle.setFillColor(color);
	double diff = (tileX / 2.0) - size;

	Position b = {begin.x * tileX, begin.y * tileY};
	Position e = {end.x * tileX, end.y * tileY};
	while (b.x != e.x) {
		circle.setPosition(b.x + diff, b.y + diff);
		window.draw(circle);
		if (e.x > b.x)
			b.x++;
		else
			b.x--;
	}
	while (b.y != e.y) {
		circle.setPosition(b.x + diff, b.y + diff);
		window.draw(circle);
		if (e.y > b.y)
			b.y++;
		else
			b.y--;
	}
}
