cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Werror -Wpedantic)

project(test_)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(
	solution/
)

add_executable( test_
	solution/solution.cpp
	ut/test.cpp
)

target_link_libraries(
  test_
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_)
