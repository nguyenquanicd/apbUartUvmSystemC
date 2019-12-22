//--------------------------------------
//Project:  Simple CPU
//Module:   SPCU Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
//#include <iostream>
#include "dut_top.cpp"
int sc_main (int argc, char* argv[]) {
  //1. Internal signal declaration
  sc_signal <bool> pResetN;
  //2. Create the clock 
  //Cycle: 2 ns
  //Duty cycle: 50%
  sc_clock pClk("pClk", 2, SC_NS, 0.5);
  //3. Instances
  TOP* dut_top = new TOP("dut_top");
  dut_top->pclk_0(pClk);
  dut_top->pclk_1(pClk);
  cout << "3.Start simulation" << endl;
  int count = 0;
  for (int i = 0; i < 500; i++) {
    sc_start(2, SC_NS); //One cycle
  }
  return 0;
}