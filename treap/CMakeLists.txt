cmake_minimum_required(VERSION 3.14)
project(treap)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.x
)

FetchContent_MakeAvailable(googletest)

add_executable(
  node_test
  test/node_test.cc
)
target_link_libraries(
  node_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(node_test)
