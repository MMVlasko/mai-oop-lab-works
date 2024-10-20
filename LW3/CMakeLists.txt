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

add_library(LW3_figure src/figure.cpp)
target_include_directories(LW3_figure PRIVATE include)

add_library(LW3_square src/square.cpp)
target_include_directories(LW3_square PRIVATE include)

add_library(LW3_rectangle src/rectangle.cpp)
target_include_directories(LW3_rectangle PRIVATE include)

add_library(LW3_trapeze src/trapeze.cpp)
target_include_directories(LW3_trapeze PRIVATE include)

add_library(LW3_exceptions src/exceptions.cpp)
target_include_directories(LW3_exceptions PRIVATE include)

add_library(LW3_point src/point.cpp)
target_include_directories(LW3_point PRIVATE include)

add_library(LW3_tools src/tools.cpp)
target_include_directories(LW3_tools PRIVATE include)

add_executable(LW3 main.cpp)
target_include_directories(LW3 PRIVATE include)

target_link_libraries(LW3 PRIVATE LW3_array LW3_exceptions LW3_rectangle LW3_square LW3_trapeze LW3_tools LW3_point LW3_figure)
target_link_libraries(LW3_array PRIVATE LW3_exceptions)
target_link_libraries(LW3_figure PRIVATE LW3_exceptions LW3_tools)
target_link_libraries(LW3_tools PRIVATE LW3_exceptions)

enable_testing()

add_executable(LW3_array_tests test/test_array.cpp)
target_include_directories(LW3_array_tests PRIVATE include)

add_executable(LW3_figure_tests test/test_figure.cpp)
target_include_directories(LW3_figure_tests PRIVATE include)

add_executable(LW3_square_tests test/test_square.cpp)
target_include_directories(LW3_square_tests PRIVATE include)

add_executable(LW3_rectangle_tests test/test_rectangle.cpp)
target_include_directories(LW3_rectangle_tests PRIVATE include)

add_executable(LW3_trapeze_tests test/test_trapeze.cpp)
target_include_directories(LW3_trapeze_tests PRIVATE include)

add_executable(LW3_point_tests test/test_point.cpp)
target_include_directories(LW3_point_tests PRIVATE include)

add_executable(LW3_tools_tests test/test_tools.cpp)
target_include_directories(LW3_tools_tests PRIVATE include)

target_link_libraries(LW3_array_tests LW3_array gtest_main)
target_link_libraries(LW3_figure_tests LW3_figure LW3_array LW3_point gtest_main)
target_link_libraries(LW3_square_tests LW3_square LW3_figure LW3_array LW3_point gtest_main)
target_link_libraries(LW3_rectangle_tests LW3_rectangle LW3_figure LW3_array LW3_point gtest_main)
target_link_libraries(LW3_trapeze_tests LW3_trapeze LW3_figure LW3_array LW3_point gtest_main)
target_link_libraries(LW3_point_tests LW3_point gtest_main)
target_link_libraries(LW3_tools_tests LW3_tools LW3_array LW3_point LW3_exceptions gtest_main)

add_test(NAME LW3_array_tests COMMAND LW3_array_tests)
add_test(NAME LW3_figure_tests COMMAND LW3_figure_tests)
add_test(NAME LW3_point_tests COMMAND LW3_point_tests)
add_test(NAME LW3_tools_tests COMMAND LW3_tools_tests)
add_test(NAME LW3_square_tests COMMAND LW3_square_tests)
add_test(NAME LW3_rectangle_tests COMMAND LW3_rectangle_tests)
add_test(NAME LW3_trapeze_tests COMMAND LW3_trapeze_tests)