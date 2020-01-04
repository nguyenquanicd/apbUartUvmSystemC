//--------------------------------------
//Project:  The UVM SYSTEMC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: subscriber for reset from TX
//Author:   Le Hoang Van
//Page:     VLSI Technology
//--------------------------------------

#ifndef RESETFRMTX_SUBCRIBER_H_
#define RESETFRMTX_SUBCRIBER_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

class resetfrmTX_subscriber : public uvm::uvm_subscriber<bool>
{
 public:
  resetfrmTX_subscriber( uvm::uvm_component_name name );

  UVM_COMPONENT_UTILS(resetfrmTX_subscriber);

  virtual void write(const bool reset);
};

#endif

