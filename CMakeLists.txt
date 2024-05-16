cmake_minimum_required(VERSION 3.25)
project(filesystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(filesystem OBJECT path.cpp)
target_include_directories(filesystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(unit_test)
