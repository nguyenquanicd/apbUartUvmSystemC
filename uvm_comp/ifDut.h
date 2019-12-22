//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

#ifndef CIFAPBUART_H_
#define CIFAPBUART_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

///////
class ifApbUart
{
    public:
        sc_core::sc_signal<bool> pclk;
        sc_core::sc_signal<bool> preset_n;
        sc_core::sc_signal<bool> psel;
        sc_core::sc_signal<bool> penable;
        sc_core::sc_signal<bool> pwrite;
        sc_core::sc_signal<sc_dt::sc_uint<32> > paddr;
        sc_core::sc_signal<bool> apbSeqEn;
        sc_core::sc_signal<sc_dt::sc_uint<32> > pwdata;
        sc_core::sc_signal<sc_dt::sc_uint<32> > prdata;
        sc_core::sc_signal<sc_dt::sc_uint<4> > pstrb;
        sc_core::sc_signal<bool> pready;
        sc_core::sc_signal<bool> pslverr;      
        ifApbUart(const std::string& name) : pwdata("pwdata"), preset_n("preset_n"),psel("psel"),
                                             penable("penable"), pwrite("pwrite"), paddr("paddr"), 
                                             apbSeqEn("apbSeqEn"), prdata("prdata"), pstrb("pstrb"),
                                             pready("pready"), pslverr("pslverr")                                              
        {}
}; // class cApbTransaction   

class ifInterrupt 
{
    public:
        #ifdef INTERRUPT_COM
        sc_signal<bool > ctrl_if;
        ifInterrupt(const std::string& name) : ctrl_if("ctrl_if"){}
        #else
        sc_signal<bool > ctrl_fif;
        sc_signal<bool > ctrl_oif;
        sc_signal<bool > ctrl_pif;
        sc_signal<bool > ctrl_rif;
        sc_signal<bool > ctrl_tif;                
        ifInterrupt(const std::string& name) : ctrl_fif("ctrl_fif"), ctrl_oif("ctrl_oif"),
                                               ctrl_pif("ctrl_pif"), ctrl_rif("ctrl_rif"),
                                               ctrl_tif("ctrl_tif")
                                               {}
        #endif  

};

class ifUart
{
    public:
        sc_signal<bool> uartTx;
        sc_signal<bool> uartRx;
        ifUart(const std::string& name) : uartTx("uartTx"), uartRx("uartRx")
        {}
};
#endif /* CIFAPBUART_H_ */