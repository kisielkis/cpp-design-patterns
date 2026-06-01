cmake_minimum_required(VERSION 3.16)
project(Command CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build Google Test unit tests" OFF)

add_executable(command src/main.cpp)

target_include_directories(command PRIVATE include)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
