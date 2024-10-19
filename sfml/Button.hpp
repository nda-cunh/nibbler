#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../include/IPlugin.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

# define DARKER(c) sf::Color(c.r * 0.8, c.g * 0.8, c.b * 0.8, c.a)

class Button {
	std::unique_ptr<sf::Font>		_font;
	sf::RectangleShape	_rect;
	sf::Text			_text;
	Event				_click_event;
	bool				_is_hover;

	void	draw_rounded( sf::RenderTarget	&win);
	void	centerText();

	public:
		/* ---- Constructors & Coplien ---- */
		Button();
		~Button();
		Button(const Button &);

		Button	&operator=(const Button &);

		/* ---- Accessors ---- */
		sf::Rect<float>	getRect() const;
		Event	getEvent() const;
		void	setClickEvent(Event e);
		void	setTxtSize(int size);
		void	setHover( bool );
		void	setBgColor(const sf::Color &c);
		void	setTxtColor(const sf::Color &c);
		void	setTxt(const std::string &txt);
		void	setRect(float x, float y, float w, float h);

		/* ---- Display methods ---- */
		void	draw(sf::RenderTarget &win);
};
#endif
