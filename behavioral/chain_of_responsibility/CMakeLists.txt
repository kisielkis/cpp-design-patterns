cmake_minimum_required(VERSION 3.16)
project(ChainOfResponsibility CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build Google Test unit tests" OFF)

add_executable(chain_of_responsibility src/main.cpp)

target_include_directories(chain_of_responsibility PRIVATE include)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
