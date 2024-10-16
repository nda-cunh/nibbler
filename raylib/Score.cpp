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
void Score::draw(int n) {
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
void Score::drawLed(LedPosition led_pos, Vector2 start) const {
	const float rdns = 0.8f;
	const Vector2	shape = {15, 3};
	Color c = this->_color;

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
	drawLed(Top, start);
	drawLed(TopLeft, start);
	drawLed(TopRight, start);
	drawLed(Middle, start);
	drawLed(BottomLeft, start);
	drawLed(BottomRight, start);
	drawLed(Bottom, start);
}

void Score::drawDigit(int digit, Vector2 start) {
	_color.a = 30;
	this->drawBackground(start);
	_color.a = 255;
	switch (digit) {
		case 0:
			drawLed(Top, start);
			drawLed(TopLeft, start);
			drawLed(TopRight, start);
			drawLed(BottomLeft, start);
			drawLed(BottomRight, start);
			drawLed(Bottom, start);
			break;
		case 1:
			drawLed(TopRight, start);
			drawLed(BottomRight, start);
			break;
		case 2:
			drawLed(Top, start);
			drawLed(TopRight, start);
			drawLed(Middle, start);
			drawLed(BottomLeft, start);
			drawLed(Bottom, start);
			break;
		case 3:
			drawLed(Top, start);
			drawLed(TopRight, start);
			drawLed(Middle, start);
			drawLed(BottomRight, start);
			drawLed(Bottom, start);
			break;
		case 4:
			drawLed(TopLeft, start);
			drawLed(TopRight, start);
			drawLed(Middle, start);
			drawLed(BottomRight, start);
			break;
		case 5:
			drawLed(Top, start);
			drawLed(TopLeft, start);
			drawLed(Middle, start);
			drawLed(BottomRight, start);
			drawLed(Bottom, start);
			break;
		case 6:
			drawLed(Top, start);
			drawLed(TopLeft, start);
			drawLed(Middle, start);
			drawLed(BottomLeft, start);
			drawLed(BottomRight, start);
			drawLed(Bottom, start);
			break;
		case 7:
			drawLed(Top, start);
			drawLed(TopRight, start);
			drawLed(BottomRight, start);
			break;
		case 8:
			drawLed(Top, start);
			drawLed(TopLeft, start);
			drawLed(TopRight, start);
			drawLed(Middle, start);
			drawLed(BottomLeft, start);
			drawLed(BottomRight, start);
			drawLed(Bottom, start);
			break;
		case 9:
			drawLed(Top, start);
			drawLed(TopLeft, start);
			drawLed(TopRight, start);
			drawLed(Middle, start);
			drawLed(BottomRight, start);
			drawLed(Bottom, start);
			break;
	}
}

