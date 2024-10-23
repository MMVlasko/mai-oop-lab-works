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


add_library(LW4_array include/array.h)

add_library(LW4_figure include/figure.h)
set_target_properties(LW4_figure PROPERTIES LINKER_LANGUAGE CXX)

add_library(LW4_square include/square.h)
set_target_properties(LW4_square PROPERTIES LINKER_LANGUAGE CXX)

add_library(LW4_rectangle include/rectangle.h)
set_target_properties(LW4_rectangle PROPERTIES LINKER_LANGUAGE CXX)

add_library(LW4_trapeze include/trapeze.h)
set_target_properties(LW4_trapeze PROPERTIES LINKER_LANGUAGE CXX)

add_library(LW4_exceptions src/exceptions.cpp)
target_include_directories(LW4_exceptions PRIVATE include)

add_library(LW4_point include/point.h)
set_target_properties(LW4_point PROPERTIES LINKER_LANGUAGE CXX)

add_library(LW4_tools src/tools.cpp include/tools.h)
target_include_directories(LW4_tools PRIVATE include)

add_executable(LW4 main.cpp)
target_include_directories(LW4 PRIVATE include)

target_link_libraries(LW4 PRIVATE LW4_array LW4_exceptions LW4_rectangle LW4_square LW4_trapeze LW4_tools LW4_point LW4_figure)
target_link_libraries(LW4_array PRIVATE LW4_exceptions)
target_link_libraries(LW4_figure PRIVATE LW4_exceptions LW4_tools)
target_link_libraries(LW4_tools PRIVATE LW4_exceptions)

enable_testing()

add_executable(LW4_array_tests test/test_array.cpp)
target_include_directories(LW4_array_tests PRIVATE include)

add_executable(LW4_figure_tests test/test_figure.cpp)
target_include_directories(LW4_figure_tests PRIVATE include)

add_executable(LW4_square_tests test/test_square.cpp)
target_include_directories(LW4_square_tests PRIVATE include)

add_executable(LW4_rectangle_tests test/test_rectangle.cpp)
target_include_directories(LW4_rectangle_tests PRIVATE include)

add_executable(LW4_trapeze_tests test/test_trapeze.cpp)
target_include_directories(LW4_trapeze_tests PRIVATE include)

add_executable(LW4_point_tests test/test_point.cpp)
target_include_directories(LW4_point_tests PRIVATE include)

add_executable(LW4_tools_tests test/test_tools.cpp)
target_include_directories(LW4_tools_tests PRIVATE include)

target_link_libraries(LW4_array_tests LW4_array gtest_main)
target_link_libraries(LW4_figure_tests LW4_figure LW4_array LW4_point gtest_main)
target_link_libraries(LW4_square_tests LW4_square LW4_figure LW4_array LW4_point gtest_main)
target_link_libraries(LW4_rectangle_tests LW4_rectangle LW4_figure LW4_array LW4_point gtest_main)
target_link_libraries(LW4_trapeze_tests LW4_trapeze LW4_figure LW4_array LW4_point gtest_main)
target_link_libraries(LW4_point_tests LW4_point gtest_main)
target_link_libraries(LW4_tools_tests LW4_tools LW4_array LW4_point LW4_exceptions gtest_main)

add_test(NAME LW4_array_tests COMMAND LW4_array_tests)
add_test(NAME LW4_figure_tests COMMAND LW4_figure_tests)
add_test(NAME LW4_point_tests COMMAND LW4_point_tests)
add_test(NAME LW4_tools_tests COMMAND LW4_tools_tests)
add_test(NAME LW4_square_tests COMMAND LW4_square_tests)
add_test(NAME LW4_rectangle_tests COMMAND LW4_rectangle_tests)
add_test(NAME LW4_trapeze_tests COMMAND LW4_trapeze_tests)