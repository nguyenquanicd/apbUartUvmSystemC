//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------
#define UART0_CLOCK_CYCLE 50
#define UART1_CLOCK_CYCLE 86

#include <systemc>
#include <uvm>

#include "../uvm_comp/cTest.h"
#include "../dut/dut_top.cpp"
#include "../uvm_comp/ifDut.h"

///////
int sc_main(int, char*[])
{
    sc_clock uart0_clk("uart0_clk", UART0_CLOCK_CYCLE/2, SC_NS, 0.5);
    sc_clock uart1_clk("uart1_clk", UART1_CLOCK_CYCLE/2, SC_NS, 0.5);
    
    sc_signal<bool> uart_0to1;
    sc_signal<bool> uart_1to0;
    sc_signal<bool> preset_n;
    
    cTest* coTest = new cTest("coTest");
    uartTop* dut_top = new uartTop("dut_top");
    
    ifApbUart *vifApbUartTx = new ifApbUart("vifApbUartTx");
    ifApbUart *vifApbUartRx = new ifApbUart("vifApbUartRx");
    ifInterrupt *vifInterruptTx = new ifInterrupt("vifInterruptTx");
    ifInterrupt *vifInterruptRx = new ifInterrupt("vifInterruptRx");
    
    //vifApbUartTx->pclk(uart0_clk);
    //vifApbUartRx->pclk(uart1_clk);
    //vifApbUartTx->preset_n(preset_n);
    //vifApbUartRx->preset_n(preset_n);
      
    uvm::uvm_config_db<ifApbUart*>::set(0,"coTest.coEnv.coApbUartAgentTx.*","vifApbMaster", vifApbUartTx);
    uvm::uvm_config_db<ifApbUart*>::set(0,"coTest.coEnv.coApbUartAgentRx.*","vifApbMaster", vifApbUartRx);
    
    uvm::uvm_config_db<ifInterrupt*>::set(0,"coTest.coEnv.coApbUartAgentTx.*","vifInterrupt",vifInterruptTx);
    uvm::uvm_config_db<ifInterrupt*>::set(0,"coTest.coEnv.coApbUartAgentRx.*","vifInterrupt",vifInterruptRx);
    
    // Connect to UART 0
    dut_top->pclk_0(vifApbUartTx->pclk);
    dut_top->preset_n_0(vifApbUartTx->preset_n);
    dut_top->pwrite_0(vifApbUartTx->pwrite);
    dut_top->psel_0(vifApbUartTx->psel);
    dut_top->penable_0(vifApbUartTx->penable);
    dut_top->pwdata_0(vifApbUartTx->pwdata);
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
   
    preset_n.write(0);
    sc_core::wait(UART0_CLOCK_CYCLE + UART1_CLOCK_CYCLE, sc_core::SC_NS);
    preset_n.write(1);
    sc_core::wait(1, sc_core::SC_NS);
    cout << "Combine duoc roi" << std::endl;
    uvm::run_test();
    
    delete dut_top;
    delete coTest;
    delete vifApbUartTx;
    delete vifApbUartRx;
    
    return 0;
}
        
     
