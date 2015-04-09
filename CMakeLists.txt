project(Utilities)

# to shut up cmake, I have no clue what version this needs:
cmake_minimum_required(VERSION 2.8)


# create sane environment
#####################################################################

# I would love to use those, but cmake insists on using C++11, when I ask for fourteen;
# it would be wise to check whether this problem persists from time to time:
#set_property(GLOBAL PROPERTY CXX_STANDARD 14)
#set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

# Ok, so let's just hardcode all the flags instead:
# TODO: make this portable
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++1y" )

# we want tests:
enable_testing()


# options
#####################################################################
Option(BUILD_TESTS "build-tests" ON)


# required packages
#####################################################################

if(BUILD_TESTS)
	find_package(Boost COMPONENTS unit_test_framework REQUIRED)
endif()


# targets
#####################################################################

include_directories("include")

set(IncludePath "include/utilities")
file(GLOB library_headers "${INCLUDEPATH}/*.hpp")

# If this doesn't work on non-unix: patches are appreciated:
install(DIRECTORY ${IncludePath} DESTINATION "include")

add_custom_target(uninstall COMMAND
	${CMAKE_COMMAND} -E remove_directory "${CMAKE_INSTALL_PREFIX}/include/utilities")

if(BUILD_TESTS)
	file(GLOB test_sources "src/test/*.cpp")
	add_executable(tests
		${test_sources}
	)
	target_link_libraries(tests
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	)
	add_test(
		NAME Unit-Tests
		COMMAND tests
	)
endif()
