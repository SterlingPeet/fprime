# CMake generated Testfile for 
# Source directory: /Users/jishii/Documents/split_repo/fprime-sw/Fw/SerializableFile
# Build directory: /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Fw/SerializableFile
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Fw_SerializableFile_ut_exe "/Users/jishii/Documents/split_repo/fprime-sw/build_test/bin/Darwin/Fw_SerializableFile_ut_exe")
set_tests_properties(Fw_SerializableFile_ut_exe PROPERTIES  _BACKTRACE_TRIPLES "/Users/jishii/Documents/split_repo/fprime-sw/cmake/support/Unit_Test.cmake;114;add_test;/Users/jishii/Documents/split_repo/fprime-sw/cmake/API.cmake;413;generate_ut;/Users/jishii/Documents/split_repo/fprime-sw/Fw/SerializableFile/CMakeLists.txt;32;register_fprime_ut;/Users/jishii/Documents/split_repo/fprime-sw/Fw/SerializableFile/CMakeLists.txt;0;")
subdirs("test/TestSerializable")
