#ifndef UTILITIES_RANDOM_HPP
#define UTILITIES_RANDOM_HPP

#include <algorithm>
#include <random>
#include <cstdint>
#include <limits>
#include <vector>
#include <functional>

namespace util {

template<std::size_t N>
std::seed_seq get_seed() {
	auto data = std::array<std::uint32_t, N>{};
	std::random_device rd{};
	std::generate(data.begin(), data.end(), std::ref(rd));
	return std::seed_seq{data.begin(), data.end()};
}

inline std::mt19937& get_urng() {
	thread_local static auto urng = []{
		// 624 = size of the state in mt19937
		auto seed = get_seed<624>();
		return std::mt19937{seed};
	}();
	return urng;
}

template<typename Integer = std::size_t>
inline Integer rand_int() {
	std::uniform_int_distribution<Integer> dist{0, std::numeric_limits<Integer>::max()};
	return dist(get_urng());
}

template<typename Integer = std::size_t>
inline Integer rand_int(Integer max) {
	std::uniform_int_distribution<Integer> dist{0, max};
	return dist(get_urng());
}

template<typename Integer = std::size_t>
inline Integer rand_int(Integer min, Integer max) {
	std::uniform_int_distribution<Integer> dist{min, max};
	return dist(get_urng());
}

template<typename T>
inline std::vector<T> make_random_vec(std::size_t size) {
	std::vector<T> returnvec;
	for (std::size_t i =0; i < size; ++i) {
		returnvec.push_back(rand_int<T>());
	}
	return returnvec;
}

}
#endif
