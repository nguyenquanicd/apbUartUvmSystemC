//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

#ifndef CAPBUARTSEQUENCE_H_
#define CAPBUARTSEQUENCE_H_

#include <scv.h>
#include <systemc>
#include <tlm.h>
#include <uvm>

#include "cApbUartSequencer.h"


struct package{
      //bool conEn;
      //sc_uint<32> addr;
      sc_dt::sc_uint<32> data;
      //sc_uint<4>  be;
};
  
  SCV_EXTENSIONS(package)
{
      public:
        scv_extensions<sc_dt::sc_uint<32> > data;
        SCV_EXTENSIONS_CTOR(package)
        {
            SCV_FIELD(data);
        }
};

template <typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>
class cApbUartSequence : public uvm::uvm_sequence<REQ,RSP>
{
 public:
  cApbUartSequence( const std::string& name ) : uvm::uvm_sequence<REQ,RSP>( name )
  {
    std::cout << sc_core::sc_time_stamp() << ": constructor " << name << std::endl;
  } 
   
  UVM_OBJECT_PARAM_UTILS(cApbUartSequence<REQ,RSP>);
  UVM_DECLARE_P_SEQUENCER(cApbUartSequencer<REQ>);
  
  void body()
  {
    REQ* req;
    //RSP* rsp;
    
    scv_smart_ptr<package> packageSmrPtr("packageSmrPtr");
    
    UVM_INFO(this->get_name(), "Starting sequence ", uvm::UVM_MEDIUM);
    for(int i = 5; i < 10; i++)
    {
      req = new REQ();
      //rsp = new RSP();
      //req->pwdata = i;
      packageSmrPtr->data.next();
      //req->pwdata.write() = i;
      std::cout << sc_core::sc_time_stamp() << ": " << this->get_full_name() << " Get random value " << i << std::endl;
      req->apbSeqEn = 1;
      req->pwdata   = packageSmrPtr->data;
      std::cout << sc_core::sc_time_stamp() << " Start item " << i << std::endl;
      this->start_item(req);

      std::cout << sc_core::sc_time_stamp() << " Finish item" << i << std::endl;
      this->finish_item(req);

      //this->get_response(rsp);
    }
    UVM_INFO(this->get_name(), "Finishing sequence ", uvm::UVM_MEDIUM);
  }

};

#endif /* SEQUENCE_H_ */