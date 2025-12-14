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

install(
  TARGETS cli_template_app
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )


# -----------------------------------------------------------------------------
# vtk_cone_app
# -----------------------------------------------------------------------------

# NOTE: Configure using
# ```shell
# emcmake cmake -G Ninja \
#     -S ..\..\repos\Cpp-Playground\ \
#     -B .
#     -DCMAKE_BUILD_TYPE=Debug \
#     -DCMAKE_C_COMPILER=icx \
#     -DCMAKE_CXX_COMPILER=icx \
#     -DVTK_DIR="C:\Users\kurij\Projects\builds\VTK-9.5.2"
# ```
#
# Mind the order of the switches.

# Show message that we are building the `vtk_cone_app' target
message (STATUS "Configuring the `vtk_cone_app' target ...")
message(STATUS "VTK_DIR: ${VTK_DIR}")

find_package(VTK
  COMPONENTS
    CommonColor
    CommonTransforms
    FiltersSources      # VTK pipeline
    InteractionStyle    # Mouse handling
    InteractionWidgets  # Widgets
    RenderingOpenGL2    # For Rendering
    RenderingUI         # For SDL2 Window
    CommonCore
    RenderingContextOpenGL2
    RenderingCore
    RenderingFreeType
)

if(VTK_FOUND)
  # Set the source files for the `vtk_cone_app' target
  add_executable(
    vtk_cone_app
    vtk_cone_app.cxx
    )
  
  target_link_libraries(
    vtk_cone_app PRIVATE
    ${VTK_LIBRARIES}
  )
  
  # VTK modules initialization
  vtk_module_autoinit(
    TARGETS  vtk_cone_app
    MODULES  ${VTK_LIBRARIES}
  )
  
  # Copy HTML to build directory
  add_custom_command(
    TARGET vtk_cone_app
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/index.html"
        $<TARGET_FILE_DIR:vtk_cone_app>
  )
  
  install(
    TARGETS vtk_cone_app
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
else()
  message("Aborting configuration: ${VTK_NOT_FOUND_MESSAGE}")
  return()
endif()


# End of `CMakeLists.txt'
