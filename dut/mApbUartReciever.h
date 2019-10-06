//--------------------------------------
//Project:  The UVM environemnt for UART (Universal Asynchronous Receiver Transmitter)
//Module:   mApbUartReciever
//Function: Receive the serial data follow UART protocol
//Author:   Truong Cong Hoang Viet
//Page:     VLSI Technology
//--------------------------------------
//
//MEMORY
//
#include "systemc.h"
#define IDLE_RX 0x0
#define CHECK_START 0x1
#define SHIFT_DATA 0x3

SC_MODULE(mApbUartReciever) {
	sc_in<bool>		   pClk;
	sc_in<bool>		   pResetN;	 
	sc_in<bool>		   ctrlEn;
	sc_in<bool>		   ctrlD9;
	sc_in<bool>		   ctrlEp;
	sc_in<bool>		   ctrlShiftRx;
	sc_in<bool>		   ctrlDataRd;
	sc_in<sc_uint<2> > ctrlRxt;
	sc_in<bool>		   uartRx;

	sc_out<bool>	   rxNe;
	sc_out<bool>	   rxBusy;

	sc_out<bool>	   rxRxf;

	sc_out<bool>	    rxOv;
	sc_out<bool>	    rxPe;
	sc_out<bool>	    rxFe;
	sc_out<sc_uint<8> > rxData; 

  sc_signal<bool>    rxRxfReg;
  
	sc_signal<bool>        setSampleCounter;
	sc_signal<sc_uint<4> > sampleCounter;
	sc_signal<bool>        fsmActive;

	sc_signal<sc_uint<4> >   rxCounterBit;
	sc_signal<sc_uint<2> >   ffSync;
	sc_signal<sc_uint<10> >  rxShiftReg;
	sc_signal<bool>          fsmStart;
	sc_signal<bool>          fsmShift;
	sc_signal<sc_uint<2> >   rxNextState;
	sc_signal<sc_uint<2> >   rxCurrentState;
	sc_signal<bool>          rxFifoOv;
	sc_signal<sc_uint<5> >   rxWptr;
	sc_signal<sc_uint<5> >   rxRptr;
	sc_signal <sc_uint<10> > rxMemArray[16];


	sc_signal<sc_uint<8> >  dataIn;
	sc_signal<bool>         frameError;
	sc_signal<bool>         parityError;
	sc_signal<bool>         uartSync;
	sc_signal<bool>         rxShiftEn;
	sc_signal<bool>         rxComplete;
	sc_signal<bool>         wrRxRifo;
	sc_signal<bool>         rdRxFifo;
	sc_signal<bool>         rxFifoEmplty;
	sc_signal<bool>         rxFifoFull;

	sc_signal<sc_uint<5> >  rxFifoPtrCompare;
	sc_signal<sc_uint<10> > rxFifoDataOut;
	sc_signal<bool>         lsbRxfifoEqual;
	sc_signal<bool>         msbRxfifoDiff;
	sc_signal<sc_uint<10> > dataInRxFifo;
	sc_signal<bool>         rxFifoWe;
	sc_signal<bool>         rxFifoRe;



	void pcProcess();
	void pmProcess();
	void for_wait();

	SC_CTOR(mApbUartReciever) {

		SC_CTHREAD(pcProcess, pClk.pos());
			reset_signal_is(pResetN, false);
			
		SC_METHOD(pmProcess);
			sensitive << ctrlShiftRx;
			sensitive << sampleCounter;
			sensitive << fsmStart;
			sensitive << fsmShift;
			sensitive << ctrlD9;
			sensitive << rxCounterBit;
			sensitive << ffSync;
			sensitive << rxFifoEmplty;
			sensitive << rxFifoOv;
			sensitive << ctrlShiftRx;
			sensitive << rxShiftEn;
			sensitive << uartSync;
			sensitive << rxComplete;
			sensitive << rxCurrentState;
			sensitive << rxComplete;
			sensitive << rxFifoFull;
			sensitive << ctrlDataRd;
			sensitive << rxFifoEmplty;
			sensitive << ctrlD9;
			sensitive << rxShiftReg;
			sensitive << ctrlEp;
			sensitive << frameError;
			sensitive << parityError;
			sensitive << dataIn;
			sensitive << dataInRxFifo;
			sensitive << rxFifoPtrCompare;
			sensitive << rxFifoOv;
			sensitive << rxFifoDataOut;
			sensitive << rxWptr;
			sensitive << rxRptr;
			sensitive << msbRxfifoDiff;
			sensitive << lsbRxfifoEqual;
			for (int i = 0; i < 16; i++) {
				sensitive << rxMemArray[i];
			}			
	}
};


