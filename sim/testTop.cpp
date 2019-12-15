//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
#include <systemc>
#include <uvm>

#include "cTest.h"
#include "DUT.h"
#include "cIfApbUart.h"

///////
int sc_main(int, char*[])
{
    cTest* coTest = new cTest("coTest");
    DUT* coDUT = new DUT("coDUT");
    
    cIfApbUart *coIfApbUartTx = new cIfApbUart("coIfApbUartTx");
    //cIfApbUart *coIfApbUartRx = new cIfApbUart("coIfApbUartRx");
    
    uvm::uvm_config_db<cIfApbUart*>::set(0,"coTest.coEnv.coApbUartAgentTx.*","IfApbUart", coIfApbUartTx);
    coDUT->apbSeqEn(coIfApbUartTx->apbSeqEn);
    coDUT->pwdata(coIfApbUartTx->pwdata);
    
    uvm::run_test();
    
    delete coDUT;
    delete coTest;
    delete coIfApbUartTx;
    
    return 0;
}
        
     
