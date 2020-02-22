//--------------------------------------
//Project:  Simple CPU
//Module:   SPCU Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
//START
sc_trace_file *uart_waveform =  sc_create_vcd_trace_file("uart_waveform");
  if(uart_waveform==NULL) cout<<"Cannot create the waveform file"<< endl;
  else cout << "Create the waveform file - " << uart_waveform << endl;
//
//RX
//
//Ports
//APB I/F TX
sc_trace(uart_waveform, dut_top->pclk_0,"pClk_Tx");
sc_trace(uart_waveform, dut_top->preset_n_0,"pResetN_Tx");
sc_trace(uart_waveform, dut_top->pwrite_0,"pWrite_Tx");
sc_trace(uart_waveform, dut_top->psel_0,"pSel_Tx");
sc_trace(uart_waveform, dut_top->penable_0,"pEnable_Tx");
sc_trace(uart_waveform, dut_top->paddr_0,"pAddr_Tx");
sc_trace(uart_waveform, dut_top->pwdata_0,"pWData_Tx");
sc_trace(uart_waveform, dut_top->pstrb_0,"pStrb_Tx");
sc_trace(uart_waveform, dut_top->prdata_0,"pRData_Tx");
sc_trace(uart_waveform, dut_top->pready_0,"pReady_Tx");
sc_trace(uart_waveform, dut_top->pslverr_0,"pSlvErr_Tx");
  //Internal connection
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlD9,"ctrlD9_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlData,"ctrlData_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlDataRd,"ctrlDataRd_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlEn,"ctrlEn_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlEp,"ctrlEp_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlRxt,"ctrlRxt_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlShiftRx,"ctrlShiftRx_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlShiftTx,"ctrlShiftTx_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlTxEn,"ctrlTxEn_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlTxt,"ctrlTxt_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxBusy,"rxBusy_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxData,"rxData_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxFe,"rxFe_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxNe,"rxNe_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxOv,"rxOv_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxPe,"rxPe_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxRxf,"rxRxf_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.txBusy,"txBusy_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.txNf,"txNf_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.txTxe,"txTxe_Tx");
// IF
//sc_trace(uart_waveform, dut_top->InstApbUartApbIf.errCondition,"InstApbUartApbIf.errCondition_Tx");

sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pClk,"pClkif_Tx");       
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pResetN,"pResetNif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pWrite,"pWriteif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pSel,"pSelif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pEnable,"pEnableif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pAddr,"pAddrif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pWData,"pWDataif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pStrb,"pStrbif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txNf,"txNfif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txBusy,"txBusyif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txTxe,"txTxeif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxNe,"rxNeif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxBusy,"rxBusyif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxRxf,"rxRxfif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxOv,"rxOvif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxPe,"rxPeif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxFe,"rxFeif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxData,"rxDataif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlEn,"ctrlEnif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlTxEn,"ctrlTxEnif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlD9,"ctrlD9if_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlEp,"ctrlEpif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlShiftRx,"ctrlShiftRxif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlShiftTx,"ctrlShiftTxif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlTxt,"ctrlTxtif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlRxt,"ctrlRxtif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlDataRd,"ctrlDataRdif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlData,"ctrlDataif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pRData,"pRDataif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pReady,"pReadyif_Tx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pSlvErr,"pSlvErrif_Tx");

//Transmitter
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.uartTx,"InstApbUartTransmitter.uartTx_Tx");
//sc_trace(uart_waveform, dut_top->InstApbUartTransmitter.txShiftReg,"InstApbUartTransmitter.txShiftReg_Tx");
//sc_trace(uart_waveform, dut_top->InstApbUartTransmitter.loadData,"InstApbUartTransmitter.loadData_Tx");
//sc_trace(uart_waveform, dut_top->InstApbUartTransmitter.shiftEn,"InstApbUartTransmitter.shiftEn_Tx");

//sc_trace(uart_waveform, dut_top.uart_top_inst_tx->InstApbUartTransmitter.txMemArray[],"InstApbUartTransmitter.txMemArray_Tx");
//sc_trace(uart_waveform, dut_top->InstApbUartTransmitter.txWptr,"InstApbUartTransmitter.txWptr_Tx");
//sc_trace(uart_waveform, dut_top->InstApbUartTransmitter.txRptr,"InstApbUartTransmitter.txRptr_Tx");
// Interrupt
#ifdef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->ctrl_if_0,"ctrlTIf_Tx");
#else
sc_trace(uart_waveform, dut_top->ctrl_fif_0,"ctrlTIf_Tx");
sc_trace(uart_waveform, dut_top->ctrl_oif_0,"ctrlRIf_Tx");
sc_trace(uart_waveform, dut_top->ctrl_pif_0,"ctrlOIf_Tx");
sc_trace(uart_waveform, dut_top->ctrl_rif_0,"ctrlPIf_Tx");
sc_trace(uart_waveform, dut_top->ctrl_tif_0,"ctrlFIf_Tx");
#endif



//
//Ports
//APB I/F RX
sc_trace(uart_waveform, dut_top->pclk_1,"pClk_Rx");
sc_trace(uart_waveform, dut_top->preset_n_1,"pResetN_Rx");
sc_trace(uart_waveform, dut_top->pwrite_1,"pWrite_Rx");
sc_trace(uart_waveform, dut_top->psel_1,"pSel_Rx");
sc_trace(uart_waveform, dut_top->penable_1,"pEnable_Rx");
sc_trace(uart_waveform, dut_top->paddr_1,"pAddr_Rx");
sc_trace(uart_waveform, dut_top->pwdata_1,"pWData_Rx");
sc_trace(uart_waveform, dut_top->pstrb_1,"pStrb_Rx");
sc_trace(uart_waveform, dut_top->prdata_1,"pRData_Rx");
sc_trace(uart_waveform, dut_top->pready_1,"pReady_Rx");
sc_trace(uart_waveform, dut_top->pslverr_1,"pSlvErr_Rx");
  //Internal connection
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlD9,"ctrlD9_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlData,"ctrlData_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlDataRd,"ctrlDataRd_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlEn,"ctrlEn_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlEp,"ctrlEp_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlRxt,"ctrlRxt_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlShiftRx,"ctrlShiftRx_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlShiftTx,"ctrlShiftTx_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlTxEn,"ctrlTxEn_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlTxt,"ctrlTxt_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxBusy,"rxBusy_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxData,"rxData_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxFe,"rxFe_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxNe,"rxNe_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxOv,"rxOv_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxPe,"rxPe_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxRxf,"rxRxf_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.txBusy,"txBusy_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.txNf,"txNf_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.txTxe,"txTxe_Rx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.uartRx,"InstApbUartTransmitter.uartRx_Rx");
//sc_trace(uart_waveform, dut_top->InstApbUartApbIf.errCondition,"errCondition_Rx");
    // Interrupt    
#ifdef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->ctrl_if_1,"ctrlTIf_Rx");
#else
sc_trace(uart_waveform, dut_top->ctrl_fif_1,"ctrlTIf_Rx");
sc_trace(uart_waveform, dut_top->ctrl_oif_1,"ctrlRIf_Rx");
sc_trace(uart_waveform, dut_top->ctrl_pif_1,"ctrlOIf_Rx");
sc_trace(uart_waveform, dut_top->ctrl_rif_1,"ctrlPIf_Rx");
sc_trace(uart_waveform, dut_top->ctrl_tif_1,"ctrlFIf_Rx");
#endif

//END