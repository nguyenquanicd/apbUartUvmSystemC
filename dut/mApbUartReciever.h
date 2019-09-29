
//--------------------------------------
//Project: Simple CPU
//Module:  Decoder - body file
//Function: Decoder
//Author:  Truong Cong Hoang Viet
//Page:    VLSI Technology
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
	sc_signal<bool>    rxRxfReg;

	sc_out<bool>	    rxOv;
	sc_out<bool>	    rxPe;
	sc_out<bool>	    rxFe;
	sc_out<sc_uint<8> > rxData; 

	sc_signal<bool>        setSampleCounter;
	sc_signal<sc_uint<4> > sampleCounter;
	sc_signal<bool>        fsmActive;


	// Register
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


	//Wire
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



	void pmFsmActive();
	void pmSetSampleCounter();
	void pcSampleCounter();
	void pmShiftEn();


	void pcRxCounterBit();
	void pmComplete();


	void pcFfSync();


	void pmUartSync();
	void pcRxShiftReg();

	void pmNextState();
	void pcRxCurrentState();
	void pmWrRxFfifoAndRxFfifoWe();

	void pmRdRxFifoAndRxFifoRe();

	void pmDataInAndError();
	//void FrameError_METHOD();


	//void ParityError_METHOD();

	void pmDataInRxFifo();
	void pmrxNeAndOv();
	//void rxBusy_METHOD();
	void pmrxRxf();

	// BIT STATUS and RXDATA
	void pmSttrxData();
	//void rxOv_METHOD();
	//void RX_PE_METHOD();
	//void RX_FE_METHOD();
	//void RX_DATA_METHOD();

	//void RxFifoWe_METHOD();
	void pcRxWptr();
	//void RxFifoRe_METHOD();
	void pcRxRptr();
	void pmRxFifoPtrCompare();
	void pcRxFifoOv();
	//Full, empty flag of RXFIFO
	//void FULL_EMPTY_RXFIFO_METHOD();
	void pmEqualDiffRxfifo();

	void pcRxMemArray();
	void pmRxFifoDataOut();
	void for_wait();

	SC_CTOR(mApbUartReciever) {

		SC_METHOD(pmFsmActive);
			sensitive << fsmStart;
			sensitive << fsmShift;

		SC_METHOD(pmSetSampleCounter);
			sensitive << fsmActive;
			sensitive << ctrlShiftRx;

		SC_CTHREAD(pcSampleCounter, pClk.pos());
			reset_signal_is(pResetN, false);
			
		SC_METHOD(pmShiftEn);
			sensitive << ctrlShiftRx;
			sensitive << sampleCounter;

		SC_CTHREAD(pcRxCounterBit, pClk.pos());
			reset_signal_is(pResetN, false);

		SC_METHOD(pmComplete);
			sensitive << ctrlD9;
			sensitive << rxCounterBit;

		SC_CTHREAD(pcFfSync, pClk.pos());
			reset_signal_is(pResetN, false);

		SC_METHOD(pmUartSync);
			sensitive << ffSync;

		SC_METHOD(pmrxNeAndOv);
			sensitive << rxFifoEmplty;
			sensitive << rxFifoOv;

		SC_CTHREAD(pcRxShiftReg, pClk.pos());
			reset_signal_is(pResetN, false);

		SC_METHOD(pmNextState);
			sensitive << ctrlShiftRx		;
			sensitive << rxShiftEn		;
			sensitive << uartSync			;
			sensitive << rxComplete		;
			sensitive << rxCurrentState	;

		SC_CTHREAD(pcRxCurrentState, pClk.pos());
			reset_signal_is(pResetN, false);

		SC_METHOD(pmWrRxFfifoAndRxFfifoWe);
			sensitive << rxComplete;
			sensitive << rxFifoFull;

		SC_METHOD(pmRdRxFifoAndRxFifoRe);
			sensitive << ctrlDataRd;
			sensitive << rxFifoEmplty;


		SC_METHOD(pmDataInAndError);
			sensitive << ctrlD9;
			sensitive << rxShiftReg;
			sensitive << ctrlEp;

		//SC_METHOD(FrameError_METHOD);
		//	sensitive << rxShiftReg;

		//SC_METHOD(ParityError_METHOD);
		//	sensitive << ctrlEp;
		//	sensitive << rxShiftReg;
		//	sensitive << rxShiftReg;

		SC_METHOD(pmDataInRxFifo);
			sensitive << frameError;
			sensitive << parityError;
			sensitive << dataIn;
            sensitive << dataInRxFifo;

		SC_METHOD(pmrxRxf);
			sensitive << rxFifoFull;
			sensitive << rxFifoPtrCompare;

		//SC_METHOD(rxBusy_METHOD);
		//	sensitive << fsmActive;

		//SC_METHOD(rxRxf_METHOD);


		SC_METHOD(pmSttrxData);
			sensitive << rxFifoOv;
			sensitive << rxFifoDataOut;

		//SC_METHOD(RxFifoWe_METHOD);
		//	sensitive << rxFifoWe;

		SC_CTHREAD(pcRxWptr, pClk.pos());
			reset_signal_is(pResetN, false);

		//SC_METHOD(RxFifoRe_METHOD);
		//	sensitive << ctrlDataRd;
		//	sensitive << rxFifoEmplty;

		SC_CTHREAD(pcRxRptr, pClk.pos());
			reset_signal_is(pResetN, false);


		SC_METHOD(pmRxFifoPtrCompare);
			sensitive << rxWptr;
			sensitive << rxRptr;
			sensitive << msbRxfifoDiff;
			sensitive << lsbRxfifoEqual;

		SC_CTHREAD(pcRxFifoOv, pClk.pos());
			reset_signal_is(pResetN, false);

		SC_METHOD(pmEqualDiffRxfifo);
			sensitive << rxWptr;
			sensitive << rxRptr;

		//SC_METHOD(FULL_EMPTY_RXFIFO_METHOD);
		//	sensitive << msbRxfifoDiff;
		//	sensitive << lsbRxfifoEqual;

		SC_CTHREAD(pcRxMemArray, pClk.pos());
			reset_signal_is(pResetN, false);

		SC_METHOD(pmRxFifoDataOut);
			sensitive << rxRptr;
            for(int i = 0; i < 16; i++){
                sensitive << rxMemArray[i];
            }
			
	}
};


