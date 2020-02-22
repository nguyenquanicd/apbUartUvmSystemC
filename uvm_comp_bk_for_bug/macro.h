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
WriteSeq->start(p_sequencer->coApbUartAgentTx->coApbUartSequencer, NULL);\
}

#define ApbWriteRandTX(address) \
{\
WriteSeq = new cApbWriteSequence<cApbTransaction>("cApbMasterWriteSeq", address);\
WriteSeq->start(p_sequencer->coApbUartAgentTx->coApbUartSequencer, NULL);\
}

#define ApbReadTX(address, data, umask) \
{\
ReadSeq = new cApbReadSequence<cApbTransaction>("cApbMasterReadSeq", address, data, umask);\
ReadSeq->start(p_sequencer->coApbUartAgentTx->coApbUartSequencer, NULL);\
}

#define ApbWriteRX(address, data) \
{\
WriteSeq = new cApbWriteSequence<cApbTransaction>("cApbMasterWriteSeq", address, data);\
WriteSeq->start(p_sequencer->coApbUartAgentRx->coApbUartSequencer, NULL);\
}

#define ApbReadRX(address, data, umask) \
{\
ReadSeq = new cApbReadSequence<cApbTransaction>("cApbMasterReadSeq" , address, data, umask);\
ReadSeq->start(p_sequencer->coApbUartAgentRx->coApbUartSequencer, NULL);\
}
#endif /* MACRO_H_ */