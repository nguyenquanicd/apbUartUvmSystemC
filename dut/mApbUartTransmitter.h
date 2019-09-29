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
  sc_in<sc_uint<8> > ctrlData;
  sc_in<bool> ctrlEn;
  sc_in<bool> ctrlTxEn;
  sc_in<bool> ctrlD9;
  sc_in<bool> ctrlEp;
  sc_in<bool> ctrlShiftTx;
  sc_in<sc_uint<2> > ctrlTxt;

  // Outputs
  sc_out<bool> txNf;
  sc_out<bool> txBusy;
  sc_out<bool> txTxe;
  sc_out<bool> uartTx;    

  // Internal signals
  sc_signal<sc_uint<4> > shiftTxCounter;
  sc_signal<bool> state;
  sc_signal<bool> fsmShift;
  sc_signal<bool> fsmIdle;
  sc_signal<bool> txShiftComplete;
  sc_signal<bool> shiftEn;
  sc_signal<bool> loadData;
  sc_signal<bool> data9;
  sc_signal<sc_uint<8> > txFifoOut;
  sc_signal<sc_uint<8> > txMemArray[16];
  sc_signal<sc_uint<5> > txRptr;
  sc_signal<sc_uint<5> > txWptr;
  sc_signal<sc_uint<5> > dataNum;
  //sc_signal<bool> tx_fifo_ud;
  //sc_signal<bool> tx_fifo_ov;
  sc_signal<bool> txFifoRe;
  sc_signal<bool> txFifoWe;
  sc_signal<bool> txFifoFull;
  sc_signal<bool> txFifoEmpty;
  sc_signal<sc_uint<10> > txShiftReg;
  sc_signal<bool> txParity;
  sc_signal<bool> txWr;

  // other variables
  // because of SystemC Restriction
  sc_signal<bool> txTxeFb;
  sc_uint<4> bitSelect;

  // Process declaration
  //
  // InitReset
  // Internal function supports initialize value of Registers
  void InitReset();

  // pcRegisters
  // CTHREAD contains all Registers
  void pcRegisters();

  // pmOutput_1
  // METHOD of Outputs, using assignment
  void pmOutput_1();

  // pmOutput_2
  // METHOD of Outputs, using swich case
  void pmOutput_2();

  // pmTxFifoStatus
  // METHOD of internal signals, which are status of FIFO
  // and other signals have same sensitive list
  void pmTxFifoStatus();

  // pmTxFifoControl
  // METHOD of internal signals, which control FIFO
  // and other signals have same sensitive list
  void pmTxFifoControl();

  // pmRegistersControl
  // METHOD of internal signals, which control CTHREAD Registers
  // and other signals have same sensitive list
  void pmRegistersControl();

  // Constructor
  SC_CTOR(mApbUartTransmitter) {

    SC_CTHREAD(pcRegisters, pClk.pos());
      reset_signal_is(pResetN, false);

    SC_METHOD(pmOutput_1);
      sensitive << txFifoFull;
      sensitive << txTxeFb;
      sensitive << txShiftReg;
      sensitive << fsmIdle;

    SC_METHOD(pmOutput_2);
      sensitive << ctrlTxt;
      sensitive << dataNum;

    SC_METHOD(pmTxFifoStatus);
      sensitive << txRptr;
      sensitive << txWptr;
      for (bitSelect = 0; bitSelect < 16; bitSelect ++) {
        sensitive << txMemArray[bitSelect];
      }

    SC_METHOD(pmTxFifoControl);
      sensitive << loadData;
      sensitive << txFifoEmpty;
      sensitive << txFifoFull;
      sensitive << txFifoOut;
      sensitive << txWr;
      sensitive << ctrlEp;
      sensitive << state;

    SC_METHOD(pmRegistersControl);
      sensitive << ctrlD9;
      sensitive << ctrlEn;
      sensitive << ctrlTxEn;
      sensitive << ctrlShiftTx;
      sensitive << shiftTxCounter;
      sensitive << txParity;
      sensitive << txFifoEmpty;
      sensitive << fsmIdle;
      sensitive << fsmShift;

  }
};

