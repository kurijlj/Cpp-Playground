# =============================================================================
# CMake build script for the `LoggingService' library
# =============================================================================

# ============================================================================
#
# 2026-01-08 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Created.
#
# ============================================================================

# Print message to console that we are building the source targets -----------
message(STATUS "Configuring the `LoggingService' target ...")

# Component name -------------------------------------------------------------
set(COMPONENT_NAME LoggingService)

# Target ---------------------------------------------------------------------
add_library(${COMPONENT_NAME} SHARED)

# Sources --------------------------------------------------------------------
target_sources(
  ${COMPONENT_NAME}
  PRIVATE
    ConsoleLoggingService.cxx
    LoggerObject.cxx
    LoggingServiceBase.cxx
    TraceableLoggingService.cxx

  INTERFACE
    FILE_SET interface_headers
    TYPE HEADERS
    BASE_DIRS
      ${PROJECT_SOURCE_DIR}/include/LoggingService
    FILES
      ${PROJECT_SOURCE_DIR}/include/LoggingService/ConsoleLoggingService.hxx
      ${PROJECT_SOURCE_DIR}/include/LoggingService/LoggerObject.hxx
      ${PROJECT_SOURCE_DIR}/include/LoggingService/LoggingServiceBase.hxx
      ${PROJECT_SOURCE_DIR}/include/LoggingService/TraceableLoggingService.hxx
)

# Target specific include directories ----------------------------------------
target_include_directories(
  ${COMPONENT_NAME}
  BEFORE PRIVATE
    ${PROJECT_SOURCE_DIR}/include
  )

# Install instructions -------------------------------------------------------
install(
  TARGETS
    ${COMPONENT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )


# End of `CMakeLists.txt'
