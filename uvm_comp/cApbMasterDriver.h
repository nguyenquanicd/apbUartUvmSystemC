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
      //1. Declare the virtual interface
        ifApbMaster* uart_vifApbMaster;   
      //2. Class constructor with argunemt name
      //3. Call parent class uvm_driver with data type REQ
        cApbMasterDriver(uvm::uvm_component_name name) : uvm::uvm_driver<REQ>(name){}        
      //3. Register to the factory
      //`uvm_component_utils is for parameterized classes         
        UVM_COMPONENT_PARAM_UTILS(cApbMasterDriver<REQ>);
      //4. Build phase
        // - uvm::uvm_driver<REQ>::build_phase(phase) is called and executed first
        // - Configure the component before creating it
        // - Create the UVM component
        void build_phase(uvm::uvm_phase& phase)
        {
            uvm::uvm_driver<REQ>::build_phase(phase);
            if(!uvm::uvm_config_db<ifApbMaster*>::get(this,"*","vifApbMaster",uart_vifApbMaster))
                UVM_FATAL(this->name(), "Virtual interface not defined! Simulation aborted!");
        }
        //5. Run phase
        //Call 2 tasks for parallel execution 
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
                this->seq_item_port->item_done(req);
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
                std::cout << "uart_vifApbMaster->pwrite.write(user_req.pwrite) " << user_req.pwrite <<std::endl;                       
                if(user_req.pwrite){
                    uart_vifApbMaster->pwdata.write(user_req.pwdata);
                }                
                wait(uart_vifApbMaster->pclk.posedge_event());
                uart_vifApbMaster->penable.write(1);
                if(!user_req.pwrite && uart_vifApbMaster->pready) {
                    user_req.prdata = uart_vifApbMaster->prdata.read();
                    std::cout << "uart_vifApbMaster->prdata.read() " << uart_vifApbMaster->prdata.read() <<std::endl;
                }                
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
        }
        
};   
#endif /* CAPBUARTDRIVER_H_ */