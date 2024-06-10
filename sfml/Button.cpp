# include "Button.hpp"

Button::Button() {
	_font = std::make_unique<sf::Font>();
	if (_font->loadFromFile("./sfml/Answer.ttf") == false)
		throw std::runtime_error("can't load Answer.bmp");
	this->reset();
}

Button::~Button() {}

Button::Button(const Button &other) {
	*this = other;
}

Button	&Button::operator=(const Button &rhs) {
	if (this == &rhs)
		return *this;

	this->_rect = rhs._rect;
	this->_font = std::make_unique<sf::Font>(*rhs._font);
	this->_text = rhs._text;
	this->_offset = rhs._offset;
	this->_click_event = rhs._click_event;
	this->_is_rounded = rhs._is_rounded;
	return *this;
}

sf::Rect<float>	Button::getRect( void ) const { 
	sf::Vector2f	pos = _rect.getPosition();
	sf::Vector2f	size = _rect.getSize();

	return {pos.x, pos.y, size.x, size.y};
}
Activity	Button::getEvent( void ) const { return _click_event; }
void	Button::setClickEvent(Activity act) {_click_event = act;}
void	Button::setTxtSize(int size) {
	_text.setCharacterSize(size);
}
void	Button::setOffSet(float x, float y) { _offset = {x, y};
	_text.setPosition(_offset + _rect.getPosition());
}
void	Button::setTxt(const std::string txt) {
	_text.setString(txt);
}
void	Button::setRounded(bool rounded) {
	this->_is_rounded = rounded;
}
void	Button::setTxtColor(const sf::Color &c) {
	_text.setFillColor(c);
}
void	Button::setBgColor(const sf::Color &c) {
	_rect.setFillColor(c);
}
void	Button::setRect(float x, float y, float w, float h)
{
	_rect.setPosition(x, y);
	_rect.setSize({w, h});
}

void	Button::centerText() {
	_offset.x = (this->_rect.getSize().x - _text.getCharacterSize() * _text.getString().getSize() / 1.8) / 1.6f;
	_offset.y = (this->_rect.getSize().y - _text.getCharacterSize()) / 2.5f;

	_text.setPosition(_offset + _rect.getPosition());
}


void	Button::reset() {
	_rect = sf::RectangleShape({0, 0});
	_rect.setFillColor(sf::Color::White);
	_offset = {0, 0};
	_text.setPosition({20, 20});
	_click_event = ON_NONE;
	_is_rounded = true;
}

void	Button::draw_rounded(sf::RenderTarget	&win) {
	sf::RectangleShape	r = _rect;
	sf::Vector2f		v;
	sf::CircleShape		c;
	float				radius = 15;

	
	c.setFillColor(r.getFillColor());
	c.setRadius(radius);
	v = _rect.getPosition();

	c.setPosition(v);
	win.draw(c);
	c.setPosition({v.x + _rect.getSize().x - 2 * radius, v.y});
	win.draw(c);
	c.setPosition({v.x, v.y + _rect.getSize().y - 2 * radius});
	win.draw(c);
	c.setPosition({v.x + _rect.getSize().x - 2 * radius,
			v.y + _rect.getSize().y - 2 * radius});
	win.draw(c);

	v = _rect.getPosition();
	r.setPosition(v.x + radius, v.y);
	v = _rect.getSize();
	r.setSize({v.x - 2 * radius, v.y});
	win.draw(r);

	v = _rect.getPosition();
	r.setPosition(v.x, v.y + radius);
	v = _rect.getSize();
	r.setSize({v.x, v.y - 2 * radius});
	win.draw(r);
}

void	Button::draw(sf::RenderTarget &win){
	if (_is_rounded)
		this->draw_rounded(win);
	else
		win.draw(_rect);
	
	if (_font) {
		_text.setFont(*_font);
		win.draw(_text);
	}
}
