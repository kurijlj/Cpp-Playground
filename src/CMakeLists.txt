# =============================================================================
# CMake build script for the `C++ Playground' components
# =============================================================================

# ============================================================================
#
# 2026-01-09 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Added `LoggingService' target as a subdirectory.
#
# 2025-09-21 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Created.
#
# ============================================================================

# Print message to console that we are building the source targets
message(STATUS "Configuring build targets ...")

# =============================================================================
# Build targets
# =============================================================================

# -----------------------------------------------------------------------------
# LoggingService
# -----------------------------------------------------------------------------

add_subdirectory(LoggingService)


# -----------------------------------------------------------------------------
# DummyClass
# -----------------------------------------------------------------------------

add_subdirectory(DummyClass)


# -----------------------------------------------------------------------------
# binning_study
# -----------------------------------------------------------------------------

# Show message that we are building the `binning_study' target
message (STATUS "Configuring the `binning_study' target ...")

# Set the source files for the `binning_study' target
add_executable(
  binning_study
  binning_study.cxx
  )

target_include_directories(
  binning_study
  PRIVATE
   ${PROJECT_SOURCE_DIR}/include
  )

target_link_libraries(
  binning_study
  PRIVATE
    LoggingService
)


# -----------------------------------------------------------------------------
# cli_template_app
# -----------------------------------------------------------------------------

# Show message that we are building the `cli_template_app' target
message (STATUS "Configuring the `cli_template_app' target ...")

# Set the source files for the `cli_template_app' target
add_executable(
  cli_template_app
  cli_template_app.cxx
  hello_world_strategy.cxx
  )

target_include_directories(
  cli_template_app PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )

target_link_libraries(
  cli_template_app PRIVATE
  clipp
)


# -----------------------------------------------------------------------------
# resource_release_study
# -----------------------------------------------------------------------------

# Show message that we are building the `resource_release_study' target
message (STATUS "Configuring the `resource_release_study' target ...")

# Set the source files for the `resource_release_study' target
add_executable(
  resource_release_study
  resource_release_study.cxx
  )

target_include_directories(
  resource_release_study PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )

target_link_libraries(
  resource_release_study PRIVATE
  DummyClass
  LoggingService
)


# -----------------------------------------------------------------------------
# substring_study
# -----------------------------------------------------------------------------

# Show message that we are building the `substring_study' target
message (STATUS "Configuring the `substring_study' target ...")

# Set the source files for the `substring_study' target
add_executable(
  substring_study
  substring_study.cxx
  )

target_include_directories(
  substring_study PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )

target_link_libraries(
  substring_study PRIVATE
  LoggingService
)


# -----------------------------------------------------------------------------
# palindrome
# -----------------------------------------------------------------------------

# Show message that we are building the `palindrome' target
message (STATUS "Configuring the `palindrome' target ...")

# Set the source files for the `palindrome' target
add_executable(
  palindrome
  palindrome.cxx
  )

target_include_directories(
  palindrome PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )


# -----------------------------------------------------------------------------
# subsequence
# -----------------------------------------------------------------------------

# Show message that we are building the `subsequence' target
message (STATUS "Configuring the `subsequence' target ...")

# Set the source files for the `subsequence' target
add_executable(
  subsequence
  subsequence.cxx
  )

target_include_directories(
  subsequence PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )


# -----------------------------------------------------------------------------
# ransom_note
# -----------------------------------------------------------------------------

# Show message that we are building the `ransom_note' target
message (STATUS "Configuring the `ransom_note' target ...")

# Set the source files for the `ransom_note' target
add_executable(
  ransom_note
  ransom_note.cxx
  )

target_include_directories(
  ransom_note PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )


# -----------------------------------------------------------------------------
# isomorphic_strings
# -----------------------------------------------------------------------------

# Show message that we are building the `isomorphic_strings' target
message (STATUS "Configuring the `isomorphic_strings' target ...")

# Set the source files for the `isomorphic_strings' target
add_executable(
  isomorphic_strings
  isomorphic_strings.cxx
  )

target_include_directories(
  isomorphic_strings PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )


# -----------------------------------------------------------------------------
# word_pattern
# -----------------------------------------------------------------------------

# Show message that we are building the `word_pattern' target
message (STATUS "Configuring the `word_pattern' target ...")

# Set the source files for the `word_pattern' target
add_executable(
  word_pattern
  word_pattern.cxx
  )

target_include_directories(
  word_pattern PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )


# =============================================================================
# Install instructions
# =============================================================================

install(
  TARGETS
    binning_study
    cli_template_app
    resource_release_study
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )


# End of `CMakeLists.txt'
