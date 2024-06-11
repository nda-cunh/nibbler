#ifndef BUTTON_HPP
#define BUTTON_HPP

# include "../include/utils.hpp"
# include <string>
# include "./utils.hpp"

class Button {
	Rectangle	_rect;
	Vector2		_offset;
	Color		_bg_color;
	
	std::string	_txt;
	int			_txt_size;
	Color		_txt_color;
	
	Activity	_click_event;
	
	public:
		/* ---- Constructors & Coplien ---- */
		Button();
		~Button();
		Button(const Button &);

		Button	&operator=(const Button &);

		/* ---- Accessors ---- */
		Rectangle	getRect() const;
		Activity	getEvent() const;
		void	setClickEvent(Activity act);
		void	setTxtSize(int size);
		void	setBgColor(const Color &c);
		void	setTxtColor(const Color &c);
		void	setOffSet(float x, float y);
		void	setTxt(const std::string &txt);
		void	setRect(float x, float y, float w, float h);

		/* ---- public methods ---- */
		void	centerText();

		/* ---- Display methods ---- */
		void	reset();
		void	draw();
};
#endif
