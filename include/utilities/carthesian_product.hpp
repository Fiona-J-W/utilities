
#ifndef UTILITIES_MULTI_RANGE_HPP
#define UTILITIES_MULTI_RANGE_HPP


/*
 * Sadly the EXTREME runtime-overhead makes it impossible
 * to recommend actual usage at this point.
 */
#ifndef UTILITIES_ENABLE_EXPERIMENTAL_FEATURES
#error "experimental featues have to be enabled via a compile-switch"
#endif

#include <utility>
#include <iterator>
#include <tuple>
#include <cstdint>
#include <type_traits>

#include "core.hpp"

namespace util {
namespace experimental {

template <typename CarthesianProductRange>
class carthesian_product_iterator;
template <typename... Ranges>
class carthesian_product_range;

template <typename... Ranges>
carthesian_product_range<Ranges...> make_carthesian_product_range(Ranges&&...);

namespace impl {
template <std::size_t I>
struct index_t : std::integral_constant<std::size_t, I> {};
template <typename Container>
using iterator_t = decltype(std::begin(std::declval<Container>()));
template <typename Iterator>
using value_type_t = typename std::iterator_traits<Iterator>::value_type;
template <typename Container>
using container_value_type_t =
        typename std::iterator_traits<decltype(std::begin(std::declval<Container>()))>::value_type;

template <template <typename> class, typename>
struct apply_to_tuple_members {};

template <template <typename> class Metafunction, typename... Ts>
struct apply_to_tuple_members<Metafunction, std::tuple<Ts...>> {
	using type = std::tuple<Metafunction<Ts>...>;
};
template <template <typename> class Metafunction, typename T>
using apply_to_tuple_members_t = typename apply_to_tuple_members<Metafunction, T>::type;
} // namespace impl

template <typename... Ranges>
class carthesian_product_range {
public:
	template <typename... ArgumentRanges>
	carthesian_product_range(ArgumentRanges&&... args)
	        : m_ranges{std::forward<ArgumentRanges>(args)...} {}

	using iterator_tuple_t = std::tuple<impl::iterator_t<std::add_const_t<Ranges>>...>;
	using iterator = carthesian_product_iterator<carthesian_product_range<Ranges...>>;
	using value_type =
	        std::tuple<std::decay_t<impl::container_value_type_t<std::add_const_t<Ranges>>>...>;

	auto begin() const { return begin_impl(std::make_index_sequence<num_ranges()>{}); }
	auto end() const { return end_impl(std::make_index_sequence<num_ranges()>{}); }

	template <std::size_t Index>
	auto& get() {
		return std::get<Index>(m_ranges);
	}
	template <std::size_t Index>
	const auto& get() const {
		return std::get<Index>(m_ranges);
	}

	constexpr static std::size_t num_ranges() { return sizeof...(Ranges); }

private:
	template <std::size_t... Indexes>
	auto begin_impl(std::integer_sequence<std::size_t, Indexes...>) const {
		return iterator{*this, std::begin(get<Indexes>())...};
	}
	template <std::size_t... Indexes>
	auto end_impl(std::integer_sequence<std::size_t, 0, Indexes...>) const {
		return iterator{*this, std::end(get<0>()), std::begin(get<Indexes>())...};
	}

	std::tuple<std::add_const_t<Ranges>...> m_ranges;
};

template <typename CarthesianProductRange>
class carthesian_product_iterator {
public:
	using value_type = typename CarthesianProductRange::value_type;
	using reference = impl::apply_to_tuple_members_t<std::add_lvalue_reference_t, value_type>;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::forward_iterator_tag;
	using pointer = impl::apply_to_tuple_members_t<std::add_lvalue_reference_t, value_type>*;

	template <typename... Args>
	carthesian_product_iterator(const CarthesianProductRange& mr, Args&&... args)
	        : m_carthesian_product_range{&mr}, m_iterators{std::forward<Args>(args)...} {}

	friend bool operator==(const carthesian_product_iterator& lhs,
	                       const carthesian_product_iterator& rhs) {
		return lhs.m_iterators == rhs.m_iterators;
	}
	friend bool operator!=(const carthesian_product_iterator& lhs,
	                       const carthesian_product_iterator& rhs) {
		return !(lhs == rhs);
	}

	carthesian_product_iterator& operator++() {
		increment();
		return *this;
	}
	carthesian_product_iterator operator++(int) {
		auto tmp = *this;
		increment();
		return tmp;
	}

	auto operator*() { return dereference(); }
	auto operator -> () { return dereference(); }

private:
	util::pointer<const CarthesianProductRange> m_carthesian_product_range;
	typename CarthesianProductRange::iterator_tuple_t m_iterators;

	constexpr static std::size_t num_ranges() { return CarthesianProductRange::num_ranges(); }

	// we cannot specialize member-templates of unspecialized templates,
	// so we have to emulate that behavior by overloading functions:
	// the returned bool tells, whether the iterators have to be set back to the beginning
	template <typename Index = impl::index_t<num_ranges() - 1>>
	void increment(Index = {});
	void increment(impl::index_t<0>);

	template <std::size_t Index>
	decltype(auto) dereference_impl() const {
		return *std::get<Index>(m_iterators);
	}

	template <std::size_t... Indexes>
	decltype(auto) dereference_impl(std::integer_sequence<std::size_t, Indexes...>) const {
		return std::tie(dereference_impl<Indexes>()...);
	}

	decltype(auto) dereference() const {
		return dereference_impl(std::make_index_sequence<num_ranges()>{});
	}
};

template <typename CarthesianProductRange>
template <typename Index>
void carthesian_product_iterator<CarthesianProductRange>::increment(Index) {
	auto& range = m_carthesian_product_range->template get<Index::value>();
	auto& it = std::get<Index::value>(m_iterators);
	++it;
	if (it == std::end(range)) {
		increment(impl::index_t<Index::value - 1>{});
		it = std::begin(range);
	}
}

template <typename CarthesianProductRange>
void carthesian_product_iterator<CarthesianProductRange>::increment(impl::index_t<0>) {
	auto& it = std::get<0>(m_iterators);
	++it;
}

template <typename... Ranges>
carthesian_product_range<Ranges...> carthesian_product(Ranges&&... ranges) {
	return carthesian_product_range<Ranges...>{std::forward<Ranges>(ranges)...};
}

}} // namespace util::experimental

#endif
