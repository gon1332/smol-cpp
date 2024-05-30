include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(unit_test
  test_algorithm.cpp
  test_filesystem.cpp
  test_path.cpp
  test_string.cpp
)
target_link_libraries(
  unit_test
  smol
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_test)

add_custom_command(TARGET unit_test POST_BUILD
  COMMAND size --format=berkeley ${CMAKE_CURRENT_BINARY_DIR}/unit_test
)
