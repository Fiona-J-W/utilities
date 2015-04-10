#include "utilities/filter.hpp"
#include "utilities/irange.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

#include <boost/test/unit_test.hpp>

template<typename R1, typename R2>
bool is_equal(const R1& lhs, const R2& rhs) {
	return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

BOOST_AUTO_TEST_CASE(basic) {
	const auto actual = util::filter(util::irange(5), [](int i){return i%2;});
	const auto expected = {1,3};
	BOOST_CHECK(is_equal(actual, expected));
}

BOOST_AUTO_TEST_CASE(mutable_functor) {
	const auto actual = util::filter(std::vector<int>{0,1,2,4,4,7},
			[x=0](int i)mutable{
			std::cout << i << ", " << x << "\n";
			return i==x++;});
	const auto expected = {0,1,2,4};
	std::copy(actual.begin(), actual.end(), std::ostream_iterator<int>{std::cout, "\n"});
	BOOST_CHECK(is_equal(actual, expected));
}

