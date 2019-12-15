//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
#include <systemc>
#include <uvm>

#include "../uvm_comp/cTest.h"
#include "../dut/dut_top.cpp"
#include "../uvm_comp/ifDut.h"

///////
int sc_main(int, char*[])
{
    cTest* coTest = new cTest("coTest");
    mUartApbIf* mApbUartApbIf = new DUT("mUartApbIf");
    
    cIfApbUart *coIfApbUartTx = new cIfApbUart("coIfApbUartTx");
    cIfApbUart *coIfApbUartRx = new cIfApbUart("coIfApbUartRx");
    
    uvm::uvm_config_db<cIfApbUart*>::set(0,"coTest.coEnv.coApbUartAgentTx.*","IfApbUart", coIfApbUartTx);
    mUartApbIf->apbSeqEn(coIfApbUartTx->apbSeqEn);
    mUartApbIf->pwdata(coIfApbUartTx->pwdata);
    
    uvm::run_test();
    
    delete mUartApbIf;
    delete coTest;
    delete coIfApbUartTx;
    
    return 0;
}
        
     
