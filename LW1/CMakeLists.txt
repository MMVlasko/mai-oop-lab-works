cmake_minimum_required(VERSION 3.10)
project(mai-oop)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(LW1_lib src/solver.cpp)
add_executable(LW1 main.cpp)

target_link_libraries(LW1 PRIVATE LW1_lib)

enable_testing()

add_executable(LW1_tests test/test_solver.cpp)
target_link_libraries(LW1_tests LW1_lib gtest_main)

add_test(NAME MyProjectTests COMMAND LW1_tests)