add_subdirectory(utils)
add_subdirectory(drivers)
add_subdirectory(devices)
add_subdirectory(core)

# Create the executable related to the main.c
add_executable(hdmri-cli main.c)
target_link_libraries(hdmri-cli
    utils
    drivers
    interfaces
    core
)

set_target_properties(hdmri-cli
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY    "${CMAKE_BINARY_DIR}/../lib"
    LIBRARY_OUTPUT_DIRECTORY    "${CMAKE_BINARY_DIR}/../lib"
    RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_BINARY_DIR}/../bin"
    COMPILE_FLAGS               "${CMAKE_C_FLAGS}"
    LINK_FLAGS                  "${PROJECT_LDFLAGS}"
)
