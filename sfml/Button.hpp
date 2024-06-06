#ifndef BUTTON_HPP
#define BUTTON_HPP

# include "../include/utils.hpp"
# include <string>
#include <SFML/Graphics.hpp>
#include <memory>
class Button {
	private:
		sf::RectangleShape	_rect;
		sf::Vector2f		_offset;
		sf::Text			_text;
		std::unique_ptr<sf::Font>		_font;
		Activity			_click_event;
	
	public:
		Button();
		~Button();
		Button(const Button &);

		Button	&operator=(const Button &);

		sf::Rect<float>	getRect() const;
		Activity	getEvent() const;
		void	setClickEvent(Activity act);
		void	setTxtSize(int size);
		void	setBgColor(const sf::Color &c);
		void	setTxtColor(const sf::Color &c);
		void	setOffSet(float x, float y);
		void	setTxt(const std::string txt);
		void	setRect(float x, float y, float w, float h);
		void	centerText();

		void	reset();
		void	draw(sf::RenderTarget &win);
};
#endif
