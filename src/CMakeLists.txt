# =============================================================================
# CMake build script for the `C++ Playground' unit tests
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
# LogService
# -----------------------------------------------------------------------------

# Show message that we are building the `libLogService' target
message (STATUS "Configuring the `libLogService' target ...")

# Target
add_library(LogService SHARED)

# Sources
target_sources(LogService
  PRIVATE
    console_log_service.cxx
    log_service_base.cxx
    tracable_log_service.cxx

  INTERFACE
    FILE_SET interface_headers
    TYPE HEADERS
    BASE_DIRS
      ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
      console_log_service.hxx
      log_service_base.hxx
      tracable_log_service.hxx
)

target_include_directories(
	LogService PRIVATE
	${PROJECT_SOURCE_DIR}/include
	)


install(
  TARGETS cli_template_app LogService
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )


# End of `CMakeLists.txt'
