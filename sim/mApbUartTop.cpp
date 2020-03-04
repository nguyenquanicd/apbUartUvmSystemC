//--------------------------------------
//Project: Simple CPU
//Module:  TOP module
//Function:Connect all sub-modules (FETCH, DECODER, EXECUTE)
//Authod:  Nguyen Hung Quan
//Page:    VLSI Technology
//--------------------------------------
#include "mApbUartApbIf.h"
#include "mApbUartReciever.h"
#include "mApbUartTransmitter.h"
SC_MODULE (mApbUartTop) {
  //
	//APB interface
  //
  sc_in< bool >  pClk;
  sc_in< bool >  pResetN;
  sc_in< bool >  pWrite;
  sc_in< bool >  pSel;
  sc_in< bool >  pEnable;
  sc_in< sc_uint<32> >  pAddr;
  sc_in< sc_uint<32> > pWData;
  sc_in< sc_uint<4> >  pStrb;
  sc_out< sc_uint<32> > pRData;
  sc_out< bool > pReady;
  sc_out< bool > pSlvErr;
  //
  //UART interface
  //
  sc_in<bool> uartRx;
  sc_out<bool> uartTx;
  //
  //Interrupt interface
  //
  #ifdef INTERRUPT_COM
  	sc_out< bool > ctrlIf;
  #endif
  #ifndef INTERRUPT_COM
  	sc_out< bool > ctrlTIf;
  	sc_out< bool > ctrlRIf;
  	sc_out< bool > ctrlOIf;
  	sc_out< bool > ctrlPIf;
  	sc_out< bool > ctrlFIf;
  #else
  	sc_signal< bool > ctrlTIf;
  	sc_signal< bool > ctrlRIf;
  	sc_signal< bool > ctrlOIf;
  	sc_signal< bool > ctrlPIf;
  	sc_signal< bool > ctrlFIf;
  #endif
  //
  //Internal connection
  //
  sc_signal< bool >			ctrlD9;		// From ctrl of controller.v
  sc_signal< sc_uint<8> > ctrlData;		// From ctrl of controller.v
  sc_signal< bool >			ctrlDataRd;		// From ctrl of controller.v
  sc_signal< bool >			ctrlEn;		// From ctrl of controller.v
  sc_signal< bool >			ctrlEp;		// From ctrl of controller.v
  sc_signal< sc_uint<2> > ctrlRxt;		// From ctrl of controller.v
  sc_signal< bool >			ctrlShiftRx;		// From ctrl of controller.v
  sc_signal< bool >			ctrlShiftTx;		// From ctrl of controller.v
  sc_signal< bool >			ctrlTxEn;		// From ctrl of controller.v
  sc_signal< sc_uint<2> > ctrlTxt;		// From ctrl of controller.v
  sc_signal< bool >			rxBusy;		// From rx of receiver.v
  sc_signal< sc_uint<8> > rxData;		// From rx of receiver.v
  sc_signal< bool >			rxFe;			// From rx of receiver.v
  sc_signal< bool >			rxNe;			// From rx of receiver.v
  sc_signal< bool >			rxOv;			// From rx of receiver.v
  sc_signal< bool >			rxPe;			// From rx of receiver.v
  sc_signal< bool >			rxRxf;			// From rx of receiver.v
  sc_signal< bool >			txBusy;		// From tx of transmitter.v
  sc_signal< bool >			txNf;			// From tx of transmitter.v
  sc_signal< bool >			txTxe;			// From tx of transmitter.v
	//
	//Instance declaration
  //
	mApbUartApbIf       InstApbUartApbIf;
	mApbUartReciever    InstApbUartReciever;
	mApbUartTransmitter InstApbUartTransmitter;
	
	//
	//SC_CTOR (mApbUartTop)
	SC_CTOR (mApbUartTop) : InstApbUartApbIf("InstApbUartApbIf"), 
		InstApbUartReciever("InstApbUartReciever"), 
		InstApbUartTransmitter("InstApbUartTransmitter")
	{
    //
	  //Connection of InstApbUartApbIf
    //
    InstApbUartApbIf.pClk       (pClk);
    InstApbUartApbIf.pResetN    (pResetN);
    InstApbUartApbIf.pWrite     (pWrite);
    InstApbUartApbIf.pSel       (pSel);
    InstApbUartApbIf.pEnable    (pEnable);
    InstApbUartApbIf.pAddr      (pAddr);
    InstApbUartApbIf.pWData     (pWData);
    InstApbUartApbIf.pStrb      (pStrb);
    InstApbUartApbIf.txNf       (txNf);
    InstApbUartApbIf.txBusy     (txBusy);
    InstApbUartApbIf.txTxe      (txTxe);
    InstApbUartApbIf.rxNe       (rxNe);
    InstApbUartApbIf.rxBusy     (rxBusy);
    InstApbUartApbIf.rxRxf      (rxRxf);
    InstApbUartApbIf.rxOv       (rxOv);
    InstApbUartApbIf.rxPe       (rxPe);
    InstApbUartApbIf.rxFe       (rxFe);
    InstApbUartApbIf.rxData     (rxData);
    InstApbUartApbIf.ctrlEn     (ctrlEn);
    InstApbUartApbIf.ctrlTxEn   (ctrlTxEn);
    InstApbUartApbIf.ctrlD9     (ctrlD9);
    InstApbUartApbIf.ctrlEp     (ctrlEp);
    InstApbUartApbIf.ctrlShiftRx(ctrlShiftRx);
    InstApbUartApbIf.ctrlShiftTx(ctrlShiftTx);
    InstApbUartApbIf.ctrlTxt    (ctrlTxt);
    InstApbUartApbIf.ctrlRxt    (ctrlRxt);
    InstApbUartApbIf.ctrlDataRd (ctrlDataRd);
    InstApbUartApbIf.ctrlData   (ctrlData);
    InstApbUartApbIf.pRData     (pRData);
    InstApbUartApbIf.pReady     (pReady);
    InstApbUartApbIf.pSlvErr    (pSlvErr);
    #ifdef INTERRUPT_COM
    	InstApbUartApbIf.ctrlIf   (ctrlIf);
    #endif
    #ifndef INTERRUPT_COM
    	InstApbUartApbIf.ctrlTIf  (ctrlTIf);
    	InstApbUartApbIf.ctrlRIf  (ctrlRIf);
    	InstApbUartApbIf.ctrlOIf  (ctrlOIf);
    	InstApbUartApbIf.ctrlPIf  (ctrlPIf);
    	InstApbUartApbIf.ctrlFIf  (ctrlFIf);
    #else
    	InstApbUartApbIf.ctrlTIf  (ctrlTIf);
    	InstApbUartApbIf.ctrlRIf  (ctrlRIf);
    	InstApbUartApbIf.ctrlOIf  (ctrlOIf);
    	InstApbUartApbIf.ctrlPIf  (ctrlPIf);
    	InstApbUartApbIf.ctrlFIf  (ctrlFIf);
    #endif
    //
	  //Connection of InstApbUartReciever
    //
	  InstApbUartReciever.pClk       (pClk       );
	  InstApbUartReciever.pResetN    (pResetN    );	 
	  InstApbUartReciever.ctrlEn     (ctrlEn     );
	  InstApbUartReciever.ctrlD9     (ctrlD9     );
	  InstApbUartReciever.ctrlEp     (ctrlEp     );
	  InstApbUartReciever.ctrlShiftRx(ctrlShiftRx);
	  InstApbUartReciever.ctrlDataRd (ctrlDataRd );
	  InstApbUartReciever.ctrlRxt    (ctrlRxt    );
	  InstApbUartReciever.uartRx     (uartRx     );
	  InstApbUartReciever.rxNe       (rxNe       );
	  InstApbUartReciever.rxBusy     (rxBusy     );
	  InstApbUartReciever.rxRxf      (rxRxf      );
	  InstApbUartReciever.rxOv       (rxOv       );
	  InstApbUartReciever.rxPe       (rxPe       );
	  InstApbUartReciever.rxFe       (rxFe       );
	  InstApbUartReciever.rxData     (rxData     );
	  //
	  //Connection of InstApbUartTransmitter
    //
    InstApbUartTransmitter.pClk       (pClk       );
    InstApbUartTransmitter.pResetN    (pResetN    );
    InstApbUartTransmitter.ctrlD9     (ctrlD9     );
    InstApbUartTransmitter.ctrlEn     (ctrlEn     );
    InstApbUartTransmitter.ctrlEp     (ctrlEp     );
    InstApbUartTransmitter.ctrlShiftTx(ctrlShiftTx);
    InstApbUartTransmitter.ctrlTxEn   (ctrlTxEn   );
    InstApbUartTransmitter.ctrlTxt    (ctrlTxt    );
    InstApbUartTransmitter.ctrlData   (ctrlData   );
    InstApbUartTransmitter.txBusy     (txBusy     );
    InstApbUartTransmitter.txNf       (txNf       );
    InstApbUartTransmitter.txTxe      (txTxe      );
    InstApbUartTransmitter.uartTx     (uartTx     );
	}
};
