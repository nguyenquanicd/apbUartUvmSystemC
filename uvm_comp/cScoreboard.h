//--------------------------------------
//Project:  The UVM environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB scoreboard
//          - Compare data between data when write in data register and data when read from data register
//Authors:  Le Hoang Van
//Page:     VLSI Technology
//--------------------------------------

#ifndef CSCOREBOARD_H_
#define CSCOREBOARD_H_

#include <systemc>
#include <uvm>

#include "resetfrmTX_subscriber.h"
#include "frmMonitorTX_subscriber.h"
#include "frmMonitorRX_subscriber.h"
#include "cApbTransaction.h"

class cScoreboard : public uvm::uvm_scoreboard
{
 public:
  //Register to Factory
  UVM_COMPONENT_UTILS(cScoreboard);
  
  // Data queue for storing the transmit data
  // of UARTs
  std::queue<int> queueTransTX;
  std::queue<int> queueTransRX;
  // Compared data
  int queueCompTX; //from queueCompTX
  int queueCompRX; //from queueCompRX
  // UART-TX and UART-RX enable status
  bool uartEnTX;
  bool uartEnRX;
  //Reset flag
  bool rst_flg;
  
  // string format
  unsigned int transfer_data;
  char char_string[1024];
  std::string info;
  std::string warning;
  std::string error;
  
  //Implement ports which receive the data sent from Monitor
  uvm::uvm_analysis_export<bool> resetfrmTX_listener_imp;
  uvm::uvm_analysis_export<cApbTransaction> frmMonitorTX_listener_imp;
  uvm::uvm_analysis_export<cApbTransaction> frmMonitorRX_listener_imp;

  resetfrmTX_subscriber* resetfrmTX_listener;
  frmMonitorTX_subscriber* frmMonitorTX_listener;
  frmMonitorRX_subscriber* frmMonitorRX_listener;
  
  //declare the constructor for class, assign the initial value for class
  cScoreboard( uvm::uvm_component_name name ) : uvm::uvm_scoreboard( name )
  {
  }
  
  void build_phase(uvm::uvm_phase& phase)
  {
    uvm::uvm_scoreboard::build_phase(phase);

    uvm::uvm_config_db<uvm_object*>::set(this, "resetfrmTX_listener", "coScoreboard", this);
    uvm::uvm_config_db<uvm_object*>::set(this, "frmMonitorTX_listener", "coScoreboard", this);
    uvm::uvm_config_db<uvm_object*>::set(this, "frmMonitorRX_listener", "coScoreboard", this);
    
    resetfrmTX_listener = resetfrmTX_subscriber::type_id::create("resetfrmTX_listener", this);
    assert(resetfrmTX_listener);

    frmMonitorTX_listener = frmMonitorTX_subscriber::type_id::create("frmMonitorTX_listener", this);
    assert(frmMonitorTX_listener);
    
    frmMonitorRX_listener = frmMonitorRX_subscriber::type_id::create("frmMonitorRX_listener", this);
    assert(frmMonitorRX_listener);
  }

  void connect_phase(uvm::uvm_phase& phase)
  {
    resetfrmTX_listener_imp.connect(resetfrmTX_listener->analysis_export);
    frmMonitorTX_listener_imp.connect(frmMonitorTX_listener->analysis_export);
    frmMonitorRX_listener_imp.connect(frmMonitorRX_listener->analysis_export);
  }

  //Check the reset status
  void write_resetfrmTX(const bool preset_n)
  {
		if (!preset_n) {
		  rst_flg = 0b1;
      sprintf(char_string, "[%s] preset_n signal is acting", sc_time_stamp().to_string().c_str());
      info = char_string;
      UVM_INFO("SB RESET", info, uvm::UVM_LOW);
		} else {
		  rst_flg = 0b0;
    }
  }

  void write_frmMonitorTX(const cApbTransaction& TransOnTX)
  {
    transfer_data = TransOnTX.prdata;
		if (rst_flg == 0) {
      //-------------------------------------
      //Store transmit data to queue
      //-------------------------------------
		  // Update the enable status
		  if (TransOnTX.pwrite && (TransOnTX.paddr.range(15,0) == 0x4)) {
		      uartEnTX = TransOnTX.pwdata[0];
		  }
      // Store transmit data to queues when UART is enabled
      // Only store 8 LSB bits, other MSB bits are mapped to 0
		  else if (TransOnTX.pwrite && (TransOnTX.paddr.range(15,0) == 0xC) && uartEnTX) {
		      queueTransTX.push((TransOnTX.pwdata & 0xff));
		  }
      //-------------------------------------
      //Compare received data on UART-TX with queueTransRX on UART-RX
      //-------------------------------------
      else if (!TransOnTX.pwrite && (TransOnTX.paddr.range(15,0) == 0xC) && uartEnTX) {
				//Get the transmitted data from queueCompRX
        queueCompRX = queueTransRX.front();
        //Compare the read data on UART-TX and transmitted data from UART-RX
        //Only compare 8 LSB bits
		    if ((TransOnTX.prdata & 0xff) == queueCompRX) {
          sprintf(char_string, "[%s] SUCCESS on UART-TX: transfer data = %u, queueTransRX size = %d", sc_time_stamp().to_string().c_str(), transfer_data, queueTransRX.size());
          info = char_string;
				  UVM_INFO("SB INFO", info, uvm::UVM_LOW);
				} else {
          sprintf(char_string, "[%s] FAIL on UART-TX: read data = %u, expected data =%u, queueTransRX size = %d", sc_time_stamp().to_string().c_str(), transfer_data, queueCompRX, queueTransRX.size());
          error = char_string;
		      UVM_ERROR("SB ERROR", error);
        }
        //Delete queue
		    if (queueTransRX.size() != 0) { 
				  queueTransRX.pop();
        } else {
          UVM_WARNING("SB UNFINISH-TX", "Read data but do NOT have any transmited data");
        }
		  }
    } else {
      //Delete all entries of queue if reset is acting
      //while (!queueTransTX.empty()) queueTransTX.pop();
      queueTransTX = std::queue<int>();
      //queueTransTX = {};
      
      //Clear UART-TX enable
		  uartEnTX = 0b0;
		}
  }

  void write_frmMonitorRX(const cApbTransaction& TransOnRX)
  {
    transfer_data = TransOnRX.prdata;
    if (rst_flg == 0) {
      //-------------------------------------
      //Store transmit data to queue
      //-------------------------------------
		  // Update the enable status
		  if (TransOnRX.pwrite && (TransOnRX.paddr.range(15,0) == 0x4)) {
		      uartEnRX = TransOnRX.pwdata[0];
		  }
      // Store transmit data to queues when UART is enabled
      // Only store 8 LSB bits, other MSB bits are mapped to 0
		  else if (TransOnRX.pwrite && (TransOnRX.paddr.range(15,0) == 0xC) && uartEnRX) {
		      queueTransRX.push((TransOnRX.pwdata & 0xff));
		  }
      //-------------------------------------
      //Compare received data on UART-RX with queueTransTX on UART-TX
      //-------------------------------------
      else if (!TransOnRX.pwrite && (TransOnRX.paddr.range(15,0) == 0xC) && uartEnRX) {
				//Get the transmitted data from queueCompTX
        queueCompRX = queueTransTX.front();
        //Compare the read data on UART-RX and transmitted data from UART-TX
        //Only compare 8 LSB bits
		    if ((TransOnRX.prdata & 0xff) == queueCompRX) {
          sprintf(char_string, "[%s] SUCCESS on UART-RX: transfer data = %u, queueTransTX size = %d", sc_time_stamp().to_string().c_str(), transfer_data, queueTransTX.size());
          info = char_string;
          UVM_INFO("SB INFO", info, uvm::UVM_LOW);
				} else {
          sprintf(char_string, "[%s] FAIL on UART-RX: read data = %u, expected data =%u, queueTransTX size = %d", sc_time_stamp().to_string().c_str(), transfer_data, queueCompTX, queueTransTX.size());
          error = char_string;
		      UVM_ERROR("SB ERROR", error);
        }
        //Delete queue
		    if (queueTransTX.size() != 0) { 
				  queueTransTX.pop();
        } else {
          UVM_WARNING("SB UNFINISH-RX", "Read data but do NOT have any transmited data");
        }
		  }
	  } else {
      //Delete all entries of queue if reset is acting
      //while (!queueTransRX.empty()) queueTransRX.pop();
      queueTransRX = std::queue<int>();
      //queueTransRX = {};
      
      //Clear UART-RX enable
		  uartEnRX = 0b0;
		}
  }
  
  void report_phase(uvm::uvm_phase& phase)
  {
    //
	  if (queueTransTX.size() != 0) {
      sprintf(char_string, "UART-TX: Queue is not empty, pending data: %d", queueTransTX.size());
      warning = char_string;
	    UVM_WARNING("SB UNFINISH-TX", warning);
		}
    //
    if (queueTransRX.size() != 0) {
      sprintf(char_string, "UART-RX: Queue is not empty, pending data: %d", queueTransRX.size());
      warning = char_string;
	    UVM_WARNING("SB UNFINISH-RX", warning);
		}
  }
};

#endif

