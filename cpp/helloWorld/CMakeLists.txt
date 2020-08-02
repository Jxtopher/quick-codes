#
# @Author: *
# @License: *
# @Date: *
# @Version: *
# @Description: *
#

cmake_minimum_required(VERSION 3.0)

project(helloworld)

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "-std=c++2a -pedantic -Wall -Wextra -Wcast-align -Wctor-dtor-privacy    \
                                -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
                                -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept    \
                                -Woverloaded-virtual -Wredundant-decls  -Wsign-promo        \
                                -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default \
                                -Wundef -Werror -Wno-unused -Wsign-conversion -Wshadow  -Wcast-qual -Wold-style-cast")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

###############################################################################
# Load modules cmake
###############################################################################
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/.cmake")
include(cppcheck)       #
include(clang-format)   #
include(version)        # Version name generator form git branch, hash
include(doxygen)        # Create le documentation


## HelloWorld
add_executable(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} sources/main.cpp)

## Cppunit
find_package(PkgConfig REQUIRED)
pkg_check_modules(CPPUNIT cppunit)
link_libraries(${CPPUNIT_LIBRARIES})

## HelloWorld unit test
add_executable(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} tests-unitaires/unitTest.cpp)
target_include_directories(${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} PUBLIC sources/)

## Test unitaire
enable_testing()
add_test(NAME ${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE} COMMAND "${PROJECT_NAME}-unittest-${CMAKE_BUILD_TYPE}")