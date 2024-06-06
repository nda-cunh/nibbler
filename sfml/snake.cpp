#include "snake.hpp"
#include <SFML/Graphics/RenderTexture.hpp>

Snake::Snake () {
	if (texture_snake.loadFromFile("./sfml/snake.bmp") == false)
		throw std::runtime_error("can't load snake.bmp");
	tounge.setTexture(texture_snake);
	mouth.setTexture(texture_snake);
	eyes_right.setTexture(texture_snake);
	s_eyes_right.setFrames({
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
	s_eyes_right.setFreq(3.0);
	s_eyes_right.setSpeed(0.07);

	eyes_left.setTexture(texture_snake);
	s_eyes_left.setFrames({
			{301, 15, 28, 28},
			{330, 15, 28, 28},
			{359, 15, 28, 28},
			{388, 15, 28, 28},
			{417, 15, 28, 28},
			{446, 15, 28, 28},
			{475, 15, 28, 28},
			{504, 15, 28, 28},
			{533, 15, 28, 28}
			});
	s_eyes_left.setFreq(3.0);
	s_eyes_left.setSpeed(0.07);
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
	s_tongue.setFreq(6.0);
	s_tongue.setSpeed(0.08);
	s_mouth.setFrames({
			{1, 58, 35, 54}
			});
	texture_head.create(TILE * 2, TILE * 1.10);
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
	this->draw_body(window, snake);

	/* draw Eyes */
	this->draw_head(window, snake[0], direction);

}

static inline sf::Vector2f	get_position(Position pos, bool is_vertical, bool is_first, float width) {
	if (is_vertical) {
		if (is_first)
			return sf::Vector2f(pos.x * TILEf + (TILEf - width) / 2.0f,
					pos.y * TILEf + TILEf / 2.0f);
		else
			return sf::Vector2f((pos.x + 1) * TILEf - (TILEf - width) / 2.0f,
					pos.y * TILEf + TILEf / 2.0f);
	} else {
		if (is_first)
			return sf::Vector2f(pos.x * TILEf + TILEf / 2.0f,
					pos.y * TILEf + (TILEf - width) / 2.0f);
		else
			return sf::Vector2f(pos.x * TILEf + TILEf / 2.0f,
					(pos.y + 1) * TILEf - (TILEf - width) / 2.0f);
	}

}
void Snake::draw_body(sf::RenderTexture& window, const std::deque<Position> &positions) {
	sf::VertexArray	vertices(sf::PrimitiveType::TriangleStrip, positions.size() * 4);
	unsigned int i;
	double	width = 0.8 * TILE;
	double	min_width;
	bool	is_vertical = true;
	double	w_step;

	sf::Color color = {81, 128, 243};
	if (positions.size() < 12)
		min_width = TILE * 0.7;
	else if (positions.size() < 22)
		min_width = TILE * 0.65;
	else
		min_width = TILE * 0.5;

	w_step = (width - min_width) / positions.size();
	vertices[0].position = get_position(positions[0], true, true, width);
	vertices[1].position = get_position(positions[0], true, false, width);
	vertices[2].position = get_position(positions[0], true, true, width);
	vertices[3].position = get_position(positions[0], true, false, width);
	vertices[0].color = color;
	vertices[1].color = color;
	vertices[2].color = color;
	vertices[3].color = color;

	for (i = 1; i < positions.size(); ++i) {
		if (i == 1 || is_vertical != (positions[i - 1].x == positions[i].x)) {
			is_vertical = (positions[i - 1].x == positions[i].x);
			sf::CircleShape	circle(width / 2);

			circle.setPosition(sf::Vector2f(positions[i - 1].x * TILEf + TILEf / 2.0, positions[i - 1].y * TILEf + TILEf / 2.0));
			circle.setFillColor(color);
			circle.setOrigin(sf::Vector2f(width / 2.0, width / 2.0));
			window.draw(circle);
		}
		vertices[i * 4].position = get_position(positions[i - 1], is_vertical, true, width);
		vertices[i * 4].color = color;
		vertices[i * 4 + 1].position = get_position(positions[i - 1], is_vertical, false, width);
		vertices[i * 4 + 1].color = color;
		width -= w_step;
		vertices[i * 4 + 2].position = get_position(positions[i], is_vertical, true, width);
		vertices[i * 4 + 2].color = color;
		vertices[i * 4 + 3].position = get_position(positions[i], is_vertical, false, width);
		vertices[i * 4 + 3].color = color;
	}

	sf::CircleShape	circle(width / 2);
	circle.setFillColor(color);
	circle.setPosition(sf::Vector2f(positions[i - 1].x * TILEf + TILEf / 2.0, positions[i - 1].y * TILEf + TILEf / 2.0));
	circle.setOrigin(sf::Vector2f(width / 2.0, width / 2.0));
	window.draw(circle);

	window.draw(vertices);
}

inline void Snake::draw_head(sf::RenderTexture& window, const Position &pos, Direction dir) {
	sf::Sprite 			sprite(eyes_left);
	Rect	r;
	/* Eyes */
	texture_head.clear({0,0,0,0});
	r = s_eyes_left.getFrame();
	sprite.setTextureRect({r.x, r.y, r.w, r.h});
	sprite.setPosition({-3.0, -4.0});
	texture_head.draw(sprite);

	r = s_eyes_right.getFrame();
	sprite.setTextureRect({r.x, r.y, r.w, r.h});
	sprite.setPosition({-3.6, TILEf / 2.0f});
	texture_head.draw(sprite);

	/* Tongue */
	r = s_tongue.getFrame();

	sprite.setTextureRect({r.x, r.y, r.w, r.h});
	sprite.setPosition({TILEf * 0.7f, TILEf / 4.0});
	texture_head.draw(sprite);

	/* Mouth */
	r = s_mouth.getFrame();

	sprite.setTextureRect({r.x, r.y, r.w, r.h});
	sprite.setPosition({TILEf * 0.4f, -4.0});
	texture_head.draw(sprite);
	texture_head.display();

	/* Display head */
	sf::Sprite		head(texture_head.getTexture());
	head.setPosition({pos.x * TILEf, pos.y * TILEf - 2.0f});
	if (dir == Left) {
		head.setPosition({(pos.x + 1) * TILEf, (pos.y + 1) * TILEf + 2.0f});
		head.setRotation(180);
	} else if (dir == Down) {
		head.setPosition({(pos.x + 1) * TILEf + 2.0f, pos.y * TILEf});
		head.setRotation(90);
	} else if (dir == Up) {
		head.setPosition({pos.x * TILEf - 2.0f, (pos.y + 1) * TILEf});
		head.setRotation(270);
	}

	window.draw(head);
}
