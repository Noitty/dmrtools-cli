file(GLOB_RECURSE sources_list "*.c")

add_library(devices STATIC ${sources_list})

target_link_libraries(devices
    utils
    drivers) # Specify dependency between libraries.
