# include "Score.hpp"
# include <string>

/* ____ CONSTRUCTORS/ DESTRUCTOR ____ */

Score::Score(): _color(WHITE), _position({0, 0}) {}

Score::Score(Color c, Vector2 pos): _color(c), _position(pos) {}

Score::Score(const Score &other) {
	*this = other;
}

Score::~Score() {}

/* ____ ASSIGNEMENT OPERATOR ____ */
Score &Score::operator=(const Score &rhs) {
	if (this == &rhs)
		return *this;

	this->_color = rhs._color;
	this->_position = rhs._position;
	return *this;
}

/* ____ PUBLIC METHODS ____ */
void Score::draw(int n) const {
	int decimal = n % 10;
	int power = 1;

	if (n == 0)
		this->drawDigit(0, {_position.x - 30 * power, _position.y});
	while (n > 0) {
		this->drawDigit(decimal, {_position.x - 30 * power, _position.y});
		n /= 10;
		decimal = n % 10;
		power++;
	}
	while (power < 4) {
		this->drawDigit(0, {_position.x - 30 * power, _position.y});
		power++;
	}
}

/* ____ PRIVATE DRAW METHODS ____ */
void Score::drawLed(LedPosition led_pos, Vector2 start, Color c) const {
	const float rdns = 0.8f;
	const Vector2	shape = {15, 3};

	switch (led_pos) {
		case Top:
			DrawRectangleRounded({start.x, start.y, shape.x, shape.y},
					rdns, 10, c);
			break;

		case TopLeft:
			DrawRectangleRounded({start.x - shape.y / 2, start.y + shape.y * 1.5f,
					shape.y, shape.x}, rdns, 10, c);
			break;
		case  TopRight:
			DrawRectangleRounded({start.x + shape.x - shape.y / 2,
								start.y + shape.y * 1.5f,
					shape.y, shape.x}, rdns, 10, c);
			break;
		case Middle:
			DrawRectangleRounded({start.x,
								start.y + 2 * shape.y + shape.x,
					shape.x, shape.y}, rdns, 10, c);
			break;
		case BottomLeft:
			DrawRectangleRounded({start.x - shape.y / 2,
								start.y + 3.5f * shape.y + shape.x,
					shape.y, shape.x}, rdns, 10, c);
			break;

		case BottomRight:
			DrawRectangleRounded({start.x + shape.x - shape.y / 2,
								start.y + 3.5f * shape.y + shape.x,
					shape.y, shape.x}, rdns, 10, c);
			break;
		case Bottom:
			DrawRectangleRounded({start.x, start.y + 4 * shape.y + 2 * shape.x,
					shape.x, shape.y}, rdns, 10, c);
			break;
		default:
			break;
	}
}

void Score::drawBackground(Vector2 start) const {
	Color c = this->_color;
	c.a = 30;

	drawLed(Top, start, c);
	drawLed(TopLeft, start, c);
	drawLed(TopRight, start, c);
	drawLed(Middle, start, c);
	drawLed(BottomLeft, start, c);
	drawLed(BottomRight, start, c);
	drawLed(Bottom, start, c);
}

void Score::drawDigit(int digit, Vector2 start) const {
	this->drawBackground(start);
	switch (digit) {
		case 0:
			drawLed(Top, start, this->_color);
			drawLed(TopLeft, start, this->_color);
			drawLed(TopRight, start, this->_color);
			drawLed(BottomLeft, start, this->_color);
			drawLed(BottomRight, start, this->_color);
			drawLed(Bottom, start, this->_color);
			break;
		case 1:
			drawLed(TopRight, start, this->_color);
			drawLed(BottomRight, start, this->_color);
			break;
		case 2:
			drawLed(Top, start, this->_color);
			drawLed(TopRight, start, this->_color);
			drawLed(Middle, start, this->_color);
			drawLed(BottomLeft, start, this->_color);
			drawLed(Bottom, start, this->_color);
			break;
		case 3:
			drawLed(Top, start, this->_color);
			drawLed(TopRight, start, this->_color);
			drawLed(Middle, start, this->_color);
			drawLed(BottomRight, start, this->_color);
			drawLed(Bottom, start, this->_color);
			break;
		case 4:
			drawLed(TopLeft, start, this->_color);
			drawLed(TopRight, start, this->_color);
			drawLed(Middle, start, this->_color);
			drawLed(BottomRight, start, this->_color);
			break;
		case 5:
			drawLed(Top, start, this->_color);
			drawLed(TopLeft, start, this->_color);
			drawLed(Middle, start, this->_color);
			drawLed(BottomRight, start, this->_color);
			drawLed(Bottom, start, this->_color);
			break;
		case 6:
			drawLed(Top, start, this->_color);
			drawLed(TopLeft, start, this->_color);
			drawLed(Middle, start, this->_color);
			drawLed(BottomLeft, start, this->_color);
			drawLed(BottomRight, start, this->_color);
			drawLed(Bottom, start, this->_color);
			break;
		case 7:
			drawLed(Top, start, this->_color);
			drawLed(TopRight, start, this->_color);
			drawLed(BottomRight, start, this->_color);
			break;
		case 8:
			drawLed(Top, start, this->_color);
			drawLed(TopLeft, start, this->_color);
			drawLed(TopRight, start, this->_color);
			drawLed(Middle, start, this->_color);
			drawLed(BottomLeft, start, this->_color);
			drawLed(BottomRight, start, this->_color);
			drawLed(Bottom, start, this->_color);
			break;
		case 9:
			drawLed(Top, start, this->_color);
			drawLed(TopLeft, start, this->_color);
			drawLed(TopRight, start, this->_color);
			drawLed(Middle, start, this->_color);
			drawLed(BottomRight, start, this->_color);
			drawLed(Bottom, start, this->_color);
			break;
	}
}

