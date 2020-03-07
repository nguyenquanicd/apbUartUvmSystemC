//--------------------------------------
//Project:  Simple CPU
//Module:   SPCU Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

// START
sc_trace_file *uart_waveform =  sc_create_vcd_trace_file("uart_waveform");
  if(uart_waveform==NULL) cout<<"Cannot create the waveform file"<< endl;
  else cout << "Create the waveform file - " << uart_waveform << endl;

// END
