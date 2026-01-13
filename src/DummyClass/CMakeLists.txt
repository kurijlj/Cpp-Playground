# =============================================================================
# CMake build script for the `DummyClass' library
# =============================================================================

# ============================================================================
#
# 2026-01-11 Ljubomir Kurij <ljubomir_kurij@proton.me>
#
# * Created.
#
# ============================================================================

# Print message to console that we are building the source targets -----------
message(STATUS "Configuring the `DummyClass' target ...")

# Component name -------------------------------------------------------------
set(COMPONENT_NAME DummyClass)

# Target ---------------------------------------------------------------------
add_library(${COMPONENT_NAME} SHARED)

# Sources --------------------------------------------------------------------
target_sources(
  ${COMPONENT_NAME}
  PRIVATE
    DummyClass.cxx

  INTERFACE
    FILE_SET interface_headers
    TYPE HEADERS
    BASE_DIRS
      ${PROJECT_SOURCE_DIR}/include/DummyClass
    FILES
      ${PROJECT_SOURCE_DIR}/include/DummyClass/DummyClass.hxx
)

# Enable automatic symbol export on Windows to generate .lib import library
set_target_properties(
  ${COMPONENT_NAME}
  PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

# Disable /GL (Whole Program Optimization) for this target on MSVC because
# it is incompatible with WINDOWS_EXPORT_ALL_SYMBOLS
if(MSVC)
  target_compile_options(${COMPONENT_NAME} PRIVATE
    $<$<CONFIG:Release>:/GL->
    $<$<CONFIG:MinSizeRel>:/GL->
  )
endif()

# Target specific include directories ----------------------------------------
target_include_directories(
  ${COMPONENT_NAME}
  BEFORE PRIVATE
    ${PROJECT_SOURCE_DIR}/include
  )

# Link against LoggingService ------------------------------------------------
target_link_libraries(
  ${COMPONENT_NAME}
  PRIVATE
    LoggingService
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
