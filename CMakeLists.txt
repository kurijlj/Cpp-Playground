# =============================================================================
# A CMake build script for the `C++ Playground' project
# =============================================================================

# ============================================================================
#
# 2025-09-21 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Created.
#
# ============================================================================

# ============================================================================
#
# Most common compiler options for available buld types:
#
#   Debug:          -g -O0
#   Release:        -O3 -DNDEBUG
#   RelWithDebInfo: -g -O2 -DNDEBUG
#   MinSizeRel:     -Os -DNDEBUG
#
#   Source: https://stackoverflow.com/questions/48754619/what-are-cmake-build-type-debug-release-relwithdebinfo-and-minsizerel
# ============================================================================


# -----------------------------------------------------------------------------
# Define the minimum required version of CMake
# -----------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.14...3.29)


# -----------------------------------------------------------------------------
# Enable Hot Reload for MSVC compilers if supported.
# -----------------------------------------------------------------------------

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


# -----------------------------------------------------------------------------
# Define the project name and version
# -----------------------------------------------------------------------------

project (
  Cpp_Playground
  VERSION 1.0.0
  DESCRIPTION "Small, valuable, and interesting C++ projects"
  LANGUAGES C CXX
  )


# -----------------------------------------------------------------------------
# Define customizable user options
# -----------------------------------------------------------------------------

# option (BUILD_SHARED_LIBS "Build using shared libraries" ON)
option (BUILD_TESTS "Build with tests" OFF)
option (USE_VECTORIZATION "Build with vectorization support" OFF)


# -----------------------------------------------------------------------------
# Configure build options
# -----------------------------------------------------------------------------

# Show which project we are building
message(STATUS
  "Configuring build for `"
  ${PROJECT_NAME}
  "' v"
  ${PROJECT_VERSION}
  " ..."
  )

# Set the C++ standard to C++17 and make it required
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the build type to MinSizeRel if not specified
if (NOT DEFINED CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE MinSizeRel)
endif ()
message(STATUS "Build type set to: `" ${CMAKE_BUILD_TYPE} "' ...")

# If build type is Debug set for debugging code to compile
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "Use debugging code set to: `ON' ...")
  set(USE_DEBUG ON)
else ()
  message(STATUS "Use debugging code set to: `OFF' ...")
  set(USE_DEBUG OFF)
endif ()

# Set custom compiler options
message (STATUS "Setting custom compiler options ...")
include ("${CMAKE_SOURCE_DIR}/CMake/set_compiler_flags.cmake")
set_compiler_flags()
message (STATUS "Custom compiler options set to: `"
  ${CMAKE_CXX_FLAGS} " "
  ${CMAKE_CXX_FLAGS_DEBUG}
  "' ..."
  )

# -----------------------------------------------------------------------------
# Check if we are building with the unit tests
# -----------------------------------------------------------------------------

# Check if the tests are enabled
if (NOT DEFINED BUILD_TESTS)
  set (BUILD_TESTS OFF)  # Default to OFF
endif ()
message(STATUS "Build tests set to: `" ${BUILD_TESTS} "' ...")

# -----------------------------------------------------------------------------
# Configure subdirectories
# -----------------------------------------------------------------------------
add_subdirectory ("${PROJECT_SOURCE_DIR}/extern")
add_subdirectory ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src")

# Add the test files directory if the tests are enabled
if (BUILD_TESTS)
  enable_testing ()
  add_subdirectory ("${PROJECT_SOURCE_DIR}/tests")
endif ()


# End of `CMakeLists.txt'
