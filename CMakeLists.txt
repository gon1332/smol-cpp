cmake_minimum_required(VERSION 3.25)
project(smol)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(smol OBJECT
    src/filesystem_path.cpp
)

target_include_directories(smol PUBLIC include)

set_target_properties(smol PROPERTIES CXX_EXTENSIONS OFF)

add_subdirectory(port)
add_subdirectory(unit_test)
