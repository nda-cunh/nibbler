# include "Button.hpp"

Button::Button() {
	_font = std::make_unique<sf::Font>();
	if (_font->loadFromFile("./sfml/Answer.ttf") == false)
		throw std::runtime_error("can't load Answer.bmp");
	_text.setFont(*_font);
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
	// this->_text = rhs._text;
	//TODO// *this->_font = rhs->_font;
	this->_offset = rhs._offset;
	this->_click_event = rhs._click_event;
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
void	Button::setOffSet(float x, float y) { _offset = {x, y}; }
void	Button::setTxt(const std::string txt) {
	_text.setString(txt);
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
	// _offset.y = (this->_rect.getSize().y - _text.getCharacterSize()) / 2.5f;
	// _offset.x = (this->_rect.getSize().x - _text.getCharacterSize() * _text.getString().getSize() / 1.8) / 1.5f;

	// _text.setOrigin(_rect.getPosition());
	// _text.setPosition(_offset);
}


void	Button::reset() {
	_rect = sf::RectangleShape({0, 0});
	_rect.setFillColor(sf::Color::White);
	_offset = {0, 0};
	_text.setPosition({10, 10});
	_click_event = ON_NONE;
}

void	Button::draw(sf::RenderTarget &win){
	win.draw(_rect);
	win.draw(_text);
}
