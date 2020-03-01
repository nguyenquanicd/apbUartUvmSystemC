#!/usr/bin/perl

# This script generate source code which is used for dump waveform.
# Put main script (waveform.pl) & define file (waveform.def)
#   at the simulation folder which contain main C++ file (sc_main funtion)
# Usage:  waveform.pl <waveform file> <trace file>
# Output: <trace file> - temporary source code has 2 part:
#   + Intance sc_trace_file & list of signal => user should put those source code
#       in sc_main funtion, after instance necessary model.
#   + sc_close_vcd_trace_file => user should put this line at the end of sc_main funtion.

#Example: waveform file = wf, trace file = counter_wf.h
#sc_trace_file *wf = sc_create_vcd_trace_file("wf");
#sc_trace(wf, clock, "clock");
#sc_trace(wf, reset, "reset");
#sc_trace(wf, enable, "enable");
#sc_trace(wf, counter_out, "count");
#sc_close_vcd_trace_file(wf);

use File::Basename;
use File::Copy;
use File::Path;

my $argv_count = $#ARGV + 1 ;
if ($argv_count != 2) {
  print ("Wrong argument !\n") ;
  print ("Usage: ./waveform.pl <waveform file> <trace file>\n") ;
  exit ;
}

my $waveform_file    = "$ARGV[0]";
my $trace_file       = "$ARGV[1]" ;
my $def_line ;
my @def_line_split ;
my $hierarchy ;
my $enable_flag ;
my @hierarchy_split ;
my %instance_hash ;
my $model_file ;
my $model_line ;
my @model_line_split ;
my @model_all_line ;
my @pointer_find ;
my @instance_find ;
my $module_name ;
my @module_find ;
my $routing_path ;
my $start_flag ;
my $signal ;
my @signal_split ;
my $signal_prefix ;

my $pj_introduce = "//--------------------------------------\
//Project:  Simple CPU\
//Module:   SPCU Testbench - header file\
//Function: Provide input for CPU\
//Author:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan\
//Page:     VLSI Technology\
//--------------------------------------\
" ;

my $waveform_begin = "// START
sc_trace_file *$waveform_file =  sc_create_vcd_trace_file(\"$waveform_file\");\
  if($waveform_file==NULL) cout<<\"Cannot create the waveform file\"<< endl;\
  else cout << \"Create the waveform file - \" << $waveform_file << endl;\
" ;

open (TEMP_FILE, "> TEMP_FILE") ;
print TEMP_FILE ("$pj_introduce\n") ;
print TEMP_FILE ("$waveform_begin\n") ;

open (DEF_FILE, "< waveform.def") ;
  foreach $def_line (<DEF_FILE>) {
    chomp $def_line ;
    next if (("$def_line" =~ /#/) || ("$def_line" !~ / [01]$/)) ;
    
    @def_line_split = split (/ /, "$def_line") ;
    $hierarchy      = "$def_line_split[0]" ;
    $enable_flag    = "$def_line_split[1]" ;
    next if ($enable_flag == 0) ;
    
    @hierarchy_split = split (/\./, "$hierarchy") ;
    $routing_path = "" ;
    for (my $i = 0; $i < @hierarchy_split; $i++) {
      if (! defined $instance_hash{$hierarchy_split[$i]}) {
        $instance_hash{$hierarchy_split[$i]}{name} = "$hierarchy_split[$i]" ;
        
        foreach $model_file (glob "*\.h *\.cpp") {
          open (MODEL_FILE, "< $model_file") ;
          @model_all_line = <MODEL_FILE> ;
          close (MODEL_FILE) ;
          
          @pointer_find  = grep /\s*\b$hierarchy_split[$i]\b\s*=\s*new/, @model_all_line ;
          @instance_find = grep /\s*\b$hierarchy_split[$i]\b\s*;/, @model_all_line ;
          if (@pointer_find == 1) {
            $instance_hash{$hierarchy_split[$i]}{type} = "pointer" ;
            open (MODEL_FILE, "< $model_file") ;
            foreach $model_line (<MODEL_FILE>) {
              if ("$model_line" =~ /\s*\b$hierarchy_split[$i]\b\s*=\s*new/) {
                chomp $model_line ;
                $model_line       =~ s/\s*//g ;
                @model_line_split = split (/\*/, "$model_line") ;
                $module_name      = "$model_line_split[0]";
                last ;
              }
            }
            close (MODEL_FILE) ;
            last ;
          } elsif (@instance_find == 1) {
              $instance_hash{$hierarchy_split[$i]}{type} = "instance" ;
              open (MODEL_FILE, "< $model_file") ;
              foreach $model_line (<MODEL_FILE>) {
                if ("$model_line" =~ /\s*\b$hierarchy_split[$i]\b\s*;/) {
                  chomp $model_line ;
                  $model_line  =~ s/\b$hierarchy_split[$i]\b.+// ;
                  $model_line  =~ s/\s*//g ;
                  $module_name = "$model_line";
                  last ;
                }
              }
              close (MODEL_FILE) ;
              last ;
          }
        }
        
        if ((@pointer_find == 0) && (@instance_find == 0)) {
          print ("ERROR: can not find new pointer or new instance $instance_hash{$hierarchy_split[$i]}{name}, plz check again !\n") ;
          exit ;
        }
        
        foreach $model_file (glob "*\.h *\.cpp") {
          open (MODEL_FILE, "< $model_file") ;
          @model_all_line = <MODEL_FILE> ;
          close (MODEL_FILE) ;
          
          @module_find  = grep /SC_MODULE.*\b$module_name\b/, @model_all_line ;
          if (@module_find == 1) {
            $instance_hash{$hierarchy_split[$i]}{file} = "$model_file" ;
            last ;
          }
        }
        
        if (@module_find == 0) {
          print ("ERROR: can not find module declaration for $instance_hash{$hierarchy_split[$i]}{name}, plz check again !\n") ;
          exit ;
        }
        
        if ($i == @hierarchy_split - 1) {
            if ("$instance_hash{$hierarchy_split[$i]}{type}" eq "pointer") {
              $routing_path .= "$instance_hash{$hierarchy_split[$i]}{name}->" ;
            } else {
                $routing_path .= "$instance_hash{$hierarchy_split[$i]}{name}." ;
            }
            
            $signal_prefix = "$routing_path" ;
            $signal_prefix =~ s/->/./g ;
            
            #list all signal
            open (MODEL_FILE, "< $instance_hash{$hierarchy_split[$i]}{file}") ;
            $start_flag = 0 ;
            foreach $model_line (<MODEL_FILE>) {
              if ($start_flag == 1) {
                $model_line =~ s/\r\n/\n/ ;
                if ("$model_line" =~ /SC_CTOR/) {
                  print TEMP_FILE ("\n") ;
                  last ;
                } elsif ("$model_line" =~ /sc_in|sc_out|sc_signal|sc_inout/) {
                    chomp $model_line ;
                    @model_line_split = split (/>/, "$model_line") ;
                    $signal = "$model_line_split[-1]" ;
                    $signal =~ s/;.*//g ;
                    $signal =~ s/\s*//g ;
                    if ("$signal" =~ /\[/) {
                      $signal =~ s/\]//g ;
                      @signal_split = split (/\[/, "$signal") ;
                      
                      print TEMP_FILE ("for (int i=0; i<$signal_split[1]; i++) {\n") ;
                      print TEMP_FILE ("  char str[4];\n") ;
                      print TEMP_FILE ("  sprintf(str, \"(%0d)\",i);\n") ;
                      #print TEMP_FILE ("  sc_trace($waveform_file, $routing_path$signal_split[0]\[i], \"$signal_split[0]_$instance_hash{$hierarchy_split[$i]}{name}_\" + string(str));\n") ;
                      print TEMP_FILE ("  sc_trace($waveform_file, $routing_path$signal_split[0]\[i], \"$signal_prefix$signal_split[0]_\" + string(str));\n") ;
                      print TEMP_FILE ("}\n") ;
                    } else {
                        #print TEMP_FILE ("sc_trace($waveform_file, $routing_path$signal, \"$signal\_$instance_hash{$hierarchy_split[$i]}{name}\");\n") ;
                        print TEMP_FILE ("sc_trace($waveform_file, $routing_path$signal, \"$signal_prefix$signal\");\n") ;
                    }
                } elsif ("$model_line" =~ /#ifdef|#ifndef|#else|#endif/) {
                    chomp $model_line ;
                    $model_line =~ s/\s*//g ;
                    print TEMP_FILE ("$model_line\n") ;
                }
              } elsif ("$model_line" =~ /SC_MODULE/) {
                  $start_flag = 1 ;
                  print TEMP_FILE ("//$instance_hash{$hierarchy_split[$i]}{name} --- list of ports & signals\n") ;
              }
            }
            close (MODEL_FILE) ; 
        } else {
            if ("$instance_hash{$hierarchy_split[$i]}{type}" eq "pointer") {
              $routing_path .= "$instance_hash{$hierarchy_split[$i]}{name}->" ;
            } else {
                $routing_path .= "$instance_hash{$hierarchy_split[$i]}{name}." ;
            }
        }
      } else {
          if ($i == @hierarchy_split - 1) {
            if ("$instance_hash{$hierarchy_split[$i]}{type}" eq "pointer") {
              $routing_path .= "$instance_hash{$hierarchy_split[$i]}{name}->" ;
            } else {
                $routing_path .= "$instance_hash{$hierarchy_split[$i]}{name}." ;
            }
            
            $signal_prefix = "$routing_path" ;
            $signal_prefix =~ s/->/./g ;
            
            #list all signal
            open (MODEL_FILE, "< $instance_hash{$hierarchy_split[$i]}{file}") ;
            $start_flag = 0 ;
            foreach $model_line (<MODEL_FILE>) {
              if ($start_flag == 1) {
                $model_line =~ s/\r\n/\n/ ;
                if ("$model_line" =~ /SC_CTOR/) {
                  print TEMP_FILE ("\n") ;
                  last ;
                } elsif ("$model_line" =~ /sc_in|sc_out|sc_signal|sc_inout/) {
                    chomp $model_line ;
                    @model_line_split = split (/>/, "$model_line") ;
                    $signal = "$model_line_split[-1]" ;
                    $signal =~ s/;.*//g ;
                    $signal =~ s/\s*//g ;
                    if ("$signal" =~ /\[/) {
                      $signal =~ s/\]//g ;
                      @signal_split = split (/\[/, "$signal") ;
                      
                      print TEMP_FILE ("for (int i=0; i<$signal_split[1]; i++) {\n") ;
                      print TEMP_FILE ("  char str[4];\n") ;
                      print TEMP_FILE ("  sprintf(str, \"(%0d)\",i);\n") ;
                      #print TEMP_FILE ("  sc_trace($waveform_file, $routing_path$signal_split[0]\[i], \"$signal_split[0]_$instance_hash{$hierarchy_split[$i]}{name}_\" + string(str));\n") ;
                      print TEMP_FILE ("  sc_trace($waveform_file, $routing_path$signal_split[0]\[i], \"$signal_prefix$signal_split[0]_\" + string(str));\n") ;
                      print TEMP_FILE ("}\n") ;
                    } else {
                        #print TEMP_FILE ("sc_trace($waveform_file, $routing_path$signal, \"$signal\_$instance_hash{$hierarchy_split[$i]}{name}\");\n") ;
                        print TEMP_FILE ("sc_trace($waveform_file, $routing_path$signal, \"$signal_prefix$signal\");\n") ;
                    }
                } elsif ("$model_line" =~ /#ifdef|#ifndef|#else|#endif/) {
                    chomp $model_line ;
                    $model_line =~ s/\s*//g ;
                    print TEMP_FILE ("$model_line\n") ;
                }
              } elsif ("$model_line" =~ /SC_MODULE/) {
                  $start_flag = 1 ;
                  print TEMP_FILE ("//$instance_hash{$hierarchy_split[$i]}{name} --- list of ports & signals\n") ;
              }
            }
            close (MODEL_FILE) ; 
          } else {
              if ("$instance_hash{$hierarchy_split[$i]}{type}" eq "pointer") {
                $routing_path .= "$instance_hash{$hierarchy_split[$i]}{name}->" ;
              } else {
                  $routing_path .= "$instance_hash{$hierarchy_split[$i]}{name}." ;
              }
          }
      }
    }
  }
close (DEF_FILE) ;

print TEMP_FILE ("// END\n") ;
close (TEMP_FILE) ;
move ("TEMP_FILE", "$trace_file") ;

1;
