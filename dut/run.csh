#!/usr/bin/csh

g++ -I/cygdrive/d/SystemC/uvm-systemc-1.0-beta2/uvm-systemc-1.0-beta2/include \
 -L/cygdrive/d/SystemC/uvm-systemc-1.0-beta2/uvm-systemc-1.0-beta2/lib-cygwin \
 -I/cygdrive/d/SystemC/systemc_lib/include \
 -L/cygdrive/d/SystemC/systemc_lib/lib-cygwin -o test_top *.cpp -lscv -luvm-systemc -lsystemc -lm
