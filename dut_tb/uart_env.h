//--------------------------------------
//Project:  Simple CPU
//Module:   UART Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet
//Page:     VLSI Technology
//--------------------------------------
#include "mApbUartTop.cpp"
#include "uart_testbench.h"
SC_MODULE (uart_env) {
	//Ports and signals
	sc_in <bool> pClk;
	sc_signal <bool> pResetN;

  //  ***** APB interface TX *****
    sc_signal< bool >  pWrite_Tx;
    sc_signal< bool >  pSel_Tx;
    sc_signal< bool >  pEnable_Tx;
    sc_signal< sc_uint<32> >  pAddr_Tx;
    sc_signal< sc_uint<32> > pWData_Tx;
    sc_signal< sc_uint<4> >  pStrb_Tx;
    sc_signal< sc_uint<32> > pRData_Tx;
    sc_signal< bool > pReady_Tx;
    sc_signal< bool > pSlvErr_Tx;
  
   //  ***** APB interface RX *****
    sc_signal< bool >  pWrite_Rx;
    sc_signal< bool >  pSel_Rx;
    sc_signal< bool >  pEnable_Rx;
    sc_signal< sc_uint<32> >  pAddr_Rx;
    sc_signal< sc_uint<32> > pWData_Rx;
    sc_signal< sc_uint<4> >  pStrb_Rx;
    sc_signal< sc_uint<32> > pRData_Rx;
    sc_signal< bool > pReady_Rx;
    sc_signal< bool > pSlvErr_Rx;
    sc_signal< bool > Tx_Rx;
    sc_signal< bool > Rx_Tx;
  
    // ***************************
	mApbUartTop *uart_top_inst_tx;
    mApbUartTop *uart_top_inst_rx;
    uart_testbench *uart_testbench_inst;
    //
	void TEST();
    void write_apb_Tx(sc_uint<32> address, sc_uint<32> data);
    void read_apb_Tx(sc_uint<32> address, sc_uint<32> exp_data);
    void write_apb_Rx(sc_uint<32> address, sc_uint<32> data);
    void read_apb_Rx(sc_uint<32> address, sc_uint<32> exp_data);
    sc_uint<32> read_apb_Rx_N_cmpr(unsigned int address);
	//Constructor
	SC_CTOR (uart_env)  {
        
	  //
        uart_testbench_inst = new uart_testbench("uart_testbench_inst");
	    uart_testbench_inst->pClk(pClk);
	    uart_testbench_inst->pResetN(pResetN);
        
        uart_testbench_inst->pWrite_Tx(pWrite_Tx);
        uart_testbench_inst->pSel_Tx(pSel_Tx);
        uart_testbench_inst->pEnable_Tx(pEnable_Tx);
        uart_testbench_inst->pAddr_Tx(pAddr_Tx);
        uart_testbench_inst->pWData_Tx(pWData_Tx);
        uart_testbench_inst->pStrb_Tx(pStrb_Tx);
        uart_testbench_inst->pRData_Tx(pRData_Tx);
        uart_testbench_inst->pReady_Tx(pReady_Tx);
        uart_testbench_inst->pSlvErr_Tx(pSlvErr_Tx);
        
        uart_testbench_inst->pWrite_Rx(pWrite_Rx);
        uart_testbench_inst->pSel_Rx(pSel_Rx);
        uart_testbench_inst->pEnable_Rx(pEnable_Rx);
        uart_testbench_inst->pAddr_Rx(pAddr_Rx);
        uart_testbench_inst->pWData_Rx(pWData_Rx);
        uart_testbench_inst->pStrb_Rx(pStrb_Rx);
        uart_testbench_inst->pRData_Rx(pRData_Rx);
        uart_testbench_inst->pReady_Rx(pReady_Rx);
        uart_testbench_inst->pSlvErr_Rx(pSlvErr_Rx);

        
	    uart_top_inst_tx = new mApbUartTop("uart_top_inst_tx");
	    uart_top_inst_tx->pClk(pClk);
	    uart_top_inst_tx->pResetN(pResetN);
        uart_top_inst_tx->pWrite(pWrite_Tx);
        uart_top_inst_tx->pSel(pSel_Tx);
        uart_top_inst_tx->pEnable(pEnable_Tx);
        uart_top_inst_tx->pAddr(pAddr_Tx);
        uart_top_inst_tx->pWData(pWData_Tx);
        uart_top_inst_tx->pStrb(pStrb_Tx);
        uart_top_inst_tx->pRData(pRData_Tx);
        uart_top_inst_tx->pReady(pReady_Tx);
        uart_top_inst_tx->pSlvErr(pSlvErr_Tx);
        
      uart_top_inst_rx = new mApbUartTop("uart_top_inst_rx");
	    uart_top_inst_rx->pClk(pClk);
	    uart_top_inst_rx->pResetN(pResetN);
        uart_top_inst_rx->pWrite(pWrite_Rx);
        uart_top_inst_rx->pSel(pSel_Rx);
        uart_top_inst_rx->pEnable(pEnable_Rx);
        uart_top_inst_rx->pAddr(pAddr_Rx);
        uart_top_inst_rx->pWData(pWData_Rx);
        uart_top_inst_rx->pStrb(pStrb_Rx);
        uart_top_inst_rx->pRData(pRData_Rx);
        uart_top_inst_rx->pReady(pReady_Rx);
        uart_top_inst_rx->pSlvErr(pSlvErr_Rx);
      
        uart_top_inst_tx->uartTx(Tx_Rx);
        uart_top_inst_rx->uartRx(Tx_Rx);
        uart_top_inst_tx->uartRx(Rx_Tx);
        uart_top_inst_rx->uartTx(Rx_Tx);
    }
	//Destructor
	~uart_env(){	
	   delete uart_top_inst_tx;
       delete uart_top_inst_rx;
    }
};

