#include <benchmark/benchmark.h>
#include "smol/filesystem.h"
#include <filesystem>

template <class Path>
static void BM_Path_LexicallyNormal(benchmark::State &p_state, const char *p_path) {
    Path the_path{p_path};
    benchmark::DoNotOptimize(the_path);
    for (auto _ : p_state) {
        the_path.lexically_normal();
    }
}

const char *kAlreadyNormalizedPath = "/one/today/is/worth/two/tomorrow";
const char *kNotNormalizedPath = "/././one//../today/../is//worth/two/../tomorrow/";

BENCHMARK_TEMPLATE1_CAPTURE(BM_Path_LexicallyNormal, smol::filesystem::path, already_normalized, kAlreadyNormalizedPath);
BENCHMARK_TEMPLATE1_CAPTURE(BM_Path_LexicallyNormal, std::filesystem::path, already_normalized, kAlreadyNormalizedPath);
BENCHMARK_TEMPLATE1_CAPTURE(BM_Path_LexicallyNormal, smol::filesystem::path, not_normalized, kNotNormalizedPath);
BENCHMARK_TEMPLATE1_CAPTURE(BM_Path_LexicallyNormal, std::filesystem::path, not_normalized, kNotNormalizedPath);

BENCHMARK_MAIN();
