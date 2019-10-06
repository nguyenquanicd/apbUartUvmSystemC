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
      bool ctrlEn_r          = ctrlEn.read();
      bool data9_r           = data9.read();
      bool loadData_r        = loadData.read();
      bool shiftEn_r         = shiftEn.read();
      bool state_r           = state.read();
      bool txFifoRe_r        = txFifoRe.read();
      bool txFifoWe_r        = txFifoWe.read();
      bool txShiftComplete_r = txShiftComplete.read();
      sc_uint<4> shiftTxCounter_r = shiftTxCounter.read();
      sc_uint<5> txRptr_r         = txRptr.read();
      sc_uint<5> txWptr_r         = txWptr.read();
      sc_uint<8> ctrlData_r     = ctrlData.read();
      sc_uint<8> txFifoOut_r      = txFifoOut.read();
      sc_uint<10> txShiftReg_r    = txShiftReg.read();
      sc_uint<8> txMemArray_r[16];
      txMemArray_r[txFifoWe_r] = txMemArray[txFifoWe_r].read();

      // Output prepare
      sc_uint<4> shiftTxCounter_w;
      sc_uint<10> txShiftReg_w;
      bool state_w;
      sc_uint<5> txRptr_w;
      sc_uint<5> txWptr_w;
      sc_uint<8> txMemArray_w[16];
      
      // get value base on control signals
      if (ctrlEn_r == 0) {
        shiftTxCounter_w = 0; //Shift counter
        txShiftReg_w     = 0x3FF; //Transmit shift register
        state_w          = IDLE; //FSM tcreates fsmShift and fsmIdle signals
        txRptr_w         = txWptr_r; //Read pointer
        txWptr_w         = 0; //Write pointer
      } else {
        //Shift counter
        if (txShiftComplete_r == 1) {
          shiftTxCounter_w = 0;
        } else if (shiftEn_r == 1) {
            shiftTxCounter_w = shiftTxCounter_r + 1;
        } else {
            shiftTxCounter_w = shiftTxCounter_r;
        }
        
        //Transmit shift register
        if ((loadData_r == 1) && (shiftEn_r == 0)) {
          txShiftReg_w = (data9_r, txFifoOut_r, 0b0);
        } else if ((loadData_r == 0) && (shiftEn_r == 1)) {
            txShiftReg_w = (0b1, txShiftReg_r.range(9,1));
        } else {
            txShiftReg_w = txShiftReg_r;
        }
        
        //FSM tcreates fsmShift and fsmIdle signals
        if ((state_r == IDLE) && (loadData_r == 1)) {
          state_w = TXSHIFT;
        } else if ((state_r == TXSHIFT) && (txShiftComplete_r == 1)) {
            state_w = IDLE;
        } else {
            state_w = state_r;
        }
        
        //Read pointer
        if (txFifoRe_r == 1) {
          txRptr_w = txRptr_r + 1;
        } else {
            txRptr_w = txRptr_r;
        }
      
        //Write pointer
        if (txFifoWe_r == 1) {
          txWptr_w = txWptr_r + 1;
        } else {
            txWptr_w = txWptr_r;
        }
      }

      //memory of TXFIFO
      if (txFifoWe_r == 1) {
        txMemArray_w[txWptr_r] = ctrlData_r;
      } else {
        txMemArray_w[txWptr_r] = txMemArray_r[txWptr_r];
      }


      // write ports
      shiftTxCounter.write(shiftTxCounter_w); //Shift counter
      txShiftReg.write(txShiftReg_w); //Transmit shift register
      state.write(state_w); //FSM tcreates fsmShift and fsmIdle signals
      txRptr.write(txRptr_w); //Read pointer
      txWptr.write(txWptr_w); //Write pointer
      txMemArray[txWptr_r].write(txMemArray_w[txWptr_r]); //memory of TXFIFO
      
      wait();
    }
}

// pmSignals
void mApbUartTransmitter::pmSignals() {
  // Read input value
  bool ctrlD9_r      = ctrlD9.read();
  bool ctrlEn_r      = ctrlEn.read();
  bool ctrlEp_r      = ctrlEp.read();
  bool ctrlShiftTx_r = ctrlShiftTx.read();
  bool ctrlTxEn_r    = ctrlTxEn.read();
  bool fsmIdle_r     = fsmIdle.read();
  bool fsmShift_r    = fsmShift.read();
  bool loadData_r    = loadData.read();
  bool state_r       = state.read();
  bool txFifoEmpty_r = txFifoEmpty.read();
  bool txFifoFull_r  = txFifoFull.read();
  bool txParity_r    = txParity.read();
  bool txTxeFb_r     = txTxeFb.read();
  bool TxWr_r        = TxWr.read();
  sc_uint<2> ctrlTxt_r        = ctrlTxt.read();
  sc_uint<4> shiftTxCounter_r = shiftTxCounter.read();
  sc_uint<5> dataNum_r        = dataNum.read();
  sc_uint<5> txRptr_r         = txRptr.read();
  sc_uint<5> txWptr_r         = txWptr.read();
  sc_uint<8> txFifoOut_r      = txFifoOut.read();
  sc_uint<10> txShiftReg_r    = txShiftReg.read();
  sc_uint<8> txMemArray_r[16];
  txMemArray_r[txRptr_r] = txMemArray[txRptr_r].read();

  //
  bool txBusy_w = ~(fsmIdle_r & txTxeFb_r);
  bool txNf_w   = ~txFifoFull_r;
  bool uartTx_w = txShiftReg_r[0];
  
  txBusy.write(txBusy_w);
  txNf.write(txNf_w);
  uartTx.write(uartTx_w);

  //
  bool txTxe_w;
  switch (ctrlTxt_r) {
	  case 0: 
      txTxe_w = (dataNum_r == 0);
      break;
	  case 1: 
      txTxe_w = (dataNum_r <= 2);
      break;
	  case 2: 
      txTxe_w = (dataNum_r <= 4);
      break;
	  case 3: 
      txTxe_w = (dataNum_r <= 8);
      break;
	  default:
      txTxe_w = 0;
      break;
	}
  txTxe.write(txTxe_w);
  txTxeFb.write(txTxe_w);

  //
  bool txFifoEmpty_w     = (txRptr_r.range(3,0) == txWptr_r.range(3,0)) & (txRptr_r[4] == txWptr_r[4]);
  bool txFifoFull_w      = (txRptr_r.range(3,0) == txWptr_r.range(3,0)) & (txRptr_r[4] != txWptr_r[4]);
  sc_uint<5> dataNum_w   = txWptr_r - txRptr_r;
  sc_uint<8> txFifoOut_w = txMemArray_r[txRptr_r];
  
  txFifoEmpty.write(txFifoEmpty_w);
  txFifoFull.write(txFifoFull_w);
  dataNum.write(dataNum_w);
  txFifoOut.write(txFifoOut_w);

  //
  bool fsmIdle_w  = ~state_r;
  bool fsmShift_w = state_r;
  bool txParity_w = (ctrlEp_r == 1) ? ~txFifoOut_r.xor_reduce() : txFifoOut_r.xor_reduce();
  bool txFifoRe_w = loadData_r & ~txFifoEmpty_r;
  bool txFifoWe_w = TxWr_r & ~txFifoFull_r;

  fsmIdle.write(fsmIdle_w);
  fsmShift.write(fsmShift_w);
  txParity.write(txParity_w);
  txFifoRe.write(txFifoRe_w);
  txFifoWe.write(txFifoWe_w);

  //
  bool data9_w           = (ctrlD9_r == 1) ? txParity_r : 0b1;
  bool loadData_w        = ctrlShiftTx_r & ~txFifoEmpty_r & fsmIdle_r;
  bool shiftEn_w         = fsmShift_r & ctrlShiftTx_r;
  bool txShiftComplete_w = (ctrlD9_r == 1) ? (shiftTxCounter_r == 0xA) : (shiftTxCounter_r == 0x9);
  bool TxWr_w            = ctrlEn_r & ctrlTxEn_r;

  data9.write(data9_w);
  loadData.write(loadData_w);
  shiftEn.write(shiftEn_w);
  txShiftComplete.write(txShiftComplete_w);
  TxWr.write(TxWr_w);
}

// Initialize value of Registers
void mApbUartTransmitter::InitReset() {
  shiftTxCounter.write(0); //Shift counter
  state.write(IDLE); //FSM tcreates fsmShift and fsmIdle signals
  txShiftReg.write(0x3FF); //Transmit shift register
  txRptr.write(0); //Read pointer
  txWptr.write(0); //Write pointer
}

