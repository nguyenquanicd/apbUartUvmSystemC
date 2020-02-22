//--------------------------------------
//Project:  Simple CPU
//Module:   SPCU Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
//#include <iostream>
#include "uart_env.h"
int sc_main (int argc, char* argv[]) {
  //1. Internal signal declaration
  sc_signal <bool> pResetN;
  //2. Create the clock 
  //Cycle: 2 ns
  //Duty cycle: 50%
  sc_clock pClk("pClk", 2, SC_NS, 0.5);
  //3. Instances
  uart_env uart_env_inst("uart_env_inst");
  uart_env_inst.pClk(pClk);
  //4. Create VCD file to trace
  #include "uart_trace.h"
  //5. Start simulation
  cout << "3.Start simulation" << endl;
  int count = 0;
  for (int i = 0; i < 500; i++) {
    sc_start(2, SC_NS); //One cycle
  }
  //6. Close the waveform file
  sc_close_vcd_trace_file (uart_waveform);
  //7. END
  return 0;
}