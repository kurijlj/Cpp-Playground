# =============================================================================
# CMake build script for the `clipp' library
# =============================================================================

# ============================================================================
#
# 2025-09-21 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Created.
#
# ============================================================================

# Make sure that `clipp' is available
FetchContent_MakeAvailable(clipp)

# Create an INTERFACE library target for `clipp'
add_library(clipp INTERFACE) # INTERFACE library for header-only
target_include_directories(
	clipp
	INTERFACE
	"${clipp_SOURCE_DIR}/include"
	)


# End of `CMakeLists.txt'
