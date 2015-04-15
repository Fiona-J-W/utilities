#include <vector>
#include <iterator>
#include <iostream>
#include <utility>

#include <boost/test/unit_test.hpp>

#ifndef UTILITIES_ENABLE_EXPERIMENTAL_FEATURES
#define UTILITIES_ENABLE_EXPERIMENTAL_FEATURES
#endif

#include "utilities/irange.hpp"
#include "utilities/timer.hpp"
#include "utilities/carthesian_product.hpp"


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


