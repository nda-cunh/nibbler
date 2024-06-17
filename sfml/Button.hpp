#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../include/IPlugin.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

class Button {
	sf::RectangleShape	_rect;
	sf::Vector2f		_offset;
	sf::Text			_text;
	std::unique_ptr<sf::Font>		_font;
	Event				_click_event;
	bool				_is_rounded;

	void	draw_rounded( sf::RenderTarget	&win);

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
		void	setRounded(bool rounded);
		void	setBgColor(const sf::Color &c);
		void	setTxtColor(const sf::Color &c);
		void	setOffSet(float x, float y);
		void	setTxt(const std::string txt);
		void	setRect(float x, float y, float w, float h);

		/* ---- public methods ---- */
		void	centerText();

		/* ---- Display methods ---- */
		void	reset();
		void	draw(sf::RenderTarget &win);
};
#endif
