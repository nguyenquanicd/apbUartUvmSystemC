//--------------------------------------
//Project:  The UVM environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Module:   apbUartApbIf
//Function: APB interface and Status/Configuration Registers
//Author:   Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

#include "mApbUartApbIf.h"

// Combination circuits
void mApbUartApbIf::pmCombination() {
    //Detect read/write access
    bool writeEn     = pWrite.read();
    bool regSel      = pSel.read() & pEnable.read();
    bool pStrb_all1  = pStrb.read().and_reduce();
    sc_uint<16> pAddr_lsb  = pAddr.read().range(15,0);
    sc_uint<4> conReg_    = conReg.read();
    sc_uint<3> seReg_ = seReg.read();
    bool ctrlEn_0     = seReg_[0];
    bool ctrlD9_1     = seReg_[1];
    bool ctrlEp_2     = seReg_[2];
    sc_uint<5> ieReg_ = ieReg.read();
    bool txTxe_ = txTxe.read();
    bool rxRxf_ = rxRxf.read();
    bool rxOv_  = rxOv.read();
    bool rxPe_  = rxPe.read(); 
    bool rxFe_  = rxFe.read();
    sc_uint<8> brReg_ = brReg.read();
    bool dtWe_; 
    bool ctrlShiftRxTmp_;
    bool regWe  = writeEn & regSel & pStrb_all1;
    bool regRe  = ~writeEn & regSel;
    //Write register decoder
    switch (pAddr_lsb.range(4,0)) {
	    case 0x00:
        dtWe_ = false;        
        conWe = regWe;
        break;
	    case 0x04:
        dtWe_ = false;
        seWe.write(regWe);
        break;
	    case 0x08: 
        dtWe_ = false;
        brWe.write(regWe);
        break;
	    case 0x0C:
        dtWe_ = false;
        dtWe_ = regWe;
        break;
      case 0x10:
        dtWe_ = false;
        ieWe.write(regWe);
        break;
	    default:
        conWe.write(0);
        seWe.write(0);
        brWe.write(0);
        dtWe_ = 0;
        ieWe.write(0);
      break;
	  }    
    //
    ctrlTxEn.write(dtWe_);
    if (pAddr_lsb.range(4,0) == 0x0C) {
      ctrlDataRd.write(regRe);
    }
    else {
      ctrlDataRd.write(0);
    }
    //Outputs
    ctrlTxt.write(conReg_.range(1,0));
    ctrlRxt.write(conReg_.range(3,2));
    ctrlEnTmp.write(ctrlEn_0);
    ctrlEn.write(ctrlEn_0);
    ctrlD9.write(ctrlD9_1);
    ctrlEp.write(ctrlEp_2);
    //Interrupt signals
    bool ctrlTIfTmp = txTxe_ & ieReg_[0]; //Transmit Interrupt
    bool ctrlRIfTmp = rxRxf_ & ieReg_[1]; //Receiver Interrupt
    bool ctrlOIfTmp = rxOv_  & ieReg_[2]; //Overflow Interrupt
    bool ctrlPIfTmp = rxPe_  & ieReg_[3]; //Parity error Interrup
    bool ctrlFIfTmp = rxFe_  & ieReg_[4]; //Frame error Interrupt
    ctrlTIf.write(txTxe_ & ieReg_[0]); //Transmit Interrupt
    ctrlRIf.write(rxRxf_ & ieReg_[1]); //Receiver Interrupt
    ctrlOIf.write(rxOv_  & ieReg_[2]); //Overflow Interrupt
    ctrlPIf.write(rxPe_  & ieReg_[3]); //Parity error Interrup
    ctrlFIf.write(rxFe_  & ieReg_[4]); //Frame error Interrupt
    //Transmit data
    ctrlData.write(pWData.read().range(7,0));
    //Busy status bit
    bool ctrlBusyTmp = txBusy.read() | rxBusy.read();
    //Read data decoder
    switch (pAddr_lsb.range(4,0)) {
	    case 0x00: 
        pRData.write((sc_uint<28>(0), conReg_));
        break;
	    case 0x04: 
        pRData.write((sc_uint<24>(0), ctrlBusyTmp, rxNe.read(), txNf.read(), sc_uint<2>(0), seReg_));
        break;
	    case 0x08: 
        pRData.write((sc_uint<24>(0), brReg_));
        break;
	    case 0x0C: 
        pRData.write((sc_uint<24>(0), rxData.read()));
        break;
      case 0x10: 
        pRData.write((sc_uint<27>(0), ieReg_));
        break;
      case 0x14: 
        pRData.write((sc_uint<27>(0), rxFe_, rxPe_, rxOv_, rxRxf_, txTxe_));
        break;
      case 0x18: 
        pRData.write((sc_uint<27>(0), ctrlFIfTmp, ctrlPIfTmp, ctrlOIfTmp, ctrlRIfTmp, ctrlTIfTmp));
        break;
	    default:
        pRData.write(0);
        break;
	  }
    //Receiver shift enable
    if (rxCounter.read() == brReg_) {
      ctrlShiftRxTmp.write(1);
      ctrlShiftRxTmp_ = 1;
    }
    else {
      ctrlShiftRxTmp.write(0);
      ctrlShiftRxTmp_ = 0;
    }
    ctrlShiftRx.write(ctrlShiftRxTmp_);
    //Transmit shift enable
    if ((ctrlShiftRxTmp_ == 1) & (txCounter.read() == 15)) {
      ctrlShiftTx.write(1);
    }
    else {
      ctrlShiftTx.write(0);
    }
    //Pready
    pReady.write(1);
    //Error conditions
    if ((pAddr_lsb.range(1,0) != 0x0)
        || (pAddr_lsb >= 0x18)
        || ((~pStrb_all1) && writeEn && regSel)) {
      errCondition.write(1);
    }
    else {
      errCondition.write(0);
    }
}
// Configuration registers
void mApbUartApbIf::pcSequence() {
  initReset();
  wait();
  while (1) {
    sc_uint <8> pWData_ = pWData.read();
    bool ctrlEnTmp_   = ctrlEnTmp.read();
    bool ctrlShiftRx_ = ctrlShiftRxTmp.read();
    //Control register
    if (conWe.read()) {
      conReg.write(pWData_.range(3,0));
    }
    //Status Enable register
    if (seWe.read()) {
      seReg.write(pWData_.range(2,0));
    }
    //Baud rate register
    if (brWe.read()) {
      brReg.write(pWData_);
    }
    //Interrupt enable register
    if (ieWe.read()) {
      ieReg.write(pWData_.range(4,0));
    }
    //Combined Interrupt signal
    #ifdef INTERRUPT_COM
      ctrlIf.write(  ctrlTIf.read() | ctrlRIf.read()
                    | ctrlOIf.read() | ctrlPIf.read()
                    | ctrlFIf.read());
    #endif
    //Receiver shift counter
    if (!ctrlEnTmp_) {
      rxCounter.write(0);
    }
    else if ((ctrlEnTmp_ & ctrlShiftRx_)) {
      rxCounter.write(0);
    }
    else if ((ctrlEnTmp_ & !ctrlShiftRx_)) {
      rxCounter.write(rxCounter.read() + 1);
    }
    //Transmit shift counter
    if (!ctrlEnTmp_) {
      txCounter.write(0);
    }
    else if ((ctrlEnTmp_ & ctrlShiftRx_)) {
      txCounter.write(txCounter.read() + 1);
    }
    //Pslv error signal
    pSlvErr.write(pSel.read() & errCondition.read());
    //
    wait();
  }
}

// Initial/Reset value of registers
void mApbUartApbIf::initReset() {
  conReg.write(0); //Control register
  seReg.write(0); //Status enable register
  brReg.write(0); //Baud rate register
  ieReg.write(0); //Interrupt enable register
  #ifdef INTERRUPT_COM
    ctrlIf.write(0); //Interrupt bit
  #endif
  rxCounter.write(0); //Receiver shift counter
  txCounter.write(0); //Transmit shift counter
  pSlvErr.write(0); //Pslv error signal
}