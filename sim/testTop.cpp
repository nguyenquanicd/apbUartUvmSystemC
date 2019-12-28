//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
#define UART0_CLOCK_CYCLE 50
#define UART1_CLOCK_CYCLE 86

#include <scv.h>
#include <systemc>
#include <tlm.h>
#include <uvm>

#include "cTest.h"
#include "ifDut.h"
#include "dut_top.cpp"
#include "mPeripheral.cpp"

///////
int sc_main(int, char*[])
{
    sc_signal<bool> uart_0to1;
    sc_signal<bool> uart_1to0;
    
    cTest* coTest = new cTest("coTest");
    dut_top* instDutTop = new dut_top("instDutTop");
    mPeripheral* peripheral = new mPeripheral("peripheral");
    
    ifApbUart *vifApbUartTx = new ifApbUart("vifApbUartTx");
    ifApbUart *vifApbUartRx = new ifApbUart("vifApbUartRx");
    ifInterrupt *vifInterruptTx = new ifInterrupt("vifInterruptTx");
    ifInterrupt *vifInterruptRx = new ifInterrupt("vifInterruptRx");
    
    peripheral->uart0_clk(vifApbUartTx->pclk);
    peripheral->uart1_clk(vifApbUartRx->pclk);
    peripheral->uart0_pResetN(vifApbUartTx->preset_n);
    peripheral->uart1_pResetN(vifApbUartRx->preset_n);
      
    uvm::uvm_config_db<ifApbUart*>::set(0,"coTest.coEnv.coApbUartAgentTx.*","vifApbMaster", vifApbUartTx);
    uvm::uvm_config_db<ifApbUart*>::set(0,"coTest.coEnv.coApbUartAgentRx.*","vifApbMaster", vifApbUartRx);
    
    uvm::uvm_config_db<ifInterrupt*>::set(0,"coTest.coEnv.coApbUartAgentTx.*","vifInterrupt",vifInterruptTx);
    uvm::uvm_config_db<ifInterrupt*>::set(0,"coTest.coEnv.coApbUartAgentRx.*","vifInterrupt",vifInterruptRx);
    
    //Connect to UART 0
    instDutTop->pclk_0(vifApbUartTx->pclk);
    instDutTop->preset_n_0(vifApbUartTx->preset_n);
    instDutTop->pwrite_0(vifApbUartTx->pwrite);
    instDutTop->psel_0(vifApbUartTx->psel);
    instDutTop->penable_0(vifApbUartTx->penable);
    instDutTop->pwdata_0(vifApbUartTx->pwdata);
    instDutTop->paddr_0(vifApbUartTx->paddr);
    instDutTop->pstrb_0(vifApbUartTx->pstrb);
    instDutTop->prdata_0(vifApbUartTx->prdata);
    instDutTop->pready_0(vifApbUartTx->pready);
    instDutTop->pslverr_0(vifApbUartTx->pslverr);
    #ifdef INTERRUPT_COM
    instDutTop->ctrl_if_0(vifInterruptTx->ctrl_if);
    #else
    instDutTop->ctrl_fif_0(vifInterruptTx->ctrl_fif);
    instDutTop->ctrl_oif_0(vifInterruptTx->ctrl_oif);
    instDutTop->ctrl_pif_0(vifInterruptTx->ctrl_pif);
    instDutTop->ctrl_rif_0(vifInterruptTx->ctrl_rif);
    instDutTop->ctrl_tif_0(vifInterruptTx->ctrl_tif);
    #endif
    
    // Connect to UART 2    
    instDutTop->pclk_1(vifApbUartRx->pclk);
    instDutTop->preset_n_1(vifApbUartRx->preset_n);
    instDutTop->pwrite_1(vifApbUartRx->pwrite);
    instDutTop->psel_1(vifApbUartRx->psel);
    instDutTop->penable_1(vifApbUartRx->penable);
    instDutTop->pwdata_1(vifApbUartRx->pwdata);
    instDutTop->paddr_1(vifApbUartRx->paddr);
    instDutTop->pstrb_1(vifApbUartRx->pstrb);
    instDutTop->prdata_1(vifApbUartRx->prdata);
    instDutTop->pready_1(vifApbUartRx->pready);
    instDutTop->pslverr_1(vifApbUartRx->pslverr); 
    #ifdef INTERRUPT_COM
    instDutTop->ctrl_if_1(vifInterruptRx->ctrl_if);
    #else
    instDutTop->ctrl_fif_1(vifInterruptRx->ctrl_fif);
    instDutTop->ctrl_oif_1(vifInterruptRx->ctrl_oif);
    instDutTop->ctrl_pif_1(vifInterruptRx->ctrl_pif);
    instDutTop->ctrl_rif_1(vifInterruptRx->ctrl_rif);
    instDutTop->ctrl_tif_1(vifInterruptRx->ctrl_tif);
    #endif
    
    // For UART checker 
    instDutTop->uart_0to1(uart_0to1);
    instDutTop->uart_1to0(uart_1to0);
   
    cout << "Combine duoc roi" << std::endl;
    //peripheral->uart1_pResetN.write(0);
    //peripheral->uart0_pResetN.write(0);
    //sc_core::sc_start(10, SC_NS);
    //peripheral->uart1_pResetN.write(1);
    //peripheral->uart0_pResetN.write(1);    
    uvm::run_test();
    
    delete instDutTop;
    delete coTest;
    delete vifApbUartTx;
    delete vifApbUartRx;
    
    return 0;
}
        
     
