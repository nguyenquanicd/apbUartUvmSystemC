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
if(WriteSeq){ \
   WriteSeq->wdata = data;\
   WriteSeq->addr = address;\
} else { \
WriteSeq = new cApbWriteSequence<cApbTransaction>("cApbMasterWriteSeq", address, data);\
} \
WriteSeq->start(p_sequencer->coApbMasterAgentTx->coApbMasterSequencer, this);\
}

#define ApbWriteRandTX(address) \
{\
if(WriteSeq) {\
    writeSeq->addr = address;\
    WriteSeq->random();\
} else {\
WriteSeq = new cApbWriteSequence<cApbTransaction>("cApbMasterWriteSeq", address);\
}\
WriteSeq->start(p_sequencer->coApbMasterAgentTx->coApbMasterSequencer, this);\
}

#define ApbReadTX(address, data, umask) \
{\
if(ReadSeqTX){\
   ReadSeqTX->addr  = address;\
   ReadSeqTX->expData = data;\
   ReadSeqTX->mask = umask;\
} else {\
ReadSeqTX = new cApbReadSequence<cApbTransaction>("cApbMasterReadSeq", address, data, umask);\
}\
ReadSeqTX->start(p_sequencer->coApbMasterAgentTx->coApbMasterSequencer, this);\
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
if(ReadSeqRX){\
   ReadSeqRX->addr  = address;\
   ReadSeqRX->expData = data;\
   ReadSeqRX->mask = umask;\
} else {\
ReadSeqRX = new cApbReadSequence<cApbTransaction>("cApbMasterReadSeq" , address, data, umask);\
}\
ReadSeqRX->start(p_sequencer->coApbMasterAgentRx->coApbMasterSequencer, this);\
}

#define ApbReadWoCmprRX(address, umask) \
{\
if(ReadWoComprSeq) {\
  ReadWoComprSeq->addr = address;\
  ReadWoComprSeq->mask = umask;\
} else {\
 ReadWoComprSeq = new cApbReadWoCmprSequence<cApbTransaction>\
           ("cApbReadWoCmprSequence", address, umask);\
}\
ReadWoComprSeq->start(p_sequencer->coApbMasterAgentRx->coApbMasterSequencer, this);\
}
#endif /* MACRO_H_ */