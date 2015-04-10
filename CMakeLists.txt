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
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++1y -fPIC" )

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
file(GLOB LibraryHeaders "${IncludePath}/*.hpp")
set(SourcePath "src/lib")
file(GLOB LibrarySources "${SourcePath}/*.cpp")

add_library(UtilitiesCore OBJECT ${LibraryHeaders} ${LibrarySources})
add_library(UtilitiesStatic STATIC $<TARGET_OBJECTS:UtilitiesCore>)
add_library(UtilitiesShared SHARED $<TARGET_OBJECTS:UtilitiesCore>)

set_target_properties(UtilitiesStatic PROPERTIES OUTPUT_NAME utilities)
if(${UNIX})
	set_target_properties(UtilitiesShared PROPERTIES OUTPUT_NAME utilities)
else()
	set_target_properties(UtilitiesShared PROPERTIES OUTPUT_NAME utilities_shared)
endif()


# If this doesn't work on non-unix: patches are appreciated:
install(TARGETS UtilitiesStatic UtilitiesShared 
	LIBRARY DESTINATION "lib"
	ARCHIVE DESTINATION "lib"
)
install(DIRECTORY ${IncludePath} DESTINATION "include")

# TODO: make this work completely, aka also remove the libs
#add_custom_target(uninstall COMMAND
#	${CMAKE_COMMAND} -E remove_directory "${CMAKE_INSTALL_PREFIX}/include/utilities")

if(BUILD_TESTS)
function(addUnitTest Filename)
	get_filename_component(Test ${Filename} NAME_WE )
	set_property(SOURCE ${Filename} APPEND PROPERTY COMPILE_DEFINITIONS
		BOOST_TEST_DYN_LINK
		BOOST_TEST_MAIN
		BOOST_TEST_MODULE=${Test})
	set(TestName "test_${Test}")
	add_executable(${TestName} ${Source})
	target_link_libraries(${TestName}
		UtilitiesShared
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	)
	add_test(
		NAME "<${Test}.hpp>"
		COMMAND ${TestName}
	)
endfunction(addUnitTest)

	file(GLOB TestSources "src/test/*.cpp")

	foreach(Source ${TestSources})
		addUnitTest(${Source})
	endforeach(Source)
endif()
