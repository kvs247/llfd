cmake_minimum_required(VERSION 3.28)
project(LaplacianLeaderFollowerDynamics)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_executable(llfd
main.cpp
Matrix/Matrix.cpp
)

enable_testing()

add_executable(
  matrix_test
  Matrix/test.cpp
)
target_link_libraries(
  matrix_test 
  gtest gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix_test)