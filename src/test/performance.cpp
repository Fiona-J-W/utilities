#include <vector>
#include <iterator>
#include <iostream>
#include <utility>

#include <boost/test/unit_test.hpp>

#ifndef UTILITIES_ENABLE_EXPERIMENTAL_FEATURES
#define UTILITIES_ENABLE_EXPERIMENTAL_FEATURES
#endif

#include "utilities/carthesian_product.hpp"
#include "utilities/irange.hpp"
#include "utilities/string.hpp"
#include "utilities/timer.hpp"


std::pair<unsigned long, int> test_carthesian_product() {
	auto timer = util::timer{};
	auto res = unsigned{};
	timer.start();
	for(auto e: util::experimental::carthesian_product(util::irange(100u), util::irange(20u), util::irange(50u))) {
		auto x = int{};
		auto y = int{};
		auto z = int{};
		std::tie(x,y,z) = e;
		res += x*y*z;
	}
	timer.stop();
	return {timer.ticks(), res};
}


std::pair<unsigned long, int> test_irange_loops() {
	auto timer = util::timer{};
	auto res = unsigned{};
	timer.start();
	for(auto x : util::irange(100u)) {
		for(auto y : util::irange(20u)) {
			for(auto z : util::irange(50u)) {
				res += x*y*z;
			}
		}
	}
	timer.stop();
	return {timer.ticks(), res};
}


std::pair<unsigned long, int> test_loops() {
	auto timer = util::timer{};
	auto res = unsigned{};
	timer.start();
	for(auto x = unsigned{}; x < 100u; ++x) {
		for(auto y = unsigned{}; y <  20u; ++y) {
			for(auto z = unsigned{}; z <  50u; ++z) {
				res += x*y*z;
			}
		}
	}
	timer.stop();
	return {timer.ticks(), res};
}


BOOST_AUTO_TEST_CASE(carthesian_product_vs_loops) {
	for(auto i = 0; i < 10; ++i) {
		const auto results1 = test_carthesian_product();
		const auto results2 = test_irange_loops();
		const auto results3 = test_loops();
		std::cout
			<< "carthesian_product: " << results1.first << "\t," << results1.second << '\n'
			<< "irange-loops:       " << results2.first << "\t," << results2.second << '\n'
			<< "loops:              " << results3.first << "\t," << results3.second << '\n';
	}
}

BOOST_AUTO_TEST_CASE(operator_plus_vs_concat) {
	using util::timer;
	auto plus   = std::vector<timer::tick_type>{};
	auto concat = std::vector<timer::tick_type>{};
	using namespace std::string_literals;
	const auto str1 = "foobar";
	const auto str2 = "foobar"s;
	const auto str3 = "foobar";
	const auto str4 = "foobar"s;
	const auto str5 = "foobar";
	const auto str6 = "foobar"s;

	for(auto i: util::irange(30)) {
		(void) i;
		{
			auto t = util::timer{};
			t.start();
			const auto result = str1 + str2 + str3 + str4 + str5 + str6;
			t.stop();
			plus.push_back(t.ticks());
		}
		{
			auto t = util::timer{};
			t.start();
			const auto result = util::concat(str1, str2, str3, str4, str5, str6);
			t.stop();
			concat.push_back(t.ticks());
		}
	}
	const auto total_plus   = std::accumulate(plus.begin(), plus.end(), timer::tick_type{});
	const auto total_concat = std::accumulate(concat.begin(), concat.end(), timer::tick_type{});
	// This should be clear enough to allow this test:
	BOOST_CHECK(total_plus > total_concat);
	std::cout
		<< "plus:   " << total_plus << '\n'
		<< "concat: " << total_concat << '\n';
}
