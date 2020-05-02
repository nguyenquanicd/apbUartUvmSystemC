#!/usr/bin/bash

g++ -I/cygdrive/d/Cygwin/Lib_install/SystemC/include \
    -L/cygdrive/d/Cygwin/Lib_install/SystemC/lib-cygwin \
    -I/cygdrive/d/Cygwin/Lib_install/uvm-systemc-1.0-beta2/include \
    -L/cygdrive/d/Cygwin/Lib_install/uvm-systemc-1.0-beta2/lib-cygwin \
    -I. -L. \
    -I../dut -L../dut \
    -I../uvm_comp -L../uvm_comp \
    -o test_top \
    *.cpp ../dut/*.cpp ../uvm_comp/*.cpp \
    -lscv -luvm-systemc -lsystemc -lm
