
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
		bool wrRxFifo_			= wrRxFifo.read();
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
		bool UartSync_			= uartSync.read();
		bool RxFifoOv_			= rxFifoOv.read();
		//sc_uint<10> RxMemArray_[16];
		sc_uint<2>	FfSync_			= ffSync.read();
		sc_uint<4>	SampleCounter_	= sampleCounter.read();
		sc_uint<5>	RxWptr_			= rxWptr.read();
		sc_uint<5>	RxRptr_			= rxRptr.read();
		sc_uint<2>  RxCurrentState_ = rxCurrentState.read();
		sc_uint<10>	DataInRxFifo_	= dataInRxFifo.read();
		sc_uint<4>  RxCounterBit_	= rxCounterBit.read();
		sc_uint<2>  RxNextState_    = rxNextState.read();

		//Sampler counter: determine the sampled position of a bit
		if (CtrlEn_ == 0) {
			SampleCounter_ = 0;
		}
		else {
			switch (setsampleCounter_ << 1 | RxComplete_){
			case 0x01:
				SampleCounter_ = 0;
				break;
			case 0x02:
				SampleCounter_ = SampleCounter_ + 1;
				break;
			default:
				break;
			}
		}

		//Overload flag of RxFifo
		switch ((wrRxFifo_ & RxFifoFull_) << 1 | RdRxFifo_)
		{
		case 0x01: case 0x11:
			RxFifoOv_ = 0;
			break;

		case 0x10:
			RxFifoOv_ = 1;
			break;

		default:
			break;
		}

		// Reciever counter: count the number of the received bits RxCounterBit
		if (CtrlEn_ == 0) {
			RxCounterBit_ = 0;
		}
		else {
			sc_uint<2> condition_ = RxShiftEn_ << 1 | RxComplete_;
			switch (condition_)
			{
			case 0x01:
				RxCounterBit_ = 0;
				break;
			case 0x02:
				RxCounterBit_ = RxCounterBit_ + 1;
				break;
			default:
				break;
			}
		}

        //Shift register: Sample a bit at the sampled point and store in this register
        //Right shift because the LSB is transfered first
		RxShiftReg_ = (RxShiftReg_ >> 1) | (UartSync_ << 9);
		FfSync_ = FfSync_ << 1 | UartRx_; // Input synchronizer - 2FF

		// Write pointer RxWptr
		if (CtrlEn_ == 0) {
			RxWptr_ = RxRptr_; //Clear FIFO by assigning wptr = rprt
		}
		else {
			if (RxFifoWe_) {
				RxWptr_ = RxWptr_ + 1;
			}
		}

        //Memory array of RXFIFO
		if (RxFifoWe_ == 1) {
			//RxMemArray_[RxWptr_] = DataInRxFifo_;
			rxMemArray[RxWptr_].write(DataInRxFifo_);
		}

		// current state register
		if (CtrlEn_ == 0) {
			RxCurrentState_ = IDLE_RX;
		}
		else {
			RxCurrentState_ = RxNextState_;
		}

		//Read pointer
		if (RxFifoRe_ == 1) {
			RxRptr_ = RxRptr_ + 1;
		}
		///////////////////////////////////////////////

		// Write output value of process
        rxRptr.write(RxRptr_);
		//rxMemArray[RxWptr_].write(RxMemArray_[RxWptr_]);
        //rxMemArray[RxWptr_] = RxMemArray_[RxWptr_];
		rxFifoOv.write(RxFifoOv_);
		rxCounterBit.write(RxCounterBit_);
		ffSync.write(FfSync_);
		sampleCounter.write(SampleCounter_); 
		rxShiftReg.write(RxShiftReg_);
		rxWptr.write(RxWptr_);
		rxCurrentState.write(RxNextState_);
		for_wait();
	}
}

void mApbUartReciever::pmProcess(){

	// Read value of input and signal
    
	bool CtrlShiftRx_	    = ctrlShiftRx.read();
	bool CtrlD9_		    = ctrlD9.read();
	bool CtrlDataRd_	    = ctrlDataRd.read();
	bool CtrlEp_		    = ctrlEp.read();
	bool RxFifoOv_		    = rxFifoOv.read();
	sc_uint<4>	sampleCounter_		= sampleCounter.read();
	sc_uint<2>	RxCurrentState_		= rxCurrentState.read();
	sc_uint<4>	RxCounterBit_		= rxCounterBit.read();
	sc_uint<2>	FfSync_				= ffSync.read();
	sc_uint<5>	RxWptr_				= rxWptr.read();
	sc_uint<5>	RxRptr_				= rxRptr.read();
	sc_uint<10>	RxShiftReg_			= rxShiftReg.read();
	sc_uint<2>	CtrlRxt_			= ctrlRxt.read();
	////////////////////////////////////////////////////////
    
	//Shift enable
		bool RxShiftEn_  = CtrlShiftRx_ & (sampleCounter_ == 7);
	//Complete a received frame when all bits are sampled
	//Non-parity: START - 8 data bits - STOP
	//Parity: START - 8 data bits - Parity bit - STOP
		bool RxComplete_ = (CtrlD9_) ? (RxCounterBit_ == 11) : (RxCounterBit_ == 10);

	//Input synchronizer - 2FF
		bool UartSync_ = FfSync_[1];
        
    // Full, empty flag of RXFIFO
        bool LsbRxfifoEqual_ 	= (RxWptr_ == RxRptr_);
        bool MsbRxfifoDiff_		= RxWptr_[4] ^ RxRptr_[4];
        bool RxFifoFull_ 		= MsbRxfifoDiff_ & LsbRxfifoEqual_;
        bool RxFifoEmplty_		= (!MsbRxfifoDiff_) & LsbRxfifoEqual_;
        sc_uint<5> RxFifoPtrCompare_   = RxWptr_ - RxRptr_;
        
	//FSM of receiver
	//Next state and outputs
    	bool FsmShift_;
		bool FsmStart_;
        sc_uint<2>  RxNextState_;
		switch (RxCurrentState_)
		{
		case IDLE_RX:
			FsmStart_ = 0;
			FsmShift_ = 0;
			if (UartSync_ == 0) {
				RxNextState_ = CHECK_START;
			}
			else {
				RxNextState_ = RxCurrentState_;
			}
			break;
		case CHECK_START:
			FsmStart_ = 1;
			FsmShift_ = 0;
			if (CtrlShiftRx_ && UartSync_) {
				RxNextState_ = IDLE_RX;
			}
			else if (RxShiftEn_) {
				RxNextState_ = SHIFT_DATA;
			}
			else {
				RxNextState_ = RxCurrentState_;
			}
			break;
		case SHIFT_DATA:
			FsmStart_ = 0;
			FsmShift_ = 1;
			if (RxComplete_) {
				RxNextState_ = IDLE_RX;
			}
			else {
				RxNextState_ = RxCurrentState_;
			}
			break;
		default:
			FsmStart_ = 0;
			FsmShift_ = 0;
			RxNextState_ = IDLE_RX;
			break;
		}

	//Sampler counter: determine the sampled position of a bit
		bool FsmActive_        = FsmStart_ | FsmShift_;
	    bool SetSampleCounter_ = FsmActive_ & CtrlShiftRx_;

	//Reciever FIFO
	//Inputs of FIFO
        bool FrameError_ 	= !RxShiftReg_[9];  // frame error
		bool ParityError_	= (CtrlEp_) ? RxShiftReg_.xor_reduce() : !RxShiftReg_.xor_reduce(); // parity error
		bool wrRxFifo_		= RxComplete_;
		sc_uint<8> DataIn_		    = (CtrlD9_) ? RxShiftReg_.range(7, 0) : RxShiftReg_(8, 1);
		sc_uint<10> DataInRxFifo_	= (FrameError_ << 9) | (ParityError_ << 8) | DataIn_;
		bool RdRxFifo_		= CtrlDataRd_;
		bool RxFifoRe_ = CtrlDataRd_ & (!RxFifoEmplty_);
		bool RxFifoWe_ = RxComplete_ & (!RxFifoFull_);

	//Outputs of FIFO
		bool RxOv_ = RxFifoOv_;
		bool RxNe_ = !RxFifoEmplty_;   // fifo not empty status flag
		bool RxRxf_;
		switch (CtrlRxt_) {
		case 0x0: RxRxf_ = RxFifoFull_;
			break;
		case 0x1: RxRxf_ = (RxFifoPtrCompare_ >= 8);
			break;

		case 0x2: RxRxf_ = (RxFifoPtrCompare_ >= 4);
			break;

		case 0x3: RxRxf_ = (RxFifoPtrCompare_ >= 2);
			break;

		default:
			break;
		}
 
    // Output of fifo
        sc_uint<10> RxFifoDataOut_ = rxMemArray[RxRptr_];
		bool RxPe_		= RxNe_ & RxFifoDataOut_[8];
		bool RxFe_		= RxNe_ & RxFifoDataOut_[9];
		sc_uint<8> RxData_ 	= RxFifoDataOut_;
    ////////////////////////////////////////////////////////////
    
    // Write 
	// Signal and register
	rxFifoDataOut.write(RxFifoDataOut_);
	fsmActive.write(FsmActive_);
	setSampleCounter.write(SetSampleCounter_);
	rxFifoPtrCompare.write(RxFifoPtrCompare_);
	rxFifoFull.write(RxFifoFull_);
	rxFifoEmplty.write(RxFifoEmplty_);
	lsbRxfifoEqual.write(LsbRxfifoEqual_);
	msbRxfifoDiff.write(MsbRxfifoDiff_);
	dataInRxFifo.write(DataInRxFifo_);
	parityError.write(ParityError_);
	frameError.write(!FrameError_);
	dataIn.write(DataIn_);
	wrRxFifo.write(wrRxFifo_);
	rxFifoWe.write(RxFifoWe_);
	rdRxFifo.write(RdRxFifo_);
	rxFifoRe.write(RxFifoRe_);
	fsmStart.write(FsmStart_);
	fsmShift.write(FsmShift_);
	rxNextState.write(RxNextState_);
	uartSync.write(UartSync_);
	rxComplete.write(RxComplete_);
	rxShiftEn.write(RxShiftEn_);

	// Output port
	rxBusy.write(FsmActive_);
	rxPe.write(RxPe_);
	rxFe.write(RxFe_);
	rxData.write(RxData_);
	rxRxf.write(RxRxf_);
	rxOv.write(RxOv_);
	rxNe.write(RxNe_);
}

