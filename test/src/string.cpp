#include "../../src/include/string.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(string);

using namespace std::string_literals;

BOOST_AUTO_TEST_CASE(whitspace) {
	const auto str1 = "    x"s;
	BOOST_CHECK(util::find_non_whitespace(str1) == str1.begin()+4);
	const auto str2 = "    "s;
	BOOST_CHECK(util::find_non_whitespace(str2) == str2.end());
	const auto str3 = "x"s;
	BOOST_CHECK(util::find_non_whitespace(str3) == str3.begin());
	const auto str4 = ""s;
	BOOST_CHECK(util::find_non_whitespace(str4) == str4.end());
}

BOOST_AUTO_TEST_CASE(empty_or_comment) {
	BOOST_CHECK(util::is_empty_or_comment("   "s));
	BOOST_CHECK(util::is_empty_or_comment("   "s, ' '));
	BOOST_CHECK(util::is_empty_or_comment("   "s,';'));
	BOOST_CHECK(util::is_empty_or_comment("#foobar  "s));
	BOOST_CHECK(util::is_empty_or_comment("; foo bar"s,';'));
	BOOST_CHECK(util::is_empty_or_comment("  #foobar  "s));
	BOOST_CHECK(util::is_empty_or_comment("  ; foo bar"s,';'));
	BOOST_CHECK(util::is_empty_or_comment("  #foobar  "s));
	BOOST_CHECK(util::is_empty_or_comment("  ; foo bar"s,';'));

	BOOST_CHECK(!util::is_empty_or_comment("  foo # bar  "s));
	BOOST_CHECK(!util::is_empty_or_comment("   foo ; bar"s,';'));
	BOOST_CHECK(!util::is_empty_or_comment("foo # bar  "s));
	BOOST_CHECK(!util::is_empty_or_comment("foo ; bar"s,';'));
	BOOST_CHECK(!util::is_empty_or_comment("foo  bar  "s));
	BOOST_CHECK(!util::is_empty_or_comment("foo  bar"s,';'));
}

BOOST_AUTO_TEST_CASE(strip) {
	BOOST_CHECK_EQUAL("foo"s, util::strip("foo"s));
	BOOST_CHECK_EQUAL("foo"s, util::strip("  foo"s));
	BOOST_CHECK_EQUAL("foo"s, util::strip("foo  "s));
	BOOST_CHECK_EQUAL("foo"s, util::strip("    foo  "s));
	BOOST_CHECK_EQUAL("foo"s, util::strip(" foo"s));
	BOOST_CHECK_EQUAL("foo"s, util::strip("foo "s));
	BOOST_CHECK_EQUAL("foo"s, util::strip(" foo "s));
	BOOST_CHECK_EQUAL(""s, util::strip(""s));
	BOOST_CHECK_EQUAL(""s, util::strip(" "s));
	BOOST_CHECK_EQUAL(""s, util::strip("   "s));
	BOOST_CHECK_EQUAL("foo bar"s, util::strip("foo bar"s));
	BOOST_CHECK_EQUAL("foo  bar"s, util::strip("foo  bar"s));
	BOOST_CHECK_EQUAL("foo bar"s, util::strip("  foo bar"s));
	BOOST_CHECK_EQUAL("foo  bar"s, util::strip("  foo  bar"s));
	BOOST_CHECK_EQUAL("foo bar"s, util::strip(" foo bar  "s));
	BOOST_CHECK_EQUAL("foo  bar"s, util::strip(" foo  bar  "s));
	BOOST_CHECK_EQUAL("foo bar"s, util::strip(" foo bar "s));
	BOOST_CHECK_EQUAL("foo  bar"s, util::strip(" foo  bar "s));
}


BOOST_AUTO_TEST_SUITE_END();

