# =============================================================================
# CMake build script for the `C++ Playground' include files
# =============================================================================

# ============================================================================
#
# 2025-09-21 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Created.
#
# ============================================================================

# Print message to console that we are processing './include' dir
message(STATUS "Configuring includes ...")


# =============================================================================
# Configure include files
# =============================================================================

message (STATUS "Configuring `common.hxx")
configure_file(
  ${PROJECT_SOURCE_DIR}/include/common.hxx.in
  ${PROJECT_SOURCE_DIR}/include/common.hxx
  @ONLY
  )


# End of `CMakeLists.txt'
