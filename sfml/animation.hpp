#ifndef _ANIMATION_HPP
#define _ANIMATION_HPP

#include <SFML/System.hpp>

class Animation : sf::Clock {
	public:
		Animation ();
		void time_ms (int ms);
		bool isElapsed ();
	private:
		sf::Int32 ms; 
};

#endif
