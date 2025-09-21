# ============================================================================
# A CMake build script for the C++ CLI application using the clipp.h library.
# ============================================================================

# Define the minimum required version of CMake
cmake_minimum_required (VERSION 3.14...3.40)

# Define the project name and version
project (
    cli_framework
    VERSION 0.1
    DESCRIPTION "A simple C++ CLI application using the clipp.h library"
    HOMEPAGE_URL ""
    LANGUAGES C CXX
    )

# Set the C++ standard to C++17 and make it required
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CMake module path
list (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

# Set the build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif ()

# Set to build with shared libraries by default
option (BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Set to build with tests by default
option (BUILD_TESTS "Build with tests" ON)

# Determine whether the libraries are built as shared or static
if (BUILD_SHARED_LIBS)
    set (LIB_TYPE SHARED)
else ()
    set (LIB_TYPE STATIC)
endif (BUILD_SHARED_LIBS)

# Set the output directory for the executable
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the clipp.h library
add_library (clipp INTERFACE)
target_sources (clipp INTERFACE "${PROJECT_SOURCE_DIR}/extern/clipp/clipp.hpp")
target_include_directories (
    clipp
    INTERFACE
    "${PROJECT_SOURCE_DIR}/extern/clipp"
    )

# Add the sqlite3 library
add_library (sqlite3 STATIC)  # Use STATIC to avoid the need for the SQLITE_API
                              # macro in the sqlite3.h header
target_sources (
    sqlite3
    PRIVATE
    "${PROJECT_SOURCE_DIR}/extern/sqlite3/sqlite3.c"
    )
target_include_directories (
    sqlite3
    PUBLIC
    "${PROJECT_SOURCE_DIR}/extern/sqlite3"
    )

# Enable FetchContent module
include(FetchContent)

# Add the CSV Parser library
FetchContent_Declare(
    csv_parser
    GIT_REPOSITORY https://github.com/vincentlaucsb/csv-parser.git
    GIT_TAG 2.3.0
    )
FetchContent_MakeAvailable(csv_parser)

# Patch the CSV Parser library CMakeLists.txt file
configure_file (
    "${PROJECT_SOURCE_DIR}/extern/csv-parser/CMakeLists.txt.in"
    "${csv_parser_SOURCE_DIR}/CMakeLists.txt"
    COPYONLY
    )

# Add the source files directory
add_subdirectory ("${PROJECT_SOURCE_DIR}/src")

# Check if the tests are enabled
if (NOT DEFINED BUILD_TESTS)
    option (BUILD_TESTS "Build the tests" OFF)  # Default to OFF
endif ()

# Add the test files directory if the tests are enabled
if (BUILD_TESTS)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's
    # compiler/linker settings
    set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    add_subdirectory ("${PROJECT_SOURCE_DIR}/tests")

endif ()
