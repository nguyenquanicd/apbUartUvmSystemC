//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet
//Page:     VLSI Technology
//--------------------------------------

#ifndef COMMONSEQUENCE_H_
#define COMMONSEQUENCE_H_

#include <scv.h>
#include <systemc>
#include <tlm.h>
#include <uvm>
#include <string>

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
        scv_extensions<bool> apbConEn;
        scv_extensions<sc_dt::sc_uint<32> > paddr;
        scv_extensions<sc_dt::sc_uint<32> > pwdata;
        scv_extensions<sc_dt::sc_uint<4> > pstrb;
        //scv_extensions<bool> apbSeqEn;
        //scv_extensions<bool> apbConEn;
        //scv_extensions<unsigned int> apbDelay;
        SCV_EXTENSIONS_CTOR(package)
        {
            SCV_FIELD(apbConEn);
            SCV_FIELD(paddr);
            SCV_FIELD(pwdata);
            SCV_FIELD(pstrb);
            //SCV_FIELD(apbSeqEn);
            //SCV_FIELD(apbConEn);
            //SCV_FIELD(apbDelay);
        }
};

class  package_constraint : public scv_constraint_base 
{
    public:
        scv_smart_ptr<package> packageSmrPtr;
        SCV_CONSTRAINT_CTOR(package_constraint){
            SCV_CONSTRAINT(packageSmrPtr->apbConEn() == 0);
            SCV_CONSTRAINT(packageSmrPtr->pwdata() >= 0 && packageSmrPtr->pwdata() <= 0xFF);
            SCV_CONSTRAINT(packageSmrPtr->pstrb() == 0xF);
        }
};

template <typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>
class cApbWriteSequence : public uvm::uvm_sequence<REQ,RSP>
{
 public:
  bool conEn;
  //bool enableRandomization;
  sc_dt::sc_uint<32> addr;
  sc_dt::sc_uint<32> wdata;
  sc_dt::sc_uint<4>  strb;
  //package_constraint constraint("constraint");
  
  cApbWriteSequence(const std::string& name, sc_dt::sc_uint<32> address = 0x0, sc_dt::sc_uint<32>  data = 0x0) : uvm::uvm_sequence<REQ,RSP>( name )
  { 
    std::cout << sc_core::sc_time_stamp() << ": Construct sequence " << name << std::endl;
    addr = address;
    wdata = data;
  } 
  
  cApbWriteSequence(const std::string& name, sc_dt::sc_uint<32> address = 0x0) : uvm::uvm_sequence<REQ,RSP>( name )
  { 
    std::cout << sc_core::sc_time_stamp() << ": Construct sequence with random data " << name << std::endl;
    addr = address;
  } 
  
  ~cApbWriteSequence(){}
   
  UVM_OBJECT_PARAM_UTILS(cApbWriteSequence<REQ,RSP>);
  UVM_DECLARE_P_SEQUENCER(cApbUartSequencer<REQ>);
  
  void body()
  {    
    REQ* coApbTransaction; 
    package_constraint constraint("constraint");
    //scv_smart_ptr<package> packageSmrPtr("packageSmrPtr");   
    
    UVM_INFO(this->get_name(), "Starting write sequence ", uvm::UVM_MEDIUM);
      coApbTransaction = new REQ();
      constraint.packageSmrPtr->pwdata.next();
      constraint.packageSmrPtr->pstrb.next();       
      //if(enableRandomization){
      //coApbTransaction->pwdata = constraint.packageSmrPtr->pwdata;    
      //}
      
      //packageSmrPtr->apbConEn.next();
      //packageSmrPtr->pstrb.next();
      //packageSmrPtr->paddr.next();
      
      conEn = constraint.packageSmrPtr->apbConEn;
      wdata  = constraint.packageSmrPtr->pwdata;
      strb  = constraint.packageSmrPtr->pstrb;
      //addr  = constraint.packageSmrPtr->paddr;
      
      coApbTransaction->apbSeqEn = 1;     
      coApbTransaction->pwrite   = 1;
      coApbTransaction->paddr    = addr;      
      coApbTransaction->pstrb    = strb;
      coApbTransaction->pwdata   = wdata;
      coApbTransaction->apbConEn = conEn;
      std::cout << sc_core::sc_time_stamp() << " Start item " << std::endl;
      this->start_item(coApbTransaction);
      std::cout << sc_core::sc_time_stamp() << " Finish item" << std::endl;
      std::ostringstream str;
          str << "Address: '" << addr.to_string().c_str() << "' Data: '"
              << wdata.to_string().c_str() << "'";
      UVM_INFO("TRANSACTION INFO", str.str(), uvm::UVM_MEDIUM);      
      this->finish_item(coApbTransaction);
    UVM_INFO(this->get_name(), "Finishing sequence ", uvm::UVM_MEDIUM);
  }

};


template <typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>
class cApbReadSequence : public uvm::uvm_sequence<REQ,RSP>
{
 public:
  bool conEn;
  bool compareResult;
  sc_dt::sc_uint<32> mask;
  sc_dt::sc_uint<32> addr;
  sc_dt::sc_uint<32> expData;
  cApbReadSequence( const std::string& name = "cApbMasterReadSeq", sc_dt::sc_uint<32> address = 0x0, sc_dt::sc_uint<32> data = 0x0, sc_dt::sc_uint<32> umask = 0x0) : uvm::uvm_sequence<REQ,RSP>( name )
  {
    std::cout << sc_core::sc_time_stamp() << ": constructor " << name << std::endl;
    addr = address;
    expData = data;
    mask = umask;
  } 
  
  //~cApbReadSequence(){
  //}
   
  UVM_OBJECT_PARAM_UTILS(cApbReadSequence<REQ,RSP>);
  UVM_DECLARE_P_SEQUENCER(cApbUartSequencer<REQ>);
  void body()
  {    
    REQ* coApbTransaction;
    package_constraint constraint("constraint");    
    //scv_smart_ptr<package> packageSmrPtr("packageSmrPtr");   
    UVM_INFO(this->get_name(), "Starting read sequence ", uvm::UVM_MEDIUM);
      coApbTransaction = new REQ();
     
      //packageSmrPtr->paddr.next();     
      //packageSmrPtr->apbConEn.next();
      
      //addr  = packageSmrPtr->paddr;
      conEn = constraint.packageSmrPtr->apbConEn;
      
      coApbTransaction->pwrite   = 0;
      coApbTransaction->apbSeqEn = 1;
      coApbTransaction->paddr    = addr;      
      coApbTransaction->apbConEn = conEn;
      
      std::cout << sc_core::sc_time_stamp() << " Start item " << std::endl;
      this->start_item(coApbTransaction);
      std::cout << sc_core::sc_time_stamp() << " Finish item" << std::endl;
      this->finish_item(coApbTransaction);
    compareResult = (coApbTransaction->prdata ^ expData) & mask;
    cout << "mask " << mask << " compareResult " << compareResult << std::endl;
    if(compareResult){
        std::ostringstream str;
            str << "Address: '" << addr.to_string().c_str() << "' Expected data: '"
                << expData.to_string().c_str() << "'Actual data: '" << coApbTransaction->prdata.to_string().c_str()
                << "' Mask: '" << mask.to_string().c_str() << "'";
        UVM_ERROR("READ FAIL", str.str());
    } else {
        std::ostringstream str;
            str << "Address: '" << addr.to_string().c_str() << "' Expected data: '"
                << expData.to_string().c_str() << "'Actual data: '" << coApbTransaction->prdata.to_string().c_str()
                << "' Mask: '" << mask.to_string().c_str() << "'";
        UVM_INFO("TRANSACTION INFO", str.str(), uvm::UVM_MEDIUM);
        
    }
    UVM_INFO(this->get_name(), "Finishing sequence ", uvm::UVM_MEDIUM);
  }

};

#endif /* COMMONSEQUENCE_H_ */