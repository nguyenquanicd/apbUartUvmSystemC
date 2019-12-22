//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

#ifndef DUT_H_
#define DUT_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

///////
class DUT : public sc_core::sc_module{
        public:
            //sc_signal<bool> pclk;
            //sc_signal<bool> preset_n;
            //sc_signal<bool> psel;
            //sc_signal<bool> penable;
            //sc_signal<bool> pwrite;
            //sc_signal<sc_uint<32> > paddr;
            sc_core::sc_in<bool> apbSeqEn;
            sc_core::sc_in<sc_dt::sc_uint<32> > pwdata;
            //sc_signal<sc_uint<32> > prdata;
            //sc_signal<sc_uint<32> > pstrb;
            //sc_signal<sc_uint<32> > pready;
            //sc_signal<sc_uint<32> > pslverr;
        void printData(){
            std::cout << "Data has been received: " << pwdata.read() << std::endl;
        }
        SC_CTOR(DUT):apbSeqEn("apbSeqEn"), pwdata("pwdata"){
              SC_METHOD(printData);
                sensitive << pwdata;
                dont_initialize();
        }   
}; // class DUT

#endif /* DUT_H_ */