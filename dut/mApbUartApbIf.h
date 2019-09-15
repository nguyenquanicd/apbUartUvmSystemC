//--------------------------------------
//Project:  The UVM environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Module:   apbUartApbIf
//Function: APB interface and Status/Configuration Registers
//Author:   Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
#include "systemc.h"
SC_MODULE (mApbUartApbIf) { 
  //
  // Input Signals
  //
  //APB interface
  sc_in< bool >  pClk;
  sc_in< bool >  pResetN;
  sc_in< bool >  pWrite;
  sc_in< bool >  pSel;
  sc_in< bool >  pEnable;
  sc_in< sc_uint<32> >  pAddr;
  sc_in< sc_uint<32> > pWData;
  sc_in< sc_uint<4> >  pStrb;
  //From Transmitter
  sc_in< bool >  txNf;
  sc_in< bool >  txBusy;
  sc_in< bool >  txTxe;
  //From Receiver
  sc_in< bool >  rxNe;
  sc_in< bool >  rxBusy;
  sc_in< bool >  rxRxf;
  sc_in< bool >  rxOv;
  sc_in< bool >  rxPe;
  sc_in< bool >  rxFe;
  sc_in< sc_uint<8> > rxData;
  //
  // Output Signals
  //
  sc_out< bool > ctrlEn;
  sc_out< bool > ctrlTxEn;
  sc_out< bool > ctrlD9;
  sc_out< bool > ctrlEp;
  sc_out< bool > ctrlShiftRx;
  sc_out< bool > ctrlShiftTx;
  sc_out< sc_uint<2> > ctrlTxt;
  sc_out< sc_uint<2> > ctrlRxt;
  sc_out< bool > ctrlDataRd;
  sc_out< sc_uint<8> > ctrlData;
  sc_out< sc_uint<32> > pRData;
  sc_out< bool > pReady;
  sc_out< bool > pSlvErr;
  #ifdef INTERRUPT_COM
  	sc_out< bool > ctrlIf;
  #endif
  #ifndef INTERRUPT_COM
  	sc_out< bool > ctrlTIf;
  	sc_out< bool > ctrlRIf;
  	sc_out< bool > ctrlOIf;
  	sc_out< bool > ctrlPIf;
  	sc_out< bool > ctrlFIf;
  #else
  	sc_signal< bool > ctrlTIf;
  	sc_signal< bool > ctrlRIf;
  	sc_signal< bool > ctrlOIf;
  	sc_signal< bool > ctrlPIf;
  	sc_signal< bool > ctrlFIf;
  #endif
  //
  // Internal Signals
  //
  sc_signal< bool > ctrlEnTmp;
  sc_signal< bool > conWe;
  sc_signal< bool > seWe;
  sc_signal< bool > brWe;
  sc_signal< bool > dtWe;
  sc_signal< bool > ieWe;
  sc_signal< sc_uint<4> > conReg;
  sc_signal< sc_uint<3> > seReg;
  sc_signal< sc_uint<8> > brReg;
  sc_signal< sc_uint<5> > ieReg;
  sc_signal< sc_uint<8> > rxCounter;
  sc_signal< sc_uint<4> > txCounter;
  sc_signal< bool > errCondition;
  //
  // Process declaration
  // RESET
	void initReset();
  
  void pmCombination();
  
  void pcSequence();
  
  //Constructor
	SC_CTOR(mApbUartApbIf) {
    
    //Address decoder
    SC_METHOD(pmCombination);
      sensitive << pSel;
      sensitive << pEnable;
      sensitive << pWrite;
      sensitive << pStrb;
      sensitive << pAddr;
      sensitive << brReg;
      sensitive << conReg;
      sensitive << seReg;
      sensitive << ieReg;
      sensitive << txTxe;
      sensitive << rxRxf;
      sensitive << rxOv;
      sensitive << rxPe;
      sensitive << rxFe;
      sensitive << txBusy;
      sensitive << rxBusy;
      sensitive << rxNe;
      sensitive << txNf;
      sensitive << rxData;
      sensitive << rxCounter;
      sensitive << txCounter;

    //Registers of UART
    SC_CTHREAD(pcSequence, pClk.pos());
      reset_signal_is(pResetN, false);
  }
};
