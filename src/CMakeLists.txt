# =============================================================================
# Build source targets
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./src")

# -----------------------------------------------------------------------------
# app
# -----------------------------------------------------------------------------

# Show message that we are building the `cli_app' target
message(STATUS "Configuring the `cli_app' target")

# Set the source files for the `cli_app' target
add_executable(cli_app cli_app.cxx)

# Link the `app` target with the required libraries
target_link_libraries(cli_app PRIVATE
    clipp
    sqlite3
    csv
)

# Include the required directories for the `app` target
target_include_directories(cli_app PRIVATE
    ${CSV_INCLUDE_DIR}
)

# Post-build actions for the `app` target
add_custom_command(TARGET cli_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/sample_data
        ${CMAKE_CURRENT_BINARY_DIR}/sample_data
)


# -----------------------------------------------------------------------------
# stat_demo
# -----------------------------------------------------------------------------

# Show message that we are building the `stat_demo` target
message(STATUS "Configuring the `stat_demo` target")

# Set the source files for the `stat_demo` target
add_executable(stat_demo stat_demo.cxx)

# Link the `stat_demo` target with the required libraries
target_link_libraries(stat_demo PRIVATE
    clipp
)