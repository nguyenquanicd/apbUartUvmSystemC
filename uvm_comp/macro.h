//--------------------------------------
//Project:  The UVM-SystemC environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Function: APB sequence
// - Create the APB transaction
//Authors:   Truong Cong Hoang Viet
//Page:     VLSI Technology
//--------------------------------------

#ifndef MACRO_H_
#define MACRO_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

#define ApbWriteTX(address, data) \
UVM_DO_ON_WITH(WriteSeq, p_sequencer->coApbUartAgentTx->coApbUartSequencer, \
    {WriteSeq.conEn = 0; \
     WriteSeq.addr = address; \
     WriteSeq.wdata = data; \
     WriteSeq.strb = 0xF;})

#define ApbReadTX(address, data, umask) \
UVM_DO_ON_WITH(ReadSeq, p_sequencer->coApbUartAgentTx->coApbUartSequencer,\
    {ReadSeq.conEn = 0; \
     ReadSeq.addr = address; \
     ReadSeq.expData = data; \
     ReadSeq.mask = umask;} \
)

#define ApbWriteRX(address, data) \
UVM_DO_ON_WITH(ReadSeq, p_sequencer->coApbUartAgentRx->coApbUartSequencer,\
    {WriteSeq.conEn = 0; \
     WriteSeq.addr = address; \
     WriteSeq.wdata = data; \
     WriteSeq.strb = 0xF;} \
)

#define ApbReadRX(address, data, umask) \
UVM_DO_ON_WITH(ReadSeq, p_sequencer->coApbUartAgentRx->coApbUartSequencer,\
    {ReadSeq.conEn = 0; \
     ReadSeq.addr = address; \
     ReadSeq.expData = data; \
     ReadSeq.mask = umask;} \
)
#endif /* MACRO_H_ */