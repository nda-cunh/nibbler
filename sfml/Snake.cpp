#include "Snake.hpp"
#include <SFML/Graphics/RenderTexture.hpp>

/* ____ CONSTRUCTORS & COPLIEN ____ */
Snake::Snake () {
	if (texture_snake.loadFromFile("./sfml/snake.bmp") == false)
		throw std::runtime_error("can't load snake.bmp");
	s_eyes_right.setTexture(texture_snake);
	s_eyes_right.setTexture(texture_snake);
	s_eyes_right.addFrames({1, 15, 28, 28}, {29, 0}, 9);
	s_eyes_right.setFreq(3.0);
	s_eyes_right.setSpeed(0.07);

	s_eyes_left.setTexture(texture_snake);
	s_eyes_left.setTexture(texture_snake);
	s_eyes_left.addFrames({301, 15, 28, 28}, {29, 0}, 9);
	s_eyes_left.setFreq(3.0);
	s_eyes_left.setSpeed(0.07);

	s_tongue.setTexture(texture_snake);
	s_tongue.addFrames({1, 127, 48, 24}, {49, 0}, 21);
	s_tongue.addFrames({{1, 127, 2, 2}});
	s_tongue.setSpeed(0.08);
	s_tongue.setFreq(6.0);

	s_mouth.setTexture(texture_snake);
	s_mouth.addFrames({{1, 58, 35, 54}});

	texture_head.create(TILE * 2, TILE * 1.10);
}

Snake::Snake(const Snake &other) {
	*this = other;
}

Snake::~Snake() {
	texture_head.clear();
}

Snake	&Snake::operator=(const Snake &rhs) {
	if (this == &rhs)
		return *this;
	texture_snake = rhs.texture_snake;
	s_eyes_left = rhs.s_eyes_left;
	s_eyes_right = rhs.s_eyes_right;
	s_tongue = rhs.s_tongue;
	s_mouth = rhs.s_mouth;
	return *this;
}


/* ____ PRIVATE METHODS ____ */

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
	const sf::Color color = {81, 128, 243};
	const double	width = 0.8 * TILE;
	sf::CircleShape	circle(width / 2);
	bool			is_vertical = true;
	double			min_width;
	unsigned int 	i;

	if (positions.size() < 12)
		min_width = TILE * 0.7;
	else if (positions.size() < 22)
		min_width = TILE * 0.65;
	else
		min_width = TILE * 0.5;

	// Draw every corner of first segment
	for (int j = 0; j < 4; ++j) {
		vertices[j].position = get_position(positions[0], true, j % 2 == 0, width);
		vertices[j].color = color;
	}

	for (i = 1; i < positions.size(); ++i) {
		// Draw circle if head or a corner
		if (i == 1 || is_vertical != (positions[i - 1].x == positions[i].x)) {
			is_vertical = (positions[i - 1].x == positions[i].x);

			circle.setPosition(sf::Vector2f(positions[i - 1].x * TILEf + TILEf / 2.0,
									positions[i - 1].y * TILEf + TILEf / 2.0));
			circle.setFillColor(color);
			circle.setOrigin(sf::Vector2f(width / 2.0, width / 2.0));
			window.draw(circle);
		}

		// Draw every corner of segment
		for (int j = 0; j < 4; ++j) {
			vertices[i * 4 + j].position = get_position(positions[i - (j < 2)],
												is_vertical, j % 2 == 0, width);
			vertices[i * 4 + j].color = color;
		}
	}

	circle.setFillColor(color);
	circle.setPosition(sf::Vector2f(positions[i - 1].x * TILEf + TILEf / 2.0,
								positions[i - 1].y * TILEf + TILEf / 2.0));
	circle.setOrigin(sf::Vector2f(width / 2.0, width / 2.0));
	window.draw(circle);

	window.draw(vertices);
}

void Snake::draw_head(sf::RenderTexture& window, const Position &pos, Direction dir) {
	texture_head.clear({0,0,0,0});
	/* Eyes */
	texture_head.draw(s_eyes_left.getFrame(-3, -4));
	texture_head.draw(s_eyes_right.getFrame(-3.6, TILEf / 2.0f));

	/* Tongue */
	texture_head.draw(s_tongue.getFrame(TILEf * 0.7f, TILEf / 4.0));

	/* Mouth */
	texture_head.draw(s_mouth.getFrame(TILEf * 0.4f, -4.0));

	texture_head.display();

	/* Display head */
	sf::Sprite		head(texture_head.getTexture());
	
	if (dir == Left) {
		head.setPosition({(pos.x + 1) * TILEf, (pos.y + 1) * TILEf + 2.0f});
		head.setRotation(180);
	} else if (dir == Down) {
		head.setPosition({(pos.x + 1) * TILEf + 2.0f, pos.y * TILEf});
		head.setRotation(90);
	} else if (dir == Up) {
		head.setPosition({pos.x * TILEf - 2.0f, (pos.y + 1) * TILEf});
		head.setRotation(270);
	} else
		head.setPosition({pos.x * TILEf, pos.y * TILEf - 2.0f});

	window.draw(head);
}


/* ____ PUBLIC METHODS ____ */

void Snake::update_snake(sf::RenderTexture &window, const std::deque<Position> &snake, Direction direction) {

	/* Draw Body */
	this->draw_body(window, snake);

	/* draw Eyes */
	this->draw_head(window, snake[0], direction);

}
