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
            std::cout << sc_core::sc_time_stamp() << ": " << this->name() << " " << phase.get_name() << "..." << std::endl;              
            SC_FORK
                sc_core::sc_spawn(sc_bind(&cApbUartDriver::reset_all, this)),         
                sc_core::sc_spawn(sc_bind(&cApbUartDriver::get_seq_and_drive, this)) 
            SC_JOIN 
            //get_seq_and_drive();
        }
        
        void reset_all(){
           // This is to avoid hang up
           wait(uart_vifApbMaster->preset_n.negedge_event());
              uart_vifApbMaster->psel = 0;
              uart_vifApbMaster->penable = 0;                  
           while(true){
              if(uart_vifApbMaster->preset_n.negedge()){
               uart_vifApbMaster->psel = 0;
               uart_vifApbMaster->penable = 0;                    
              }               
           } 
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
              //std::cout << sc_core::sc_time_stamp()<<": "<< this->name() << " sending data " << user_req.apbSeqEn << std::endl;                
                wait(uart_vifApbMaster->pclk.posedge_event());          
                uart_vifApbMaster->psel.write(1);
                uart_vifApbMaster->paddr.write(user_req.paddr);
                uart_vifApbMaster->pwrite.write(user_req.pwrite);
                if(uart_vifApbMaster->pwrite.read()){
                    uart_vifApbMaster->pwdata.write(user_req.pwdata);
                } else {
                    uart_vifApbMaster->prdata.write(user_req.prdata);
                }
                uart_vifApbMaster->pstrb.write(user_req.pstrb);
                wait(uart_vifApbMaster->pclk.posedge_event());
                uart_vifApbMaster->penable.write(1);
                if(uart_vifApbMaster->psel || uart_vifApbMaster->penable || uart_vifApbMaster->pready){
                    if(uart_vifApbMaster->pclk.pesedgess()){
                        uart_vifApbMaster->psel = 0;
                        uart_vifApbMaster->penable = 0;
                    }
                }
              sc_core::wait(5, sc_core::SC_NS);          
            } 
            //sc_core::wait(1, sc_core::SC_NS);
        }
        
};   
#endif /* CAPBUARTDRIVER_H_ */