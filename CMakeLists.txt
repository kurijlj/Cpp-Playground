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

# Set the build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release)
endif ()
message(STATUS "Build type set to: `" ${CMAKE_BUILD_TYPE} "' ...")

# If build type is Debug set for debugging code to compile
if (CMAKE_BUILD_TYPE MATCHES "Debug")
  message(STATUS "Use debugging code set to: `ON' ...")
  set(USE_DEBUG ON)
else ()
  message(STATUS "Use debugging code set to: `OFF' ...")
  set(USE_DEBUG OFF)
endif ()

# Set custom compiler options
cmake_path(GET CMAKE_CXX_COMPILER STEM compiler)
if (compiler MATCHES "icx")
  message (STATUS "Using Intel's oneAPI compiler ...")
elseif (compiler MATCHES "c\\+\\+" OR compiler MATCHES "gcc")
  message (STATUS "Using GNU's compiler ...")
elseif (compiler MATCHES "clang")
  message (STATUS "Using Clang's compiler ...")
elseif (compiler MATCHES "cl")
  message (STATUS "Using Microsoft's compiler ...")
else ()
  message (STATUS "Using '" ${compiler} "' compiler ...")
endif ()


# -----------------------------------------------------------------------------
# Check if we are building with the unit tests
# -----------------------------------------------------------------------------

# Check if the tests are enabled
if (NOT DEFINED BUILD_TESTS)
  set (BUILD_TESTS OFF)  # Default to OFF
endif ()

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
