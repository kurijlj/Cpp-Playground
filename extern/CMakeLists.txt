# =============================================================================
# CMake build script for the `C++ Playground' external dependencies
# =============================================================================

# ============================================================================
#
# 2025-09-21 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Created.
#
# ============================================================================

# Print message to console that we are building the tests targets
message(STATUS "Configuring external dependencies ...")

# =============================================================================
# Configure external dependencies
# =============================================================================

# Enable FetchContent facility
include(FetchContent)

# -----------------------------------------------------------------------------
# clipp
# -----------------------------------------------------------------------------

message (STATUS "Fetching the `clipp' library ...")

FetchContent_Declare(
  clipp
  GIT_REPOSITORY  https://github.com/muellan/clipp
  GIT_TAG         4cda95d8c1536c3778773a4468a350a7ea8bcd3f
)

add_subdirectory(clipp)

# -----------------------------------------------------------------------------
# GoogleTest
# -----------------------------------------------------------------------------

if (BUILD_TESTS)
	message (STATUS "Fetching the `googletest' library ...")

	FetchContent_Declare(
	  googletest
		GIT_REPOSITORY https://github.com/google/googletest
		GIT_TAG        52eb8108c5bdec04579160ae17225d66034bd723
	)

	add_subdirectory(GoogleTest)

endif ()


# End of `CMakeLists.txt'
