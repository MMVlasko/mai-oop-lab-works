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


add_library(LW3_array include/array.h)
# target_include_directories(LW3_array PRIVATE include)

add_library(LW3_figure src/figure.cpp)
target_include_directories(LW3_figure PRIVATE include)

add_library(LW3_exceptions src/exceptions.cpp)
target_include_directories(LW3_exceptions PRIVATE include)

add_library(LW3_point src/point.cpp)
target_include_directories(LW3_point PRIVATE include)

add_executable(LW3 main.cpp)
target_include_directories(LW3 PRIVATE include)

# target_link_libraries(LW2 PRIVATE LW2_array)
# target_link_libraries(LW2 PRIVATE LW2_hex)
target_link_libraries(LW3_array PRIVATE LW3_exceptions)
target_link_libraries(LW3_figure PRIVATE LW3_exceptions)
# target_link_libraries(LW2_hex PRIVATE LW2_array)
# target_link_libraries(LW2_hex PRIVATE LW2_tools)
# target_link_libraries(LW2_tools PRIVATE LW2_exceptions)

enable_testing()

add_executable(LW3_array_tests test/test_array.cpp)
target_include_directories(LW3_array_tests PRIVATE include)

add_executable(LW3_figure_tests test/test_figure.cpp)
target_include_directories(LW3_figure_tests PRIVATE include)

add_executable(LW3_point_tests test/test_point.cpp)
target_include_directories(LW3_point_tests PRIVATE include)

target_link_libraries(LW3_array_tests LW3_array gtest_main)
target_link_libraries(LW3_figure_tests LW3_figure LW3_array LW3_point gtest_main)
target_link_libraries(LW3_point_tests LW3_point gtest_main)

add_test(NAME MyProjectTests COMMAND LW3_array_tests LW3_figure_tests)