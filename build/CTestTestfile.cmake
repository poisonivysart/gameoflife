# CMake generated Testfile for 
# Source directory: /home/poisonivysart/Documents/L2/S2/CS_DevTech/GameOfLife
# Build directory: /home/poisonivysart/Documents/L2/S2/CS_DevTech/GameOfLife/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[my_test]=] "/home/poisonivysart/Documents/L2/S2/CS_DevTech/GameOfLife/build/my_test")
set_tests_properties([=[my_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/poisonivysart/Documents/L2/S2/CS_DevTech/GameOfLife/CMakeLists.txt;32;add_test;/home/poisonivysart/Documents/L2/S2/CS_DevTech/GameOfLife/CMakeLists.txt;0;")
subdirs("game")
subdirs("console")
