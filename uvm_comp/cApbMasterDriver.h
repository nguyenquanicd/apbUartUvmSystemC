//--------------------------------------
//Project: The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: ApbDriver
//Author: Truong Cong Hoang Viet
//Page:    VLSI Technology
//--------------------------------------

#ifndef CAPBUARTDRIVER_H_
#define CAPBUARTDRIVER_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

#include "ifDut.h"
#include "cApbTransaction.h"

template <class REQ>
class cApbUartDriver : public uvm::uvm_driver<REQ>
{
    public:
        ifApbUart* uart_vifApbMaster; //component
 
        cApbUartDriver(uvm::uvm_component_name name) : uvm::uvm_driver<REQ>(name)
        {}
        
        UVM_COMPONENT_PARAM_UTILS(cApbUartDriver<REQ>);
        
        void build_phase(uvm::uvm_phase& phase)
        {
            uvm::uvm_driver<REQ>::build_phase(phase);
            if(!uvm::uvm_config_db<ifApbUart*>::get(this,"*","vifApbMaster",uart_vifApbMaster))
                UVM_FATAL(this->name(), "Virtual interface not defined! Simulation aborted!");
        }
        
        void run_phase(uvm::uvm_phase& phase){
            //reset_all();
            //phase.raise_objection(this);
            std::cout << sc_core::sc_time_stamp() << ": " << this->name() << " " << phase.get_name() << "..." << std::endl;           
            get_seq_and_drive(); 
            //phase.drop_objection(this);
          
        }
        
        void get_seq_and_drive(){
            REQ req;//, rsp;
            while(true){
                std::cout << sc_time_stamp() <<"get_next_item "<< req.pwdata << std::endl; 
                this->seq_item_port->get_next_item(req);
                convert_seq2apb(req);
                std::cout << "item_done "<< req.pwdata << std::endl;
                this->seq_item_port->item_done();   
            }
        }
        
        void convert_seq2apb(const REQ& user_req){
            if(user_req.apbSeqEn){
              std::cout << sc_core::sc_time_stamp()<<": "<< this->name() << " sending data " << user_req.apbSeqEn << std::endl;
              if(user_req.apbSeqEn == 0){
                  wait(uart_vifApbMaster->pclk.posedge_event());
              }
              //sc_core::wait(5, sc_core::SC_NS);
              std::cout << sc_time_stamp() << " Ca quan que ne " << uart_vifApbMaster->pwdata <<  std::endl;
            } 
            //sc_core::wait(1, sc_core::SC_NS);
        }
        
};   
#endif /* CAPBUARTDRIVER_H_ */