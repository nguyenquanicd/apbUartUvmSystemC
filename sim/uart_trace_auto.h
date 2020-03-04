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
sc_trace(uart_waveform, dut_top->pclk_0, "dut_top.pclk_0");
sc_trace(uart_waveform, dut_top->preset_n_0, "dut_top.preset_n_0");
sc_trace(uart_waveform, dut_top->pwrite_0, "dut_top.pwrite_0");
sc_trace(uart_waveform, dut_top->psel_0, "dut_top.psel_0");
sc_trace(uart_waveform, dut_top->penable_0, "dut_top.penable_0");
sc_trace(uart_waveform, dut_top->paddr_0, "dut_top.paddr_0");
sc_trace(uart_waveform, dut_top->pwdata_0, "dut_top.pwdata_0");
sc_trace(uart_waveform, dut_top->pstrb_0, "dut_top.pstrb_0");
sc_trace(uart_waveform, dut_top->prdata_0, "dut_top.prdata_0");
sc_trace(uart_waveform, dut_top->pready_0, "dut_top.pready_0");
sc_trace(uart_waveform, dut_top->pslverr_0, "dut_top.pslverr_0");
#ifdef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->ctrl_if_0, "dut_top.ctrl_if_0");
#endif
#ifndef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->ctrl_fif_0, "dut_top.ctrl_fif_0");
sc_trace(uart_waveform, dut_top->ctrl_oif_0, "dut_top.ctrl_oif_0");
sc_trace(uart_waveform, dut_top->ctrl_pif_0, "dut_top.ctrl_pif_0");
sc_trace(uart_waveform, dut_top->ctrl_rif_0, "dut_top.ctrl_rif_0");
sc_trace(uart_waveform, dut_top->ctrl_tif_0, "dut_top.ctrl_tif_0");
#endif
sc_trace(uart_waveform, dut_top->pclk_1, "dut_top.pclk_1");
sc_trace(uart_waveform, dut_top->preset_n_1, "dut_top.preset_n_1");
sc_trace(uart_waveform, dut_top->pwrite_1, "dut_top.pwrite_1");
sc_trace(uart_waveform, dut_top->psel_1, "dut_top.psel_1");
sc_trace(uart_waveform, dut_top->penable_1, "dut_top.penable_1");
sc_trace(uart_waveform, dut_top->paddr_1, "dut_top.paddr_1");
sc_trace(uart_waveform, dut_top->pwdata_1, "dut_top.pwdata_1");
sc_trace(uart_waveform, dut_top->pstrb_1, "dut_top.pstrb_1");
sc_trace(uart_waveform, dut_top->prdata_1, "dut_top.prdata_1");
sc_trace(uart_waveform, dut_top->pready_1, "dut_top.pready_1");
sc_trace(uart_waveform, dut_top->pslverr_1, "dut_top.pslverr_1");
#ifdef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->ctrl_if_1, "dut_top.ctrl_if_1");
#else
sc_trace(uart_waveform, dut_top->ctrl_fif_1, "dut_top.ctrl_fif_1");
sc_trace(uart_waveform, dut_top->ctrl_oif_1, "dut_top.ctrl_oif_1");
sc_trace(uart_waveform, dut_top->ctrl_pif_1, "dut_top.ctrl_pif_1");
sc_trace(uart_waveform, dut_top->ctrl_rif_1, "dut_top.ctrl_rif_1");
sc_trace(uart_waveform, dut_top->ctrl_tif_1, "dut_top.ctrl_tif_1");
#endif
sc_trace(uart_waveform, dut_top->uart_0to1, "dut_top.uart_0to1");
sc_trace(uart_waveform, dut_top->uart_1to0, "dut_top.uart_1to0");

//InstApbUartTop_0 --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pClk, "dut_top.InstApbUartTop_0.pClk");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pResetN, "dut_top.InstApbUartTop_0.pResetN");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pWrite, "dut_top.InstApbUartTop_0.pWrite");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pSel, "dut_top.InstApbUartTop_0.pSel");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pEnable, "dut_top.InstApbUartTop_0.pEnable");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pAddr, "dut_top.InstApbUartTop_0.pAddr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pWData, "dut_top.InstApbUartTop_0.pWData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pStrb, "dut_top.InstApbUartTop_0.pStrb");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pRData, "dut_top.InstApbUartTop_0.pRData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pReady, "dut_top.InstApbUartTop_0.pReady");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.pSlvErr, "dut_top.InstApbUartTop_0.pSlvErr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.uartRx, "dut_top.InstApbUartTop_0.uartRx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.uartTx, "dut_top.InstApbUartTop_0.uartTx");
#ifdef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlIf, "dut_top.InstApbUartTop_0.ctrlIf");
#endif
#ifndef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlTIf, "dut_top.InstApbUartTop_0.ctrlTIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlRIf, "dut_top.InstApbUartTop_0.ctrlRIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlOIf, "dut_top.InstApbUartTop_0.ctrlOIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlPIf, "dut_top.InstApbUartTop_0.ctrlPIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlFIf, "dut_top.InstApbUartTop_0.ctrlFIf");
#else
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlTIf, "dut_top.InstApbUartTop_0.ctrlTIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlRIf, "dut_top.InstApbUartTop_0.ctrlRIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlOIf, "dut_top.InstApbUartTop_0.ctrlOIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlPIf, "dut_top.InstApbUartTop_0.ctrlPIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlFIf, "dut_top.InstApbUartTop_0.ctrlFIf");
#endif
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlD9, "dut_top.InstApbUartTop_0.ctrlD9");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlData, "dut_top.InstApbUartTop_0.ctrlData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlDataRd, "dut_top.InstApbUartTop_0.ctrlDataRd");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlEn, "dut_top.InstApbUartTop_0.ctrlEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlEp, "dut_top.InstApbUartTop_0.ctrlEp");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlRxt, "dut_top.InstApbUartTop_0.ctrlRxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlShiftRx, "dut_top.InstApbUartTop_0.ctrlShiftRx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlShiftTx, "dut_top.InstApbUartTop_0.ctrlShiftTx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlTxEn, "dut_top.InstApbUartTop_0.ctrlTxEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.ctrlTxt, "dut_top.InstApbUartTop_0.ctrlTxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxBusy, "dut_top.InstApbUartTop_0.rxBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxData, "dut_top.InstApbUartTop_0.rxData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxFe, "dut_top.InstApbUartTop_0.rxFe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxNe, "dut_top.InstApbUartTop_0.rxNe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxOv, "dut_top.InstApbUartTop_0.rxOv");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxPe, "dut_top.InstApbUartTop_0.rxPe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.rxRxf, "dut_top.InstApbUartTop_0.rxRxf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.txBusy, "dut_top.InstApbUartTop_0.txBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.txNf, "dut_top.InstApbUartTop_0.txNf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.txTxe, "dut_top.InstApbUartTop_0.txTxe");

//InstApbUartApbIf --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pClk, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pClk");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pResetN, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pResetN");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pWrite, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pWrite");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pSel, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pSel");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pEnable, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pEnable");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pAddr, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pAddr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pWData, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pWData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pStrb, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pStrb");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txNf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.txNf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txBusy, "dut_top.InstApbUartTop_0.InstApbUartApbIf.txBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txTxe, "dut_top.InstApbUartTop_0.InstApbUartApbIf.txTxe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxNe, "dut_top.InstApbUartTop_0.InstApbUartApbIf.rxNe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxBusy, "dut_top.InstApbUartTop_0.InstApbUartApbIf.rxBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxRxf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.rxRxf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxOv, "dut_top.InstApbUartTop_0.InstApbUartApbIf.rxOv");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxPe, "dut_top.InstApbUartTop_0.InstApbUartApbIf.rxPe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxFe, "dut_top.InstApbUartTop_0.InstApbUartApbIf.rxFe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxData, "dut_top.InstApbUartTop_0.InstApbUartApbIf.rxData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlEn, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlTxEn, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlTxEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlD9, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlD9");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlEp, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlEp");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlShiftRx, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlShiftRx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlShiftTx, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlShiftTx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlTxt, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlTxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlRxt, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlRxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlDataRd, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlDataRd");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlData, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pRData, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pRData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pReady, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pReady");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.pSlvErr, "dut_top.InstApbUartTop_0.InstApbUartApbIf.pSlvErr");
#ifdef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlIf");
#endif
#ifndef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlTIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlTIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlRIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlRIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlOIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlOIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlPIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlPIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlFIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlFIf");
#else
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlTIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlTIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlRIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlRIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlOIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlOIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlPIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlPIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlFIf, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlFIf");
#endif
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlEnTmp, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlEnTmp");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.conWe, "dut_top.InstApbUartTop_0.InstApbUartApbIf.conWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.seWe, "dut_top.InstApbUartTop_0.InstApbUartApbIf.seWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.brWe, "dut_top.InstApbUartTop_0.InstApbUartApbIf.brWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ieWe, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ieWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.conReg, "dut_top.InstApbUartTop_0.InstApbUartApbIf.conReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.seReg, "dut_top.InstApbUartTop_0.InstApbUartApbIf.seReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.brReg, "dut_top.InstApbUartTop_0.InstApbUartApbIf.brReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ieReg, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ieReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.rxCounter, "dut_top.InstApbUartTop_0.InstApbUartApbIf.rxCounter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.txCounter, "dut_top.InstApbUartTop_0.InstApbUartApbIf.txCounter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.errCondition, "dut_top.InstApbUartTop_0.InstApbUartApbIf.errCondition");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartApbIf.ctrlShiftRxTmp, "dut_top.InstApbUartTop_0.InstApbUartApbIf.ctrlShiftRxTmp");

//InstApbUartReciever --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.pClk, "dut_top.InstApbUartTop_0.InstApbUartReciever.pClk");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.pResetN, "dut_top.InstApbUartTop_0.InstApbUartReciever.pResetN");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlEn, "dut_top.InstApbUartTop_0.InstApbUartReciever.ctrlEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlD9, "dut_top.InstApbUartTop_0.InstApbUartReciever.ctrlD9");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlEp, "dut_top.InstApbUartTop_0.InstApbUartReciever.ctrlEp");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlShiftRx, "dut_top.InstApbUartTop_0.InstApbUartReciever.ctrlShiftRx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlDataRd, "dut_top.InstApbUartTop_0.InstApbUartReciever.ctrlDataRd");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.uartRx, "dut_top.InstApbUartTop_0.InstApbUartReciever.uartRx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ctrlRxt, "dut_top.InstApbUartTop_0.InstApbUartReciever.ctrlRxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxNe, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxNe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxBusy, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxRxf, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxRxf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxOv, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxOv");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxPe, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxPe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFe, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxFe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxData, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.setSampleCounter, "dut_top.InstApbUartTop_0.InstApbUartReciever.setSampleCounter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoOv, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxFifoOv");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.fsmActive, "dut_top.InstApbUartTop_0.InstApbUartReciever.fsmActive");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.fsmStart, "dut_top.InstApbUartTop_0.InstApbUartReciever.fsmStart");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.fsmShift, "dut_top.InstApbUartTop_0.InstApbUartReciever.fsmShift");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxRxfReg, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxRxfReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.frameError, "dut_top.InstApbUartTop_0.InstApbUartReciever.frameError");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.parityError, "dut_top.InstApbUartTop_0.InstApbUartReciever.parityError");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.uartSync, "dut_top.InstApbUartTop_0.InstApbUartReciever.uartSync");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxShiftEn, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxShiftEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxComplete, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxComplete");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.wrRxFifo, "dut_top.InstApbUartTop_0.InstApbUartReciever.wrRxFifo");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rdRxFifo, "dut_top.InstApbUartTop_0.InstApbUartReciever.rdRxFifo");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoEmplty, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxFifoEmplty");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoFull, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxFifoFull");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.lsbRxfifoEqual, "dut_top.InstApbUartTop_0.InstApbUartReciever.lsbRxfifoEqual");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.msbRxfifoDiff, "dut_top.InstApbUartTop_0.InstApbUartReciever.msbRxfifoDiff");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoWe, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxFifoWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoRe, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxFifoRe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.sampleCounter, "dut_top.InstApbUartTop_0.InstApbUartReciever.sampleCounter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxCounterBit, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxCounterBit");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.ffSync, "dut_top.InstApbUartTop_0.InstApbUartReciever.ffSync");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxNextState, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxNextState");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxCurrentState, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxCurrentState");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxWptr, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxWptr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxRptr, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxRptr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.dataIn, "dut_top.InstApbUartTop_0.InstApbUartReciever.dataIn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoPtrCompare, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxFifoPtrCompare");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxShiftReg, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxShiftReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxFifoDataOut, "dut_top.InstApbUartTop_0.InstApbUartReciever.rxFifoDataOut");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.dataInRxFifo, "dut_top.InstApbUartTop_0.InstApbUartReciever.dataInRxFifo");
for (int i=0; i<16; i++) {
  char str[4];
  sprintf(str, "(%0d)",i);
  sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartReciever.rxMemArray[i], "dut_top.InstApbUartTop_0.InstApbUartReciever.rxMemArray" + string(str));
}

//InstApbUartTransmitter --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.pClk, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.pClk");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.pResetN, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.pResetN");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlD9, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.ctrlD9");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlEn, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.ctrlEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlEp, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.ctrlEp");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlShiftTx, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.ctrlShiftTx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlTxEn, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.ctrlTxEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlTxt, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.ctrlTxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.ctrlData, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.ctrlData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txBusy, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txNf, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txNf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txTxe, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txTxe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.uartTx, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.uartTx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.data9, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.data9");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.loadData, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.loadData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.shiftEn, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.shiftEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txFifoRe, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txFifoRe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txFifoWe, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txFifoWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txShiftComplete, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txShiftComplete");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txFifoOut, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txFifoOut");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.state, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.state");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.shiftTxCounter, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.shiftTxCounter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txRptr, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txRptr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txWptr, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txWptr");
for (int i=0; i<16; i++) {
  char str[4];
  sprintf(str, "(%0d)",i);
  sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txMemArray[i], "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txMemArray" + string(str));
}
sc_trace(uart_waveform, dut_top->InstApbUartTop_0.InstApbUartTransmitter.txShiftReg, "dut_top.InstApbUartTop_0.InstApbUartTransmitter.txShiftReg");

//InstApbUartTop_1 --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pClk, "dut_top.InstApbUartTop_1.pClk");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pResetN, "dut_top.InstApbUartTop_1.pResetN");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pWrite, "dut_top.InstApbUartTop_1.pWrite");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pSel, "dut_top.InstApbUartTop_1.pSel");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pEnable, "dut_top.InstApbUartTop_1.pEnable");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pAddr, "dut_top.InstApbUartTop_1.pAddr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pWData, "dut_top.InstApbUartTop_1.pWData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pStrb, "dut_top.InstApbUartTop_1.pStrb");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pRData, "dut_top.InstApbUartTop_1.pRData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pReady, "dut_top.InstApbUartTop_1.pReady");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.pSlvErr, "dut_top.InstApbUartTop_1.pSlvErr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.uartRx, "dut_top.InstApbUartTop_1.uartRx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.uartTx, "dut_top.InstApbUartTop_1.uartTx");
#ifdef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlIf, "dut_top.InstApbUartTop_1.ctrlIf");
#endif
#ifndef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlTIf, "dut_top.InstApbUartTop_1.ctrlTIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlRIf, "dut_top.InstApbUartTop_1.ctrlRIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlOIf, "dut_top.InstApbUartTop_1.ctrlOIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlPIf, "dut_top.InstApbUartTop_1.ctrlPIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlFIf, "dut_top.InstApbUartTop_1.ctrlFIf");
#else
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlTIf, "dut_top.InstApbUartTop_1.ctrlTIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlRIf, "dut_top.InstApbUartTop_1.ctrlRIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlOIf, "dut_top.InstApbUartTop_1.ctrlOIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlPIf, "dut_top.InstApbUartTop_1.ctrlPIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlFIf, "dut_top.InstApbUartTop_1.ctrlFIf");
#endif
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlD9, "dut_top.InstApbUartTop_1.ctrlD9");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlData, "dut_top.InstApbUartTop_1.ctrlData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlDataRd, "dut_top.InstApbUartTop_1.ctrlDataRd");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlEn, "dut_top.InstApbUartTop_1.ctrlEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlEp, "dut_top.InstApbUartTop_1.ctrlEp");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlRxt, "dut_top.InstApbUartTop_1.ctrlRxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlShiftRx, "dut_top.InstApbUartTop_1.ctrlShiftRx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlShiftTx, "dut_top.InstApbUartTop_1.ctrlShiftTx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlTxEn, "dut_top.InstApbUartTop_1.ctrlTxEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.ctrlTxt, "dut_top.InstApbUartTop_1.ctrlTxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxBusy, "dut_top.InstApbUartTop_1.rxBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxData, "dut_top.InstApbUartTop_1.rxData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxFe, "dut_top.InstApbUartTop_1.rxFe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxNe, "dut_top.InstApbUartTop_1.rxNe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxOv, "dut_top.InstApbUartTop_1.rxOv");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxPe, "dut_top.InstApbUartTop_1.rxPe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.rxRxf, "dut_top.InstApbUartTop_1.rxRxf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.txBusy, "dut_top.InstApbUartTop_1.txBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.txNf, "dut_top.InstApbUartTop_1.txNf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.txTxe, "dut_top.InstApbUartTop_1.txTxe");

//InstApbUartApbIf --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pClk, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pClk");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pResetN, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pResetN");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pWrite, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pWrite");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pSel, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pSel");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pEnable, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pEnable");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pAddr, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pAddr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pWData, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pWData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pStrb, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pStrb");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.txNf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.txNf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.txBusy, "dut_top.InstApbUartTop_1.InstApbUartApbIf.txBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.txTxe, "dut_top.InstApbUartTop_1.InstApbUartApbIf.txTxe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxNe, "dut_top.InstApbUartTop_1.InstApbUartApbIf.rxNe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxBusy, "dut_top.InstApbUartTop_1.InstApbUartApbIf.rxBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxRxf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.rxRxf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxOv, "dut_top.InstApbUartTop_1.InstApbUartApbIf.rxOv");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxPe, "dut_top.InstApbUartTop_1.InstApbUartApbIf.rxPe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxFe, "dut_top.InstApbUartTop_1.InstApbUartApbIf.rxFe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxData, "dut_top.InstApbUartTop_1.InstApbUartApbIf.rxData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlEn, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlTxEn, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlTxEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlD9, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlD9");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlEp, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlEp");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlShiftRx, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlShiftRx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlShiftTx, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlShiftTx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlTxt, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlTxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlRxt, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlRxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlDataRd, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlDataRd");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlData, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pRData, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pRData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pReady, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pReady");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.pSlvErr, "dut_top.InstApbUartTop_1.InstApbUartApbIf.pSlvErr");
#ifdef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlIf");
#endif
#ifndef INTERRUPT_COM
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlTIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlTIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlRIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlRIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlOIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlOIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlPIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlPIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlFIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlFIf");
#else
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlTIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlTIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlRIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlRIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlOIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlOIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlPIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlPIf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlFIf, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlFIf");
#endif
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlEnTmp, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlEnTmp");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.conWe, "dut_top.InstApbUartTop_1.InstApbUartApbIf.conWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.seWe, "dut_top.InstApbUartTop_1.InstApbUartApbIf.seWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.brWe, "dut_top.InstApbUartTop_1.InstApbUartApbIf.brWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ieWe, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ieWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.conReg, "dut_top.InstApbUartTop_1.InstApbUartApbIf.conReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.seReg, "dut_top.InstApbUartTop_1.InstApbUartApbIf.seReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.brReg, "dut_top.InstApbUartTop_1.InstApbUartApbIf.brReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ieReg, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ieReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.rxCounter, "dut_top.InstApbUartTop_1.InstApbUartApbIf.rxCounter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.txCounter, "dut_top.InstApbUartTop_1.InstApbUartApbIf.txCounter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.errCondition, "dut_top.InstApbUartTop_1.InstApbUartApbIf.errCondition");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartApbIf.ctrlShiftRxTmp, "dut_top.InstApbUartTop_1.InstApbUartApbIf.ctrlShiftRxTmp");

//InstApbUartReciever --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.pClk, "dut_top.InstApbUartTop_1.InstApbUartReciever.pClk");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.pResetN, "dut_top.InstApbUartTop_1.InstApbUartReciever.pResetN");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlEn, "dut_top.InstApbUartTop_1.InstApbUartReciever.ctrlEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlD9, "dut_top.InstApbUartTop_1.InstApbUartReciever.ctrlD9");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlEp, "dut_top.InstApbUartTop_1.InstApbUartReciever.ctrlEp");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlShiftRx, "dut_top.InstApbUartTop_1.InstApbUartReciever.ctrlShiftRx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlDataRd, "dut_top.InstApbUartTop_1.InstApbUartReciever.ctrlDataRd");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.uartRx, "dut_top.InstApbUartTop_1.InstApbUartReciever.uartRx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ctrlRxt, "dut_top.InstApbUartTop_1.InstApbUartReciever.ctrlRxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxNe, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxNe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxBusy, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxRxf, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxRxf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxOv, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxOv");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxPe, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxPe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFe, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxFe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxData, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.setSampleCounter, "dut_top.InstApbUartTop_1.InstApbUartReciever.setSampleCounter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoOv, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxFifoOv");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.fsmActive, "dut_top.InstApbUartTop_1.InstApbUartReciever.fsmActive");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.fsmStart, "dut_top.InstApbUartTop_1.InstApbUartReciever.fsmStart");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.fsmShift, "dut_top.InstApbUartTop_1.InstApbUartReciever.fsmShift");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxRxfReg, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxRxfReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.frameError, "dut_top.InstApbUartTop_1.InstApbUartReciever.frameError");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.parityError, "dut_top.InstApbUartTop_1.InstApbUartReciever.parityError");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.uartSync, "dut_top.InstApbUartTop_1.InstApbUartReciever.uartSync");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxShiftEn, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxShiftEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxComplete, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxComplete");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.wrRxFifo, "dut_top.InstApbUartTop_1.InstApbUartReciever.wrRxFifo");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rdRxFifo, "dut_top.InstApbUartTop_1.InstApbUartReciever.rdRxFifo");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoEmplty, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxFifoEmplty");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoFull, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxFifoFull");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.lsbRxfifoEqual, "dut_top.InstApbUartTop_1.InstApbUartReciever.lsbRxfifoEqual");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.msbRxfifoDiff, "dut_top.InstApbUartTop_1.InstApbUartReciever.msbRxfifoDiff");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoWe, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxFifoWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoRe, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxFifoRe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.sampleCounter, "dut_top.InstApbUartTop_1.InstApbUartReciever.sampleCounter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxCounterBit, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxCounterBit");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.ffSync, "dut_top.InstApbUartTop_1.InstApbUartReciever.ffSync");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxNextState, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxNextState");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxCurrentState, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxCurrentState");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxWptr, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxWptr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxRptr, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxRptr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.dataIn, "dut_top.InstApbUartTop_1.InstApbUartReciever.dataIn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoPtrCompare, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxFifoPtrCompare");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxShiftReg, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxShiftReg");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxFifoDataOut, "dut_top.InstApbUartTop_1.InstApbUartReciever.rxFifoDataOut");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.dataInRxFifo, "dut_top.InstApbUartTop_1.InstApbUartReciever.dataInRxFifo");
for (int i=0; i<16; i++) {
  char str[4];
  sprintf(str, "(%0d)",i);
  sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartReciever.rxMemArray[i], "dut_top.InstApbUartTop_1.InstApbUartReciever.rxMemArray" + string(str));
}

//InstApbUartTransmitter --- list of ports & signals
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.pClk, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.pClk");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.pResetN, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.pResetN");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlD9, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.ctrlD9");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlEn, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.ctrlEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlEp, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.ctrlEp");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlShiftTx, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.ctrlShiftTx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlTxEn, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.ctrlTxEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlTxt, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.ctrlTxt");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.ctrlData, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.ctrlData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txBusy, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txBusy");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txNf, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txNf");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txTxe, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txTxe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.uartTx, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.uartTx");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.data9, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.data9");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.loadData, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.loadData");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.shiftEn, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.shiftEn");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txFifoRe, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txFifoRe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txFifoWe, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txFifoWe");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txShiftComplete, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txShiftComplete");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txFifoOut, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txFifoOut");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.state, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.state");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.shiftTxCounter, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.shiftTxCounter");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txRptr, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txRptr");
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txWptr, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txWptr");
for (int i=0; i<16; i++) {
  char str[4];
  sprintf(str, "(%0d)",i);
  sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txMemArray[i], "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txMemArray" + string(str));
}
sc_trace(uart_waveform, dut_top->InstApbUartTop_1.InstApbUartTransmitter.txShiftReg, "dut_top.InstApbUartTop_1.InstApbUartTransmitter.txShiftReg");

// END
