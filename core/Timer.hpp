#ifndef TIMER_HPP
# define TIMER_HPP

#include <iostream>
#include <chrono>

class Timer {
	public:
		Timer();
		void reset();
		double elapsed() const;
		// coplien
		Timer(const Timer &src);
		Timer &operator=(const Timer &src);

	private:
		typedef std::chrono::high_resolution_clock clock_;
		typedef std::chrono::duration<double, std::ratio<1> > second_;
		std::chrono::time_point<clock_> beg_;
};

#endif
