#include "utilities/mut_arguments.hpp"

#include <boost/test/unit_test.hpp>

using util::mut;
using util::mut_arg;

BOOST_AUTO_TEST_CASE(basics) {
	const auto fun1 = [](mut_arg<int>){};
	auto i = 23;
	fun1(mut(i));

	const auto fun2 = [&](mut_arg<int> arg){fun1(mut(arg));};
	fun2(mut(i));
}
