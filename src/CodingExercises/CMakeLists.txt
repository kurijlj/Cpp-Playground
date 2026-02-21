# =============================================================================
# CMake build script for the `CodingExercises' study cases
# =============================================================================

# ============================================================================
#
# 2026-02-21 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Created.
#
# ============================================================================

# Print message to console that we are building the source targets -----------
message(STATUS "Configuring the `CodingExercises' targets ...")


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
    isomorphic_strings
    palindrome
    ransom_note
    subsequence
    substring_study
    word_pattern
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )


# End of `CMakeLists.txt'
