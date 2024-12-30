cmake_minimum_required(VERSION 3.28)
project(LaplacianLeaderFollowerDynamics)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

FetchContent_Declare(
  kmath
  GIT_REPOSITORY https://github.com/kvs247/kmath.git
  GIT_TAG main
)

FetchContent_MakeAvailable(googletest kmath)

add_executable(llfd
  src/main.cpp
  src/QRDecomp/GramSchmidt/GramSchmidt.cpp
  src/QRAlgo/QRAlgo.cpp
)
target_include_directories(llfd
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(llfd
  PRIVATE
  kmath
)

enable_testing()


add_executable(
  qr_gs_test
  src/QRDecomp/GramSchmidt/test.cpp
  src/QRDecomp/GramSchmidt/GramSchmidt.cpp
)
target_link_libraries(
  qr_gs_test
  gtest gtest_main
  kmath
)

include(GoogleTest)
gtest_discover_tests(qr_gs_test)
