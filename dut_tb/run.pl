#!/usr/bin/perl

system "g++ -I. -I/cygdrive/d/SystemC/systemc_lib/include -L. -L/cygdrive/d/SystemC/systemc_lib/lib-cygwin -o test_top *.cpp -lsystemc -lm";

__END__
