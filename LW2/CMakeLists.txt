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


add_library(LW2_array src/array.cpp)
target_include_directories(LW2_array PRIVATE include)

add_library(LW2_hex src/hex.cpp)
target_include_directories(LW2_hex PRIVATE include)

add_library(LW2_exceptions src/exceptions.cpp)
target_include_directories(LW2_exceptions PRIVATE include)

add_library(LW2_tools src/tools.cpp)
target_include_directories(LW2_tools PRIVATE include)

add_executable(LW2 main.cpp)
target_include_directories(LW2 PRIVATE include)

target_link_libraries(LW2 PRIVATE LW2_array)
target_link_libraries(LW2 PRIVATE LW2_hex)
target_link_libraries(LW2_array PRIVATE LW2_exceptions)
target_link_libraries(LW2_hex PRIVATE LW2_exceptions)
target_link_libraries(LW2_hex PRIVATE LW2_array)
target_link_libraries(LW2_hex PRIVATE LW2_tools)
target_link_libraries(LW2_tools PRIVATE LW2_exceptions)

enable_testing()

add_executable(LW2_array_tests test/test_array.cpp)
target_include_directories(LW2_array_tests PRIVATE include)

add_executable(LW2_hex_tests test/test_hex.cpp)
target_include_directories(LW2_hex_tests PRIVATE include)

add_executable(LW2_tools_tests test/test_tools.cpp)
target_include_directories(LW2_tools_tests PRIVATE include)

target_link_libraries(LW2_array_tests LW2_array gtest_main)
target_link_libraries(LW2_hex_tests LW2_hex gtest_main)
target_link_libraries(LW2_tools_tests LW2_tools gtest_main)

add_test(NAME MyProjectTests COMMAND LW2_array_tests LW2_hex_tests LW2_tools_tests)