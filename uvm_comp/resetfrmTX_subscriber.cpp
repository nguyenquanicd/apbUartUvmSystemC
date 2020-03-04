//--------------------------------------
//Project:  The UVM SYSTEMC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: subscriber for reset from TX
//Author:   Le Hoang Van
//Page:     VLSI Technology
//--------------------------------------

#include <systemc>
#include <tlm.h>
#include <uvm>

#include "resetfrmTX_subscriber.h"
#include "cScoreboard.h"

using namespace uvm;
using namespace sc_core;

resetfrmTX_subscriber::resetfrmTX_subscriber( uvm_component_name name ) : uvm_subscriber<bool>( name )
{
}

void resetfrmTX_subscriber::write(const bool& reset)
{
  uvm_object* obj;// = get_parrent();
  cScoreboard* coScoreboard;
    
  uvm::uvm_config_db<uvm_object*>::get(this, "", "coScoreboard", obj);

  coScoreboard = dynamic_cast<cScoreboard*>(obj);
  coScoreboard->write_resetfrmTX(reset);
}

