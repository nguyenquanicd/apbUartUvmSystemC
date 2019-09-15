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
    bool writeEn = pWrite.read();
    bool regSel  = pSel.read() & pEnable.read();
    bool regWe   = writeEn & regSel & pStrb.read().and_reduce();
    bool regRe  = ~writeEn & regSel;
    //Write register decoder
    switch (pAddr.read().range(4,0)) {
	    case 0x00: 
        conWe = regWe;
        break;
	    case 0x04: 
        seWe  = regWe;
        break;
	    case 0x08: 
        brWe  = regWe;
        break;
	    case 0x0C: 
        dtWe  = regWe;
        break;
      case 0x10: 
        ieWe  = regWe;
        break;
	    default:
        conWe = 0;
        seWe = 0;
        brWe = 0;
        dtWe = 0;
        ieWe = 0;
        break;
	  }
    //
    ctrlTxEn.write(dtWe);
    if (pAddr.read().range(4,0) == 0x0C) {
      ctrlDataRd.write(regRe);
    }
    else {
      ctrlDataRd.write(0);
    }
    //Outputs
    ctrlTxt.write(conReg.read().range(1,0));
    ctrlRxt.write(conReg.read().range(3,2));
    ctrlEnTmp.write(seReg.read()[0]);
    ctrlEn.write(ctrlEnTmp);
    ctrlD9.write(seReg.read()[1]);
    ctrlEp.write(seReg.read()[2]);
    //Interrupt signals
    bool ctrlTIfTmp = txTxe.read() & ieReg.read()[0]; //Transmit Interrupt
    bool ctrlRIfTmp = rxRxf.read() & ieReg.read()[1]; //Receiver Interrupt
    bool ctrlOIfTmp = rxOv.read()  & ieReg.read()[2]; //Overflow Interrupt
    bool ctrlPIfTmp = rxPe.read()  & ieReg.read()[3]; //Parity error Interrup
    bool ctrlFIfTmp = rxFe.read()  & ieReg.read()[4]; //Frame error Interrupt
    ctrlTIf.write(ctrlTIfTmp); //Transmit Interrupt
    ctrlRIf.write(ctrlRIfTmp); //Receiver Interrupt
    ctrlOIf.write(ctrlOIfTmp); //Overflow Interrupt
    ctrlPIf.write(ctrlPIfTmp); //Parity error Interrup
    ctrlFIf.write(ctrlFIfTmp); //Frame error Interrupt
    //Transmit data
    ctrlData.write(pWData.read().range(7,0));
    //Busy status bit
    bool ctrlBusyTmp = txBusy.read() | rxBusy.read();
    //Read data decoder
    switch (pAddr.read().range(4,0)) {
	    case 0x00: 
        pRData.write((sc_uint<28>(0), conReg.read()));
        break;
	    case 0x04: 
        pRData.write((sc_uint<24>(0), ctrlBusyTmp, rxNe.read(), txNf.read(), sc_uint<2>(0), seReg.read()));
        break;
	    case 0x08: 
        pRData.write((sc_uint<24>(0), brReg.read()));
        break;
	    case 0x0C: 
        pRData.write((sc_uint<24>(0), rxData.read()));
        break;
      case 0x10: 
        pRData.write((sc_uint<27>(0), ieReg.read()));
        break;
      case 0x14: 
        pRData.write((sc_uint<27>(0), rxFe.read(), rxPe.read(), rxOv.read(), rxRxf.read(), txTxe.read()));
        break;
      case 0x18: 
        pRData.write((sc_uint<27>(0), ctrlFIfTmp, ctrlPIfTmp, ctrlOIfTmp, ctrlRIfTmp, ctrlTIfTmp));
        break;
	    default:
        pRData.write(0);
        break;
	  }
    //Receiver shift enable
    bool ctrlShiftRxTmp;
    if (rxCounter.read() == brReg.read()) {
      ctrlShiftRxTmp = 1;
    }
    else {
      ctrlShiftRxTmp = 0;
    }
    ctrlShiftRx.write(ctrlShiftRxTmp);
    //Transmit shift enable
    if ((ctrlShiftRxTmp == 1) & (txCounter.read() == 15)) {
      ctrlShiftTx.write(1);
    }
    else {
      ctrlShiftTx.write(0);
    }
    //Pready
    pReady.write(1);
    //Error conditions
    if ((pAddr.read().range(1,0) != 0x0)
        || (pAddr.read().range(15,0) >= 0x18)
        || ((~pStrb.read().and_reduce()) && writeEn && regSel)) {
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
    //Control register
    if (conWe.read()) {
      conReg.write(pWData.read().range(3,0));
    }
    //Status Enable register
    if (seWe.read()) {
      seReg.write(pWData.read().range(2,0));
    }
    //Baud rate register
    if (brWe.read()) {
      brReg.write(pWData.read().range(7,0));
    }
    //Interrupt enable register
    if (ieWe.read()) {
      ieReg.write(pWData.read().range(4,0));
    }
    //Combined Interrupt signal
    #ifdef INTERRUPT_COM
      ctrlIf.write(  ctrlTIf.read() | ctrlRIf.read()
                    | ctrlOIf.read() | ctrlPIf.read()
                    | ctrlFIf.read());
    #endif
    //Receiver shift counter
    if (~ctrlEnTmp.read()) {
      rxCounter.write(0);
    }
    else if (ctrlEnTmp.read() & ctrlShiftRx.read()) {
      rxCounter.write(0);
    }
    else if (ctrlEnTmp.read() & ~ctrlShiftRx.read()) {
      rxCounter.write(rxCounter.read() + 1);
    }
    //Transmit shift counter
    if (~ctrlEnTmp.read()) {
      txCounter.write(0);
    }
    else if (ctrlEnTmp.read() & ctrlShiftRx.read()) {
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