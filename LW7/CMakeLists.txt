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

add_library(LW7_npcs src/npc.cpp)
target_include_directories(LW7_npcs PRIVATE include)

add_library(LW7_array include/array.h)
set_target_properties(LW7_array PROPERTIES LINKER_LANGUAGE CXX)

add_library(LW7_editor src/editor.cpp)
target_include_directories(LW7_editor PRIVATE include)

add_library(LW7_factory src/factory.cpp)
target_include_directories(LW7_factory PRIVATE include)

add_library(LW7_visitor src/visitor.cpp)
target_include_directories(LW7_visitor PRIVATE include)

add_library(LW7_observer src/observer.cpp)
target_include_directories(LW7_observer PRIVATE include)

add_library(LW7_exceptions src/exceptions.cpp)
target_include_directories(LW7_exceptions PRIVATE include)

add_library(LW7_tools src/tools.cpp)
target_include_directories(LW7_tools PRIVATE include)

add_executable(LW7 main.cpp)
target_include_directories(LW7 PRIVATE include)

target_link_libraries(LW7_array PRIVATE LW7_exceptions)
target_link_libraries(LW7_npcs PRIVATE LW7_visitor)
target_link_libraries(LW7_editor PRIVATE LW7_array LW7_factory LW7_npcs LW7_observer LW7_exceptions)
target_link_libraries(LW7_factory PRIVATE LW7_npcs LW7_exceptions LW7_tools)
target_link_libraries(LW7_visitor PRIVATE LW7_array LW7_observer LW7_npcs LW7_tools)
target_link_libraries(LW7 PRIVATE LW7_editor LW7_observer LW7_exceptions)
target_link_libraries(LW7_tools PRIVATE LW7_factory)

enable_testing()

add_executable(LW7_npcs_tests test/test_npc.cpp)
target_include_directories(LW7_npcs_tests PRIVATE include)

add_executable(LW7_factory_tests test/test_factory.cpp)
target_include_directories(LW7_factory_tests PRIVATE include)

add_executable(LW7_editor_tests test/test_editor.cpp)
target_include_directories(LW7_editor_tests PRIVATE include)

add_executable(LW7_visitor_tests test/test_visitor.cpp)
target_include_directories(LW7_visitor_tests PRIVATE include)

add_executable(LW7_array_tests test/test_array.cpp)
target_include_directories(LW7_array_tests PRIVATE include)

add_executable(LW7_observer_tests test/test_observer.cpp)
target_include_directories(LW7_observer_tests PRIVATE include)

add_executable(LW7_tools_tests test/test_tools.cpp)
target_include_directories(LW7_tools_tests PRIVATE include)

target_link_libraries(LW7_npcs_tests LW7_npcs gtest_main)
target_link_libraries(LW7_factory_tests LW7_factory LW7_npcs LW7_exceptions gtest_main)
target_link_libraries(LW7_editor_tests LW7_observer LW7_editor LW7_factory LW7_npcs LW7_exceptions gtest_main)
target_link_libraries(LW7_visitor_tests LW7_observer LW7_visitor LW7_factory LW7_npcs LW7_exceptions gtest_main)
target_link_libraries(LW7_array_tests LW7_array LW7_exceptions gtest_main)
target_link_libraries(LW7_observer_tests LW7_observer gtest_main)
target_link_libraries(LW7_tools_tests LW7_tools LW7_exceptions gtest_main)

add_test(NAME LW7_npcs_tests COMMAND LW7_npcs_tests)
add_test(NAME LW7_factory_tests COMMAND LW7_factory_tests)
add_test(NAME LW7_editor_tests COMMAND LW7_editor_tests)
add_test(NAME LW7_visitor_tests COMMAND LW7_visitor_tests)
add_test(NAME LW7_array_tests COMMAND LW7_array_tests)
add_test(NAME LW7_observer_tests COMMAND LW7_observer_tests)
add_test(NAME LW7_tools_tests COMMAND LW7_tools_tests)