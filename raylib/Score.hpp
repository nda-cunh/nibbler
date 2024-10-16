#ifndef SCORE_HPP
#define SCORE_HPP

#include "raylib.h"

typedef enum LedPosition {
	Top,
	TopLeft,
	TopRight,
	Middle,
	BottomLeft,
	BottomRight,
	Bottom
} LedPosition;

class Score {
	public:
		/* ---- Constructors/ Destructor ---- */
		Score();
		Score(const Score &other);
		Score(Color c, Vector2 pos);
		~Score();

		/* ---- Assignement operator ---- */
		Score &operator=(const Score &rhs);

		/* ---- Public methods ---- */
		void draw(int n) const;

	private:
		Color 	_color;
		Vector2 _position;

		/* ---- Private draw methods ---- */
		void drawDigit(int digit, Vector2 start) const; 
		void drawLed(LedPosition led_pos, Vector2 start, Color c) const; 
		void drawBackground(Vector2 start) const; 
};

#endif
