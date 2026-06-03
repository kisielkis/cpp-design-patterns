include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES "test_*.cpp")

if(TEST_SOURCES)
    add_executable(state_tests ${TEST_SOURCES} ../src/State.cpp)

    target_include_directories(state_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )

    target_link_libraries(state_tests
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(state_tests)
else()
    message(STATUS "No test files found in ${CMAKE_CURRENT_SOURCE_DIR}. Skipping test target.")
endif()
