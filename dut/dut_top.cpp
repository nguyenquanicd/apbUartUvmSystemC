//--------------------------------------
//Project: The UVM environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Module:  DUT top connects 2 UART instances
//Function: Instance 2 uart_top
//Author:  Nguyen Hung Quan, Truong Cong Hoang Viet, Le Hoang Van
//Page:    VLSI Technology
//--------------------------------------
#include "systemc.h"
#include "mApbUartTop.cpp"
SC_MODULE (dut_top) { 
  //
  //UART 0
  //
  sc_in< bool >  pclk_0;
  sc_in< bool >  preset_n_0;
  sc_in< bool >  pwrite_0;
  sc_in< bool >  psel_0;
  sc_in< bool >  penable_0;
  sc_in< sc_uint<32> >  paddr_0;
  sc_in< sc_uint<32> >  pwdata_0;
  sc_in< sc_uint<4> >  pstrb_0;
  sc_out< sc_uint<32> > prdata_0;
  sc_out< bool > pready_0;
  sc_out< bool > pslverr_0;
  #ifdef INTERRUPT_COM
	  sc_out< bool > ctrl_if_0;
  #endif
  #ifndef INTERRUPT_COM
  	sc_out< bool >	ctrl_fif_0;
  	sc_out< bool >	ctrl_oif_0;
  	sc_out< bool >	ctrl_pif_0;
  	sc_out< bool >	ctrl_rif_0;
  	sc_out< bool >	ctrl_tif_0;
  #endif
  //
  //UART 1
  //
  sc_in< bool >  pclk_1;
  sc_in< bool >  preset_n_1;
  sc_in< bool >  pwrite_1;
  sc_in< bool >  psel_1;
  sc_in< bool >  penable_1;
  sc_in< sc_uint<32> > paddr_1;
  sc_in< sc_uint<32> > pwdata_1;
  sc_in< sc_uint<4> >  pstrb_1;
  sc_out< sc_uint<32> > prdata_1;
  sc_out< bool > pready_1;
  sc_out< bool > pslverr_1;
  #ifdef INTERRUPT_COM
	  sc_out< bool >			ctrl_if_1;
  #else
  	sc_out< bool >			ctrl_fif_1;
  	sc_out< bool >			ctrl_oif_1;	
  	sc_out< bool >			ctrl_pif_1;	
  	sc_out< bool >			ctrl_rif_1;	
  	sc_out< bool >			ctrl_tif_1;	
  #endif
  //
  //For UART protocol checker
  //
  sc_out< bool > uart_0to1;
  sc_out< bool > uart_1to0;
  //
	//Instance declaration
  //
	mApbUartTop    InstApbUartTop_0;
	mApbUartTop    InstApbUartTop_1;
  //Constructor
	SC_CTOR (dut_top) : InstApbUartTop_0("InstApbUartTop_0"), 
		InstApbUartTop_1("InstApbUartTop_1")
	{
   //
	 //Connection of InstApbUartTop_0
   //
   InstApbUartTop_0.uartTx (uart_0to1)       ;
   InstApbUartTop_0.pRData (prdata_0)        ;
   InstApbUartTop_0.pReady (pready_0)        ;
   InstApbUartTop_0.pSlvErr(pslverr_0)       ;
   InstApbUartTop_0.pStrb  (pstrb_0)         ;
   #ifdef INTERRUPT_COM
     InstApbUartTop_0.ctrlIf (ctrl_if_0)     ;
   #else
     InstApbUartTop_0.ctrlTIf (ctrl_tif_0)   ;
     InstApbUartTop_0.ctrlRIf (ctrl_rif_0)   ;
     InstApbUartTop_0.ctrlPIf (ctrl_pif_0)   ;
     InstApbUartTop_0.ctrlOIf (ctrl_oif_0)   ;
     InstApbUartTop_0.ctrlFIf (ctrl_fif_0)   ;
   #endif
   // Inputs
   InstApbUartTop_0.uartRx   (uart_1to0)     ;
   InstApbUartTop_0.pWrite   (pwrite_0)      ;
   InstApbUartTop_0.pWData   (pwdata_0)      ;
   InstApbUartTop_0.pSel     (psel_0)        ;
   InstApbUartTop_0.pResetN  (preset_n_0)    ;
   InstApbUartTop_0.pEnable  (penable_0)     ;
   InstApbUartTop_0.pClk     (pclk_0)        ;
   InstApbUartTop_0.pAddr    (paddr_0)       ;
   //
	 //Connection of InstApbUartTop_1
   //
   InstApbUartTop_1.uartTx (uart_1to0)       ;
   InstApbUartTop_1.pRData (prdata_1)        ;
   InstApbUartTop_1.pReady (pready_1)        ;
   InstApbUartTop_1.pSlvErr(pslverr_1)       ;
   InstApbUartTop_1.pStrb  (pstrb_1)         ;
   #ifdef INTERRUPT_COM
     InstApbUartTop_1.ctrlIf (ctrl_if_1)     ;
   #else
     InstApbUartTop_1.ctrlTIf (ctrl_tif_1)   ;
     InstApbUartTop_1.ctrlRIf (ctrl_rif_1)   ;
     InstApbUartTop_1.ctrlPIf (ctrl_pif_1)   ;
     InstApbUartTop_1.ctrlOIf (ctrl_oif_1)   ;
     InstApbUartTop_1.ctrlFIf (ctrl_fif_1)   ;
   #endif
   // Inputs
   InstApbUartTop_1.uartRx   (uart_0to1)     ;
   InstApbUartTop_1.pWrite   (pwrite_1)      ;
   InstApbUartTop_1.pWData   (pwdata_1)      ;
   InstApbUartTop_1.pSel     (psel_1)        ;
   InstApbUartTop_1.pResetN  (preset_n_1)    ;
   InstApbUartTop_1.pEnable  (penable_1)     ;
   InstApbUartTop_1.pClk     (pclk_1)        ;
   InstApbUartTop_1.pAddr    (paddr_1)       ;
	}
};
