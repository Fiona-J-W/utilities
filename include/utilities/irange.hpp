#ifndef UTILITIES_NUMBER_RANGE_HPP
#define UTILITIES_NUMBER_RANGE_HPP

#include <cassert>
#include <iterator>
#include <cstdint>

#include "core.hpp"

namespace util {

template<typename Number, Number Step = 1>
class fixed_number_iterator {
public:
	using value_type = Number;
	using reference = const Number&;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::random_access_iterator_tag;
	using pointer = ::util::pointer<const Number>;

	fixed_number_iterator(): m_current_value{0} {}
	fixed_number_iterator(Number start_value): m_current_value{start_value} {}

	reference operator*() const {
		return m_current_value;
	}
	pointer operator->() const {
		return &m_current_value;
	}
	
	fixed_number_iterator operator++() {
		m_current_value += Step;
		return *this;
	}

	fixed_number_iterator operator++(int) {
		auto tmp = *this;
		m_current_value += Step;
		return tmp;
	}

	fixed_number_iterator operator--() {
		m_current_value -= Step;
		return *this;
	}

	fixed_number_iterator operator--(int) {
		auto tmp = *this;
		m_current_value -= Step;
		return tmp;
	}

	Number operator[](difference_type n) {
		return m_current_value + (Step * n);
	}

	fixed_number_iterator operator+=(difference_type n) {
		m_current_value += n * Step;
		return *this;
	}

	fixed_number_iterator& operator+(difference_type n) const {
		return fixed_number_iterator{m_current_value + Step * n};
	}

	fixed_number_iterator operator-=(difference_type n) {
		m_current_value -= n * Step;
		return *this;
	}

	fixed_number_iterator& operator-(difference_type n) const {
		return fixed_number_iterator{m_current_value - Step * n};
	}

	friend bool operator==(fixed_number_iterator lhs, fixed_number_iterator rhs) {
		return lhs.m_current_value == rhs.m_current_value;
	}
	friend bool operator!=(fixed_number_iterator lhs, fixed_number_iterator rhs) { return !(lhs == rhs); }

	friend bool operator<(fixed_number_iterator lhs, fixed_number_iterator rhs) {
		return lhs.m_current_value < rhs.m_current_value;
	}
	friend bool operator>(fixed_number_iterator lhs, fixed_number_iterator rhs) { return rhs < lhs; }
	friend bool operator<=(fixed_number_iterator lhs, fixed_number_iterator rhs) { return !(rhs < lhs); }
	friend bool operator>=(fixed_number_iterator lhs, fixed_number_iterator rhs) { return !(lhs > rhs); }
	friend difference_type operator-(fixed_number_iterator lhs, fixed_number_iterator rhs) {
		return (lhs.m_current_value - rhs.m_current_value)/Step; }
private:
	Number m_current_value;
};

template<typename Number, Number Step>
auto operator-(fixed_number_iterator<Number, Step> lhs, fixed_number_iterator<Number, Step> rhs)
		->typename fixed_number_iterator<Number, Step>::difference_type {
	assert(*rhs % Step == *lhs % Step);
	return (*lhs - *rhs) / Step;
}

template<typename Number, Number Step = 1>
class fixed_number_range {
public:
	fixed_number_range(Number low, Number high): m_low{low}, m_high{high} {
		auto offset_high = high % Step;
		auto offset_low = low % Step;
		if (offset_low != offset_high) {
			m_high += -offset_high + offset_low;
			if (offset_high > offset_low) {
				m_high += Step;
			}
		}
	}
	fixed_number_iterator<Number, Step> begin() const {
		return {m_low};
	}
	fixed_number_iterator<Number, Step> end() const {
		return {m_high};
	}
	
	constexpr Number low() const {return m_low;}
	constexpr Number high() const {return m_high;}
	constexpr Number step() const {return Step;}
	
	constexpr std::size_t size() const {
		return (m_high - m_low) / Step;
	}
private:
	Number m_low;
	Number m_high;
};

template<typename Number, Number Step = 1>
fixed_number_range<Number, Step> make_fixed_number_range(Number low, Number high) {
	return {low, high};
}


/////////////////////////////


template<typename Number>
class number_iterator {
public:
	using value_type = Number;
	using reference = const Number&;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::random_access_iterator_tag;
	using pointer = ::util::pointer<const Number>;

	number_iterator(): m_current_value{0} {}
	number_iterator(Number start_value): m_current_value{start_value} {}
	number_iterator(Number start_value, Number step): m_current_value{start_value}, m_step{step} {}

	Number step() const {return m_step;}

	reference operator*() const {
		return m_current_value;
	}
	pointer operator->() const {
		return &m_current_value;
	}
	
	number_iterator operator++() {
		m_current_value += m_step;
		return *this;
	}
 
	number_iterator operator++(int) {
		auto tmp = *this;
		m_current_value += m_step;
		return tmp;
	}

	number_iterator operator--() {
		m_current_value -= m_step;
		return *this;
	}

	number_iterator operator--(int) {
		auto tmp = *this;
		m_current_value -= m_step;
		return tmp;
	}

	Number operator[](difference_type n) {
		return m_current_value + (m_step * n);
	}

	number_iterator operator+=(difference_type n) {
		m_current_value += n * m_step;
		return *this;
	}

	number_iterator& operator+(difference_type n) const {
		return number_iterator{m_current_value + m_step * n};
	}

	number_iterator operator-=(difference_type n) {
		m_current_value -= n * m_step;
		return *this;
	}

	number_iterator& operator-(difference_type n) const {
		return number_iterator{m_current_value - m_step * n};
	}

	friend bool operator==(number_iterator lhs, number_iterator rhs) {
		assert(lhs.m_step = rhs.m_step);
		return lhs.m_current_value == rhs.m_current_value;
	}
	friend bool operator!=(number_iterator lhs, number_iterator rhs) { return !(lhs == rhs); }

	friend bool operator<(number_iterator lhs, number_iterator rhs) {
		assert(lhs.m_step = rhs.m_step);
		return lhs.m_current_value < rhs.m_current_value;
	}
	friend bool operator>(number_iterator lhs, number_iterator rhs) { return rhs < lhs; }
	friend bool operator<=(number_iterator lhs, number_iterator rhs) { return !(rhs < lhs); }
	friend bool operator>=(number_iterator lhs, number_iterator rhs) { return !(lhs > rhs); }
private:
	Number m_current_value;
	Number m_step = 1;
};


template<typename Number>
auto operator-(number_iterator<Number> lhs, number_iterator<Number> rhs)
		->typename number_iterator<Number>::difference_type {
	assert(lhs.step() == rhs.step());
	const auto step = lhs.step();
	assert(*rhs % step == *lhs % step);
	return (*lhs - *rhs) / step;
}


template<typename Number>
class number_range {
public:
	number_range(Number low, Number high, Number step): m_low{low}, m_high{high}, m_step{step} {
		auto offset_high = m_high % m_step;
		auto offset_low = m_low % m_step;
		if (offset_low != offset_high) {
			m_high += -offset_high + offset_low;
			if (offset_high > offset_low) {
				m_high += m_step;
			}
		}
	}
	template<Number Step>
	number_range(const fixed_number_range<Number, Step>& other): m_low{other.m_low()}, m_high{other.m_high()}, m_step{other.m_step()} {}
	number_iterator<Number> begin() const {
		return {m_low, m_step};
	}
	number_iterator<Number> end() const {
		return {m_high, m_step};
	}
	
	constexpr Number low() const {return m_low;}
	constexpr Number high() const {return m_high;}
	constexpr Number step() const {return m_step;}
	
	constexpr std::size_t size() const {
		return (m_high - m_low) / m_step;
	}
	
private:
	Number m_low;
	Number m_high;
	Number m_step;
};



template<typename Number>
number_range<Number> make_number_range(Number low, Number high, Number step) {
	return {low, high, step};
}


///////////////////////

template<typename Number, Number Step = 1>
fixed_number_range<Number, Step> irange(Number high) {
	return make_fixed_number_range<Number, Step>({0}, high);
}

template<typename Number, Number Step = 1>
fixed_number_range<Number, Step> irange(Number low, Number high) {
	return make_fixed_number_range<Number, Step>(low, high);
}

template<typename Number>
number_range<Number> irange(Number low, Number high, Number step) {
	return make_number_range(low, high, step);
}

} // namespace util

#endif
