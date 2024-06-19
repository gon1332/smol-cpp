cmake_minimum_required(VERSION 3.25)
project(smol)

option(USE_STD_STRING_VIEW "Use std::string_view instead of smol::string_view internally")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(smol OBJECT
    src/filesystem_path.cpp
)

if(${USE_STD_STRING_VIEW})
target_compile_definitions(smol PRIVATE USE_STD_STRING_VIEW)
endif()

target_include_directories(smol PUBLIC include)

set_target_properties(smol PROPERTIES CXX_EXTENSIONS OFF)

add_subdirectory(port)
add_subdirectory(unit_test)
