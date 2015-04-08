#ifndef UTILITIES_TIMER_HPP
#define UTILITIES_TIMER_HPP

#include <cassert>
#include <chrono>

namespace util {

class timer {
public:
	using duration_type = std::chrono::nanoseconds;
	using clock = std::chrono::steady_clock;
	using time_point = std::chrono::time_point<clock>;
	
	void start() {
		m_start = clock::now();
	}
	void stop() {
		m_end = clock::now();
	}
	
	duration_type duration() const {
		assert(m_start < m_end);
		return m_end - m_start;
	}
	
	duration_type::rep ticks() const {
		return duration().count();
	}
private:
	time_point m_start = {};
	time_point m_end = {};
};

} // namespace util

#endif
