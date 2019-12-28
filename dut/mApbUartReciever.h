
//--------------------------------------
//Project:  mApbUart
//Module:   mApbUartReciever - header file
//Function: mApbUartReciever
//Author:	Nguyen Hung Quan - Conver to SystemC: Truong Cong Hoang Viet
//Page:     VLSI Technology
//--------------------------------------
//
#include "systemc.h"
#define IDLE_RX		 0x0
#define CHECK_START	 0x1
#define SHIFT_DATA	 0x3

SC_MODULE(mApbUartReciever) {

	// Input
	sc_in<bool>		   pClk;
	sc_in<bool>		   pResetN;	 
	sc_in<bool>		   ctrlEn;
	sc_in<bool>		   ctrlD9;
	sc_in<bool>		   ctrlEp;
	sc_in<bool>		   ctrlShiftRx;
	sc_in<bool>		   ctrlDataRd;
	sc_in<bool>		   uartRx;
	sc_in<sc_uint<2> > ctrlRxt;

	// Output 
	sc_out<bool>	    rxNe;
	sc_out<bool>	    rxBusy;
	sc_out<bool>	    rxRxf;
	sc_out<bool>	    rxOv;
	sc_out<bool>	    rxPe;
	sc_out<bool>	    rxFe;
	sc_out<sc_uint<8> > rxData;

	// Signal and register
	sc_signal<bool>          setSampleCounter;
	sc_signal<bool>          rxFifoOv;
	sc_signal<bool>          fsmActive;
	sc_signal<bool>          fsmStart;
	sc_signal<bool>          fsmShift;
	sc_signal<bool>	         rxRxfReg;
	sc_signal<bool>          frameError;
	sc_signal<bool>          parityError;
	sc_signal<bool>          uartSync;
	sc_signal<bool>          rxShiftEn;
	sc_signal<bool>          rxComplete;
	sc_signal<bool>          wrRxFifo;
	sc_signal<bool>          rdRxFifo;
	sc_signal<bool>          rxFifoEmplty;
	sc_signal<bool>          rxFifoFull;
	sc_signal<bool>          lsbRxfifoEqual;
	sc_signal<bool>          msbRxfifoDiff;
	sc_signal<bool>          rxFifoWe;
	sc_signal<bool>          rxFifoRe;
	sc_signal<sc_uint<4> >   sampleCounter;
	sc_signal<sc_uint<4> >   rxCounterBit;
	sc_signal<sc_uint<2> >   ffSync;
	sc_signal<sc_uint<2> >   rxNextState;
	sc_signal<sc_uint<2> >   rxCurrentState;
	sc_signal<sc_uint<5> >   rxWptr;
	sc_signal<sc_uint<5> >   rxRptr;
	sc_signal<sc_uint<8> >   dataIn;
	sc_signal<sc_uint<5> >   rxFifoPtrCompare;
	sc_signal<sc_uint<10> >  rxShiftReg;
	sc_signal<sc_uint<10> >  rxFifoDataOut;
	sc_signal<sc_uint<10> >  dataInRxFifo;
	sc_signal<sc_uint<10> >  rxMemArray[16];
	//sc_uint<10>  rxMemArray[16];

	// Function
	void pcProcess();
	void pmProcess();
	void for_wait();

	// Constructor
	SC_CTOR(mApbUartReciever) {

		SC_CTHREAD(pcProcess, pClk.pos());
			reset_signal_is(pResetN, false); // synchronous reset assignment, active low
			
		SC_METHOD(pmProcess);
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
			//for (int i = 0; i < 16; i++) {
				//sensitive << rxMemArray[i];
			//}
	}
};


