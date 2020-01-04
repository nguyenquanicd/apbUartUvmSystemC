//--------------------------------------
//Project:  The UVM SYSTEMC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: subscriber for monitor RX
//Author:   Le Hoang Van
//Page:     VLSI Technology
//--------------------------------------

#ifndef FRMMONITORRX_SUBSCRIBER_H_
#define FRMMONITORRX_SUBSCRIBER_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

#include "cApbTransaction.h"

class frmMonitorRX_subscriber : public uvm::uvm_subscriber<cApbTransaction>
{
 public:
  frmMonitorRX_subscriber( uvm::uvm_component_name name );

  UVM_COMPONENT_UTILS(frmMonitorRX_subscriber);

  virtual void write(const cApbTransaction& transaction);
};

#endif

