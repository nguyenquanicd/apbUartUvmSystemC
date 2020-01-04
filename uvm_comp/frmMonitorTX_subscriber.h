//--------------------------------------
//Project:  The UVM SYSTEMC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: subscriber for monitor TX
//Author:   Le Hoang Van
//Page:     VLSI Technology
//--------------------------------------

#ifndef FRMMONITORTX_SUBSCRIBER_H_
#define FRMMONITORTX_SUBSCRIBER_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

#include "cApbTransaction.h"

class frmMonitorTX_subscriber : public uvm::uvm_subscriber<cApbTransaction>
{
 public:
  frmMonitorTX_subscriber( uvm::uvm_component_name name );

  UVM_COMPONENT_UTILS(frmMonitorTX_subscriber);

  virtual void write(const cApbTransaction& transaction);
};

#endif

