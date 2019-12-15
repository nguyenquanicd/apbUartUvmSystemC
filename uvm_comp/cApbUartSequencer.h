//--------------------------------------
//Project: The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: ApbSequencer
//Author: Truong Cong Hoang Viet
//Page:    VLSI Technology
//--------------------------------------

#ifndef CAPBUARTSEQUENCER_H_
#define CAPBUARTSEQUENCER_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

template <class REQ>
class cApbUartSequencer: public uvm::uvm_sequencer<REQ>
{
    public:
        cApbUartSequencer(uvm::uvm_component_name name) : uvm::uvm_sequencer<REQ>(name)
        {
            std::cout << sc_core::sc_time_stamp() << ": constructor " << name << std::endl;
        }
        UVM_COMPONENT_PARAM_UTILS(cApbUartSequencer<REQ>);
};

#endif /*  CAPBUARTSEQUENCER_H_ */