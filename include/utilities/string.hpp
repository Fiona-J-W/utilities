#ifndef UTILITIES_STRING_HPP
#define UTILITIES_STRING_HPP

#include <algorithm>
#include <cstring>
#include <cstdint>

#include <experimental/string_view>

namespace util {

namespace impl {

std::size_t string_size(const std::string& str) {return str.size();}
std::size_t string_size(const std::experimental::string_view& str) {return str.size();}
template<std::size_t N> std::size_t string_size(const char(&)[N]) {return N-1;}
std::size_t string_size(const char* str) {return std::strlen(str);}
std::size_t string_size(char) {return 1;}

void append(std::string& str, const std::string& postfix) {
	str += postfix;
}
void append(std::string& str, const std::experimental::string_view& postfix) {
	str.append(postfix.begin(), postfix.end());
}
void append(std::string& str, const char postfix) {
	str += postfix;
}
void append(std::string& str, const char* postfix) {
	str += postfix;
}
template<std::size_t N>
void append(std::string& str, const char(&postfix)[N]) {
	str.append(postfix, postfix + N);
}

} // namespace impl


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

template<typename... Strings>
std::string concat(std::string head, const Strings&... strings) {
	const auto sizes = std::initializer_list<std::size_t>{impl::string_size(strings)...};
	const auto total_size = std::accumulate(sizes.begin(), sizes.end(), std::size_t{}) + head.size();
	head.reserve(total_size);
	// The initializer list guarantees the correct execution-order:
	(void) std::initializer_list<int>{(impl::append(head, strings),0)...};
	return head;
}
template<typename... Strings>
std::string concat(const Strings&... strings) {return concat(std::string{}, strings...);}

}

#endif
