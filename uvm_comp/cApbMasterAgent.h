//--------------------------------------
//Project: The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: ApbSequencer
//Author: Truong Cong Hoang Viet
//Page:    VLSI Technology
//--------------------------------------

#ifndef CAPBUARTAGENT_H_
#define CAPBUARTAGENT_H_

#include <systemc>
#include <tlm.h>
#include <uvm>
#include "cApbMasterSequencer.h"
#include "cApbMasterDriver.h"
#include "cApbTransaction.h"

class cApbUartAgent: public uvm::uvm_agent
{
    public:
        cApbUartSequencer<cApbTransaction>* coApbUartSequencer;
        cApbUartDriver<cApbTransaction>*    coApbUartDriver;
        
        cApbUartAgent(uvm::uvm_component_name name) 
        : uvm::uvm_agent(name), coApbUartSequencer(0), coApbUartDriver(0) 
        {
            std::cout << sc_core::sc_time_stamp() << " Construct agent " << name <<"\n" <<std::endl;
        }
        
        UVM_COMPONENT_UTILS(cApbUartAgent);
        
        void build_phase(uvm::uvm_phase& phase)
        {
            uvm::uvm_agent::build_phase(phase);
            std::cout << sc_core::sc_time_stamp() << ":" << this->name() << " abc " << phase.get_name() <<"\n" <<std::endl;
            if(get_is_active() == uvm::UVM_ACTIVE){
                UVM_INFO(get_name(), "is set to UVM_ACTIVE", uvm::UVM_NONE);
                coApbUartSequencer = cApbUartSequencer<cApbTransaction>::type_id::create("coApbUartSequencer", this);
                assert(coApbUartSequencer);
                
                coApbUartDriver = cApbUartDriver<cApbTransaction>::type_id::create("coApbUartDriver", this);
                assert(coApbUartDriver);
            } else 
                UVM_INFO(get_name(), "is set to UVM_PASSIVE", uvm::UVM_NONE);
            
           //coApbUartMonitor = cApbUartMonitor::type_id::create("coApbUartMonitor",this);
           //assert(coApbUartMonitor);
        }
        
        void connect_phase(uvm::uvm_phase& phase){
            std::cout << sc_core::sc_time_stamp() << ": connect_phase " << name() << "\n" << std::endl;
            coApbUartDriver->seq_item_port.connect(coApbUartSequencer->seq_item_export);
       }
        
};

#endif /* CAPBUARTAGENT_H_ */