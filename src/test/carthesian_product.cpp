#include "utilities/carthesian_product.hpp"
#include "utilities/irange.hpp"

#include <algorithm>
#include <tuple>
#include <initializer_list>

#include <boost/test/unit_test.hpp>

template<typename T, typename Prod>
bool is_equivalent(const Prod& actual, std::initializer_list<T> expected) {
	return std::equal(actual.begin(), actual.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(basic) {
	const auto actual = util::carthesian_product(util::irange(2), util::irange(1,3));
	auto t = [](const auto& x, const auto& y){return std::make_tuple(x, y);};
	const auto expected = {t(0,1), t(0,2), t(1,1), t(1,2)};
	BOOST_CHECK(is_equivalent(actual, expected ));
}

BOOST_AUTO_TEST_CASE(empty) {
	const auto actual = util::carthesian_product(util::irange(0,0), util::irange(2));
	const auto expected = std::initializer_list<std::tuple<int, int>>{};
	BOOST_CHECK(is_equivalent(actual, expected));
}

BOOST_AUTO_TEST_CASE(big_size) {
	const auto prod = util::carthesian_product(util::irange(100), util::irange(23), util::irange(42));
	auto temp = std::vector<std::tuple<int, int, int>>{};
	std::copy(prod.begin(), prod.end(), std::back_inserter(temp));
	BOOST_CHECK_EQUAL(temp.size(), 100 * 23 * 42);
}
