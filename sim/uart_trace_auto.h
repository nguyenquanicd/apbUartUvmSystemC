//--------------------------------------
//Project:  Simple CPU
//Module:   SPCU Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

// START
sc_trace_file *uart_waveform =  sc_create_vcd_trace_file("uart_waveform");
  if(uart_waveform==NULL) cout<<"Cannot create the waveform file"<< endl;
  else cout << "Create the waveform file - " << uart_waveform << endl;

//dut_top --- list of ports & signals
sc_trace(uart_waveform, dut_top->pclk_0, "pclk_0_dut_top");
sc_trace(uart_waveform, dut_top->preset_n_0, "preset_n_0_dut_top");
sc_trace(uart_waveform, dut_top->pwrite_0, "pwrite_0_dut_top");
sc_trace(uart_waveform, dut_top->psel_0, "psel_0_dut_top");
sc_trace(uart_waveform, dut_top->penable_0, "penable_0_dut_top");
sc_trace(uart_waveform, dut_top->paddr_0, "paddr_0_dut_top");
sc_trace(uart_waveform, dut_top->pwdata_0, "pwdata_0_dut_top");
sc_trace(uart_waveform, dut_top->pstrb_0, "pstrb_0_dut_top");
sc_trace(uart_waveform, dut_top->prdata_0, "prdata_0_dut_top");
sc_trace(uart_waveform, dut_top->pready_0, "pready_0_dut_top");
sc_trace(uart_waveform, dut_top->pslverr_0, "pslverr_0_dut_top");
#ifdefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->ctrl_if_0, "ctrl_if_0_dut_top");
#endif
#ifndefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->ctrl_fif_0, "ctrl_fif_0_dut_top");
sc_trace(uart_waveform, dut_top->ctrl_oif_0, "ctrl_oif_0_dut_top");
sc_trace(uart_waveform, dut_top->ctrl_pif_0, "ctrl_pif_0_dut_top");
sc_trace(uart_waveform, dut_top->ctrl_rif_0, "ctrl_rif_0_dut_top");
sc_trace(uart_waveform, dut_top->ctrl_tif_0, "ctrl_tif_0_dut_top");
#endif
sc_trace(uart_waveform, dut_top->pclk_1, "pclk_1_dut_top");
sc_trace(uart_waveform, dut_top->preset_n_1, "preset_n_1_dut_top");
sc_trace(uart_waveform, dut_top->pwrite_1, "pwrite_1_dut_top");
sc_trace(uart_waveform, dut_top->psel_1, "psel_1_dut_top");
sc_trace(uart_waveform, dut_top->penable_1, "penable_1_dut_top");
sc_trace(uart_waveform, dut_top->paddr_1, "paddr_1_dut_top");
sc_trace(uart_waveform, dut_top->pwdata_1, "pwdata_1_dut_top");
sc_trace(uart_waveform, dut_top->pstrb_1, "pstrb_1_dut_top");
sc_trace(uart_waveform, dut_top->prdata_1, "prdata_1_dut_top");
sc_trace(uart_waveform, dut_top->pready_1, "pready_1_dut_top");
sc_trace(uart_waveform, dut_top->pslverr_1, "pslverr_1_dut_top");
#ifdefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->ctrl_if_1, "ctrl_if_1_dut_top");
#else
sc_trace(uart_waveform, dut_top->ctrl_fif_1, "ctrl_fif_1_dut_top");
sc_trace(uart_waveform, dut_top->ctrl_oif_1, "ctrl_oif_1_dut_top");
sc_trace(uart_waveform, dut_top->ctrl_pif_1, "ctrl_pif_1_dut_top");
sc_trace(uart_waveform, dut_top->ctrl_rif_1, "ctrl_rif_1_dut_top");
sc_trace(uart_waveform, dut_top->ctrl_tif_1, "ctrl_tif_1_dut_top");
#endif
sc_trace(uart_waveform, dut_top->uart_0to1, "uart_0to1_dut_top");
sc_trace(uart_waveform, dut_top->uart_1to0, "uart_1to0_dut_top");

//InstApbUartTop_0 --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pClk, "pClk_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pResetN, "pResetN_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pWrite, "pWrite_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pSel, "pSel_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pEnable, "pEnable_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pAddr, "pAddr_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pWData, "pWData_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pStrb, "pStrb_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pRData, "pRData_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pReady, "pReady_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pSlvErr, "pSlvErr_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.uartRx, "uartRx_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.uartTx, "uartTx_InstApbUartTop_0");
#ifdefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlIf, "ctrlIf_InstApbUartTop_0");
#endif
#ifndefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlTIf, "ctrlTIf_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlRIf, "ctrlRIf_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlOIf, "ctrlOIf_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlPIf, "ctrlPIf_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlFIf, "ctrlFIf_InstApbUartTop_0");
#else
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlTIf, "ctrlTIf_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlRIf, "ctrlRIf_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlOIf, "ctrlOIf_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlPIf, "ctrlPIf_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlFIf, "ctrlFIf_InstApbUartTop_0");
#endif
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlD9, "ctrlD9_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlData, "ctrlData_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlDataRd, "ctrlDataRd_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlEn, "ctrlEn_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlEp, "ctrlEp_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlRxt, "ctrlRxt_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlShiftRx, "ctrlShiftRx_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlShiftTx, "ctrlShiftTx_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlTxEn, "ctrlTxEn_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlTxt, "ctrlTxt_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxBusy, "rxBusy_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxData, "rxData_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxFe, "rxFe_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxNe, "rxNe_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxOv, "rxOv_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxPe, "rxPe_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxRxf, "rxRxf_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.txBusy, "txBusy_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.txNf, "txNf_InstApbUartTop_0");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.txTxe, "txTxe_InstApbUartTop_0");

//InstApbUartApbIf --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pClk, "pClk_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pResetN, "pResetN_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pWrite, "pWrite_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pSel, "pSel_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pEnable, "pEnable_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pAddr, "pAddr_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pWData, "pWData_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pStrb, "pStrb_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txNf, "txNf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txBusy, "txBusy_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txTxe, "txTxe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxNe, "rxNe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxBusy, "rxBusy_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxRxf, "rxRxf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxOv, "rxOv_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxPe, "rxPe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxFe, "rxFe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxData, "rxData_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlEn, "ctrlEn_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlTxEn, "ctrlTxEn_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlD9, "ctrlD9_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlEp, "ctrlEp_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlShiftRx, "ctrlShiftRx_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlShiftTx, "ctrlShiftTx_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlTxt, "ctrlTxt_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlRxt, "ctrlRxt_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlDataRd, "ctrlDataRd_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlData, "ctrlData_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pRData, "pRData_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pReady, "pReady_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pSlvErr, "pSlvErr_InstApbUartApbIf");
#ifdefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlIf, "ctrlIf_InstApbUartApbIf");
#endif
#ifndefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlTIf, "ctrlTIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlRIf, "ctrlRIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlOIf, "ctrlOIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlPIf, "ctrlPIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlFIf, "ctrlFIf_InstApbUartApbIf");
#else
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlTIf, "ctrlTIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlRIf, "ctrlRIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlOIf, "ctrlOIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlPIf, "ctrlPIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlFIf, "ctrlFIf_InstApbUartApbIf");
#endif
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlEnTmp, "ctrlEnTmp_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.conWe, "conWe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.seWe, "seWe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.brWe, "brWe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ieWe, "ieWe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.conReg, "conReg_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.seReg, "seReg_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.brReg, "brReg_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ieReg, "ieReg_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxCounter, "rxCounter_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txCounter, "txCounter_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.errCondition, "errCondition_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlShiftRxTmp, "ctrlShiftRxTmp_InstApbUartApbIf");

//InstApbUartReciever --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.pClk, "pClk_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.pResetN, "pResetN_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlEn, "ctrlEn_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlD9, "ctrlD9_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlEp, "ctrlEp_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlShiftRx, "ctrlShiftRx_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlDataRd, "ctrlDataRd_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.uartRx, "uartRx_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlRxt, "ctrlRxt_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxNe, "rxNe_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxBusy, "rxBusy_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxRxf, "rxRxf_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxOv, "rxOv_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxPe, "rxPe_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFe, "rxFe_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxData, "rxData_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.setSampleCounter, "setSampleCounter_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoOv, "rxFifoOv_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.fsmActive, "fsmActive_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.fsmStart, "fsmStart_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.fsmShift, "fsmShift_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxRxfReg, "rxRxfReg_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.frameError, "frameError_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.parityError, "parityError_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.uartSync, "uartSync_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxShiftEn, "rxShiftEn_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxComplete, "rxComplete_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.wrRxFifo, "wrRxFifo_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rdRxFifo, "rdRxFifo_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoEmplty, "rxFifoEmplty_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoFull, "rxFifoFull_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.lsbRxfifoEqual, "lsbRxfifoEqual_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.msbRxfifoDiff, "msbRxfifoDiff_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoWe, "rxFifoWe_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoRe, "rxFifoRe_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.sampleCounter, "sampleCounter_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxCounterBit, "rxCounterBit_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ffSync, "ffSync_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxNextState, "rxNextState_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxCurrentState, "rxCurrentState_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxWptr, "rxWptr_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxRptr, "rxRptr_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.dataIn, "dataIn_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoPtrCompare, "rxFifoPtrCompare_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxShiftReg, "rxShiftReg_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoDataOut, "rxFifoDataOut_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.dataInRxFifo, "dataInRxFifo_InstApbUartReciever");
for (int i=0; i<16; i++) {
  char str[4];
  sprintf(str, "(%0d)",i);
  sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxMemArray[i], "rxMemArray_InstApbUartReciever_" + string(str));
}

//InstApbUartTransmitter --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.pClk, "pClk_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.pResetN, "pResetN_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlD9, "ctrlD9_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlEn, "ctrlEn_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlEp, "ctrlEp_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlShiftTx, "ctrlShiftTx_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlTxEn, "ctrlTxEn_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlTxt, "ctrlTxt_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlData, "ctrlData_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txBusy, "txBusy_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txNf, "txNf_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txTxe, "txTxe_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.uartTx, "uartTx_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.data9, "data9_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.loadData, "loadData_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.shiftEn, "shiftEn_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txFifoRe, "txFifoRe_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txFifoWe, "txFifoWe_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txShiftComplete, "txShiftComplete_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txFifoOut, "txFifoOut_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.state, "state_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.shiftTxCounter, "shiftTxCounter_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txRptr, "txRptr_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txWptr, "txWptr_InstApbUartTransmitter");
for (int i=0; i<16; i++) {
  char str[4];
  sprintf(str, "(%0d)",i);
  sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txMemArray[i], "txMemArray_InstApbUartTransmitter_" + string(str));
}
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txShiftReg, "txShiftReg_InstApbUartTransmitter");

//InstApbUartTop_1 --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pClk, "pClk_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pResetN, "pResetN_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pWrite, "pWrite_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pSel, "pSel_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pEnable, "pEnable_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pAddr, "pAddr_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pWData, "pWData_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pStrb, "pStrb_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pRData, "pRData_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pReady, "pReady_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pSlvErr, "pSlvErr_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.uartRx, "uartRx_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.uartTx, "uartTx_InstApbUartTop_1");
#ifdefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlIf, "ctrlIf_InstApbUartTop_1");
#endif
#ifndefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlTIf, "ctrlTIf_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlRIf, "ctrlRIf_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlOIf, "ctrlOIf_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlPIf, "ctrlPIf_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlFIf, "ctrlFIf_InstApbUartTop_1");
#else
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlTIf, "ctrlTIf_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlRIf, "ctrlRIf_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlOIf, "ctrlOIf_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlPIf, "ctrlPIf_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlFIf, "ctrlFIf_InstApbUartTop_1");
#endif
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlD9, "ctrlD9_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlData, "ctrlData_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlDataRd, "ctrlDataRd_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlEn, "ctrlEn_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlEp, "ctrlEp_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlRxt, "ctrlRxt_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlShiftRx, "ctrlShiftRx_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlShiftTx, "ctrlShiftTx_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlTxEn, "ctrlTxEn_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlTxt, "ctrlTxt_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxBusy, "rxBusy_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxData, "rxData_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxFe, "rxFe_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxNe, "rxNe_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxOv, "rxOv_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxPe, "rxPe_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxRxf, "rxRxf_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.txBusy, "txBusy_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.txNf, "txNf_InstApbUartTop_1");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.txTxe, "txTxe_InstApbUartTop_1");

//InstApbUartApbIf --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pClk, "pClk_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pResetN, "pResetN_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pWrite, "pWrite_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pSel, "pSel_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pEnable, "pEnable_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pAddr, "pAddr_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pWData, "pWData_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pStrb, "pStrb_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.txNf, "txNf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.txBusy, "txBusy_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.txTxe, "txTxe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxNe, "rxNe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxBusy, "rxBusy_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxRxf, "rxRxf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxOv, "rxOv_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxPe, "rxPe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxFe, "rxFe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxData, "rxData_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlEn, "ctrlEn_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlTxEn, "ctrlTxEn_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlD9, "ctrlD9_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlEp, "ctrlEp_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlShiftRx, "ctrlShiftRx_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlShiftTx, "ctrlShiftTx_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlTxt, "ctrlTxt_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlRxt, "ctrlRxt_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlDataRd, "ctrlDataRd_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlData, "ctrlData_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pRData, "pRData_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pReady, "pReady_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pSlvErr, "pSlvErr_InstApbUartApbIf");
#ifdefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlIf, "ctrlIf_InstApbUartApbIf");
#endif
#ifndefINTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlTIf, "ctrlTIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlRIf, "ctrlRIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlOIf, "ctrlOIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlPIf, "ctrlPIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlFIf, "ctrlFIf_InstApbUartApbIf");
#else
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlTIf, "ctrlTIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlRIf, "ctrlRIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlOIf, "ctrlOIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlPIf, "ctrlPIf_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlFIf, "ctrlFIf_InstApbUartApbIf");
#endif
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlEnTmp, "ctrlEnTmp_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.conWe, "conWe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.seWe, "seWe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.brWe, "brWe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ieWe, "ieWe_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.conReg, "conReg_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.seReg, "seReg_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.brReg, "brReg_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ieReg, "ieReg_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxCounter, "rxCounter_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.txCounter, "txCounter_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.errCondition, "errCondition_InstApbUartApbIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlShiftRxTmp, "ctrlShiftRxTmp_InstApbUartApbIf");

//InstApbUartReciever --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.pClk, "pClk_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.pResetN, "pResetN_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlEn, "ctrlEn_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlD9, "ctrlD9_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlEp, "ctrlEp_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlShiftRx, "ctrlShiftRx_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlDataRd, "ctrlDataRd_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.uartRx, "uartRx_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlRxt, "ctrlRxt_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxNe, "rxNe_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxBusy, "rxBusy_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxRxf, "rxRxf_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxOv, "rxOv_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxPe, "rxPe_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFe, "rxFe_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxData, "rxData_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.setSampleCounter, "setSampleCounter_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoOv, "rxFifoOv_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.fsmActive, "fsmActive_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.fsmStart, "fsmStart_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.fsmShift, "fsmShift_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxRxfReg, "rxRxfReg_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.frameError, "frameError_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.parityError, "parityError_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.uartSync, "uartSync_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxShiftEn, "rxShiftEn_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxComplete, "rxComplete_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.wrRxFifo, "wrRxFifo_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rdRxFifo, "rdRxFifo_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoEmplty, "rxFifoEmplty_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoFull, "rxFifoFull_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.lsbRxfifoEqual, "lsbRxfifoEqual_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.msbRxfifoDiff, "msbRxfifoDiff_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoWe, "rxFifoWe_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoRe, "rxFifoRe_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.sampleCounter, "sampleCounter_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxCounterBit, "rxCounterBit_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ffSync, "ffSync_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxNextState, "rxNextState_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxCurrentState, "rxCurrentState_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxWptr, "rxWptr_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxRptr, "rxRptr_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.dataIn, "dataIn_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoPtrCompare, "rxFifoPtrCompare_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxShiftReg, "rxShiftReg_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoDataOut, "rxFifoDataOut_InstApbUartReciever");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.dataInRxFifo, "dataInRxFifo_InstApbUartReciever");
for (int i=0; i<16; i++) {
  char str[4];
  sprintf(str, "(%0d)",i);
  sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxMemArray[i], "rxMemArray_InstApbUartReciever_" + string(str));
}

//InstApbUartTransmitter --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.pClk, "pClk_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.pResetN, "pResetN_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlD9, "ctrlD9_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlEn, "ctrlEn_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlEp, "ctrlEp_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlShiftTx, "ctrlShiftTx_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlTxEn, "ctrlTxEn_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlTxt, "ctrlTxt_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlData, "ctrlData_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txBusy, "txBusy_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txNf, "txNf_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txTxe, "txTxe_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.uartTx, "uartTx_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.data9, "data9_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.loadData, "loadData_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.shiftEn, "shiftEn_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txFifoRe, "txFifoRe_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txFifoWe, "txFifoWe_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txShiftComplete, "txShiftComplete_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txFifoOut, "txFifoOut_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.state, "state_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.shiftTxCounter, "shiftTxCounter_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txRptr, "txRptr_InstApbUartTransmitter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txWptr, "txWptr_InstApbUartTransmitter");
for (int i=0; i<16; i++) {
  char str[4];
  sprintf(str, "(%0d)",i);
  sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txMemArray[i], "txMemArray_InstApbUartTransmitter_" + string(str));
}
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txShiftReg, "txShiftReg_InstApbUartTransmitter");

// END
