#!/usr/bin/perl

# This script generate source code which is used for dump waveform.
# Put main script (waveform.pl) & define file (waveform.def)
#   at the simulation folder which contain main C++ file (sc_main funtion)
# Usage: waveform.pl
# Output: temporary source code has 2 part:
#   + Intance sc_trace_file & list of signal => user should put those source code
#       in sc_main funtion, after instance necessary model.
#   + sc_close_vcd_trace_file => user should put this line at the end of sc_main funtion.



#sc_trace_file *wf = sc_create_vcd_trace_file("counter");
#sc_trace(wf, clock, "clock");
#sc_trace(wf, reset, "reset");
#sc_trace(wf, enable, "enable");
#sc_trace(wf, counter_out, "count");

#sc_close_vcd_trace_file(wf);