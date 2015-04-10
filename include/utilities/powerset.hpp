#ifndef UTILITIES_POWERSET_HPP
#define UTILITIES_POWERSET_HPP

#include <cassert>
#include <utility>

#include "core.hpp"
#include "range_basics.hpp"
#include "dynamic_bitset.hpp"

namespace util {

template<typename Range> class powerset_range;
template<typename Range> class powerset_iterator;
template<typename Iterator> class set_iterator;

namespace impl {

} // namespace impl


template<typename Iterator>
class set_iterator {
public:
private:
};


template<typename Range>
class powerset_iterator {
public:
private:
	powerset_iterator(pointer<powerset_range<Range>> range, dynamic_bitset active = {0});

	pointer<powerset_range<Range>> m_range;
	dynamic_bitset m_active;
};


template<typename Range>
class powerset_range {
public:
	powerset_range(Range range): m_range{std::forward<Range>(range)} {}

	friend class powerset_iterator<powerset_range<Range>>;
private:
	Range m_range;
};

//////////////////////////////////////////////////////////////////////////////////////////

template<typename Range>
powerset_iterator<Range>::powerset_iterator(pointer<powerset_range<Range>> range, dynamic_bitset active):
	m_range{range},
	m_active{std::move(active)}
{
	if (size(m_range->m_range) == 0) {
		m_active = dynamic_bitset{size(m_range->m_range)};
	}
	assert(size(m_range->m_range) == m_active.size());
}


} // namespace util;


#endif

