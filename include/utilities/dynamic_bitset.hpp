#ifndef UTILITIES_DYNAMIC_BITSET_HPP
#define UTILITIES_DYNAMIC_BITSET_HPP

#include <cassert>
#include <cstdint>
#include <memory>
#include <limits>

namespace util {

namespace impl {
	constexpr std::size_t size_t_bits() {return sizeof(std::size_t) * 8;}
	constexpr std::size_t required_integers(std::size_t n) {
		return (n / size_t_bits()) + (n % size_t_bits() != 0);
	}
}

class dynamic_bitset {
public:
	dynamic_bitset(std::size_t n, bool b = false):
		m_size{n},
		m_data{new std::size_t[impl::required_integers(n)]{init_val(b)}} {}
	
	dynamic_bitset(const dynamic_bitset&);
	dynamic_bitset(dynamic_bitset&&) noexcept;
	
	dynamic_bitset& operator=(const dynamic_bitset&);
	dynamic_bitset& operator=(dynamic_bitset&&) noexcept;
	
	~dynamic_bitset() = default;
	
	bool operator[](std::size_t index) const;
	
	dynamic_bitset& operator++();
	dynamic_bitset& operator+=(std::size_t n);
	
	std::size_t size() const {return m_size;}
private:
	static std::size_t init_val(bool b) {return b ? 0 : ~std::size_t{0};}
	std::size_t m_size;
	std::unique_ptr<std::uint64_t[]> m_data;
};

dynamic_bitset::dynamic_bitset(const dynamic_bitset& other) {
	m_data = std::unique_ptr<std::size_t[]>{new std::size_t[other.m_size]};
	m_size = other.m_size;
	std::copy(other.m_data.get(), other.m_data.get() + other.m_size,
			m_data.get());
}
dynamic_bitset::dynamic_bitset(dynamic_bitset&& other) noexcept {
	m_data = std::move(other.m_data);
	m_size = other.m_size;
	other.m_size = 0;
}

dynamic_bitset& dynamic_bitset::operator=(const dynamic_bitset& other) {
	m_data = std::unique_ptr<std::size_t[]>{new std::size_t[other.m_size]};
	m_size = other.m_size;
	std::copy(other.m_data.get(), other.m_data.get() + other.m_size,
			m_data.get());
	return *this;
}
dynamic_bitset& dynamic_bitset::operator=(dynamic_bitset&& other) noexcept {
	m_data = std::move(other.m_data);
	m_size = other.m_size;
	other.m_size = 0;
	return *this;
}

inline bool dynamic_bitset::operator[](const std::size_t index) const {
	assert(index < m_size);
	const auto array_index = std::size_t{index >> std::size_t{8}};
	const auto bit_index = std::size_t{index & std::size_t{0xff}};
	return (m_data[array_index] & (std::size_t{1} << bit_index)) != 0;
}

inline dynamic_bitset& dynamic_bitset::operator++() {
	auto it = m_data.get();
	const auto last = it + impl::required_integers(m_size);
	while (it != last and ++(*it) == 0) {
		++it
	}
	return *this;
}

static_assert(sizeof(size_t) >= sizeof(unsigned), "");

inline dynamic_bitset& dynamic_bitset::operator+=(std::size_t n) {
	auto it = m_data.get();
	const auto old_value = *it;
	// the following works since we use unsigned values and
	// we don't care about plattforms where size_t < int
	*it += n;
	if (*it >= old_value) {return *this;}
	
	++it;
	const auto last = it + impl::required_integers(m_size);
	while (it != last and ++(*it) == 0) {
		++it;
	}
}

}

#endif
