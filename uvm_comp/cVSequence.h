//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: Common sequences help create the user sequences easily
//  - User adds more the common sequences in this file
//Authors:   Truong Cong Hoang Viet
//Page:     VLSI Technology
//--------------------------------------

//--------------------------------------
//Write sequence
//--------------------------------------

#include <systemc>
#include <tlm.h>
#include <uvm>
#include "macro.h"
#include "cCommonSequence.h"
#include "cApbTransaction.h"

class cApbUartVirSequence: public uvm::uvm_sequence<>
{
    public:
        cApbWriteSequence<cApbTransaction>* WriteSeq;
        cApbReadSequence<cApbTransaction>* ReadSeq;
        
        cApbUartVirSequence(const std::string& name = "cApbUartVirSequence") : uvm_sequence<>(name){
        }
        ~cApbUartVirSequence(){
            delete WriteSeq;
            delete ReadSeq;
        }       
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
            sc_core::wait(50,SC_NS);
            ApbWriteTX(0x8,0x82);
            //ApbWriteRandTX(0x08);
            ApbReadTX(0x08,0x82,0xFF);
            
            ApbWriteTX(0x4,0x23);
            ApbReadTX(0x4,0x23,0xFF);
            
            ApbWriteRX(0x8,0x4B);
            ApbReadRX(0x8,0x4B,0xFF);
            
            ApbWriteRX(0x0,0x8);
            ApbReadRX(0x0,0x8,0xFF);            
            sc_core::wait(50,SC_NS);
            UVM_INFO(this->get_name(), "Sequence finished here", uvm::UVM_NONE);
            sc_core::sc_stop();
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
            