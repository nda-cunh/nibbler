#include "snake.hpp"

Snake::Snake () {
	texture_snake.loadFromFile("./sfml/snake.png");
	tounge.setTexture(texture_snake);
	eyes.setTexture(texture_snake);
}

void Snake::update_snake(sf::RenderTexture &window, const std::deque<Position> &snake, Direction direction) {

	// sf::RenderTexture head;
	// head.create(TILE, TILE);
	
	// eyes.setTextureRect({1, 15, 28, 28});
	// head.draw(eyes);
	// head.setSmooth(true);
	// head.display();
	// sf::Sprite sprite;
	// sprite.setTexture(head.getTexture());

	// window.draw(sprite);
	/* Draw Langue */
	/*
	auto boca = sf::Vector2f(snake[0].x * TILE, snake[0].y * TILE);

	switch (direction) {
		case Up:
			tounge.setRotation(-95.0f);
			boca.x += TILE/2;
			break;
		case Down:
			boca.x += TILE/2;
			boca.y += TILE;
			tounge.setRotation(95.f);
			break;
		case Left:
			boca.y += TILE/2;
			tounge.setRotation(180.f);
			break;
		case Right:
			boca.y += TILE/2;
			boca.x += TILE;
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
	auto color_head = sf::Color(78, 125, 246, 255);
	auto color = color_head;
	double size_head = (TILE / 2.0 - 4.0);
	double size = size_head;
	for (auto i : snake) {
		draw_segment (window, i, last, size, color);
		color.b -= 3;
		last = i;
		size -= 0.2;
	}
	draw_segment (window, snake[0], snake[1], size_head, color_head);


}
void Snake::draw_segment(sf::RenderTexture& window, const Position begin, const Position end, double size, sf::Color color) {
	sf::CircleShape circle(size);
	circle.setFillColor(color);
	double diff = (TILE / 2.0) - size;

	Position b = {begin.x * TILE, begin.y * TILE};
	Position e = {end.x * TILE, end.y * TILE};
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
