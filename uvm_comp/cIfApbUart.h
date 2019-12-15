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
class cIfApbUart
{
    public:
        //sc_signal<bool> pclk;
        //sc_signal<bool> preset_n;
        //sc_signal<bool> psel;
        //sc_signal<bool> penable;
        //sc_signal<bool> pwrite;
        //sc_signal<sc_uint<32> > paddr;
        sc_core::sc_signal<bool> apbSeqEn;
        sc_core::sc_signal<sc_dt::sc_uint<32> > pwdata;
        //sc_signal<sc_uint<32> > prdata;
        //sc_signal<sc_uint<32> > pstrb;
        //sc_signal<sc_uint<32> > pready;
        //sc_signal<sc_uint<32> > pslverr;
        cIfApbUart(const std::string& name) : pwdata("pwdata")
        {}
}; // class cApbTransaction   

#endif /* CIFAPBUART_H_ */