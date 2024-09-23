# CMake generated Testfile for 
# Source directory: /home/mihail/Общедоступные/oop-labs/LW2
# Build directory: /home/mihail/Общедоступные/oop-labs/build/LW2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MyProjectTests "/home/mihail/Общедоступные/oop-labs/build/LW2/LW2_array_tests" "LW2_hex_tests")
set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "/home/mihail/Общедоступные/oop-labs/LW2/CMakeLists.txt;39;add_test;/home/mihail/Общедоступные/oop-labs/LW2/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
