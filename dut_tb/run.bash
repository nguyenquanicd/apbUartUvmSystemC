#!/usr/bin/bash

g++ -I/cygdrive/d/Cygwin/Lib_install/SystemC/include \
    -L/cygdrive/d/Cygwin/Lib_install/SystemC/lib-cygwin \
    -I. -L. \
    -I../dut -L../dut \
    *.cpp \
    ../dut/*.cpp \
    -o test_top  \
    -lsystemc -lm
