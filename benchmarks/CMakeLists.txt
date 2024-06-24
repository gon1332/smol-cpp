unset(BENCHMARK_ENABLE_GTEST_TESTS)
add_subdirectory(benchmark)

add_executable(smol_bench main.cpp)

target_compile_features(smol_bench PRIVATE cxx_std_17)

target_link_libraries(smol_bench PRIVATE
  benchmark::benchmark
  smol
)