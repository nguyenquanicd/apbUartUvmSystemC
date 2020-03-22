//--------------------------------------
//Project:  Simple CPU
//Module:   UART Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet
//Page:     VLSI Technology
//--------------------------------------

#include "systemc.h"
SC_MODULE (uart_testbench) {
	//Ports and signals
	sc_in <bool> pClk;
	sc_out <bool> pResetN;

  //  ***** APB interface TX *****
    sc_out< bool >  pWrite_Tx;
    sc_out< bool >  pSel_Tx;
    sc_out< bool >  pEnable_Tx;
    sc_out< sc_uint<32> >  pAddr_Tx;
    sc_out< sc_uint<32> > pWData_Tx;
    sc_out< sc_uint<4> >  pStrb_Tx;
    sc_in< sc_uint<32> > pRData_Tx;
    sc_in< bool > pReady_Tx;
    sc_in< bool > pSlvErr_Tx;
  
   //  ***** APB interface RX *****
    sc_out< bool >  pWrite_Rx;
    sc_out< bool >  pSel_Rx;
    sc_out< bool >  pEnable_Rx;
    sc_out< sc_uint<32> >  pAddr_Rx;
    sc_out< sc_uint<32> > pWData_Rx;
    sc_out< sc_uint<4> >  pStrb_Rx;
    sc_in< sc_uint<32> > pRData_Rx;
    sc_in< bool > pReady_Rx;
    sc_in< bool > pSlvErr_Rx; 
  
    //
	void TEST();
    void write_apb_Tx(unsigned int address, unsigned int data);
    void read_apb_Tx(unsigned int address, unsigned int exp_data);
    void write_apb_Rx(unsigned int address, unsigned int data);
    void read_apb_Rx(unsigned int address, unsigned int exp_data);
    unsigned int read_apb_Rx_N_cmpr(unsigned int address);
	//Constructor
	SC_CTOR (uart_testbench)  {
	  //
	    SC_THREAD (TEST);
	      sensitive << pClk.pos();
	}
	//Destructor

};

