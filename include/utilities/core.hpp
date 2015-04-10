#ifndef UTILITIES_CORE_HPP
#define UTILITIES_CORE_HPP

#include <iterator>

/**
 * Resolves overloaded functions when passing them to
 * function-templates.
 *
 * Example:
 * std::transform(vec1.begin(), vec1.end(), vec2.begin(), std::back_inserter(vec3),
 *                std::max); // ERROR: cannot infer template-argument
 *
 * std::transform(vec1.begin(), vec1.end(), vec2.begin(), std::back_inserter(vec3),
 *                UTIL_RESOLVE(std::max)); // Works.
 *
 * Description: http://florianjw.de/en/passing_overloaded_functions.html
 */
#define UTIL_RESOLVE(...) \
	[](auto&&...args)->decltype(auto){return __VA_ARGS__(std::forward<decltype(args)>(args)...);}


namespace util {

template<typename T> using pointer = T*;



} // namespace util


#endif
