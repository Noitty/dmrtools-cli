file(GLOB_RECURSE sources_list "*.c")

add_library(core STATIC ${sources_list})

target_link_libraries(core
    utils
    interfaces
    drivers) # Specify dependency between libraries.
