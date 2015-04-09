#ifndef UTILITIES_STRING_HPP
#define UTILITIES_STRING_HPP

#include <algorithm>
#include <cctype>

namespace util {


inline std::string::const_iterator find_non_whitespace(const std::string& str) {
	return std::find_if_not(str.begin(), str.end(), [](char c){return std::isspace(c);});
}

inline bool is_empty_or_comment(const std::string& str, char comment_start = '#') {
	auto it = find_non_whitespace(str);
	return (it == str.end()) || (*it == comment_start);
}

inline std::string strip(const std::string& str) {
	using rev_it = std::reverse_iterator<std::string::const_iterator>;
	auto first = std::find_if_not(str.begin(), str.end(), std::isblank);
	auto last = std::find_if_not(str.rbegin(), rev_it{first}, std::isblank).base();
	return std::string(first, last);
}

}

#endif
