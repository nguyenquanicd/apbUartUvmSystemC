#!/usr/bin/perl

# This script generate source code which is used for dump waveform.
# Put main script (waveform.pl) & define file (waveform.def)
#   at the simulation folder which contain main C++ file (sc_main funtion)
# Usage:  waveform.pl
# Output: waveform.h - temporary source code has 2 part:
#   + Intance sc_trace_file & list of signal => user should put those source code
#       in sc_main funtion, after instance necessary model.
#   + sc_close_vcd_trace_file => user should put this line at the end of sc_main funtion.



#sc_trace_file *wf = sc_create_vcd_trace_file("counter");
#sc_trace(wf, clock, "clock");
#sc_trace(wf, reset, "reset");
#sc_trace(wf, enable, "enable");
#sc_trace(wf, counter_out, "count");

#sc_close_vcd_trace_file(wf);
use File::Basename;
use File::Copy;
use File::Path;

my $def_line ;
my @def_line_split ;
my $hierarchy ;
my $enable_flag ;
my @hierarchy_split ;
my %instance_hash ;
my $model_file ;
my @model_file_all_line ;

open (DEF_FILE, "< waveform.def") ;
open (SC_TRACE, "> waveform.out") ;
  foreach $def_line (<DEF_FILE>) {
    chomp $def_line ;
    next if (("$def_line" =~ /#/) || ("$def_line" !~ / [01]$/)) ;
    
    @def_line_split = split (/ /, "$def_line") ;
    $hierarchy      = "$def_line_split[0]" ;
    $enable_flag    = "$def_line_split[1]" ;
    next if ($enable_flag == 0) ;
    
    @hierarchy_split = split (/\./, "$hierarchy") ;
    for (my $i = 0; $i < @hierarchy_split; $i++) {
      if (! defined $instance_hash{$hierarchy_split[$i]}) {
        $instance_hash{$hierarchy_split[$i]}{name} = "$hierarchy_split[$i]" ;
        
        foreach $model_file (glob "*\.h *\.cpp") {
          open (MODEL_FILE, "< $model_file") ;
          @model_file_all_line = <MODEL_FILE> ;
          close (MODEL_FILE) ;
          
          my @pointer_find = grep /\b$hierarchy_split[$i]\s+=\s+\b/, @model_file_all_line ;
          if (@pointer_find == 1) {
            $instance_hash{$hierarchy_split[$i]}{type} = "pointer" ;
            last ;
          } else if () {
              $instance_hash{$hierarchy_split[$i]}{type} = "instance" ;
              last ;
          }
        }        
        
        print ("$instance_hash{$hierarchy_split[$i]}{name} ---$instance_hash{$hierarchy_split[$i]}{type} \n") ;

        
        if ($i == @hierarchy_split - 1) {
        
        } else {
        
        }
        
        
      } else {
          if ($i == @hierarchy_split - 1) {
          
          
          } else {
          

          }

      }
 
    }
  }
close (SC_TRACE) ;
close (DEF_FILE) ;
