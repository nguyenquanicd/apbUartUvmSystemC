#include "mApbUartReciever.h"

void mApbUartReciever::for_wait() {
	wait();
}

void mApbUartReciever::pcProcess(){
    // Input
	bool ctrlEn_;
	bool setsampleCounter_;
	bool RxComplete_;
	sc_uint<4> sampleCounter_;
	bool WrRxRifo_;
	bool RxFifoFull_;
	bool RdRxFifo_;
	bool RxFifoOv_;
	bool RxShiftEn_;
	sc_uint<4> RxCounterBit_;
	bool UartSync_;
	sc_uint<10> RxShiftReg_;
	sc_uint<5> RxWptr_;
	sc_uint<5> RxRptr_;
	sc_uint<10> RxFifoDataOut_;
	sc_uint<10> RxMemArray_[16];
	sc_uint<10> DataInRxFifo_;
	bool RxFifoWe_;
	sc_uint<2> FfSync_;
	bool uartRx_;
	bool RxFifoRe_;
	sc_uint<2> RxCurrentState_;
	sc_uint<2> rxNextState_;
    
    // Output
	bool setsampleCounter_o;
	bool RxComplete_o;
	sc_uint<4> sampleCounter_o;
	bool WrRxRifo_o;
	bool RxFifoFull_o;
	bool RdRxFifo_o;
	bool RxFifoOv_o;
	bool RxShiftEn_o;
	sc_uint<4> RxCounterBit_o;
	bool UartSync_o;
	sc_uint<10> RxShiftReg_o;
	sc_uint<5> RxWptr_o;
	sc_uint<5> RxRptr_o;
	sc_uint<10> RxFifoDataOut_o;
	sc_uint<10> RxMemArray_o[16];
	sc_uint<10> DataInRxFifo_o;
	bool RxFifoWe_o;
	sc_uint<2> FfSync_o;
	bool uartRx_o;
	bool RxFifoRe_o;
	sc_uint<2> RxCurrentState_o;
	sc_uint<2> rxNextState_o;
	
	// For reset
	ffSync.write(3);
	rxWptr.write(0);
	rxShiftReg.write(1023);
	rxCounterBit.write(0);
	sampleCounter.write(0);
	rxFifoOv.write(0);
	rxRptr.write(0);
	rxCurrentState.write(IDLE_RX);
	wait();

	while (true){

		WrRxRifo_ = wrRxRifo.read();
		RxFifoFull_ = rxFifoFull.read();
		RdRxFifo_ = rdRxFifo.read();
		RxShiftReg_ = rxShiftReg.read();
		RxShiftEn_ = rxShiftEn.read();
		ctrlEn_ = ctrlEn.read();
		setsampleCounter_ = setSampleCounter.read();
		RxComplete_ = rxComplete.read();
        sampleCounter_ = sampleCounter.read();
		FfSync_ = ffSync.read();
		uartRx_ = uartRx.read();
		RxShiftEn_ = rxShiftEn.read();
		RxComplete_ = rxComplete.read();
		RxWptr_ = rxWptr.read();
		RxRptr_ = rxRptr.read();
		RxFifoWe_ = rxFifoWe.read();
		rxNextState_ = rxNextState.read();
		DataInRxFifo_ = dataInRxFifo.read();
		RxRptr_ = rxRptr.read();
		RxFifoRe_ = rxFifoRe.read();

  //Sampler counter: determine the sampled position of a bit
		if (ctrlEn_ == 0) {
			sampleCounter_o = 0;
		}
		else {
			switch (setsampleCounter_ << 1 | RxComplete_){
			case 0x01:
				sampleCounter_o = 0;
				break;
			case 0x02:
				sampleCounter_o = sampleCounter_ + 1;
				break;
			default:
				break;
			}
		}


		// Out put RxFifo
		switch ((WrRxRifo_ & RxFifoFull_) << 1 | RdRxFifo_)
		{
		case 0x01: case 0x11:
			RxFifoOv_o = 0;
			break;

		case 0x10:
			RxFifoOv_o = 1;
			break;

		default:
			//RxFifoOv_ = RxFifoOv_;
			break;
		}

		// Input synchronizer - 2FF
		FfSync_o = FfSync_ << 1 | uartRx_;


		// Reciever counter: conut the number of the received bits  RxCounterBit
		if (ctrlEn_ == 0) {
			RxCounterBit_o = 0;
		}
		else {
			sc_uint<2> condition_ = RxShiftEn_ << 1 | RxComplete_;
			switch (condition_)
			{
			case 0x01:
				RxCounterBit_o = 0;
				break;
			case 0x02:
				RxCounterBit_o = RxCounterBit_ + 1;
				break;
			default:
				break;
			}
		}

        //Shift register: Sample a bit at the sampled point and store in this register
        //Right shift because the LSB is transfered first
		RxShiftReg_o = (RxShiftReg_ >> 1) | (UartSync_ << 9);

		// Write pointer RxWptr

		if (ctrlEn_ == 0) {
			RxWptr_o = RxRptr_; //Clear FIFO by assigning wptr = rprt
		}
		else {
			if (RxFifoWe_) {
				RxWptr_o = RxWptr_ + 1;
			}
			else {
				//RxWptr_ = RxWptr_;
			}
		}

        //Memory array of RXFIFO
		if (RxFifoWe_ == 1) {
			RxMemArray_o[RxWptr_] = DataInRxFifo_;
		}

		// current state register
			if (ctrlEn_ == 0) {
				RxCurrentState_o = IDLE_RX;
			}
			else {
				RxCurrentState_o = rxNextState_;
			}


		if (RxFifoRe_ == 1) {
			RxRptr_ = RxRptr_ + 1;
		}
		else {
			//RxRptr_ = RxRptr_;
		}

		// output
        rxRptr.write(RxRptr_o);
		rxMemArray[RxWptr_].write(RxMemArray_o[RxWptr_]);
		rxFifoOv.write(RxFifoOv_o);
		rxCounterBit.write(RxCounterBit_o);
		ffSync.write(FfSync_o);
		sampleCounter.write(sampleCounter_o); 
		rxShiftReg.write(RxShiftReg_o);
		rxWptr.write(RxWptr_o);
		rxCurrentState.write(rxNextState_o);
		for_wait();
	}

}

void mApbUartReciever::pmProcess(){
	sc_uint<4> sampleCounter_;
	bool RxShiftEn_;
	bool RxComplete_;
	bool ctrlD9_;
	sc_uint<4> RxCounterBit_;
	sc_uint<2> FfSync_;
	bool UartSync_;
	sc_uint<2> RxCurrentState_;
	sc_uint<2> rxNextState_;
	bool RxFifoFull_;
	bool RxFifoWe_;
	bool WrRxRifo_;
	bool RdRxFifo_;
	bool ctrlDataRd_;
	bool RxFifoRe_;
	sc_uint<8> DataIn_;
	sc_uint<10> RxShiftReg_;
	bool RxShiftReg_xor_;
	bool ctrlEp_;
	bool FrameError_;
	bool ParityError_;
	sc_uint<10> DataInRxFifo_;
	bool rxNe_;
	bool rxOv_;
	bool RxFifoOv_;
	bool rxPe_;
	bool rxFe_;
	bool RxFifoEmplty_;
	sc_uint<8> rxData_;
	bool LsbRxfifoEqual_;
	bool MsbRxfifoDiff_;
	sc_uint<5> RxWptr_;
	sc_uint<5> RxRptr_;
	sc_uint<5> RxFifoPtrCompare_;
	bool rxFifoFull_;
	bool rxFifoEmplty_;
	bool rxRxf_;
	sc_uint<10> RxFifoDataOut_;
	sc_uint<2> CtrlRxt_;
	bool FsmStart_ ;
	bool FsmShift_ ;
	bool FsmActive_;
	bool ctrlShiftRx_;
	bool setsampleCounter_;
    
    
    
    // Output
    sc_uint<4> sampleCounter_o;
	bool RxShiftEn_o;
	bool RxComplete_o;
	bool ctrlD9_o;
	sc_uint<4> RxCounterBit_o;
	sc_uint<2> FfSync_o;
	bool UartSync_o;
	sc_uint<2> RxCurrentState_o;
	sc_uint<2> rxNextState_o;
	bool RxFifoFull_o;
	bool RxFifoWe_o;
	bool WrRxRifo_o;
	bool RdRxFifo_o;
	bool ctrlDataRd_o;
	bool RxFifoRe_o;
	sc_uint<8> DataIn_o;
	sc_uint<10> RxShiftReg_o;
	bool ctrlEp_o;
	bool FrameError_o;
	bool ParityError_o;
	sc_uint<10> DataInRxFifo_o;
	bool rxNe_o;
	bool rxOv_o;
	bool RxFifoOv_o;
	bool rxPe_o;
	bool rxFe_o;
	bool RxFifoEmplty_o;
	sc_uint<8> rxData_o;
	bool LsbRxfifoEqual_o;
	bool MsbRxfifoDiff_o;
	sc_uint<5> RxWptr_o;
	sc_uint<5> RxRptr_o;
	sc_uint<5> RxFifoPtrCompare_o;
	bool rxFifoFull_o;
	bool rxFifoEmplty_o;
	bool rxRxf_o;
	sc_uint<10> RxFifoDataOut_o;
	sc_uint<2> CtrlRxt_o;
	bool FsmStart_o ;
	bool FsmShift_o ;
	bool FsmActive_o;
	bool ctrlShiftRx_o;
	bool setsampleCounter_o;

	// Output ShiftEn
	// Input
	{	
		FsmActive_ = fsmActive.read();
		ctrlShiftRx_ = ctrlShiftRx.read();
		FsmStart_  = fsmStart.read();
		FsmShift_  = fsmShift.read();
		sampleCounter_ = sampleCounter.read();
		RxWptr_ = rxWptr.read();
		RxRptr_ = rxRptr.read();
		ctrlD9_ = ctrlD9.read();
		RxCounterBit_ = rxCounterBit.read();
		FfSync_ = ffSync.read();
		UartSync_ = uartRx.read();
		RxComplete_ = rxComplete.read();
		RxShiftEn_ = rxShiftEn.read();
		RxCurrentState_ = rxCurrentState.read();
		RxFifoFull_ = rxFifoFull.read();
		ctrlDataRd_ = ctrlDataRd.read();
		RxFifoEmplty_ = rxFifoEmplty.read();
		ctrlEp_ = ctrlEp.read();
		DataIn_ = dataIn.read();
		RxShiftReg_ = rxShiftReg.read();
		RxFifoOv_ = rxFifoOv.read();
        //Data output of RXFIFOs
		ParityError_ = parityError.read();
		FrameError_ = frameError.read();
		DataInRxFifo_ = dataInRxFifo.read();
		rxNe_ = rxNe.read();// rxNe is output cannot be read, use RxFifoEmpty instead
		RxFifoDataOut_ = rxFifoDataOut.read();
		RxFifoPtrCompare_ = rxFifoPtrCompare.read();
		CtrlRxt_ = ctrlRxt.read();

	}

	RxShiftEn_o = ctrlShiftRx_ & (sampleCounter_ == 7);

	setsampleCounter_o = FsmActive_ & ctrlShiftRx_;

	FsmActive_o = FsmStart_ | FsmShift_;
    
  //Complete a received frame when all bits are sampled
  //Non-parity: START - 8 data bits - STOP
  //Parity: START - 8 data bits - Parity bit - STOP
	RxComplete_o = (ctrlD9_) ? (RxCounterBit_ == 11) : (RxCounterBit_ == 10);

	// UartSync

	UartSync_o = FfSync_[1];


  //FSM of receiver
  //
  //Next state and outputs


	switch (RxCurrentState_)
	{
	case IDLE_RX:
		FsmStart_o = 0;
		FsmShift_o = 0;
		if (UartSync_ == 0) {
			rxNextState_o = CHECK_START;
		}
		else {
			rxNextState_o = RxCurrentState_;
		}

		break;

	case CHECK_START:
		FsmStart_o = 1;
		FsmShift_o = 0;
		if (ctrlShiftRx_ && UartSync_) {
			rxNextState_o = IDLE_RX;
		}
		else if (RxShiftEn_) {
			rxNextState_o = SHIFT_DATA;
		}
		else {
			rxNextState_o = RxCurrentState_;
		}
		break;

	case SHIFT_DATA:
		FsmStart_o = 0;
		FsmShift_o = 1;
		if (RxComplete_) {
			rxNextState_o = IDLE_RX;
		}
		else {
			rxNextState_o = RxCurrentState_;
		}
		break;

	default:
		FsmStart_o = 0;
		FsmShift_o = 0;
		rxNextState_o = IDLE_RX;
		break;
	}

  //Reciever FIFO
  //
  //Inputs of FIFO
  //WrRxRifo, RxFifoWe
    
	WrRxRifo_o = RxComplete_;
	RxFifoWe_o = RxComplete_ & (!RxFifoFull_);

	// RdRxFifo, RxFifoRe

	RdRxFifo_o = ctrlDataRd_;
	RxFifoRe_o = ctrlDataRd_ & (!RxFifoEmplty_);


	// datain, frame error, parity error

	DataIn_o = (ctrlD9_) ? RxShiftReg_.range(7, 0) : RxShiftReg_(8, 1);
	FrameError_o = !RxShiftReg_[9];

	RxShiftReg_xor_ = RxShiftReg_.xor_reduce();

	ParityError_o = (ctrlEp_) ? RxShiftReg_xor_ : !RxShiftReg_xor_;


	// DataInRxFifo_
	DataInRxFifo_o = (FrameError_ << 9) | (ParityError_ << 8) | DataIn_;


	// Output rxOv, rxNe

	rxOv_o = RxFifoOv_;
	rxNe_o = !RxFifoEmplty_;

	switch (CtrlRxt_) {
	case 0x0: rxRxf_o = RxFifoFull_;
		break;
	case 0x1: rxRxf_o = (RxFifoPtrCompare_ >= 8);
		break;

	case 0x2: rxRxf_o = (RxFifoPtrCompare_ >= 4);
		break;

	case 0x3: rxRxf_o = (RxFifoPtrCompare_ >= 2);
		break;

	default:
		break;
	}

    // //Full, empty flag of RXFIFO
	// lsb Msb Rxfifo Equal & diff
	LsbRxfifoEqual_o = (RxWptr_ == RxRptr_);
	MsbRxfifoDiff_o = RxWptr_[4] ^ RxRptr_[4];

	RxFifoPtrCompare_o = RxWptr_ - RxRptr_;
	rxFifoFull_o = MsbRxfifoDiff_ & LsbRxfifoEqual_;
	rxFifoEmplty_o = (!MsbRxfifoDiff_) & LsbRxfifoEqual_;
    
    // Output of fifo
	rxPe_o = rxNe_ & RxFifoDataOut_[8];
	rxFe_o = rxNe_ & RxFifoDataOut_[9];
	rxData_o = RxFifoDataOut_;

	/// OUTPUT
	// RxFifoDataOut
	rxFifoDataOut.write(RxFifoDataOut_o);

	// FsmACtive
	fsmActive.write(FsmActive_o);

	// FsmActive, set sample counter
	rxBusy.write(FsmActive_o);
	setSampleCounter.write(setsampleCounter_o);

	// RxFifoPtrCompare, lsb_rxfifo_full, msb_rxfifo_empty
	rxFifoPtrCompare.write(RxFifoPtrCompare_o);
	rxFifoFull.write(rxFifoFull_o);
	rxFifoEmplty.write(rxFifoEmplty_o);

	// LsbRxfifoEqual, MsbRxfifoDiff
	lsbRxfifoEqual.write(LsbRxfifoEqual_o);
	msbRxfifoDiff.write(MsbRxfifoDiff_o);

	// Rxrxf
	rxPe.write(rxPe_o);
	rxFe.write(rxFe_o);
	rxData.write(rxData_o);

	// rxRxf
	rxRxf.write(rxRxf_o);

	// rxOv, rxNe
	rxOv.write(rxOv_o);
	rxNe.write(rxNe_o);

	// DataInRxFif
	dataInRxFifo.write(DataInRxFifo_o);

	// RxShiftReg, frameError, dataIn
	parityError.write(RxShiftReg_xor_);
	frameError.write(!FrameError_o);
	dataIn.write(ctrlD9_ ? RxShiftReg_.range(7, 0) : RxShiftReg_.range(8, 1));

	// WrRxFifo
	wrRxRifo.write(WrRxRifo_o);
	rxFifoWe.write(RxFifoWe_o);

	rdRxFifo.write(RdRxFifo_o);
	rxFifoRe.write(RxFifoRe_o);
	// Next state
	fsmStart.write(FsmStart_o);
	fsmShift.write(FsmShift_o);
	rxNextState.write(rxNextState_o);

	uartSync.write(UartSync_o);
	rxComplete.write(RxComplete_o);
	rxShiftEn.write(RxShiftEn_o);
}

