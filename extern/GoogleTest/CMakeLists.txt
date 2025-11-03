# =============================================================================
# CMake build script for the `GoogleTest' library
# =============================================================================

# ============================================================================
#
# 2025-11-03 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Patches for IntelLLVM compiler support.
#
# 2025-09-21 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Created.
#
# ============================================================================

if (CMAKE_CXX_COMPILER_ID MATCHES "IntelLLVM")
  # Apply patches to `GoogleTest' when using IntelLLVM compiler
  message(STATUS
    "Using IntelLLVM compiler - applying patches to `GoogleTest' ..."
    )
  FetchContent_GetProperties(googletest)

  if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    
    message(STATUS "Patching `GoogleTest' for IntelLLVM compiler ...")
    file(READ
      "${googletest_SOURCE_DIR}/googletest/cmake/internal_utils.cmake"
      FILE_CONTENTS
      )
    # As of v2025.20, correct switch for the IntelLLVM compiler is
    # `-Wno-sycl-implicit-float-size-conversion' instead of
    # `-Wno-implicit-float-size-conversion'
    message(STATUS
      "Replacing deprecated flag "
      "`-Wno-implicit-float-size-conversion' ..."
      )
    string(REPLACE
      "-Wno-implicit-float-size-conversion"
      "-Wno-sycl-implicit-float-size-conversion"
      FILE_CONTENTS "${FILE_CONTENTS}"
      )
    # Remove `-Winline' flag which is not supported by IntelLLVM compiler
    message(STATUS
      "Removing unsupported flag `-Winline' ..."
      )
    string(REPLACE
      "-Winline "
      ""
      FILE_CONTENTS "${FILE_CONTENTS}"
      )
    file(WRITE
      "${googletest_SOURCE_DIR}/googletest/cmake/internal_utils.cmake"
      "${FILE_CONTENTS}"
      )
      message(STATUS "Patching completed.")
    
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
  endif()
else ()
  # Make sure that `GoogleTest' is available if not using IntelLLVM compiler
  FetchContent_MakeAvailable(googletest)
endif()


# End of `CMakeLists.txt'
