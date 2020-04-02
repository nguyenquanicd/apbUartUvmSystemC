//--------------------------------------
//Project:  The UVM SYSTEMC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: subscriber for monitor RX
//Author:   Le Hoang Van
//Page:     VLSI Technology
//--------------------------------------

#include <systemc>
#include <tlm.h>
#include <uvm>

#include "frmMonitorRX_subscriber.h"
#include "cApbTransaction.h"
#include "cScoreboard.h"

using namespace uvm;
using namespace sc_core;

frmMonitorRX_subscriber::frmMonitorRX_subscriber( uvm_component_name name ) : uvm_subscriber<cApbTransaction>( name )
{
}

void frmMonitorRX_subscriber::write(const cApbTransaction& transaction)
{
  uvm_object* obj;
  cScoreboard* coScoreboard;

  uvm::uvm_config_db<uvm_object*>::get(this, "", "coScoreboard", obj);
  
  coScoreboard = dynamic_cast<cScoreboard*>(obj);
  coScoreboard->write_frmMonitorRX(transaction);
}

