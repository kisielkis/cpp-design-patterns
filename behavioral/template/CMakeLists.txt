cmake_minimum_required(VERSION 3.16)
project(template CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build Google Test unit tests" OFF)

add_executable(template src/main.cpp)

target_include_directories(template PRIVATE include)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
