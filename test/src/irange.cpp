#include "../../src/include/irange.hpp"

#include <algorithm>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(irange);


BOOST_AUTO_TEST_CASE(single_arg_irange_1) {
	const auto expected = {0u, 1u, 2u};
	const auto actual = util::irange(3u);
	BOOST_CHECK(
	        std::equal(actual.begin(), actual.end(), expected.begin(), expected.end()));
}

BOOST_AUTO_TEST_CASE(single_arg_irange_2) {
	const auto expected = std::initializer_list<unsigned>{};
	const auto actual = util::irange(0u);
	BOOST_CHECK(
	        std::equal(actual.begin(), actual.end(), expected.begin(), expected.end()));
}

BOOST_AUTO_TEST_CASE(single_arg_irange_3) {
	const auto expected = {0u, 2u};
	const auto actual = util::irange<unsigned, 2>(3u);
	BOOST_CHECK(
	        std::equal(actual.begin(), actual.end(), expected.begin(), expected.end()));
}


BOOST_AUTO_TEST_CASE(dual_arg_irange_1) {
	const auto expected = {1u, 2u};
	const auto actual = util::irange(1u, 3u);
	BOOST_CHECK(
	        std::equal(actual.begin(), actual.end(), expected.begin(), expected.end()));
}

BOOST_AUTO_TEST_CASE(dual_arg_irange_2) {
	const auto expected = std::initializer_list<unsigned>{};
	const auto actual = util::irange(1u, 1u);
	BOOST_CHECK(
	        std::equal(actual.begin(), actual.end(), expected.begin(), expected.end()));
}

BOOST_AUTO_TEST_CASE(dual_arg_irange_3) {
	const auto expected = {1u, 3u};
	const auto actual = util::irange<unsigned, 2>(1u, 4u);
	BOOST_CHECK(
	        std::equal(actual.begin(), actual.end(), expected.begin(), expected.end()));
}


BOOST_AUTO_TEST_CASE(step_arg_irange_1) {
	const auto expected = std::initializer_list<unsigned>{1u, 3u};
	const auto actual = util::irange(1u, 5u, 2u);
	BOOST_CHECK(
	        std::equal(actual.begin(), actual.end(), expected.begin(), expected.end()));
}

BOOST_AUTO_TEST_CASE(step_arg_irange_2) {
	const auto expected = std::initializer_list<unsigned>{1u, 3u};
	const auto actual = util::irange(1u, 4u, 2u);
	BOOST_CHECK(
	        std::equal(actual.begin(), actual.end(), expected.begin(), expected.end()));
}

BOOST_AUTO_TEST_CASE(step_arg_irange_3) {
	const auto expected = std::initializer_list<unsigned>{};
	const auto actual = util::irange(2u, 2u, 3u);
	BOOST_CHECK(
	        std::equal(actual.begin(), actual.end(), expected.begin(), expected.end()));
}

BOOST_AUTO_TEST_CASE(number_iterator_distance) {
	const auto fixed_range = util::irange<int, 2>(1, 5);
	BOOST_CHECK_EQUAL((fixed_range.end() - fixed_range.begin()), 2);
	const auto dynamic_range = util::irange(1, 5, 2);
	BOOST_CHECK_EQUAL((dynamic_range.end() - dynamic_range.begin()), 2);
}

BOOST_AUTO_TEST_SUITE_END();
