//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

#ifndef CAPBTRANSACTION_H_
#define CAPBTRANSACTION_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

///////
class cApbTransaction : public uvm::uvm_sequence_item
{
    public:
      UVM_OBJECT_UTILS(cApbTransaction);
      
      cApbTransaction(const std::string& name = "cApbTransaction"){}
      ~cApbTransaction(){}
      
      virtual void do_print(const uvm::uvm_printer& printer) const {}
      virtual void do_pack(uvm::uvm_packer& p) const {}
      virtual void do_unpack(uvm::uvm_packer& p) {}
      virtual void do_copy(const uvm::uvm_object& rhs) {}
      virtual bool do_compare(const uvm_object& rhs, const uvm::uvm_comparer*) const {}
    
    public:  
      unsigned int APB_TRANSACTION_TIMEOUT = 100;
      //struct apbPackage{
       bool         pclk;
       bool         pwrite;
       sc_uint<32>  paddr;
       sc_dt::sc_uint<32>  pwdata;
       sc_uint<32>  pstrb;
       sc_uint<32>  prdata;
       bool         pslverr;
       bool         apbSeqEn;
       bool         apbConEn;
       unsigned int apbDelay;
       bool pready = 1;   
      //}
      

    void print_apb_seq(){
        UVM_INFO(get_name(),"Sequence start ...", uvm::UVM_LOW);
    }

}; // class cApbTransaction  

#endif /*  CAPBTRANSACTION_H_ */