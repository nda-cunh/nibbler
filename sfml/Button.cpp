# include "Button.hpp"

/* ____ CONSTRUCTOR & COPLIEN ____ */
Button::Button() {
	_font = std::make_unique<sf::Font>();
	if (_font->loadFromFile("./sfml/coolvetica.otf") == false)
		throw std::runtime_error("can't load coolvetica.otf");
	_text.setFont(*_font.get());
	_text.setPosition({0, 0});
	_rect = sf::RectangleShape({0, 0});
	_rect.setFillColor(sf::Color::White);
	_click_event = NONE;
	_is_hover = false;
}

Button::~Button() {
	_font.release();
}

Button::Button(const Button &other) {
	*this = other;
}

Button	&Button::operator=(const Button &rhs) {
	if (this == &rhs)
		return *this;

	this->_font = std::make_unique<sf::Font>(*rhs._font.get());
	this->_rect = rhs._rect;
	this->_text = rhs._text;
	this->_click_event = rhs._click_event;
	this->_is_hover = rhs._is_hover;
	return *this;
}


/* ____ ACCESSORS ____ */

Event		Button::getEvent( void ) const 			{ return _click_event; }
void		Button::setTxtColor(const sf::Color &c)	{ _text.setFillColor(c); }
void		Button::setClickEvent(Event e)			{_click_event = e;}
void		Button::setTxtSize(int size)			{ _text.setCharacterSize(size); }
void		Button::setBgColor(const sf::Color &c)	{ _rect.setFillColor(c); }
void		Button::setHover(bool is_hover)			{ this->_is_hover = is_hover; }
void		Button::setTxt(const std::string txt)	{ _text.setString(txt); }

sf::Rect<float>	Button::getRect( void ) const { 
	sf::Vector2f	pos = _rect.getPosition();
	sf::Vector2f	size = _rect.getSize();

	return {pos.x, pos.y, size.x, size.y};
}

void	Button::setRect(float x, float y, float w, float h) {
	_rect.setPosition(x, y);
	_rect.setSize({w, h});
	_text.setPosition({x, y});
}


/* ____ PRIVATE METHODS ____ */

void Button::centerText() {
	auto center = _text.getGlobalBounds().getSize() / 2.f;
    auto localBounds = center + _text.getLocalBounds().getPosition();

	_text.setOrigin(localBounds);
	_text.setPosition(sf::Vector2f{ _rect.getSize() / 2.0f } + _rect.getPosition());
}


/* ____ DISPLAY METHODS ____ */

void	Button::draw_rounded(sf::RenderTarget	&win) {
	const float				radius = 15;
	const sf::Vector2f		&pos  = _rect.getPosition();
	const sf::Vector2f		&size = _rect.getSize();
	sf::RectangleShape		r = _rect;

	if (_is_hover)
		r.setFillColor(DARKER(_rect.getFillColor()));

	// Draw the circles at the corners
	{
		sf::CircleShape		c;
		sf::Vector2f 		shift = {_rect.getSize().x - 2.f * radius,
									 _rect.getSize().y - 2.f * radius};

		c.setFillColor(r.getFillColor());
		c.setRadius(radius);

		c.setPosition(pos);
		win.draw(c);

		c.setPosition({pos.x + shift.x, pos.y});
		win.draw(c);

		c.setPosition({pos.x, pos.y + shift.y});
		win.draw(c);

		c.setPosition({pos.x + shift.x, pos.y + shift.y});
		win.draw(c);
	}
	r.setPosition(pos.x + radius, pos.y);
	r.setSize({size.x - 2 * radius, size.y});
	win.draw(r);

	r.setPosition(pos.x, pos.y + radius);
	r.setSize({size.x, size.y - 2 * radius});
	win.draw(r);
}

void	Button::draw(sf::RenderTarget &win){
	if (_click_event != NONE)
		this->draw_rounded(win);
	else
	{
		sf::Color	prevc  = _rect.getFillColor();
		if (_is_hover)  
			_rect.setFillColor(DARKER(prevc));
		win.draw(_rect);
		_rect.setFillColor(prevc);
	}

	this->centerText();
	win.draw(_text);
}
