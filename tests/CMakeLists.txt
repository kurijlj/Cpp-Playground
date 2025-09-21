# =============================================================================
# CMake build script for the `C++ Playground' unit tests
# =============================================================================

# ============================================================================
#
# 2025-09-21 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Created.
#
# ============================================================================

# Print message to console that we are building the tests targets
message(STATUS "Configuring unit tests ...")

# =============================================================================
# Build test targets
# =============================================================================

include_directories(
    ../include
)

# -----------------------------------------------------------------------------
# dummy_test
# -----------------------------------------------------------------------------

# Show message that we are building the `dummy_test' target
message (STATUS "Configuring the `dummy_test' unit test ...")

# Build the `dummy_test' target
add_executable(dummy_test
    dummy_test.cxx
)

target_link_libraries(dummy_test PUBLIC
    GTest::gtest_main
)

# add_custom_command(
#     TARGET dummy_test POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_SOURCE_DIR}/tests/test_data
#             $<TARGET_FILE_DIR:dummy_test>
# )

# Enable the tests to be discovered by CTest
include(GoogleTest)
gtest_discover_tests(
    dummy_test
    DISCOVERY_MODE PRE_TEST
    WORKING_DIRECTORY $<TARGET_FILE_DIR:dummy_test>
)


# End of `CMakeLists.txt'
