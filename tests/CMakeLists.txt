# =============================================================================
# CMake build script for the `C++ Playground' unit tests
# =============================================================================

# ============================================================================
#
# 2026-01-09 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Added the `LogServiceTest' target.
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

# To make unit tests discoverable by CTest, we need to include the GoogleTest
# CMake module
include(GoogleTest)


# -----------------------------------------------------------------------------
# DummyClassTest
# -----------------------------------------------------------------------------

# Show message that we are building the `DummyClassTest' target
message (STATUS "Configuring the `DummyClassTest' unit tests ...")

# Define the `DummyClassTest' target
add_executable(DummyClassTest)

# Add sources to the `DummyClassTest' target
target_sources(
    DummyClassTest
    PRIVATE
        DummyClassTest.cxx
)

target_link_libraries(
  DummyClassTest
  PUBLIC
    LoggingService
    GTest::gtest_main
)

# Enable the tests to be discovered by CTest
gtest_discover_tests(
    DummyClassTest
    DISCOVERY_MODE PRE_TEST
    WORKING_DIRECTORY $<TARGET_FILE_DIR:DummyClassTest>
)


# -----------------------------------------------------------------------------
# dummy_test
# -----------------------------------------------------------------------------

# Show message that we are building the `dummy_test' target
message (STATUS "Configuring the `dummy_test' unit tests ...")

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
gtest_discover_tests(
    dummy_test
    DISCOVERY_MODE PRE_TEST
    WORKING_DIRECTORY $<TARGET_FILE_DIR:dummy_test>
)


# -----------------------------------------------------------------------------
# LogServiceTest
# -----------------------------------------------------------------------------

# Show message that we are building the `LogServiceTest` target
message (STATUS "Configuring the `LogServiceTest' unit tests ...")

# Define the `LogServiceTest' target
add_executable(LogServiceTest)

# Add sources to the `LogServiceTest' target
target_sources(
    LogServiceTest
    PRIVATE
        LogServiceTest.cxx
)

# Define the target link libraries for the `LogServiceTest' target
target_link_libraries(
  LogServiceTest
  PUBLIC
    LoggingService
    GTest::gtest_main
)

# Enable the tests to be discovered by CTest
gtest_discover_tests(
  LogServiceTest
  DISCOVERY_MODE PRE_TEST
  WORKING_DIRECTORY $<TARGET_FILE_DIR:LogServiceTest>
)


# End of `CMakeLists.txt'
