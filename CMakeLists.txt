cmake_minimum_required(VERSION 3.25)
project(smol)

set(SMOL_CXX_STANDARD 17 CACHE STRING "the C++ standard to use for smol")
message("Compiling smol for C++${SMOL_CXX_STANDARD}")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(smol OBJECT
  src/filesystem_path.cpp
)

target_compile_features(smol PRIVATE cxx_std_${SMOL_CXX_STANDARD})
target_compile_definitions(smol PRIVATE
  $<$<EQUAL:${SMOL_CXX_STANDARD},11>:USE_SMOL_STRING_VIEW>
  $<$<EQUAL:${SMOL_CXX_STANDARD},14>:USE_SMOL_STRING_VIEW>
)

target_include_directories(smol PUBLIC include)

set_target_properties(smol PROPERTIES CXX_EXTENSIONS OFF)

add_subdirectory(port)
add_subdirectory(unit_test)
add_subdirectory(benchmarks EXCLUDE_FROM_ALL)
