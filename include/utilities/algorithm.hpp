#ifndef UTILITIES_ALGORITHM_HPP
#define UTILITIES_ALGORITHM_HPP

#include <cassert>
#include <algorithm>
#include <iterator>
#include <cstdint>

namespace util {

template<typename Iterator, typename Value>
bool contains(Iterator begin, Iterator end, const Value& val) {
	return std::find(begin, end, val) != end;
}

template<typename Container, typename Value>
bool contains(const Container& container, const Value& val) {
	using std::begin;
	using std::end;
	return contains(begin(container), end(container), val);
}

template<typename Container, typename Pred>
void erase_if(Container& cont, Pred pred) {
	auto begin = cont.begin();
	auto end = cont.end();
	cont.erase(std::remove_if(begin, end, pred), end);
}

template<typename Container, typename Value>
void erase(Container& cont, const Value& val) {
	auto begin = cont.begin();
	auto end = cont.end();
	cont.erase(std::remove(begin, end, val), end);
}

template<typename Container, typename Value>
void unstable_erase_one(Container& cont, const Value& val) {
	auto it = std::find(begin(cont), end(cont), val);
	if (it == end(cont)) {
		return;
	}
	*it = std::move(cont.back());
	cont.pop_back();
}

template<typename Container, typename Pred>
void unstable_erase_one_if(Container& cont, Pred pred) {
	auto it = std::find_if(begin(cont), end(cont), pred);
	if (it == end(cont)) {
		return;
	}
	*it = std::move(cont.back());
	cont.pop_back();
}


template<typename Function, typename...Args>
void times(std::size_t n, Function&& f, Args&&...args) {
	for(std::size_t i = 0; i < n; ++i) {
		f(args...);
	}
}
template<typename Function>
void times(std::size_t n, Function&& f) {
	for(std::size_t i = 0; i < n; ++i) {
		f();
	}
}

}



#endif
