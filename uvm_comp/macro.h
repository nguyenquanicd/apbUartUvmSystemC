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
{\
WriteSeq = new cApbWriteSequence<cApbTransaction>("cApbMasterWriteSeq", address, data);\
WriteSeq->start(p_sequencer->coApbMasterAgentTx->coApbMasterSequencer, this);\
}

#define ApbWriteRandTX(address) \
{\
WriteSeq = new cApbWriteSequence<cApbTransaction>("cApbMasterWriteSeq", address);\
WriteSeq->random();\
WriteSeq->start(p_sequencer->coApbMasterAgentTx->coApbMasterSequencer, this);\
}

#define ApbReadTX(address, data, umask) \
{\
ReadSeq = new cApbReadSequence<cApbTransaction>("cApbMasterReadSeq", address, data, umask);\
ReadSeq->start(p_sequencer->coApbMasterAgentTx->coApbMasterSequencer, this);\
}

#define ApbWriteRX(address, data) \
{\
if(WriteSeq){\
    WriteSeq->wdata = data;\
    WriteSeq->addr = address;\
} else {\
    WriteSeq = new cApbWriteSequence<cApbTransaction>("cApbMasterWriteSeq", address, data);\
}\
WriteSeq->start(p_sequencer->coApbMasterAgentRx->coApbMasterSequencer, this);\
}

#define ApbReadRX(address, data, umask) \
{\
ReadSeq = new cApbReadSequence<cApbTransaction>("cApbMasterReadSeq" , address, data, umask);\
ReadSeq->start(p_sequencer->coApbMasterAgentRx->coApbMasterSequencer, this);\
}

#define ApbReadWoCmprRX(address, expData, umask) \
{\
if(ReadWoComprSeq) {\
  ReadWoComprSeq->addr = address;\
  ReadWoComprSeq->exdata = expData;\
  ReadWoComprSeq->mask = umask;\
} else {\
 ReadWoComprSeq = new cApbReadWoCmprSequence<cApbTransaction>\
           ("cApbReadWoCmprSequence", address, expData, umask);\
}\
ReadWoComprSeq->start(p_sequencer->coApbMasterAgentRx->coApbMasterSequencer, this);\
}
#endif /* MACRO_H_ */