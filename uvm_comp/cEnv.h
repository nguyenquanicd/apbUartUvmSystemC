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
#include "cScoreboard.h"

#include "cApbMasterAgent.h"
#include "cApbTransaction.h"
//#include "cVSequence.h"

///////
class cEnv : public uvm::uvm_env
{
        public:
        //Instance
        cApbMasterAgent* coApbMasterAgentTx;
        cApbMasterAgent* coApbMasterAgentRx;
        cScoreboard* coScoreboard;
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
             
             coApbMasterAgentTx = cApbMasterAgent::type_id::create("coApbMasterAgentTx", this);
             assert(coApbMasterAgentTx);
             
             coApbMasterAgentRx = cApbMasterAgent::type_id::create("coApbMasterAgentRx", this);
             assert(coApbMasterAgentRx);
             
             coVSequencer = cVSequencer<cApbTransaction>::type_id::create("coVSequencer", this);
             assert(coVSequencer);
 
             coScoreboard = cScoreboard::type_id::create("coScoreboard", this);
             assert(coScoreboard);
             //std::cout << sc_core::sc_time_stamp() << " Goi VSequence -------- " << name() << "\n" << std::endl;
             //uvm::uvm_config_db<uvm::uvm_object_wrapper*>
             //::set(this,"coVSequencer.run_phase","default_sequence",
             //cApbUartVirSequence::type_id::get());
         }
         
         void connect_phase(uvm::uvm_phase& phase)
         {
             std::cout << sc_core::sc_time_stamp() << " Connect phase " << name() << "\n" << std::endl;
             coVSequencer->coApbMasterAgentTx = dynamic_cast<cApbMasterAgent*>(this->coApbMasterAgentTx);
             coVSequencer->coApbMasterAgentRx = dynamic_cast<cApbMasterAgent*>(this->coApbMasterAgentRx);
             
             coApbMasterAgentTx->coApbMasterMonitor->ap_toScoreboard.connect(coScoreboard->frmMonitorTX_listener_imp);
             coApbMasterAgentRx->coApbMasterMonitor->ap_toScoreboard.connect(coScoreboard->frmMonitorRX_listener_imp);
             coApbMasterAgentTx->coApbMasterMonitor->preset_toScoreboard.connect(coScoreboard->resetfrmTX_listener_imp);             
         }

}; // class cVSequencer

#endif /*  CENV_H_ */