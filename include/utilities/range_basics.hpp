#ifndef UTILITIES_RANGE_BASICS_HPP
#define UTILITIES_RANGE_BASICS_HPP

#include <cstdint>
#include <iterator>
#include <type_traits>

namespace util {

template<typename T>
std::size_t size(const T& container) {return container.size();}
template<typename T, std::size_t N>
constexpr std::size_t size(const T(&)[N]) {return N;}

namespace impl {
template <typename Iterator> struct is_const_iterator:
	std::is_const<typename std::iterator_traits<Iterator>::value_type> {}
} // namespace impl

template<typename Iterator>
class iterator_range {
public:
	iterator_range(Iterator first, Iterator last):
		m_first{first}, m_last{last} {}
	Iterator begin() {return m_first;}
	Iterator end() {return m_last;}
	auto size() const {return m_last - m_first;}
private:
	Iterator m_first;
	Iterator m_last;
};

template<typename Iterator>
class const_iterator_range {
public:
	static_assert(impl::is_const_iterator<Iterator>::value, "");
	const_iterator_range(Iterator first, Iterator last):
		m_first{first}, m_last{last} {}
	Iterator begin() const {return m_first;}
	Iterator end() const {return m_last;}
	auto size() const {return m_last - m_first;}
private:
	Iterator m_first;
	Iterator m_last;
};

namespace impl {
template<typename Iterator>
const_iterator_range<Iterator> make_iterator_range(Iterator first, Iterator last, std::true_type) {
	return {first, last};
}
template<typename Iterator>
iterator_range<Iterator> make_iterator_range(Iterator first, Iterator last, std::false_type) {
	return {first, last};
}
} // namespace impl

template<typename Iterator>
auto make_iterator_range(Iterator first, Iterator last) {
	return impl::make_iterator_range(first, last, impl::is_const_iterator<Iterator>{});
}

template<typename Iterator>
const_iterator_range<Iterator> make_const_iterator_range(Iterator first, Iterator last) {
	return {first, last};
}


} // namespace util

#endif

