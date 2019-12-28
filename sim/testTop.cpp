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
    TOP* dut_top = new TOP("dut_top");
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
    dut_top->pclk_0(vifApbUartTx->pclk);
    dut_top->preset_n_0(vifApbUartTx->preset_n);
    dut_top->pwrite_0(vifApbUartTx->pwrite);
    dut_top->psel_0(vifApbUartTx->psel);
    dut_top->penable_0(vifApbUartTx->penable);
    dut_top->pwdata_0(vifApbUartTx->pwdata);
    dut_top->paddr_0(vifApbUartTx->paddr);
    dut_top->pstrb_0(vifApbUartTx->pstrb);
    dut_top->prdata_0(vifApbUartTx->prdata);
    dut_top->pready_0(vifApbUartTx->pready);
    dut_top->pslverr_0(vifApbUartTx->pslverr);
    #ifdef INTERRUPT_COM
    dut_top->ctrl_if_0(vifInterruptTx->ctrl_if);
    #else
    dut_top->ctrl_fif_0(vifInterruptTx->ctrl_fif);
    dut_top->ctrl_oif_0(vifInterruptTx->ctrl_oif);
    dut_top->ctrl_pif_0(vifInterruptTx->ctrl_pif);
    dut_top->ctrl_rif_0(vifInterruptTx->ctrl_rif);
    dut_top->ctrl_tif_0(vifInterruptTx->ctrl_tif);
    #endif
    
    // Connect to UART 2    
    dut_top->pclk_1(vifApbUartRx->pclk);
    dut_top->preset_n_1(vifApbUartRx->preset_n);
    dut_top->pwrite_1(vifApbUartRx->pwrite);
    dut_top->psel_1(vifApbUartRx->psel);
    dut_top->penable_1(vifApbUartRx->penable);
    dut_top->pwdata_1(vifApbUartRx->pwdata);
    dut_top->paddr_1(vifApbUartRx->paddr);
    dut_top->pstrb_1(vifApbUartRx->pstrb);
    dut_top->prdata_1(vifApbUartRx->prdata);
    dut_top->pready_1(vifApbUartRx->pready);
    dut_top->pslverr_1(vifApbUartRx->pslverr); 
    #ifdef INTERRUPT_COM
    dut_top->ctrl_if_1(vifInterruptRx->ctrl_if);
    #else
    dut_top->ctrl_fif_1(vifInterruptRx->ctrl_fif);
    dut_top->ctrl_oif_1(vifInterruptRx->ctrl_oif);
    dut_top->ctrl_pif_1(vifInterruptRx->ctrl_pif);
    dut_top->ctrl_rif_1(vifInterruptRx->ctrl_rif);
    dut_top->ctrl_tif_1(vifInterruptRx->ctrl_tif);
    #endif
    
    // For UART checker 
    dut_top->uart_0to1(uart_0to1);
    dut_top->uart_1to0(uart_1to0);
   
    cout << "Combine duoc roi" << std::endl;
    //peripheral->uart1_pResetN.write(0);
    //peripheral->uart0_pResetN.write(0);
    //sc_core::sc_start(10, SC_NS);
    //peripheral->uart1_pResetN.write(1);
    //peripheral->uart0_pResetN.write(1);    
    uvm::run_test();
    
    delete dut_top;
    delete coTest;
    delete vifApbUartTx;
    delete vifApbUartRx;
    
    return 0;
}
        
     
