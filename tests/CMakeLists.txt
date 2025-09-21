# =============================================================================
# Build source targets
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./tests")

# Enable testing (this allows us to use the add_test() function)
enable_testing ()

# Build the "hello_test" target
add_executable(hello_test hello_test.cpp)
target_link_libraries(hello_test PRIVATE
    GTest::gtest_main
)

# Enable the tests to be discovered by CTest
include(GoogleTest)
gtest_discover_tests(hello_test)