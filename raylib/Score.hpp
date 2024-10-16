#ifndef SCORE_HPP
#define SCORE_HPP

#include "raylib.h"

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
};

#endif
