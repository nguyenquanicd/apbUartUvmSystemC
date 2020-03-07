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
#include "cApbMasterMonitor.h"
#include "cApbTransaction.h"

class cApbMasterAgent: public uvm::uvm_agent
{
    public:
        cApbMasterSequencer<cApbTransaction>* coApbMasterSequencer;
        cApbMasterDriver<cApbTransaction>*    coApbMasterDriver;
        cApbMasterMonitor* coApbMasterMonitor;
        UVM_COMPONENT_UTILS(cApbMasterAgent);
         
        cApbMasterAgent(uvm::uvm_component_name name) 
        : uvm::uvm_agent(name), coApbMasterSequencer(0), coApbMasterDriver(0) 
        {
            std::cout << sc_core::sc_time_stamp() << " [INFO] Construct agent " << name <<"\n" <<std::endl;
        }
        
        void build_phase(uvm::uvm_phase& phase)
        {
            uvm::uvm_agent::build_phase(phase);
            std::cout << sc_core::sc_time_stamp() << ":" << this->name() << " abc " << phase.get_name() <<"\n" <<std::endl;
            coApbMasterSequencer = cApbMasterSequencer<cApbTransaction>::type_id::create("coApbMasterSequencer", this);
            assert(coApbMasterSequencer);               
            coApbMasterDriver = cApbMasterDriver<cApbTransaction>::type_id::create("coApbMasterDriver", this);
            assert(coApbMasterDriver);
            coApbMasterMonitor = cApbMasterMonitor::type_id::create("coApbMasterMonitor",this);
            assert(coApbMasterMonitor);
        }
        
        void connect_phase(uvm::uvm_phase& phase){
            std::cout << sc_core::sc_time_stamp() << ": connect_phase " << name() << "\n" << std::endl;
            coApbMasterDriver->seq_item_port.connect(coApbMasterSequencer->seq_item_export);
       }
        
};

#endif /* CAPBUARTAGENT_H_ */