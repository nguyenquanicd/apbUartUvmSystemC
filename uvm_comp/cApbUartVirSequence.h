//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: Common sequences help create the user sequences easily
//  - User adds more the common sequences in this file
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

//--------------------------------------
//Write sequence
//--------------------------------------

#include <systemc>
#include <tlm.h>
#include <uvm>

#include "cApbUartSequence.h"
#include "cApbTransaction.h"

class cApbUartVirSequence: public uvm::uvm_sequence<>
{
    public:
        cApbUartSequence<cApbTransaction>* coApbUartSequence;
        
        cApbUartVirSequence(const std::string& name = "cApbUartVirSequence"):uvm_sequence<>(name){}
        
        UVM_OBJECT_UTILS(cApbUartVirSequence);
        UVM_DECLARE_P_SEQUENCER(cVSequencer<cApbTransaction>);
          
        //void pre_body()
        //{
        //    // raise objection if started as a root sequence
        //    if(this->starting_phase != NULL)
        //    this->starting_phase->raise_objection(this);
        //    std::cout << sc_core::sc_time_stamp() << " Cais DKM --------------- pre_body " << std::endl;
        //}
        
        void body(){
            
            UVM_INFO(this->get_name(), "Virtual sequence start here", uvm::UVM_NONE);
            UVM_DO_ON(coApbUartSequence,p_sequencer->coApbUartAgentTx->coApbUartSequencer)
            UVM_INFO(this->get_name(), "Sequence finished here", uvm::UVM_NONE);
            
        }
        
        //void post_body()
        //{
        //    std::cout << sc_core::sc_time_stamp() << " Cais DKM --------------- post_body " << std::endl;
        //    // drop objection if started as a root sequence
        //    if(this->starting_phase != NULL){
        //         std::cout << sc_core::sc_time_stamp() << " Cais starting_phase != " << std::endl;
        //         this->starting_phase->drop_objection(this);
        //    }
        //   
        //}

};       
            