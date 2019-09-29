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
      bool ctrlEn_ = ctrlEn.read();
      sc_uint<5> txRptr_ = txRptr.read();
      sc_uint<5> txWptr_ = txWptr.read();
      bool txShiftComplete_ = txShiftComplete.read();
      bool shiftEn_ = shiftEn.read();
      sc_uint<4> shiftTxCounter_ = shiftTxCounter.read();
      sc_uint<10> txShiftReg_ = txShiftReg.read();
      bool state_ = state.read();
      bool loadData_ = loadData.read();
      bool data9_ = data9.read();
      sc_uint<8> txFifoOut_ = txFifoOut.read();
      bool txFifoRe_ = txFifoRe.read();
      bool txFifoWe_ = txFifoWe.read();
      bool ctrlData_ = ctrlData.read();
      
      // defaut value
      sc_uint<4> ShiftTxCounter_tmp = shiftTxCounter_; //Shift counter
      sc_uint<10> TxShiftReg_tmp = txShiftReg_; //Transmit shift register
      bool State_tmp = state_; //FSM tcreates fsmShift and fsmIdle signals
      sc_uint<5> TxRptr_tmp = txRptr_; //Read pointer
      sc_uint<5> TxWptr_tmp = txWptr_; //Write pointer
      sc_uint<8> TxMemArray_tmp[16]; //memory of TXFIFO
      for (bitSelect = 0; bitSelect < 16; bitSelect ++) {
        TxMemArray_tmp[bitSelect] = txMemArray[bitSelect].read();
      }
      
      // get value base on control signals
      if (ctrlEn_ == 0) {
        ShiftTxCounter_tmp = 0; //Shift counter
        TxShiftReg_tmp = 0x3FF; //Transmit shift register
        State_tmp = IDLE; //FSM tcreates fsmShift and fsmIdle signals
        TxRptr_tmp = txWptr_; //Read pointer
        TxWptr_tmp = 0; //Write pointer
      } else {
        //Shift counter
        if (txShiftComplete_ == 1) {
          ShiftTxCounter_tmp = 0;
        } else if (shiftEn_ == 1) {
            ShiftTxCounter_tmp = shiftTxCounter_ + 1;
        }
        
        //Transmit shift register
        if ((loadData_ == 1) && (shiftEn_ == 0)) {
          TxShiftReg_tmp = (data9_, txFifoOut_, 0b0);
        } else if ((loadData_ == 0) && (shiftEn_ == 1)) {
            TxShiftReg_tmp = (0b1, txShiftReg_.range(9,1));
        }
        
        //FSM tcreates fsmShift and fsmIdle signals
        if ((state_ == IDLE) && (loadData_ == 1)) {
          State_tmp = TXSHIFT;
        } else if ((state_ == TXSHIFT) && (txShiftComplete_ == 1)) {
            State_tmp = IDLE;
        }
        
        //Read pointer
        if (txFifoRe_ == 1){
            TxRptr_tmp = txRptr_ + 1;
        }
      
        //Write pointer
        if (txFifoWe_ == 1) {
          TxWptr_tmp = txWptr_ + 1;
        }
      }

      //memory of TXFIFO
      if (txFifoWe_ == 1) {
        bitSelect = txWptr_.range(3,0);
        TxMemArray_tmp[bitSelect] = ctrlData_;
      }
      
      // write ports
      shiftTxCounter.write(ShiftTxCounter_tmp); //Shift counter
      txShiftReg.write(TxShiftReg_tmp); //Transmit shift register
      state.write(State_tmp); //FSM tcreates fsmShift and fsmIdle signals
      txRptr.write(TxRptr_tmp); //Read pointer
      txWptr.write(TxWptr_tmp); //Write pointer
      for (bitSelect = 0; bitSelect < 16; bitSelect ++) { //memory of TXFIFO
        txMemArray[bitSelect].write(TxMemArray_tmp[bitSelect]);
      }
      
      wait();
    }
}

// pmOutput_1
void mApbUartTransmitter::pmOutput_1() {
  bool TxNf_tmp = ~txFifoFull.read();
  bool TxBusy_tmp = ~(fsmIdle.read() & txTxeFb.read());
  bool UartTx_tmp = txShiftReg.read()[0];
  
  txNf.write(TxNf_tmp);
  txBusy.write(TxBusy_tmp);
  uartTx.write(UartTx_tmp);
}

// pmOutput_2
void mApbUartTransmitter::pmOutput_2() {
  bool TxTxe_tmp;
  bool TxTxeFb_tmp;
  sc_uint<5> dataNum_ = dataNum.read();
   
  switch (ctrlTxt.read()) {
	  case 0: 
      TxTxe_tmp = (dataNum_ == 0);
      TxTxeFb_tmp = (dataNum_ == 0);
      break;
	  case 1: 
      TxTxe_tmp = (dataNum_ <= 2);
      TxTxeFb_tmp = (dataNum_ <= 2);
      break;
	  case 2: 
      TxTxe_tmp = (dataNum_ <= 4);
      TxTxeFb_tmp = (dataNum_ <= 4);
      break;
	  case 3: 
      TxTxe_tmp = (dataNum_ <= 8);
      TxTxeFb_tmp = (dataNum_ <= 8);
      break;
	  default:
      TxTxe_tmp = 0;
      TxTxeFb_tmp = 0;
      break;
	}
  
  txTxe.write(TxTxe_tmp);
  txTxeFb.write(TxTxeFb_tmp);
}

// pmTxFifoStatus
void mApbUartTransmitter::pmTxFifoStatus() {
  sc_uint<5> txRptr_ = txRptr.read();
  sc_uint<5> txWptr_ = txWptr.read();

  bool TxFifoEmpty_tmp = (txRptr_.range(3,0) == txWptr_.range(3,0)) & (txRptr_[4] == txWptr_[4]);
  bool TxFifoFull_tmp = (txRptr_.range(3,0) == txWptr_.range(3,0)) & (txRptr_[4] != txWptr_[4]);
  sc_uint<8> TxFifoOut_tmp = txMemArray[txRptr_.range(3,0)].read();
  sc_uint<5> DataNum_tmp = txWptr_ - txRptr_;
  
  txFifoEmpty.write(TxFifoEmpty_tmp);
  txFifoFull.write(TxFifoFull_tmp);
  txFifoOut.write(TxFifoOut_tmp);
  dataNum.write(DataNum_tmp);
}

// pmTxFifoControl
void mApbUartTransmitter::pmTxFifoControl() {
  bool loadData_ = loadData.read();
  bool txFifoEmpty_ = txFifoEmpty.read(); 
  bool txWr_ = txWr.read();
  bool txFifoFull_ = txFifoFull.read();
  bool ctrlEp_ = ctrlEp.read();
  sc_uint<8> txFifoOut_ = txFifoOut.read();
  bool state_ = state.read();
  
  bool TxFifoRe_tmp = loadData_ & ~txFifoEmpty_;
  bool TxFifoWe_tmp = txWr_ & ~txFifoFull_;
  bool TxParity_tmp = (ctrlEp_ == 1) ? ~txFifoOut_.xor_reduce() : txFifoOut_.xor_reduce();
  bool FsmShift_tmp = state_;
  bool FsmIdle_tmp = ~state_;
  
  txFifoRe.write(TxFifoRe_tmp);
  txFifoWe.write(TxFifoWe_tmp);
  txParity.write(TxParity_tmp);
  fsmShift.write(FsmShift_tmp);
  fsmIdle.write(FsmIdle_tmp);
}

// pmRegistersControl
void mApbUartTransmitter::pmRegistersControl() {
  bool ctrlD9_ = ctrlD9.read();
  sc_uint<4> shiftTxCounter_ = shiftTxCounter.read();
  bool ctrlEn_ = ctrlEn.read();
  bool ctrlTxEn_ = ctrlTxEn.read();
  bool txParity_ = txParity.read();
  bool ctrlShiftTx_ = ctrlShiftTx.read();
  bool txFifoEmpty_ = txFifoEmpty.read();
  bool fsmIdle_ = fsmIdle.read();
  bool fsmShift_ = fsmShift.read();
  
  bool TxShiftComplete_tmp = (ctrlD9_ == 1) ? (shiftTxCounter_ == 0xA) : (shiftTxCounter_ == 0x9);
  bool TxWr_tmp = ctrlEn_ & ctrlTxEn_;
  bool Data9_tmp = (ctrlD9_ == 1) ? txParity_ : 0b1;
  bool LoadData_tmp = ctrlShiftTx_ & ~txFifoEmpty_ & fsmIdle_;
  bool ShiftEn_tmp = fsmShift_ & ctrlShiftTx_;
  
  txShiftComplete.write(TxShiftComplete_tmp);
  txWr.write(TxWr_tmp);
  data9.write(Data9_tmp);
  loadData.write(LoadData_tmp);
  shiftEn.write(ShiftEn_tmp);
}

// Initialize value of Registers
void mApbUartTransmitter::InitReset() {
  shiftTxCounter.write(0); //Shift counter
  txShiftReg.write(0x3FF); //Transmit shift register
  state.write(IDLE); //FSM tcreates fsmShift and fsmIdle signals
  txRptr.write(0); //Read pointer
  txWptr.write(0); //Write pointer
}

