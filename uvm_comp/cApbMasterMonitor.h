//--------------------------------------
//Project:  The UVM SYSTEMC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: Monitor
//Author:   Le Hoang Van
//Page:     VLSI Technology
//--------------------------------------

#ifndef CAPBMASTERMONITOR_H_
#define CAPBMASTERMONITOR_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

#include "cApbTransaction.h"

class cApbMasterMonitor : public uvm::uvm_monitor
{
 public:
  //Register to Factory
  UVM_COMPONENT_UTILS(cApbMasterMonitor);
  
  //Declare analysis ports
  uvm::uvm_analysis_port<bool> preset_toScoreboard;
  uvm::uvm_analysis_port<cApbTransaction> ap_toScoreboard;
  
  //Declare the monitored interfaces
  ifApbMaster *vifApbMaster;
  ifInterrupt *vifInterrupt;
  
     // transaction
   cApbTransaction coApbTransaction;

   //Detect interrupt toggle
   //Internal variables for vifInterrupt
   sc_uint<5> ifEn;
   #ifdef INTERRUPT_COM
   sc_uint<1> ifSta;
   bool ctrl_if;
   #else
   sc_uint<5> ifSta;
   bool ctrl_tif;
   bool ctrl_rif;
   bool ctrl_pif;
   bool ctrl_oif;  
   bool ctrl_fif;
   #endif
    
    //Internal variables for vifApbMaster
    bool preset_n;
    bool psel;
    bool penable;
    bool pready;
    bool pwrite;
    sc_uint<32> paddr;
    sc_uint<32> pwdata;
    sc_uint<32> prdata;
    sc_uint<4>  pstrb;
    
    // string format
    char char_string[1024];
    std::string warning;
  
  //Constructor
  cApbMasterMonitor(uvm::uvm_component_name name)
  : uvm_monitor(name),
    preset_toScoreboard("preset_toScoreboard"),
    ap_toScoreboard("ap_toScoreboard"),
    vifApbMaster(0),
    vifInterrupt(0)
  {}

  void build_phase(uvm::uvm_phase& phase)
  {
    uvm::uvm_monitor::build_phase(phase);
    
    //Check the APB connection
    if (!uvm::uvm_config_db<ifApbMaster*>::get(this, "*", "vifApbMaster", vifApbMaster))
      UVM_ERROR("cApbMasterDriver", "Can NOT get vifApbMaster!!!");
    
    //Check the interrupt connection
    if (!uvm::uvm_config_db<ifInterrupt*>::get(this, "*", "vifInterrupt", vifInterrupt))
      UVM_ERROR("cVSequencer", "Can NOT get vifInterrupt!!!");
    
    //Create objects and analysis ports
    //systemc declare in run_phase ??
  }

  void run_phase( uvm::uvm_phase& phase )
  { 
    while (true) {
      // detect posedge
      sc_core::wait( vifApbMaster->pclk.default_event() );
      if (vifApbMaster->pclk.read() == true) {
        // get value from interface
        read_interface();
        //Detect transaction on APB interface and send to Scoreboard
		    collect_data();
        //Setect reset status and send to Scoreboard
		    detect_reset();
        //Monitor interrupt enable
        monitor_ifEn();
        //Detect interrupt
        detect_intf();
      }
    }
  }
  // -> send the transaction to analysis port ap_toScoreboard
  void read_interface()
  {
    // get value from vifApbMaster
    preset_n = vifApbMaster->preset_n.read();
    psel     = vifApbMaster->psel.read();
    penable  = vifApbMaster->penable.read();
    pready   = vifApbMaster->pready.read();
    pwrite   = vifApbMaster->pwrite.read();
    paddr    = vifApbMaster->paddr.read();
    pwdata   = vifApbMaster->pwdata.read();
    prdata   = vifApbMaster->prdata.read();
    pstrb    = vifApbMaster->pstrb.read();
    // get value from vifInterrupt
    #ifdef INTERRUPT_COM
    ctrl_if  = vifInterrupt->ctrl_if.read();
    #else
    ctrl_rif = vifInterrupt->ctrl_rif.read();
    ctrl_pif = vifInterrupt->ctrl_pif.read();
    ctrl_oif = vifInterrupt->ctrl_oif.read();
    ctrl_fif = vifInterrupt->ctrl_fif.read();
    #endif
  }
  
	//On each clock, detect a valid transaction
  // -> get the valid transaction
  // -> send the transaction to analysis port ap_toScoreboard
  void collect_data()
  {
    if (psel && penable && pready) {
      //Get APB transaction on APB interface
      coApbTransaction.paddr  = paddr;
      coApbTransaction.pstrb  = pstrb; 
      coApbTransaction.pwrite = pwrite;
      coApbTransaction.pwdata = pwdata;
      coApbTransaction.prdata = prdata;
      //Send the transaction to analysis port which is connected to Scoreboard
      ap_toScoreboard.write(coApbTransaction);
    }
  }
  
	//On each clock, send the reset status to Scoreboard
  //via analysis port preset_toScoreboard
  void detect_reset()
  {
    preset_toScoreboard.write(preset_n);
  }
  
  // Update interrupt enable
  void monitor_ifEn()
  {
    if (psel && penable && pready && pwrite && (paddr.range(15,0) == 0x10)) {
		  ifEn = pwdata.range(4,0);
		}
  }
  
  // Check the interrupt signals
  void detect_intf()
  {
    #ifdef INTERRUPT_COM
    if (ctrl_if) {
      if (!ifSta) {
        if (ifEn.or_reduce() == false) {
          UVM_ERROR(this->get_name(), "INTERRUPT is toggled but NOT have any interrupt enable");
        } else {          
          sprintf(char_string, "NTERRUPT is toggled when interrupt enable is %d", ifEn);
          warning = char_string;
          UVM_WARNING(this->get_name(), warning);
        }
        ifSta = 0b1;
      }
    } else {
        ifSta = 0b0;
    }
    #else
    if (ctrl_tif) {
      if (!ifSta[0]) {
        if (!ifEn[0]) {
          UVM_ERROR(this->get_name(), "Transmit interrupt is toggled but it is not enable");
        } else {
          UVM_WARNING(this->get_name(), "Transmit interrupt is toggled because TXFIFO is empty");
        }
      }
      ifSta[0] = 0b1;
    } else {
      ifSta[0] = 0b0;
    }
    //
    if (ctrl_rif) {
      if (!ifSta[1]) {
        if (!ifEn[1]) {
          UVM_ERROR(this->get_name(), "Receiver interrupt is toggled but it is not enable");
        } else {
          UVM_WARNING(this->get_name(), "Receiver interrupt is toggled because RXFIFO is full");
        }
      }
      ifSta[1] = 0b1;
    } else {
      ifSta[1] = 0b0;
    }
    //
    if (ctrl_oif) {
      if (!ifSta[2]) {
        if (!ifEn[2]) {
          UVM_ERROR(this->get_name(), "Overflow interrupt is toggled but it is not enable");
        } else {
          UVM_WARNING(this->get_name(), "Overflow interrupt is toggled because RXFIFO is full but a new UART frame is received");
        } 
      }
      ifSta[2] = 0b1;
    } else {
      ifSta[2] = 0b0;
    }
    //
    if (ctrl_pif) {
      if (!ifSta[3]) {
        if (!ifEn[3]) {
          UVM_ERROR(this->get_name(), "Parity interrupt is toggled but it is not enable");
        } else {
          UVM_WARNING(this->get_name(), "Parity interrupt is toggled because parity bit is wrong");
        } 
      }
      ifSta[3] = 0b1;
    } else {     
      ifSta[3] = 0b0;
    }
    //
    if (ctrl_fif) {
      if (!ifSta[4]) {
        if (!ifEn[4]) {
          UVM_ERROR(this->get_name(), "Frame error interrupt is toggled but it is not enable");
        } else {
          UVM_WARNING(this->get_name(), "Frame error interrupt is toggled because STOP bit is 0");
        }  
      }
      ifSta[4] = 0b1;
    } else {
      ifSta[4] = 0b0;
    }
    #endif
  }
};

#endif

