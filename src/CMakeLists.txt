# =============================================================================
# CMake build script for the `C++ Playground' components
# =============================================================================

# ============================================================================
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
	binning_study PRIVATE
	${PROJECT_SOURCE_DIR}/include
	)

target_link_libraries(
  binning_study PRIVATE
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
# LoggingService
# -----------------------------------------------------------------------------

add_subdirectory(LoggingService)


# -----------------------------------------------------------------------------
# binning_study
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
  LoggingService
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
