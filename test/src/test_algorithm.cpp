#include "../../src/include/algorithm.hpp"

#include "test_algorithm.hpp"

#include <cassert>
#include <vector>


void test_unstable_erase_one() {
	std::vector<int> vec;
	
	util::unstable_erase_one(vec, 0);
	assert(vec.empty());
	
	vec.push_back(0);
	util::unstable_erase_one(vec, 0);
	assert(vec.empty());
	
	vec.push_back(1);
	util::unstable_erase_one(vec, 0);
	assert(vec == std::vector<int>{1});
	
	vec.push_back(0);
	util::unstable_erase_one(vec, 0);
	assert(vec == std::vector<int>{1});
}

void test_algorithm() {
	test_unstable_erase_one();
}
