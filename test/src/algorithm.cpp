#include <cassert>
#include <vector>

#define BOOST_TEST_MODULE utilities main
#include <boost/test/unit_test.hpp>

#include "../../src/include/algorithm.hpp"



BOOST_AUTO_TEST_CASE(unstable_erase_one_1){
	std::vector<int> vec;
	
	util::unstable_erase_one(vec, 0);
	BOOST_CHECK(vec.empty());
	
	vec.push_back(0);
	util::unstable_erase_one(vec, 0);
	BOOST_CHECK(vec.empty());
	
	vec.push_back(1);
	util::unstable_erase_one(vec, 0);
	BOOST_CHECK(vec == std::vector<int>{1});
	
	vec.push_back(0);
	util::unstable_erase_one(vec, 0);
	BOOST_CHECK(vec == std::vector<int>{1});
}

