#include "utilities/random.hpp"
#include "utilities/irange.hpp"

#include <algorithm>
#include <cstdint>

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(random_values_in_range) {
	for (auto i: util::irange(std::size_t{100})) {
		BOOST_CHECK((util::rand_int<int>() > 0));
		BOOST_CHECK((util::rand_int({i}) <= i));
		const auto temp = util::rand_int<int>(-23, i);
		BOOST_CHECK(temp <= static_cast<int>(i));
		BOOST_CHECK(temp >= -23);
	}
}

BOOST_AUTO_TEST_CASE(random_array_size) {
	for (auto i: util::irange(std::size_t{10})) {
		BOOST_CHECK_EQUAL(util::make_random_vec<int>(i).size(), i);
	}
}
