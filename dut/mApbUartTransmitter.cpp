//--------------------------------------
//Project:  The UVM environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Module:   mApbUartTransmitter
//Function: Transmit the serial data follow UART protocol
//Author:   Le Hoang Van
//Page:     VLSI Technology
//--------------------------------------

#include "mApbUartTransmitter.h"

// pcRegisters
void mApbUartTransmitter::pcRegisters() {
    InitReset();
    wait();
    while(1) {
      // Read input value
      bool ctrlEn_r         = ctrlEn.read();
      sc_uint<8> ctrlData_r = ctrlData.read();
      // Read method value
      bool data9_r           = data9.read();
      bool loadData_r        = loadData.read();
      bool shiftEn_r         = shiftEn.read();
      bool txFifoRe_r        = txFifoRe.read();
      bool txFifoWe_r        = txFifoWe.read();
      bool txShiftComplete_r = txShiftComplete.read();
      sc_uint<8> txFifoOut_r = txFifoOut.read();
      // Current status
      bool state_r                = state.read();
      sc_uint<4> shiftTxCounter_r = shiftTxCounter.read();
      sc_uint<5> txRptr_r         = txRptr.read();
      sc_uint<5> txWptr_r         = txWptr.read();
      sc_uint<10> txShiftReg_r    = txShiftReg.read();
      sc_uint<8> txMemArray_r[16];
      int j ;
      for (j=0; j<16; j++) {
        txMemArray_r[j] = txMemArray[j].read();
      }
      
      // Write pointer declare
      sc_uint<5> txWptr_w;
      
      // get value base on control signals
      if (ctrlEn_r == 0) {
        shiftTxCounter.write(0); // Shift counter
        txShiftReg.write(0x3FF); // Transmit shift register
        state.write(IDLE);       // FSM tcreates fsmShift and fsmIdle signals
        txRptr.write(txWptr_r);  // Read pointer
        txWptr_w = 0;            // Write pointer
      } else {
        // Shift counter
        if (txShiftComplete_r == 1) {
          shiftTxCounter.write(0);
        } else if (shiftEn_r == 1) {
            shiftTxCounter.write((shiftTxCounter_r + 1));
        } else {
            shiftTxCounter.write(shiftTxCounter_r);
        }
        
        // Transmit shift register
        if ((loadData_r == 1) && (shiftEn_r == 0)) {
          txShiftReg.write((data9_r, txFifoOut_r, 0b0));
        } else if ((loadData_r == 0) && (shiftEn_r == 1)) {
            txShiftReg.write((0b1, txShiftReg_r.range(9,1)));
        } else {
            txShiftReg.write(txShiftReg_r);
        }
        
        // FSM tcreates fsmShift and fsmIdle signals
        if ((state_r == IDLE) && (loadData_r == 1)) {
          state.write(TXSHIFT);
        } else if ((state_r == TXSHIFT) && (txShiftComplete_r == 1)) {
            state.write(IDLE);
        } else {
            state.write(state_r);
        }
        
        // Read pointer
        if (txFifoRe_r == 1) {
          txRptr.write((txRptr_r + 1));
        } else {
            txRptr.write(txRptr_r);
        }
      
        // Write pointer
        if (txFifoWe_r == 1) {
          txWptr_w = txWptr_r + 1;
        } else {
            txWptr_w = txWptr_r;
        }
      }
      
      // Write pointer out
      txWptr.write(txWptr_w);
      
      // memory of TXFIFO
      for (j=0; j<16; j++) {
        if ((txFifoWe_r == 1) && (j == txWptr_w)) {
          txMemArray[j].write(ctrlData_r);
        } else {
            txMemArray[j].write(txMemArray_r[j]);
        }
      }
      
      wait();
    }
}

// pmSignals
void mApbUartTransmitter::pmSignals() {
  // Read input value
  bool ctrlD9_r        = ctrlD9.read();
  bool ctrlEn_r        = ctrlEn.read();
  bool ctrlEp_r        = ctrlEp.read();
  bool ctrlShiftTx_r   = ctrlShiftTx.read();
  bool ctrlTxEn_r      = ctrlTxEn.read();
  sc_uint<2> ctrlTxt_r = ctrlTxt.read();
  // Read thread value
  bool state_r                = state.read();
  sc_uint<4> shiftTxCounter_r = shiftTxCounter.read();
  sc_uint<5> txRptr_r         = txRptr.read();
  sc_uint<5> txWptr_r         = txWptr.read();
  sc_uint<10> txShiftReg_r    = txShiftReg.read();
  // From Memory with Read pointer
  sc_uint<8> txFifoOut_w      = txMemArray[txRptr_r].read();
  
  // intermediate value
  bool fsmIdle       = !state_r;
  bool fsmShift      = state_r;
  bool txFifoEmpty   = (txRptr_r.range(3,0) == txWptr_r.range(3,0)) & (txRptr_r[4] == txWptr_r[4]);
  bool txFifoFull    = (txRptr_r.range(3,0) == txWptr_r.range(3,0)) & (txRptr_r[4] != txWptr_r[4]);
  bool txWr          = ctrlEn_r & ctrlTxEn_r;
  bool txParity      = (ctrlEp_r == 1) ? !txFifoOut_w.xor_reduce() : txFifoOut_w.xor_reduce();
  sc_uint<5> dataNum = txWptr_r - txRptr_r;

  // complex assign
  bool data9_w           = (ctrlD9_r == 1) ? txParity : 0b1;
  bool loadData_w        = ctrlShiftTx_r & !txFifoEmpty & fsmShift;  
  bool txShiftComplete_w = (ctrlD9_r == 1) ? (shiftTxCounter_r == 0xA) : (shiftTxCounter_r == 0x9);
  bool txTxe_w;
  switch (ctrlTxt_r) {
	  case 0: 
      txTxe_w = (dataNum == 0);
      break;
	  case 1: 
      txTxe_w = (dataNum <= 2);
      break;
	  case 2: 
      txTxe_w = (dataNum <= 4);
      break;
	  case 3: 
      txTxe_w = (dataNum <= 8);
      break;
	  default:
      txTxe_w = 0;
      break;
	}
  
  // Signal written
  data9.write(data9_w);
  loadData.write(loadData_w); 
  shiftEn.write((fsmShift & ctrlShiftTx_r));
  txFifoRe.write((loadData_w & !txFifoEmpty));
  txFifoWe.write((txWr & !txFifoFull));
  txShiftComplete.write(txShiftComplete_w);
  txFifoOut.write(txFifoOut_w);
  // Ouput written
  txBusy.write(!(fsmIdle & txTxe_w));
  txNf.write(!txFifoFull);
  txTxe.write(txTxe_w);
  uartTx.write((txShiftReg_r[0]));
}

// Initialize value of Registers
void mApbUartTransmitter::InitReset() {
  shiftTxCounter.write(0); //Shift counter
  state.write(IDLE);       //FSM tcreates fsmShift and fsmIdle signals
  txShiftReg.write(0x3FF); //Transmit shift register
  txRptr.write(0);         //Read pointer
  txWptr.write(0);         //Write pointer
}

