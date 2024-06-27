# include "Menu.hpp"

/* ____ CONSTRUCTOR & COPLIEN ____ */
Menu::Menu() {}

Menu::Menu(int width, int height) {
	this->init_menu(width, height);
	_size = {width, height};
	_last_click.reset();
}

Menu::~Menu() {
	_font.release();
}

Menu::Menu(const Menu &other) {
	*this = other;
}

Menu	&Menu::operator=(const Menu &rhs) {
	if (this == &rhs)
		return *this;
	_font = std::make_unique<sf::Font>(*rhs._font.get());
	_last_click = rhs._last_click;
	_speed = rhs._speed;
	_size = rhs._size;
	_button_1p = rhs._button_1p;
	_speed_down = rhs._speed_down;
	_speed_up = rhs._speed_up;
	return *this;
}


/* ____ SETTER ____ */

void	Menu::setSpeed(int speed) {
	_speed = speed;
}


/* ____ INIT ACTIVITIES ____ */

void	Menu::init_menu(int width, int height) {
	sf::Vector2f	beg = {0.2f * width, 0.13f * height};
	sf::Color		menu_color(0x4DC1F9FF);

	_font = std::make_unique<sf::Font>();
	if (_font->loadFromFile("./sfml/coolvetica.otf") == false)
		throw std::runtime_error("can't load coolvetica.otf");

	_button_1p.setTxtColor(sf::Color::Black);
	_button_1p.setTxtSize(0.08 * std::min(height, width));
	_button_1p.setRect(beg.x, 0.5 * height, width * 3.0 / 5, 0.12 * height);
	_button_1p.setBgColor(menu_color);
	_button_1p.setClickEvent(CLICK_1P);
	_button_1p.setTxt("Play");

	// Speed Buttons
	{
		Button	b;
		int		min = std::min(width, height);
		beg = {	0.35f * width, 0.8f * height};

		b.setRect(beg.x, beg.y, width * 3.0 / 5, 0.1 * height);
		b.setBgColor(sf::Color(0));
		b.setTxtColor(menu_color);
		b.setTxtSize(0.08 * min);
		b.setTxt("speed");

		beg = {0.29f * width, 0.91f * height};

		_speed_down.setTxtSize(0.06 * min);
		_speed_down.setTxtColor(sf::Color::Black);
		_speed_down.setRect(beg.x, beg.y, 0.07 * min, 0.07 * min);
		_speed_down.setBgColor(menu_color);
		_speed_down.setClickEvent(SPEED_DOWN);
		_speed_down.setTxt("-");

		beg.x = width - beg.x - 0.07 * min;

		_speed_up.setTxtSize(0.06 * min);
		_speed_up.setTxtColor(sf::Color::Black);
		_speed_up.setRect(beg.x, beg.y, 0.07 * min, 0.07 * min);
		_speed_up.setBgColor(menu_color);
		_speed_up.setClickEvent(SPEED_UP);
		_speed_up.setTxt("+");
	}
}

void Menu::formatText(sf::Text &text, float height) {
	text.setFont(*_font);
	text.setPosition(_size.x * 0.5, height);

    // Center the text
    sf::FloatRect textRect = text.getGlobalBounds();
    text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
}

/* ____ PUBLIC METHODS ____ */

Event	Menu::collides(int x, int y) {

	// Reset hover state
	_button_1p.setHover(false);
	_speed_up.setHover(false);
	_speed_down.setHover(false);

	// Check if the mouse is hovering over a button
	if (_button_1p.getRect().contains(x, y)) {
		_button_1p.setHover(true);
		return CLICK_1P;
	} else if (_speed_down.getRect().contains(x, y)) {
		_speed_down.setHover(true);
		return SPEED_DOWN;
	} else if (_speed_up.getRect().contains(x, y)) {
		_speed_up.setHover(true);
		return SPEED_UP;
	}
	return NONE;
}

void	Menu::draw(sf::RenderTarget &win){
	sf::Color	menu_color(0x4DC1F9FF);
	int			min_fontsize = std::max(_size.y * 0.05, 34.);

	win.clear();
	{
		sf::Text	text;

		text.setString("SupraSnake");
		text.setFillColor(menu_color);
		text.setCharacterSize(_size.y * 0.1);
		this->formatText(text, _size.y * 0.20);
		win.draw(text);

		text.setString("Speed");
		text.setFillColor(menu_color);
		text.setCharacterSize(_size.y * 0.05);
		this->formatText(text, _size.y * 0.85);
		win.draw(text);

		text.setString("oooooo");
		text.setFillColor(sf::Color(0x131313EE));
		text.setCharacterSize(min_fontsize);
		formatText(text, 0.91f * _size.y);
		win.draw(text);

		text.setString(
				std::string(_speed, 'o') + std::string((6 - _speed) * 2, ' '));
		text.setFillColor(menu_color);
		text.setCharacterSize(min_fontsize);
		formatText(text, 0.91f * _size.y);
		win.draw(text);
	}

	_button_1p.draw(win);
	_speed_down.draw(win);
	_speed_up.draw(win);
}
