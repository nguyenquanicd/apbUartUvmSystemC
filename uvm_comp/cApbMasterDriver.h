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
            }
        }
        
        void convert_seq2apb(REQ& user_req){

            if(user_req.apbSeqEn){
                
                if(user_req.apbConEn){
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
                    std::cout << "DECMN BUG " << uart_vifApbMaster->prdata.read() << std::endl;
                }
                
                wait(uart_vifApbMaster->pclk.posedge_event());
                uart_vifApbMaster->penable.write(1);
                wait(uart_vifApbMaster->pclk.posedge_event());
                user_req.pslverr = uart_vifApbMaster->pslverr.read();
                if(uart_vifApbMaster->psel && uart_vifApbMaster->penable && uart_vifApbMaster->pready){
                        uart_vifApbMaster->psel = 0;
                        uart_vifApbMaster->penable = 0;
                }         
            } else {
                uart_vifApbMaster->psel = 0;
                uart_vifApbMaster->penable = 0;
            }
//            sc_core::wait(1, sc_core::SC_NS);
        }
        
};   
#endif /* CAPBUARTDRIVER_H_ */