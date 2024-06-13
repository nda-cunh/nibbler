# include "Timer.hpp"

Timer::Timer() : beg_(clock_::now()) {}

void Timer::reset() { beg_ = clock_::now(); }

double Timer::elapsed() const {
	return std::chrono::duration_cast<second_>
		(clock_::now() - beg_).count();
}

Timer &Timer::operator=(const Timer &src) {
	beg_ = src.beg_;
	return *this;
}

Timer::Timer(const Timer &src) {
	*this = src;
}
