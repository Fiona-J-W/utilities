#ifndef UTILITIES_DYNAMIC_BITSET_HPP
#define UTILITIES_DYNAMIC_BITSET_HPP

#include <cassert>
#include <cstdint>
#include <memory>
#include <limits>

namespace util {

class dynamic_bitset {
public:
	dynamic_bitset(std::size_t n, bool b = false);
	
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


}

#endif
