# include "Timer.hpp"

/* ____ COPLIEN ____ */
Timer::Timer() : _beg(t_clock::now()) {}

Timer::Timer(const Timer &o) {
	*this = o;
}

Timer::~Timer() {}

Timer	&Timer::operator=(const Timer &rhs) {
	if (this == &rhs)
		return *this;
	_beg = rhs._beg;
	return *this;
}


/* ____ PUBLIC METHODS ____ */
void Timer::reset() {
	_beg = t_clock::now();
}

double Timer::elapsed() const {
	return std::chrono::duration_cast<t_second>
		(t_clock::now() - _beg).count();
}
