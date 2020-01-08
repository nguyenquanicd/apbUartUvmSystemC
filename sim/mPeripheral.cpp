//--------------------------------------
//Project: The UVM environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Module:  DUT top connects 2 UART instances
//Function: Instance 2 uart_top
//Author:  Nguyen Hung Quan, Truong Cong Hoang Viet, Le Hoang Van
//Page:    VLSI Technology
//--------------------------------------
#define UART0_CLOCK_CYCLE 50
#define UART1_CLOCK_CYCLE 86
#include "systemc.h"

SC_MODULE(mPeripheral)
{
    sc_out<bool> uart0_clk;
    sc_out<bool> uart1_clk;
    sc_out<bool> uart0_pResetN;
    sc_out<bool> uart1_pResetN;
    sc_clock uart0_clock;
    sc_clock uart1_clock; 
    void uart0ClockSupply(){
        uart0_clk.write(uart0_clock);        
        //std::cout << sc_core::sc_time_stamp() << " uart0_clock value  " << uart0_clock << std::endl;
    }
    
    void uart1ClockSupply(){
        uart1_clk.write(uart1_clock);        
        //std::cout << sc_core::sc_time_stamp() << " uart1_clock value  " << uart1_clock << std::endl;
    }
    
    void resetInitualize(){
        uart0_pResetN.write(0);
        uart1_pResetN.write(0);
        //std::cout << sc_core::sc_time_stamp() << " Value of reset has been changed to  " << uart0_pResetN.read() << std::endl;
        sc_core::wait(10, SC_NS);    
        uart0_pResetN.write(1);
        uart1_pResetN.write(1);
        //std::cout << sc_core::sc_time_stamp() << " Value of reset has been changed to  " << uart0_pResetN.read() << std::endl;
    }
    
    SC_CTOR(mPeripheral): uart0_clk("uart0_clk"), uart1_clk("uart1_clk"),
                          uart0_pResetN("uart0_pResetN"), uart1_pResetN("uart1_pResetN"),
                          uart0_clock("uart0_clock", UART0_CLOCK_CYCLE/2,SC_NS, 0.5),
                          uart1_clock("uart1_clock", UART1_CLOCK_CYCLE/2,SC_NS, 0.5)
    {
        SC_METHOD(uart0ClockSupply)
            sensitive << uart0_clock;            
        SC_METHOD(uart1ClockSupply)
            sensitive << uart1_clock;            
        SC_THREAD(resetInitualize)
    }    
};


//int sc_main(int, char*[]){
//    mPeripheral peripheral("peripheral");
//    sc_signal<bool> uart0_clock;
//    sc_signal<bool> uart1_clock;
//    sc_signal<bool> pResetN;
//    peripheral.uart0_clk.bind(uart0_clock);
//    peripheral.uart1_clk.bind(uart1_clock);     
//    peripheral.pResetN.bind(pResetN);
//    sc_start(500, SC_NS);
//}