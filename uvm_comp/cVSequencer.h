//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

#ifndef CVSEQUENCER_H_
#define CVSEQUENCER_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

#include "cApbTransaction.h"
#include "cApbUartAgent.h"

///////
template<class REQ>
class cVSequencer : public uvm::uvm_sequencer<REQ>{
        public:
        cApbUartAgent* coApbUartAgentTx;
        //cApbUartAgent<cApbTransaction>* coApbUartAgentRx;
        
        UVM_COMPONENT_PARAM_UTILS(cVSequencer<REQ>)
        cVSequencer(uvm::uvm_component_name name) : uvm::uvm_sequencer<REQ>(name)
        {}
        //Instance

        //cApbUartScoreboard* cApbUartScoreboard;
        //Factory register
        //Constructor
        //Function
         void buid_phase(uvm::uvm_phase& phase){
             uvm::uvm_sequencer<REQ>::build_phase(phase);
         }

}; // class cVSequencer
#endif /* CVSEQUENCER_H_ */