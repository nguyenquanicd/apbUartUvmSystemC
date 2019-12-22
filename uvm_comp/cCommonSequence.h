//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet
//Page:     VLSI Technology
//--------------------------------------

#ifndef CAPBUARTSEQUENCE_H_
#define CAPBUARTSEQUENCE_H_

#include <scv.h>
#include <systemc>
#include <tlm.h>
#include <uvm>

#include "cApbMasterSequencer.h"


struct package{
       bool         pwrite;
       sc_dt::sc_uint<32>  paddr;
       sc_dt::sc_uint<32>  pwdata;
       sc_dt::sc_uint<4>   pstrb;
       bool         apbSeqEn;
       bool         apbConEn;
       unsigned int apbDelay;
};
  
  SCV_EXTENSIONS(package)
{
      public:
        scv_extensions<bool> pwrite;
        scv_extensions<sc_dt::sc_uint<32> > paddr;
        scv_extensions<sc_dt::sc_uint<32> > pwdata;
        scv_extensions<sc_dt::sc_uint<4> > pstrb;
        //scv_extensions<bool> apbSeqEn;
        //scv_extensions<bool> apbConEn;
        //scv_extensions<unsigned int> apbDelay;
        SCV_EXTENSIONS_CTOR(package)
        {
            SCV_FIELD(pwrite);
            SCV_FIELD(paddr);
            SCV_FIELD(pwdata);
            SCV_FIELD(pstrb);
            //SCV_FIELD(apbSeqEn);
            //SCV_FIELD(apbConEn);
            //SCV_FIELD(apbDelay);
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
    
    scv_smart_ptr<package> packageSmrPtr("packageSmrPtr");
    
    UVM_INFO(this->get_name(), "Starting sequence ", uvm::UVM_MEDIUM);
    for(int i = 5; i < 10; i++)
    {
      req = new REQ();
      packageSmrPtr->pwdata.next();
      std::cout << sc_core::sc_time_stamp() << ": " << this->get_full_name() << " Get random value " << i << std::endl;
      req->pwrite = 1;
      req->paddr = 0;
      req->apbSeqEn = 1;
      req->pstrb = 15;
      req->pwdata   = packageSmrPtr->pwdata;
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