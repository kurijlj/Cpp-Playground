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
# happy_number
# -----------------------------------------------------------------------------

# Show message that we are building the `happy_number' target
message (STATUS "Configuring the `happy_number' target ...")

# Set the source files for the `happy_number' target
add_executable(
  happy_number
  happy_number.cxx
  )

target_include_directories(
  happy_number PRIVATE
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
# linkled_list_cycle
# -----------------------------------------------------------------------------

# Show message that we are building the `linked_list_cycle' target
message (STATUS "Configuring the `linked_list_cycle' target ...")

# Set the source files for the `linked_list_cycle' target
add_executable(
  linked_list_cycle
  linked_list_cycle.cxx
  )

target_include_directories(
  linked_list_cycle PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )


# -----------------------------------------------------------------------------
# maximum_depth_of_binary_tree
# -----------------------------------------------------------------------------

# Show message that we are building the `maximum_depth_of_binary_tree' target
message (STATUS "Configuring the `maximum_depth_of_binary_tree' target ...")

# Set the source files for the `maximum_depth_of_binary_tree' target
add_executable(
  maximum_depth_of_binary_tree
  maximum_depth_of_binary_tree.cxx
  )

target_include_directories(
  maximum_depth_of_binary_tree PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )


# -----------------------------------------------------------------------------
# merge_two_sorted_lists
# -----------------------------------------------------------------------------

# Show message that we are building the `merge_two_sorted_lists' target
message (STATUS "Configuring the `merge_two_sorted_lists' target ...")

# Set the source files for the `merge_two_sorted_lists' target
add_executable(
  merge_two_sorted_lists
  merge_two_sorted_lists.cxx
  )

target_include_directories(
  merge_two_sorted_lists PRIVATE
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
# roman_to_integer
# -----------------------------------------------------------------------------

# Show message that we are building the `roman_to_integer' target
message (STATUS "Configuring the `roman_to_integer' target ...")

# Set the source files for the `roman_to_integer' target
add_executable(
  roman_to_integer
  roman_to_integer.cxx
  )

target_include_directories(
  roman_to_integer PRIVATE
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
# summary_ranges
# -----------------------------------------------------------------------------

# Show message that we are building the `summary_ranges' target
message (STATUS "Configuring the `summary_ranges' target ...")

# Set the source files for the `summary_ranges' target
add_executable(
  summary_ranges
  summary_ranges.cxx
  )

target_include_directories(
  summary_ranges PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )


# -----------------------------------------------------------------------------
# two_sum
# -----------------------------------------------------------------------------

# Show message that we are building the `two_sum' target
message (STATUS "Configuring the `two_sum' target ...")

# Set the source files for the `two_sum' target
add_executable(
  two_sum
  two_sum.cxx
  )

target_include_directories(
  two_sum PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  )


# -----------------------------------------------------------------------------
# valid_parentheses
# -----------------------------------------------------------------------------

# Show message that we are building the `valid_parentheses' target
message (STATUS "Configuring the `valid_parentheses' target ...")

# Set the source files for the `valid_parentheses' target
add_executable(
  valid_parentheses
  valid_parentheses.cxx
  )

target_include_directories(
  valid_parentheses PRIVATE
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
    happy_number
    isomorphic_strings
    linked_list_cycle
    maximum_depth_of_binary_tree
    merge_two_sorted_lists
    palindrome
    ransom_note
    roman_to_integer
    subsequence
    substring_study
    summary_ranges
    two_sum
    valid_parentheses
    word_pattern
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )


# End of `CMakeLists.txt'
