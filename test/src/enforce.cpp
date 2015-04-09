#include "../../src/include/enforce.hpp"

#include <fstream>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(enforce);

BOOST_AUTO_TEST_CASE(default_case) {
	BOOST_CHECK_THROW(util::enforce(false, ""), std::runtime_error);
	BOOST_CHECK_NO_THROW(util::enforce(true, ""));

	const auto str = std::string{};
	BOOST_CHECK_THROW(util::enforce(false, str), std::runtime_error);
	BOOST_CHECK_NO_THROW(util::enforce(true, str));
}

BOOST_AUTO_TEST_CASE(other_exception) {
	class test_except{
	public:
		test_except(const char*){}
	};
	BOOST_CHECK_THROW(util::enforce<test_except>(false, ""), test_except);
	BOOST_CHECK_NO_THROW(util::enforce<test_except>(true, ""));

	const auto str = std::string{};
	BOOST_CHECK_THROW(util::enforce<test_except>(false, str), test_except);
	BOOST_CHECK_NO_THROW(util::enforce<test_except>(true, str));
}

BOOST_AUTO_TEST_CASE(stream) {
	std::ofstream stream;
	BOOST_CHECK_THROW(util::enforce_opened(stream, ""), std::runtime_error);
	// stream.open("some file that can always be opened");
	// BOOST_CHECK_NO_THROW(util::enforce_opened(stream, ""));
}

BOOST_AUTO_TEST_SUITE_END();
