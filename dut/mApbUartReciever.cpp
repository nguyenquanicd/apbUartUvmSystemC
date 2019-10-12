
//--------------------------------------
//Project:  mApbUart
//Module:   mApbUartReciever - header file
//Function: mApbUartReciever
//Author:	Nguyen Hung Quan - Conver to SystemC: Truong Cong Hoang Viet
//Page:     VLSI Technology
//--------------------------------------
//

#include "mApbUartReciever.h"

void mApbUartReciever::for_wait() {
	wait();
}

void mApbUartReciever::pcProcess(){
    
    // Output variable of process
	bool SetSampleCounter_o;
	bool RxComplete_o;
	bool WrRxRifo_o;
	bool RxFifoFull_o;
	bool RdRxFifo_o;
	bool RxFifoOv_o;
	bool RxShiftEn_o;
	bool UartSync_o;
	bool RxFifoWe_o;
	bool UartRx_o;
	bool RxFifoRe_o;
	sc_uint<4> RxCounterBit_o;
	sc_uint<4> SampleCounter_o;
	sc_uint<10> RxShiftReg_o;
	sc_uint<5> RxWptr_o;
	sc_uint<5> RxRptr_o;
	sc_uint<10> RxFifoDataOut_o;
	sc_uint<10> RxMemArray_o[16];
	sc_uint<10> DataInRxFifo_o;
	sc_uint<2> FfSync_o;
	sc_uint<2> RxCurrentState_o;
	sc_uint<2> RxNextState_o;
	
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
		bool WrRxRifo_			= wrRxRifo.read();
		bool RxFifoFull_		= rxFifoFull.read();
		bool RdRxFifo_			= rdRxFifo.read();
		bool RxShiftReg_		= rxShiftReg.read();
		bool RxFifoRe_			= rxFifoRe.read();
		bool CtrlEn_			= ctrlEn.read();
		bool RxShiftEn_			= rxShiftEn.read();
		bool UartRx_			= uartRx.read();
		bool setsampleCounter_	= setSampleCounter.read();
		bool RxFifoWe_			= rxFifoWe.read();
		bool RxComplete_		= rxComplete.read();
		bool UartSync_			= uartRx.read();
		sc_uint<2>	FfSync_			= ffSync.read();
		sc_uint<4>	sampleCounter_	= sampleCounter.read();
		sc_uint<5>	RxWptr_			= rxWptr.read();
		sc_uint<5>	RxRptr_			= rxRptr.read();
		sc_uint<2>	rxNextState_	= rxNextState.read();
		sc_uint<10>	DataInRxFifo_	= dataInRxFifo.read();
		sc_uint<4>  RxCounterBit_	= rxCounterBit.read();

		//Sampler counter: determine the sampled position of a bit
		if (CtrlEn_ == 0) {
			SampleCounter_o = 0;
		}
		else {
			switch (setsampleCounter_ << 1 | RxComplete_){
			case 0x01:
				SampleCounter_o = 0;
				break;
			case 0x02:
				SampleCounter_o = sampleCounter_ + 1;
				break;
			default:
				break;
			}
		}

		//Overload flag of RxFifo
		switch ((WrRxRifo_ & RxFifoFull_) << 1 | RdRxFifo_)
		{
		case 0x01: case 0x11:
			RxFifoOv_o = 0;
			break;

		case 0x10:
			RxFifoOv_o = 1;
			break;

		default:
			break;
		}

		// Reciever counter: count the number of the received bits RxCounterBit
		if (CtrlEn_ == 0) {
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
		FfSync_o = FfSync_ << 1 | UartRx_; // Input synchronizer - 2FF

		// Write pointer RxWptr
		if (CtrlEn_ == 0) {
			RxWptr_o = RxRptr_; //Clear FIFO by assigning wptr = rprt
		}
		else {
			if (RxFifoWe_) {
				RxWptr_o = RxWptr_ + 1;
			}
		}

        //Memory array of RXFIFO
		if (RxFifoWe_ == 1) {
			RxMemArray_o[RxWptr_] = DataInRxFifo_;
		}

		// current state register
		if (CtrlEn_ == 0) {
			RxCurrentState_o = IDLE_RX;
		}
		else {
			RxCurrentState_o = rxNextState_;
		}

		//Read pointer
		if (RxFifoRe_ == 1) {
			RxRptr_ = RxRptr_ + 1;
		}
		///////////////////////////////////////////////

		// Write output value of process
        rxRptr.write(RxRptr_o);
		rxMemArray[RxWptr_].write(RxMemArray_o[RxWptr_]);
		rxFifoOv.write(RxFifoOv_o);
		rxCounterBit.write(RxCounterBit_o);
		ffSync.write(FfSync_o);
		sampleCounter.write(SampleCounter_o); 
		rxShiftReg.write(RxShiftReg_o);
		rxWptr.write(RxWptr_o);
		rxCurrentState.write(RxNextState_o);
		for_wait();
	}

}

void mApbUartReciever::pmProcess(){

    // Output value of process
	bool RxShiftEn_o;
	bool RxComplete_o;
	bool CtrlD9_o;
	bool UartSync_o;
	bool RxFifoFull_o;
	bool RxFifoWe_o;
	bool WrRxRifo_o;
	bool RdRxFifo_o;
	bool CtrlDataRd_o;
	bool RxFifoRe_o;
	bool CtrlEp_o;
	bool FrameError_o;
	bool ParityError_o;
	bool RxNe_o;
	bool RxOv_o;
	bool RxFifoOv_o;
	bool RxPe_o;
	bool RxFe_o;
	bool RxFifoEmplty_o;
	bool LsbRxfifoEqual_o;
	bool MsbRxfifoDiff_o;
	bool RxRxf_o;
	bool FsmStart_o;
	bool FsmShift_o;
	bool FsmActive_o;
	bool CtrlShiftRx_o;
	bool SetSampleCounter_o;
    sc_uint<4>	SampleCounter_o;
	sc_uint<4>	RxCounterBit_o;
	sc_uint<2>	FfSync_o;
	sc_uint<2>	RxCurrentState_o;
	sc_uint<2>	RxNextState_o;
	sc_uint<8>	DataIn_o;
	sc_uint<10> RxShiftReg_o;
	sc_uint<10> DataInRxFifo_o;
	sc_uint<8>	RxData_o;
	sc_uint<5>	RxWptr_o;
	sc_uint<5>	RxRptr_o;
	sc_uint<5>	RxFifoPtrCompare_o;
	sc_uint<10> RxFifoDataOut_o;
	sc_uint<2>	CtrlRxt_o;

	// Read value of input and signal
	bool FsmActive_		 = fsmActive.read();
	bool CtrlShiftRx_	 = ctrlShiftRx.read();
	bool FsmStart_		 = fsmStart.read();
	bool FsmShift_		 = fsmShift.read();
	bool CtrlD9_		 = ctrlD9.read();
	bool UartSync_		 = uartRx.read();
	bool RxComplete_	 = rxComplete.read();
	bool RxShiftEn_		 = rxShiftEn.read();
	bool RxFifoFull_	 = rxFifoFull.read();
	bool CtrlDataRd_	 = ctrlDataRd.read();
	bool RxFifoEmplty_	 = rxFifoEmplty.read();
	bool CtrlEp_		 = ctrlEp.read();
	bool RxFifoOv_		 = rxFifoOv.read();
	bool ParityError_	 = parityError.read();
	bool FrameError_	 = frameError.read();
	bool RxNe_			 = rxNe.read();
	bool MsbRxfifoDiff_	 = msbRxfifoDiff.read();
	bool LsbRxfifoEqual_ = lsbRxfifoEqual.read();

	sc_uint<4>	sampleCounter_		= sampleCounter.read();
	sc_uint<2>	RxCurrentState_		= rxCurrentState.read();
	sc_uint<4>	RxCounterBit_		= rxCounterBit.read();
	sc_uint<2>	FfSync_				= ffSync.read();
	sc_uint<8>	DataIn_				= dataIn.read();
	sc_uint<5>	RxWptr_				= rxWptr.read();
	sc_uint<5>	RxRptr_				= rxRptr.read();
	sc_uint<10>	RxShiftReg_			= rxShiftReg.read();
	sc_uint<2>	CtrlRxt_			= ctrlRxt.read();		
	sc_uint<10>	DataInRxFifo_		= dataInRxFifo.read();
	sc_uint<10>	RxFifoDataOut_		= rxFifoDataOut.read();
	sc_uint<5>	RxFifoPtrCompare_	= rxFifoPtrCompare.read();
	////////////////////////////////////////////////////////
    
	//Sampler counter: determine the sampled position of a bit
		SetSampleCounter_o = FsmActive_ & CtrlShiftRx_;
		FsmActive_o 	   = FsmStart_ | FsmShift_;

	//Shift enable

		RxShiftEn_o  = CtrlShiftRx_ & (sampleCounter_ == 7);
	//Complete a received frame when all bits are sampled
	//Non-parity: START - 8 data bits - STOP
	//Parity: START - 8 data bits - Parity bit - STOP
		RxComplete_o = (CtrlD9_) ? (RxCounterBit_ == 11) : (RxCounterBit_ == 10);

	//Input synchronizer - 2FF
		UartSync_o = FfSync_[1];

	//FSM of receiver
	//Next state and outputs
		switch (RxCurrentState_)
		{
		case IDLE_RX:
			FsmStart_o = 0;
			FsmShift_o = 0;
			if (UartSync_ == 0) {
				RxNextState_o = CHECK_START;
			}
			else {
				RxNextState_o = RxCurrentState_;
			}

			break;
		case CHECK_START:
			FsmStart_o = 1;
			FsmShift_o = 0;
			if (CtrlShiftRx_ && UartSync_) {
				RxNextState_o = IDLE_RX;
			}
			else if (RxShiftEn_) {
				RxNextState_o = SHIFT_DATA;
			}
			else {
				RxNextState_o = RxCurrentState_;
			}
			break;
		case SHIFT_DATA:
			FsmStart_o = 0;
			FsmShift_o = 1;
			if (RxComplete_) {
				RxNextState_o = IDLE_RX;
			}
			else {
				RxNextState_o = RxCurrentState_;
			}
			break;
		default:
			FsmStart_o = 0;
			FsmShift_o = 0;
			RxNextState_o = IDLE_RX;
			break;
		}

	//Reciever FIFO
	//Inputs of FIFO
		WrRxRifo_o		= RxComplete_;
		DataIn_o		= (CtrlD9_) ? RxShiftReg_.range(7, 0) : RxShiftReg_(8, 1);
		DataInRxFifo_o	= (FrameError_ << 9) | (ParityError_ << 8) | DataIn_;
		RdRxFifo_o		= CtrlDataRd_;
		FrameError_o	= !RxShiftReg_[9];  // frame error	
		ParityError_o	= (CtrlEp_) ? RxShiftReg_.xor_reduce() : !RxShiftReg_.xor_reduce(); // parity error
		RxFifoRe_o = CtrlDataRd_ & (!RxFifoEmplty_);
		RxFifoWe_o = RxComplete_ & (!RxFifoFull_);

	//Outputs of FIFO
		RxOv_o = RxFifoOv_;
		RxNe_o = !RxFifoEmplty_;   // fifo not empty status flag
		switch (CtrlRxt_) {
		case 0x0: RxRxf_o = RxFifoFull_;
			break;
		case 0x1: RxRxf_o = (RxFifoPtrCompare_ >= 8);
			break;

		case 0x2: RxRxf_o = (RxFifoPtrCompare_ >= 4);
			break;

		case 0x3: RxRxf_o = (RxFifoPtrCompare_ >= 2);
			break;

		default:
			break;
		}

    // Full, empty flag of RXFIFO
		LsbRxfifoEqual_o	= (RxWptr_ == RxRptr_);
		MsbRxfifoDiff_o		= RxWptr_[4] ^ RxRptr_[4];
		RxFifoPtrCompare_o  = RxWptr_ - RxRptr_;
		RxFifoFull_o		= MsbRxfifoDiff_ & LsbRxfifoEqual_;
		RxFifoEmplty_o		= (!MsbRxfifoDiff_) & LsbRxfifoEqual_;
    
    // Output of fifo
		RxPe_o		= RxNe_ & RxFifoDataOut_[8];
		RxFe_o		= RxNe_ & RxFifoDataOut_[9];
		RxData_o	= RxFifoDataOut_;
    ////////////////////////////////////////////////////////////
    
    // Write 
	// Signal and register
	rxFifoDataOut.write(RxFifoDataOut_o);
	fsmActive.write(FsmActive_o);
	setSampleCounter.write(SetSampleCounter_o);
	rxFifoPtrCompare.write(RxFifoPtrCompare_o);
	rxFifoFull.write(RxFifoFull_o);
	rxFifoEmplty.write(RxFifoEmplty_o);
	lsbRxfifoEqual.write(LsbRxfifoEqual_o);
	msbRxfifoDiff.write(MsbRxfifoDiff_o);
	dataInRxFifo.write(DataInRxFifo_o);
	parityError.write(ParityError_o);
	frameError.write(!FrameError_o);
	dataIn.write(DataIn_o);
	wrRxRifo.write(WrRxRifo_o);
	rxFifoWe.write(RxFifoWe_o);
	rdRxFifo.write(RdRxFifo_o);
	rxFifoRe.write(RxFifoRe_o);
	fsmStart.write(FsmStart_o);
	fsmShift.write(FsmShift_o);
	rxNextState.write(RxNextState_o);
	uartSync.write(UartSync_o);
	rxComplete.write(RxComplete_o);
	rxShiftEn.write(RxShiftEn_o);

	// Output port
	rxBusy.write(FsmActive_o); 
	rxPe.write(RxPe_o);
	rxFe.write(RxFe_o);
	rxData.write(RxData_o);
	rxRxf.write(RxRxf_o);
	rxOv.write(RxOv_o);
	rxNe.write(RxNe_o);
}

