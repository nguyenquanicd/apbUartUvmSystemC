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


class cApbUartReadSeq : public uvm::uvm_sequence<REQ,RSP>
{

   public:
    cApbUartReadSeq(const std::string &name) : uvm::uvm_sequence<REQ,RSP>(name){}
    `UVM_OBJECT_PARAM_UTILS(cApbUartReadSeq);
    `UVM_DECLARE_P_SEQUENCER(cApbUartSequencer);
   REQ *req;

};

#endif /* SEQUENCE_H_ */