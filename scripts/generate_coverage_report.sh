#!/bin/bash

cmake --preset=coverage -DSMOL_CXX_STANDARD=$1
cmake --build --preset=coverage
LLVM_PROFILE_FILE="unit_test.profraw" ./build/coverage/unit_test/unit_test
llvm-profdata merge -sparse unit_test.profraw -o unit_test.profdata
llvm-cov show ./build/coverage/unit_test/unit_test -instr-profile=unit_test.profdata -ignore-filename-regex="build|unit_test"
llvm-cov report ./build/coverage/unit_test/unit_test -instr-profile=unit_test.profdata -ignore-filename-regex="build|unit_test"
