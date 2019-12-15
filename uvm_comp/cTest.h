//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

#ifndef CTEST_H_
#define CTEST_H_

#include <scv.h>
#include <systemc>
#include <tlm.h>
#include <uvm>

#include "cEnv.h"
#include "cApbUartVirSequence.h"


///////
class cTest : public uvm::uvm_test
{
    public:
        cEnv *coEnv;
        cApbUartVirSequence *coVSequence;
        cTest(uvm::uvm_component_name name) : uvm::uvm_test(name){}
        UVM_COMPONENT_UTILS(cTest);
        
        void build_phase(uvm::uvm_phase& phase){
            uvm::uvm_test::build_phase(phase);
            coEnv = cEnv::type_id::create("coEnv",this);
            coVSequence = cApbUartVirSequence::type_id::create("coVSequence", this);
            //uvm::uvm_config_db<uvm::uvm_object_wrapper*>::set(this,
            //"coEnv.coVSequencer.run_phase",
            //"default_sequence",cApbUartVirSequence::type_id::get());           
        }
        
        void run_phase(uvm::uvm_phase& phase){
            UVM_INFO(get_name(), "** UVM TEST STARTED **", uvm::UVM_NONE);
            uvm::uvm_test::run_phase(phase);
            phase.raise_objection(this);
            SC_FORK
              sc_core::sc_spawn(sc_bind(&cTest::start_sequence, this)), 
              sc_core::sc_spawn(sc_bind(&cTest::time_out, this))
            SC_JOIN
            phase.drop_objection(this);
        }
        
        void report_phase(){
            UVM_INFO(get_name(), "** UVM TEST ENDED **", uvm::UVM_NONE);
        }
        
        void start_sequence(){
            coVSequence->start(coEnv->coVSequencer, NULL);
        }
        
        void time_out(){
            UVM_WARNING("CTEST_H_","TIMEOUT TIMEOUT TIMEOUT");
        }
        

}; // class cTest

#endif /*  CTEST_H_ */