cmake_minimum_required(VERSION 3.16)
project(CppDesignPatterns CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build Google Test unit tests" OFF)

add_subdirectory(behavioral)
add_subdirectory(creational)
add_subdirectory(structural)
