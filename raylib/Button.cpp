# include "Button.hpp"

Button::Button() {
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
	this->_offset = rhs._offset;
	this->_txt = rhs._txt;
	this->_txt_size = rhs._txt_size;
	this->_txt_color = rhs._txt_color;
	this->_bg_color = rhs._bg_color;
	this->_click_event = rhs._click_event;
	return *this;
}

Rectangle	Button::getRect( void ) const { return _rect; }
Activity	Button::getEvent( void ) const { return _click_event; }
void	Button::setClickEvent(Activity act) {_click_event = act;}
void	Button::setTxtSize(int size) { _txt_size = size; }
void	Button::setOffSet(float x, float y) { _offset = {x, y}; }
void	Button::setTxt(const std::string &txt) { _txt = txt; }
void	Button::setTxtColor(const Color &c) { _txt_color = c; }
void	Button::setBgColor(const Color &c) { _bg_color = c; }
void	Button::setRect(float x, float y, float w, float h)
{ _rect = {x, y, w, h}; }

void	Button::centerText() {
	_offset.y = (this->_rect.height - this->_txt_size) / 2.f;
	_offset.x = (this->_rect.width - this->_txt.length() * this->_txt_size / 1.8) / 2.f;
}


void	Button::reset() {
	_rect = {0, 0, 0, 0};
	_offset = {0, 0};
	_txt = "";
	_txt_size = 10;
	_txt_color = BLACK;
	_bg_color = WHITE;
	_click_event = ON_NONE;
}

void	Button::draw() {
	DrawRectangleRec(_rect, _bg_color);
	DrawText(_txt.c_str(),
			_rect.x + _offset.x, _rect.y + _offset.y,
			_txt_size, _txt_color);
}
