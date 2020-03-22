//--------------------------------------
//Project:  Simple CPU
//Module:   SPCU Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
//START
sc_trace_file *uart_waveform =  sc_create_vcd_trace_file("uart_waveform");
  if(uart_waveform==NULL) cout<<"1. Cannot create the waveform file"<< endl;
  else cout << "2. Create the waveform file - " << uart_waveform << endl;
//
//RX
//
//Ports
//APB I/F TX
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pClk,"pClk_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pResetN,"pResetN_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pWrite,"pWrite_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pSel,"pSel_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pEnable,"pEnable_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pAddr,"pAddr_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pWData,"pWData_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pStrb,"pStrb_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pRData,"pRData_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pReady,"pReady_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->pSlvErr,"pSlvErr_Tx");
  //Internal connection
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlD9,"ctrlD9_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlData,"ctrlData_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlDataRd,"ctrlDataRd_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlEn,"ctrlEn_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlEp,"ctrlEp_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlRxt,"ctrlRxt_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlShiftRx,"ctrlShiftRx_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlShiftTx,"ctrlShiftTx_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlTxEn,"ctrlTxEn_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlTxt,"ctrlTxt_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->rxBusy,"rxBusy_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->rxData,"rxData_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->rxFe,"rxFe_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->rxNe,"rxNe_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->rxOv,"rxOv_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->rxPe,"rxPe_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->rxRxf,"rxRxf_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->txBusy,"txBusy_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->txNf,"txNf_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->txTxe,"txTxe_Tx");
// IF
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->InstApbUartApbIf.errCondition,"InstApbUartApbIf.errCondition_Tx");

//Transmitter
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->InstApbUartTransmitter.uartTx,"InstApbUartTransmitter.uartTx_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->InstApbUartTransmitter.txShiftReg,"InstApbUartTransmitter.txShiftReg_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->InstApbUartTransmitter.loadData,"InstApbUartTransmitter.loadData_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->InstApbUartTransmitter.shiftEn,"InstApbUartTransmitter.shiftEn_Tx");

//sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->InstApbUartTransmitter.txMemArray[],"InstApbUartTransmitter.txMemArray_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->InstApbUartTransmitter.txWptr,"InstApbUartTransmitter.txWptr_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->InstApbUartTransmitter.txRptr,"InstApbUartTransmitter.txRptr_Tx");
// Interrupt
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlTIf,"ctrlTIf_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlRIf,"ctrlRIf_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlOIf,"ctrlOIf_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlPIf,"ctrlPIf_Tx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->ctrlFIf,"ctrlFIf_Tx");




//
//Ports
//APB I/F RX
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pClk,"pClk_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pResetN,"pResetN_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pWrite,"pWrite_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pSel,"pSel_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pEnable,"pEnable_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pAddr,"pAddr_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pWData,"pWData_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pStrb,"pStrb_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pRData,"pRData_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pReady,"pReady_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->pSlvErr,"pSlvErr_Rx");
  //Internal connection
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlD9,"ctrlD9_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlData,"ctrlData_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlDataRd,"ctrlDataRd_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlEn,"ctrlEn_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlEp,"ctrlEp_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlRxt,"ctrlRxt_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlShiftRx,"ctrlShiftRx_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlShiftTx,"ctrlShiftTx_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlTxEn,"ctrlTxEn_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlTxt,"ctrlTxt_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->rxBusy,"rxBusy_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->rxData,"rxData_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->rxFe,"rxFe_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->rxNe,"rxNe_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->rxOv,"rxOv_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->rxPe,"rxPe_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->rxRxf,"rxRxf_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->txBusy,"txBusy_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->txNf,"txNf_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->txTxe,"txTxe_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_tx->InstApbUartApbIf.errCondition,"errCondition_Rx");
    // Interrupt    
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlTIf,"ctrlTIf_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlRIf,"ctrlRIf_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlOIf,"ctrlOIf_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlPIf,"ctrlPIf_Rx");
sc_trace(uart_waveform, uart_env_inst.uart_top_inst_rx->ctrlFIf,"ctrlFIf_Rx");

//END