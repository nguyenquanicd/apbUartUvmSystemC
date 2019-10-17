//--------------------------------------
//Project:  The UVM environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Module:   mApbUartTransmitter
//Function: Transmit the serial data follow UART protocol
//Author:   Le Hoang Van
//Page:     VLSI Technology
//--------------------------------------

#include "systemc.h"
//#include "uart_define.h"

// Parameter
#define IDLE 0
#define TXSHIFT 1

SC_MODULE (mApbUartTransmitter) {
  // Inputs
  sc_in<bool> pClk;
  sc_in<bool> pResetN;
  sc_in<bool> ctrlD9;
  sc_in<bool> ctrlEn;
  sc_in<bool> ctrlEp;
  sc_in<bool> ctrlShiftTx;
  sc_in<bool> ctrlTxEn;
  sc_in<sc_uint<2> > ctrlTxt;
  sc_in<sc_uint<8> > ctrlData;

  // Outputs
  sc_out<bool> txBusy;
  sc_out<bool> txNf;
  sc_out<bool> txTxe;
  sc_out<bool> uartTx;    

  // Internal signals
  sc_signal<bool> data9;
  sc_signal<bool> fsmIdle;
  sc_signal<bool> fsmShift;
  sc_signal<bool> loadData;
  sc_signal<bool> shiftEn;
  sc_signal<bool> state;
  sc_signal<bool> txFifoEmpty;
  sc_signal<bool> txFifoFull;
  sc_signal<bool> txFifoRe;
  sc_signal<bool> txFifoWe;
  sc_signal<bool> txParity;
  sc_signal<bool> txShiftComplete;
  sc_signal<bool> txWr;
  sc_signal<sc_uint<4> > shiftTxCounter;
  sc_signal<sc_uint<5> > dataNum;
  sc_signal<sc_uint<5> > txRptr;
  sc_signal<sc_uint<5> > txWptr;
  sc_signal<sc_uint<8> > txFifoOut;
  sc_signal<sc_uint<10> > txShiftReg;

  // other variables
  sc_uint<8> txMemArray[16];
  
  // Process declaration
  //
  // InitReset
  // Internal function supports initialize value of Registers
  void InitReset();

  // pcRegisters
  // CTHREAD for all Registers
  void pcRegisters();

  // pmSignals
  // METHOD for combinational logic
  void pmSignals();

  // Constructor
  SC_CTOR(mApbUartTransmitter) {

    SC_CTHREAD(pcRegisters, pClk.pos());
      reset_signal_is(pResetN, false);

    SC_METHOD(pmSignals);
      sensitive << ctrlD9;
      sensitive << ctrlEn;
      sensitive << ctrlEp;
      sensitive << ctrlShiftTx;
      sensitive << ctrlTxEn;
      sensitive << ctrlTxt;
      sensitive << state;
      sensitive << shiftTxCounter;
      sensitive << txShiftReg;
      sensitive << txRptr;
      sensitive << txWptr;
  }
};

