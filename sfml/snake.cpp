#include "snake.hpp"
#include <SFML/Graphics/RenderTexture.hpp>

Snake::Snake () {
	texture_snake.loadFromFile("./sfml/snake.png");
	tounge.setTexture(texture_snake);
	eyes.setTexture(texture_snake);
	s_eyes.setFrames({
			{1, 15, 28, 28},
			{30, 15, 28, 28},
			{59, 15, 28, 28},
			{88, 15, 28, 28},
			{117, 15, 28, 28},
			{146, 15, 28, 28},
			{175, 15, 28, 28},
			{204, 15, 28, 28},
			{233, 15, 28, 28}
	});
	s_eyes.setFreq(5.0);
	s_eyes.setSpeed(0.07);
	s_tongue.setFrames({
			{1, 127, 48, 24},
			{50, 127, 48, 24},
			{99, 127, 48, 24},
			{148, 127, 48, 24},
			{197, 127, 48, 24},
			{246, 127, 48, 24},
			{295, 127, 48, 24},
			{344, 127, 48, 24},
			{393, 127, 48, 24},
			{442, 127, 48, 24},
			{491, 127, 48, 24},
			{540, 127, 48, 24},
			{589, 127, 48, 24},
			{638, 127, 48, 24},
			{687, 127, 48, 24},
			{736, 127, 48, 24},
			{785, 127, 48, 24},
			{834, 127, 48, 24},
			{883, 127, 48, 24},
			{932, 127, 48, 24},
			{981, 127, 48, 24},
			{981, 127, 2, 2},
	});
	s_tongue.setFreq(5.0);
	s_tongue.setSpeed(0.08);
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
	this->draw_head(window, snake[0], direction);

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

inline void Snake::draw_head(sf::RenderTexture& window, const Position &pos, Direction dir) {
	sf::RenderTexture	texture;
	texture.create(TILE * 2, TILE);

	sf::Sprite 			sprite(eyes);
	Rect	r;
	/* Eyes */
	r = s_eyes.getFrame();

	sprite.setTextureRect({r.x, r.y, r.w, r.h});
	sprite.setPosition({0, - TILEf / 10.f});
	texture.draw(sprite);
	sprite.setPosition({0, TILEf / 2.7f});
	texture.draw(sprite);
	
	/* Tongue */
	r = s_tongue.getFrame();

	sprite.setTextureRect({r.x, r.y, r.w, r.h});
	sprite.setPosition({TILEf * 0.7f, TILEf / 6.0});
	texture.draw(sprite);

	/* Display head */
	sf::Sprite		head(texture.getTexture());
	head.setPosition({pos.x * TILEf, pos.y * TILEf});
	if (dir == Left) {
		head.setPosition({(pos.x + 1) * TILEf, (pos.y + 1) * TILEf});
		head.setRotation(180);
	} else if (dir == Down) {
		head.setPosition({(pos.x + 1) * TILEf, pos.y * TILEf});
		head.setRotation(90);
	} else if (dir == Up) {
		head.setPosition({pos.x * TILEf, (pos.y + 1) * TILEf});
		head.setRotation(270);
	}

	window.draw(head);
}
