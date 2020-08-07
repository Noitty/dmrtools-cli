file(GLOB_RECURSE sources_list "*.c")
add_library(drivers STATIC ${sources_list})
target_link_libraries(drivers
    utils) # Specify dependency between libraries.
