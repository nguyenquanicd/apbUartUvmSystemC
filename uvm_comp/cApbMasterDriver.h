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
class cApbMasterDriver : public uvm::uvm_driver<REQ>
{
    public:
        ifApbMaster* uart_vifApbMaster; //component
 
        cApbMasterDriver(uvm::uvm_component_name name) : uvm::uvm_driver<REQ>(name)
        {}
        
        UVM_COMPONENT_PARAM_UTILS(cApbMasterDriver<REQ>);
        
        void build_phase(uvm::uvm_phase& phase)
        {
            uvm::uvm_driver<REQ>::build_phase(phase);
            if(!uvm::uvm_config_db<ifApbMaster*>::get(this,"*","vifApbMaster",uart_vifApbMaster))
                UVM_FATAL(this->name(), "Virtual interface not defined! Simulation aborted!");
        }
        
        void run_phase(uvm::uvm_phase& phase){
            std::cout << sc_core::sc_time_stamp() << ": " << this->name() << " " << phase.get_name() << "..." << std::endl;              
            SC_FORK
                sc_core::sc_spawn(sc_bind(&cApbMasterDriver::reset_all, this)),         
                sc_core::sc_spawn(sc_bind(&cApbMasterDriver::get_seq_and_drive, this)) 
            SC_JOIN 
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
                this->seq_item_port->get_next_item(req);
                convert_seq2apb(req);
                this->seq_item_port->item_done();
               std::cout << sc_time_stamp() << "DECMN BUG4  " << req.prdata << std::endl;
               std::cout << sc_time_stamp() << "DECMN BUG4  " << &req << std::endl;
            }
        }
        
        void convert_seq2apb(REQ &user_req){

            if(user_req.apbSeqEn){
                
                if(user_req.apbConEn == 0){
                    wait(uart_vifApbMaster->pclk.posedge_event());                     
                }
         
                uart_vifApbMaster->psel.write(1);
                uart_vifApbMaster->paddr.write(user_req.paddr);
                uart_vifApbMaster->pwrite.write(user_req.pwrite);
                uart_vifApbMaster->pstrb.write(user_req.pstrb); 
                if(user_req.pwrite){
                    uart_vifApbMaster->pwdata.write(user_req.pwdata);
                } else {
                    user_req.prdata = uart_vifApbMaster->prdata.read();
                    std::cout << sc_time_stamp() <<" DECMN BUG2 " << user_req.prdata << std::endl;
                    std::cout << sc_time_stamp() <<" DECMN BUG2 " << user_req << std::endl;
                    wait(1,SC_NS);
                }
                
                wait(uart_vifApbMaster->pclk.posedge_event());
                uart_vifApbMaster->penable.write(1);
                user_req.pslverr = uart_vifApbMaster->pslverr.read();
                wait(uart_vifApbMaster->pclk.posedge_event());                
                if(uart_vifApbMaster->psel && uart_vifApbMaster->penable && uart_vifApbMaster->pready){
                        uart_vifApbMaster->psel = 0;
                        uart_vifApbMaster->penable = 0;
                }           
            } else {
                uart_vifApbMaster->psel = 0;
                uart_vifApbMaster->penable = 0;
            }
//            sc_core::wait(1, sc_core::SC_NS);
            std::cout << sc_time_stamp() << "DECMN BUG3  " << uart_vifApbMaster->prdata.read() << std::endl;
            
        }
        
};   
#endif /* CAPBUARTDRIVER_H_ */