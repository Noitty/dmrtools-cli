cmake_minimum_required(VERSION 3.2)

# User-defined parameters (used as hints in find_package): -----------------------------------------
project(hdmr-cli VERSION "0.0")

####################################################################################################
# Build environment setup (for GNU G++): -----------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)          # C++11 Standard.
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Force required standard.
set(CMAKE_CXX_EXTENSIONS ON)        # Enable compiler extensions (gnu++11).
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wno-reorder -O2 -pthread")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# External packages/libraries to include that are common for all sources: --------------------------

# Project's header locations: ----------------------------------------------------------------------
file(GLOB_RECURSE headers_list_src "src/*.h")
list(APPEND headers_list ${headers_list_src})

set(global_include_dirs "")
foreach(hfile ${headers_list})
    get_filename_component(hdir ${hfile} DIRECTORY)
    list(APPEND global_include_dirs ${hdir})
endforeach()
list(REMOVE_DUPLICATES global_include_dirs)

include_directories(${global_include_dirs})     # Adds all the folders with headers insdide.

# Prepare building units: --------------------------------------------------------------------------
add_subdirectory(src)
