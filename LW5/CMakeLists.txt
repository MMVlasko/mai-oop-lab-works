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

add_library(LW5_stack_memory_resource src/stack_memory_resource.cpp)
target_include_directories(LW5_stack_memory_resource PRIVATE include)

add_library(LW5_stack include/stack.h)
set_target_properties(LW5_stack PROPERTIES LINKER_LANGUAGE CXX)

add_library(LW5_exceptions src/exceptions.cpp)
target_include_directories(LW5_exceptions PRIVATE include)

add_executable(LW5 main.cpp)
target_include_directories(LW5 PRIVATE include)

target_link_libraries(LW5 PRIVATE LW5_stack LW5_stack_memory_resource LW5_exceptions)
target_link_libraries(LW5_stack PRIVATE LW5_exceptions)

enable_testing()

add_executable(LW5_stack_tests test/test_stack.cpp)
target_include_directories(LW5_stack_tests PRIVATE include)

add_executable(LW5_stack_memory_resource_tests test/test_stack_memory_resource.cpp)
target_include_directories(LW5_stack_memory_resource_tests PRIVATE include)

target_link_libraries(LW5_stack_tests LW5_exceptions LW5_stack_memory_resource LW5_stack gtest_main)
target_link_libraries(LW5_stack_memory_resource_tests LW5_stack_memory_resource gtest_main)

add_test(NAME LW5_stack_tests COMMAND LW5_stack_tests)
add_test(NAME LW5_stack_memory_resource_tests COMMAND LW5_stack_memory_resource_tests)