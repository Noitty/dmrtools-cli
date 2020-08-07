file(GLOB_RECURSE sources_list "*.c")

add_library(utils STATIC ${sources_list})

target_link_libraries(utils) # Specify dependency between libraries.
