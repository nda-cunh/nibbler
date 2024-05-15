#include "snake.hpp"

Snake::Snake () {
	texture_snake.loadFromFile("./sfml/snake.png");
	tounge.setTexture(texture_snake);
	eyes.setTexture(texture_snake);
}

void Snake::update_snake(sf::RenderTexture &window, const std::deque<Position> &snake, Direction direction) {

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
	double size_head = (TILE * 0.75);
	double size = size_head;
	for (auto i : snake) {
		draw_segment (window, i, last, size, color);
		if (color.b > 20.0)
			color.b -= 3;
		last = i;
		if (size > 6.0)
			size -= 0.2;
	}
	draw_segment (window, snake[0], snake[1], size_head, color_head);

	/* draw Eyes */
	draw_eye(window, snake[0], direction, TILEf / 7);
	draw_eye(window, snake[0], direction, - TILEf / 2.5);

}


void Snake::draw_segment(sf::RenderTexture& window, const Position begin, const Position end, double size, sf::Color color) {
	sf::VertexArray vertices(sf::PrimitiveType::TriangleStrip, 4);
	const float	sizef = static_cast<float>(size);

	if (begin.x == end.x) {
		vertices[0].position = {begin.x * TILEf + (TILEf - sizef) / 2.0f, begin.y * TILEf + TILEf / 2.0f};
		vertices[1].position = {(begin.x + 1) * TILEf - (TILEf - sizef) / 2.0f, begin.y * TILEf + TILEf / 2.0f};
		vertices[2].position = {end.x * TILEf + (TILEf - (sizef + 0.2f)) / 2.0f, end.y * TILEf + TILEf / 2.0f};
		vertices[3].position = {(end.x + 1) * TILEf - (TILEf - (sizef + 0.2f)) / 2.0f, end.y * TILEf + TILEf / 2.0f};
		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
		vertices[3].color = color;
		window.draw(vertices);
		sf::CircleShape circle(size / 2.0);
		circle.setPosition({begin.x * TILEf + TILEf / 2.0f, begin.y * TILEf + TILEf / 2.0f});
		circle.setOrigin({sizef / 2.0f, sizef / 2.0f});
		circle.setFillColor(color);
		window.draw(circle);
	} else {
		vertices[0].position = {begin.x * TILEf + TILEf / 2.0f, begin.y * TILEf + (TILEf - sizef) / 2.0f};
		vertices[1].position = {begin.x * TILEf + TILEf / 2.0f, (begin.y + 1) * TILEf - (TILEf - sizef) / 2.0f};
		vertices[2].position = {end.x * TILEf + TILEf / 2.0f, end.y * TILEf + (TILEf - (sizef + 0.2f)) / 2.0f};
		vertices[3].position = {end.x * TILEf + TILEf / 2.0f, (end.y + 1) * TILEf - (TILEf - (sizef + 0.2f)) / 2.0f};
		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
		vertices[3].color = color;
		window.draw(vertices);
		sf::CircleShape circle(size / 2.0);
		circle.setPosition({begin.x * TILEf + TILEf / 2.0f, begin.y * TILEf + TILEf / 2.0f});
		circle.setOrigin({sizef / 2.0f, sizef / 2.0f});
		circle.setFillColor(color);
		window.draw(circle);
	}
}

inline void Snake::draw_eye(sf::RenderTexture& window, const Position &pos, Direction dir, float shift) {
	sf::Sprite sprite(eyes);

	sprite.setTextureRect({1, 15, 28, 28});

	
	if (dir == Up) {
		shift += TILEf / 4.0;
		sprite.setRotation(270);
		sprite.setPosition({static_cast<float>(pos.x * TILEf) + shift, static_cast<float>((pos.y + 1) * TILEf)});
	}
	else if (dir == Left){
		sprite.setRotation(180);
		sprite.setPosition({static_cast<float>((pos.x + 1) * TILEf), static_cast<float>((pos.y + 1) * TILEf) + shift});
	}
	else if (dir == Down) {
		sprite.setRotation(90);
		sprite.setPosition({static_cast<float>((pos.x + 1) * TILEf) + shift, static_cast<float>(pos.y * TILEf)});
	} else {
		shift += TILEf / 4.0;
		sprite.setPosition({static_cast<float>(pos.x * TILEf), static_cast<float>(pos.y * TILEf) + shift});
	}
	
	window.draw(sprite);
}
