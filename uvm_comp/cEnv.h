//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

#ifndef CENV_H_
#define CENV_H_

#include <scv.h>
#include <systemc>
#include <tlm.h>
#include <uvm>

#include "cApbMasterAgent.h"
#include "cVSequencer.h" 

#include "cApbMasterAgent.h"
#include "cApbTransaction.h"
//#include "cApbUartVirSequence.h"

///////
class cEnv : public uvm::uvm_env
{
        public:
        //Instance
        cApbUartAgent* coApbUartAgentTx;
        cApbUartAgent* coApbUartAgentRx;
        //cApbUartScoreboard* coApbUartScoreboard;
        cVSequencer<cApbTransaction>* coVSequencer;
        
        UVM_COMPONENT_UTILS(cEnv);
        
        cEnv(uvm::uvm_component_name name) : uvm::uvm_env(name)
        {
           std::cout << sc_core::sc_time_stamp() << " Construct environemnt " << name <<"\n" <<std::endl; 
        }

        //Factory register
        //Constructor
        //Function
         void build_phase(uvm::uvm_phase& phase)
         {
             std::cout << sc_core::sc_time_stamp() << " Build environemnt " << "\n" <<std::endl;
             uvm::uvm_env::build_phase(phase);
             
             coApbUartAgentTx = cApbUartAgent::type_id::create("coApbUartAgentTx", this);
             assert(coApbUartAgentTx);
             
             coApbUartAgentRx = cApbUartAgent::type_id::create("coApbUartAgentRx", this);
             assert(coApbUartAgentRx);
             
             coVSequencer = cVSequencer<cApbTransaction>::type_id::create("coVSequencer", this);
             assert(coVSequencer);
 
             //coScoreboard = cApbUartScoreboard::type_id::create("coApbUartScoreboard", this);
             //assert(coScoreboard)
             std::cout << sc_core::sc_time_stamp() << " Goi VSequence -------- " << name() << "\n" << std::endl;
             //uvm::uvm_config_db<uvm::uvm_object_wrapper*>
             //::set(this,"coVSequencer.run_phase","default_sequence",
             //cApbUartVirSequence::type_id::get());
         }
         
         void connect_phase(uvm::uvm_phase& phase)
         {
             std::cout << sc_core::sc_time_stamp() << " Connect phase " << name() << "\n" << std::endl;
             coVSequencer->coApbUartAgentTx = coApbUartAgentTx;
             coVSequencer->coApbUartAgentRx = coApbUartAgentRx;
             //coApbUartAgentTx->coApbUartMonitor->item_collected_port.connect(cApbUartScoreboard->..)
             //coApbUartAgentRx->coApbUartMonitor-> ... 
         }

}; // class cVSequencer

#endif /*  CENV_H_ */