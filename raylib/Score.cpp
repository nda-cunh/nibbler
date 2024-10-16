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
void Score::drawDigit(int d, Vector2 start) const {
	const Color 	c_on = _color;
	const Color 	c_off = {c_on.r, c_on.g, c_on.b, 30};
	const Vector2	shape = {15, 3};
	const float 	rdns = 0.8f;
	const bool 		leds[10][7] = {
		{1, 1, 1, 0, 1, 1, 1}, // 0
		{0, 0, 1, 0, 0, 1, 0}, // 1
		{1, 0, 1, 1, 1, 0, 1}, // 2
		{1, 0, 1, 1, 0, 1, 1}, // 3
		{0, 1, 1, 1, 0, 1, 0}, // 4
		{1, 1, 0, 1, 0, 1, 1}, // 5
		{1, 1, 0, 1, 1, 1, 1}, // 6
		{1, 0, 1, 0, 0, 1, 0}, // 7
		{1, 1, 1, 1, 1, 1, 1}, // 8
		{1, 1, 1, 1, 0, 1, 1}  // 9
	};

	// Draw The top led
	DrawRectangleRounded({start.x, start.y, shape.x, shape.y},
			rdns, 10,
			leds[d][0] ? c_on : c_off);

	// Draw The top left led
	DrawRectangleRounded({start.x - shape.y / 2, start.y + shape.y * 1.5f,
			shape.y, shape.x}, rdns, 10,
			leds[d][1] ? c_on : c_off);
	
	// Draw The top right led
	DrawRectangleRounded({start.x + shape.x - shape.y / 3,
			start.y + shape.y * 1.5f, shape.y, shape.x}, rdns, 10,
			leds[d][2] ? c_on : c_off);
	
	// Draw The middle led
	DrawRectangleRounded({start.x, start.y + 2 * shape.y + shape.x,
			shape.x, shape.y}, rdns, 10,
			leds[d][3] ? c_on : c_off);

	// Draw The bottom left led
	DrawRectangleRounded({start.x - shape.y / 2, start.y + 3.5f * shape.y
			+ shape.x, shape.y, shape.x}, rdns, 10,
			leds[d][4] ? c_on : c_off);

	// Draw The bottom right led
	DrawRectangleRounded({start.x + shape.x - shape.y / 2, start.y
			+ 3.5f * shape.y + shape.x, shape.y, shape.x}, rdns, 10,
			leds[d][5] ? c_on : c_off);

	// Draw The bottom led
	DrawRectangleRounded({start.x, start.y + 4 * shape.y + 2 * shape.x,
			shape.x, shape.y}, rdns, 10,
			leds[d][6] ? c_on : c_off);
}

