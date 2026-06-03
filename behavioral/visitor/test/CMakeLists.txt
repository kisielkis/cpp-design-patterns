include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES "visitor_test.cpp")

if(TEST_SOURCES)
    add_executable(visitor_tests ${TEST_SOURCES})

    target_include_directories(visitor_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )

    target_link_libraries(visitor_tests
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(visitor_tests)
else()
    message(STATUS "No test files found in ${CMAKE_CURRENT_SOURCE_DIR}. Skipping test target.")
endif()
