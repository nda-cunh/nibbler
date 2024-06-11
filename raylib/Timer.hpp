#ifndef TIMER_HPP
# define TIMER_HPP

#include <iostream>
#include <chrono>

class Timer {
	typedef std::chrono::high_resolution_clock				t_clock;
	typedef std::chrono::duration<double, std::ratio<1> >	t_second;
	std::chrono::time_point<t_clock>							_beg;

	public:
		/* ---- Coplien ---- */
		Timer();
		Timer(const Timer &);
		~Timer();

		Timer	&operator=(const Timer &);

		/* ---- Public methods ---- */
		void reset();
		double elapsed() const;
};

#endif
