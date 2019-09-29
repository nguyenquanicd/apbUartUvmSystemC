#include "mApbUartReciever.h"

void mApbUartReciever::for_wait() {
	wait();
}
void mApbUartReciever::pmFsmActive(){	
	//Read input

	bool FsmStart_ = fsmStart.read();
	bool FsmShift_ = fsmShift.read();
	bool FsmActive_ = FsmStart_ | FsmShift_;

	// Output
	fsmActive.write(FsmActive_);
};

void mApbUartReciever::pmSetSampleCounter(){
	// Input
	bool FsmActive_ = fsmActive.read();
	bool ctrlShiftRx_ = ctrlShiftRx.read();

	bool setsampleCounter_ = FsmActive_ & ctrlShiftRx_;

	// Output
	rxBusy.write(FsmActive_);
	setSampleCounter.write(setsampleCounter_);
};

void mApbUartReciever::pcSampleCounter(){
	bool ctrlEn_;
	bool setsampleCounter_;
	bool RxComplete_;
	sc_uint<4> sampleCounter_;

	sampleCounter.write(0);
	wait();

	while (true){
		ctrlEn_ = ctrlEn.read();
		setsampleCounter_ = setSampleCounter.read();
		RxComplete_ = rxComplete.read();
        sampleCounter_ = sampleCounter.read();
		if (ctrlEn == 0) {
			sampleCounter_ = 0;
		}
		else {
			sc_uint<2> condition_ = setsampleCounter_ << 1 | RxComplete_;
			switch (condition_){
			case 0x01:
				sampleCounter_ = 0;
				break;
			case 0x02:
				sampleCounter_ = sampleCounter_ + 1;
				break;
			default:
				break;
			}
		}

		// output
		sampleCounter.write(sampleCounter_); 
		for_wait();
	}

}

void mApbUartReciever::pmShiftEn(){
	sc_uint<4> sampleCounter_;
	bool ctrlShiftRx_;
	bool RxShiftEn_;

	// Input
	{
		sampleCounter_ = sampleCounter.read();
		ctrlShiftRx_ = ctrlShiftRx.read();

	}

	RxShiftEn_ = ctrlShiftRx_ & (sampleCounter_ == 7);

	// Output
	rxShiftEn.write(RxShiftEn_);
}
void mApbUartReciever::pcRxCounterBit(){
	bool ctrlEn_;
	bool RxShiftEn_;
	bool RxComplete_;
	sc_uint<4> RxCounterBit_;
	
	rxCounterBit.write(0);
	wait();

	while (true) {
		ctrlEn_ = ctrlEn.read();
		RxShiftEn_ = rxShiftEn.read();
		RxComplete_ = rxComplete.read();
		if (ctrlEn == 0) {
			RxCounterBit_ = 0;
		} else {
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
        	rxCounterBit.write(RxCounterBit_);
	for_wait();        
	}

	// output

}
void mApbUartReciever::pmComplete(){
	bool RxComplete_;
	bool ctrlD9_;
	sc_uint<4> RxCounterBit_;

	// Input
	{
		ctrlD9_ = ctrlD9.read();
		RxCounterBit_ = rxCounterBit.read();
	}

	RxComplete_ = (ctrlD9_) ? (RxCounterBit_ == 11) : (RxCounterBit_ == 10);
	
	// Output
	rxComplete.write(RxComplete_);
}
void mApbUartReciever::pcFfSync(){
	sc_uint<2> FfSync_;
	bool uartRx_;

	ffSync.write(3);
	wait();
	while (true) {
		FfSync_ = ffSync.read();
		uartRx_ = uartRx.read();
		
		FfSync_ = FfSync_ << 1 | uartRx_;
        
        ffSync.write(FfSync_);
        for_wait(); 
	}

	// output
	
	

	//if (pResetN == 0) {
	//	ffSync.write(3);
	//}
	//else if (ctrlEn == 0) {
	//	ffSync.write(ffSync.read().range[0] + uartRx.read()) ;
	//}
}
void mApbUartReciever::pmUartSync(){
	sc_uint<2> FfSync_;
	bool UartSync_;

	//Input
	{
		FfSync_ = ffSync.read();
	}

	UartSync_ = FfSync_[1];

	// Output
	uartSync.write(UartSync_);
}

void mApbUartReciever::pcRxShiftReg(){
	bool RxShiftEn_;
	bool UartSync_;
	sc_uint<10> RxShiftReg_;

	rxShiftReg.write(1023);
	wait();
	while (1) {
		RxShiftReg_ = rxShiftReg.read();
		RxShiftEn_ = rxShiftEn.read();

		RxShiftReg_ = (RxShiftReg_ >> 1) | (UartSync_ << 9);

       	rxShiftReg.write(RxShiftReg_);
	for_wait();
	}

	// output

	
}
void mApbUartReciever::pmNextState(){
	sc_uint<2> RxCurrentState_;
	sc_uint<2> rxNextState_;
	bool FsmStart_;
	bool FsmShift_;
	bool UartSync_;
	bool ctrlShiftRx_;
	bool RxShiftEn_;
	bool RxComplete_;
	sc_uint<2> condition_;

	UartSync_ = uartRx.read();
	RxComplete_ = rxComplete.read();
	ctrlShiftRx_ = ctrlShiftRx.read();
	RxShiftEn_ = rxShiftEn.read();
	RxCurrentState_ = rxCurrentState.read();
	condition_ = RxCurrentState_;

	switch (condition_)
	{
	case IDLE_RX: 
		FsmStart_ = 0;
		FsmShift_ = 0;
		if (UartSync_ == 0) {
			rxNextState_ = CHECK_START;
		}
		else {
			rxNextState_ = RxCurrentState_;
		}

		break;

	case CHECK_START:
		FsmStart_ = 1;
		FsmShift_ = 0;
		if (ctrlShiftRx_ && UartSync_) {
			rxNextState_ = IDLE_RX;
		}
		else if (RxShiftEn_) {
			rxNextState_ = SHIFT_DATA;
		}
		else {
			rxNextState_ = RxCurrentState_;
		}
		break;

	case SHIFT_DATA:
		FsmStart_ = 0;
		FsmShift_ = 1;
		if (RxComplete_) {
			rxNextState_ = IDLE_RX;
		}
		else {
			rxNextState_ = RxCurrentState_;
		}
		break;

	default:
		FsmStart_ = 0;
		FsmShift_ = 0;
		rxNextState_ = IDLE_RX;
		break;
	}

	// output
	fsmStart.write(FsmStart_);
	fsmShift.write(FsmShift_);
	rxNextState.write(rxNextState_);
}

void mApbUartReciever::pcRxCurrentState(){
	bool ctrlEn_;
	sc_uint<2> RxCurrentState_;
	sc_uint<2> rxNextState_;

	rxCurrentState.write(IDLE_RX);
	wait();
	while (1) {
		rxNextState_ = rxNextState.read();
		if (ctrlEn == 0) {
			rxCurrentState.write(IDLE_RX);
		}
		else {
			RxCurrentState_ = rxNextState_;
		}
	}

	// output
	rxCurrentState.write(rxNextState_);
	for_wait();
}
void mApbUartReciever::pmWrRxFfifoAndRxFfifoWe(){
	bool RxComplete_;
	bool RxFifoFull_;
	bool RxFifoWe_;
	bool WrRxRifo_;

	// Input 
	{
		RxComplete_ =  rxComplete.read();
		RxFifoFull_ = rxFifoFull.read();
	}

	WrRxRifo_ = RxComplete_;
	RxFifoWe_ = RxComplete_ & (!RxFifoFull_);

	// Ouput 
	wrRxRifo.write(WrRxRifo_);
	rxFifoWe.write(RxFifoWe_);
}


void mApbUartReciever::pmRdRxFifoAndRxFifoRe(){
	bool RdRxFifo_;
	bool ctrlDataRd_;
	bool RxFifoEmplty_;
	bool RxFifoRe_;

	// Input 
	{
		ctrlDataRd_ = ctrlDataRd.read();
		RxFifoEmplty_ = rxFifoEmplty.read();
	}

	RdRxFifo_ = ctrlDataRd_;
	RxFifoRe_ = ctrlDataRd_ & (!RxFifoEmplty_);

	// Ouput 
	rdRxFifo.write(RdRxFifo_);
	rxFifoRe.write(RxFifoRe_);
}


void mApbUartReciever::pmDataInAndError(){
	sc_uint<8> DataIn_;
	sc_uint<8> RxShiftReg_;
	bool RxShiftReg_xor_;
	bool ctrlD9_;
	bool ctrlEp_;
	bool FrameError_;
	bool ParityError_;
	
	// Input 
	{
		ctrlD9_ = ctrlD9.read();
		ctrlEp_ = ctrlEp.read();
		DataIn_ = dataIn.read();
		RxShiftReg_ = rxShiftReg.read();

	}
	
	DataIn_ = (ctrlD9_) ? RxShiftReg_.range(7, 0) : RxShiftReg_(8, 1);
	FrameError_ = !RxShiftReg_[9];
	//for (int i = 0; i < sizeof(RxShiftReg_); i++) {
			RxShiftReg_xor_ = RxShiftReg_.xor_reduce();
	//}
	ParityError_ = (ctrlEp) ? RxShiftReg_xor_ : !RxShiftReg_xor_;

	// Output 
	parityError.write(RxShiftReg_xor_);
	frameError.write(!FrameError_);
	dataIn.write(ctrlD9_ ? RxShiftReg_.range(7, 0) : RxShiftReg_.range(8, 1));
}

//void mApbUartReciever::FrameError_METHOD(){
//	frameError.write(!rxShiftReg.read().range[9]);
//}

//void mApbUartReciever::ParityError_METHOD(){
//	parityError.write((mApbUartReciever.read()) ? (^(rxShiftReg.read().range[8,0])) : !(^rxShiftReg.read().range[8,0]));
//}

void mApbUartReciever::pmDataInRxFifo(){
	bool FrameError_;
	bool ParityError_;
	
	sc_uint<8> DataIn_;
	sc_uint<10> DataInRxFifo_;

	// Input
	{
		ParityError_ = parityError.read();
		FrameError_ = frameError.read();
		DataIn_ = dataIn.read();
		DataInRxFifo_ = dataInRxFifo.read();
	}
	
	DataInRxFifo_ = (FrameError_ << 9) | (ParityError_ << 8) | DataIn_;

	
	// Output
	dataInRxFifo.write(DataInRxFifo_);

}
void mApbUartReciever::pmrxNeAndOv(){
	bool RxFifoEmplty_;
	bool rxNe_;
	bool rxOv_;
	bool RxFifoOv_;

	// Input
	{
		RxFifoEmplty_ = rxFifoEmplty.read();
		RxFifoOv_ = rxFifoOv.read();
	}
	rxOv_ = RxFifoOv_;
	rxNe_ = !RxFifoEmplty_;

	// Output
	rxOv.write(rxOv_);
	rxNe.write(rxNe_);
}
//void mApbUartReciever::rxBusy_METHOD(){}
void mApbUartReciever::pmrxRxf(){
	bool RxFifoFull_;
	bool rxRxf_;
	sc_uint<2> ctrlRxt_;
	sc_uint<5> RxFifoPtrCompare_;
	sc_uint<2> condition_;
	
	// Input

	RxFifoFull_ = rxFifoFull.read();
	RxFifoPtrCompare_ = rxFifoPtrCompare.read();
	ctrlRxt_ = ctrlRxt.read();
	condition_ = ctrlRxt_;

	switch (condition_) {
	case 0x0: rxRxf_ = RxFifoFull_;
		break;
	case 0x1: rxRxf_ = (RxFifoPtrCompare_ >= 8);
		break;

	case 0x2: rxRxf_ = (RxFifoPtrCompare_ >= 4);
		break;

	case 0x3: rxRxf_ = (RxFifoPtrCompare_ >= 2);
		break;

	default:
		break;
	}

	// Output
	rxRxf.write(rxRxf_);

}
void mApbUartReciever::pmSttrxData(){
	bool rxNe_;
	bool rxPe_;
	bool rxFe_;
	bool RxFifoEmplty_;
	sc_uint<8> RxFifoDataOut_;
	sc_uint<8> rxData_;

	// Input
	{
		RxFifoEmplty_ = rxFifoEmplty.read();
		rxNe_ = !RxFifoEmplty_;// rxNe is output cannot be read, use RxFifoEmpty instead
		RxFifoDataOut_ = rxFifoDataOut.read();
	}

	rxPe_ = rxNe_ & RxFifoDataOut_[8];
	rxFe_ = rxNe_ & RxFifoDataOut_[9];
	rxData_ = RxFifoDataOut_;

	// Output
	rxPe.write(rxPe_);
	rxFe.write(rxFe_);
	rxData.write(rxData_);

}
//void mApbUartReciever::RxFifoWe_METHOD() {}

void mApbUartReciever::pcRxWptr() {
	sc_uint<6> RxWptr_;
	sc_uint<6> RxRptr_;
	bool ctrlEn_;
	bool RxFifoWe_;

	rxWptr.write(0);
	wait();
	while (true) {
		RxWptr_ = rxWptr.read();
		RxRptr_ = rxRptr.read();
		ctrlEn_ = ctrlEn.read();
		RxFifoWe_ = rxFifoWe.read();

		if (ctrlEn_ == 0) {
			RxWptr_ = RxRptr_;
		}
		else {
			if (RxFifoWe_) {
				RxWptr_ = RxWptr_ + 1;
			}
			else {
				//RxWptr_ = RxWptr_;
			}
		}
        
        rxWptr.write(RxWptr_);
        for_wait();
	}

	// output

}

//void mApbUartReciever::RxFifoRe_METHOD() {}

void mApbUartReciever::pcRxRptr() {
	sc_uint<6> RxRptr_;
	bool RxFifoRe_;

	rxRptr.write(0);
	wait();
	while (true) {
		RxRptr_ = rxRptr.read();
		RxFifoRe_ = rxFifoRe.read();

		if (RxFifoRe_ == 1) {
			RxRptr_ = RxRptr_ + 1;
		}
		else {
			//RxRptr_ = RxRptr_;
		}
        
        rxRptr.write(RxRptr_);
        for_wait();
        
	}

	// output


}

void mApbUartReciever::pmEqualDiffRxfifo() {
	sc_uint<4> RxWptr_;
	sc_uint<4> RxRptr_;
	bool LsbRxfifoEqual_;
	bool MsbRxfifoDiff_;

	// Input
	{
		LsbRxfifoEqual_ = (RxWptr_ == RxRptr_);
		MsbRxfifoDiff_ = RxWptr_[4] ^ RxRptr_[4];
	}

	// Output
	lsbRxfifoEqual.write(LsbRxfifoEqual_);
	msbRxfifoDiff.write(MsbRxfifoDiff_);
}

void mApbUartReciever::pmRxFifoPtrCompare() {
	sc_uint<5> RxWptr_;
	sc_uint<5> RxRptr_;
	sc_uint<5> RxFifoPtrCompare_;
	bool lsb_rxfifo_full_;
	bool msb_rxfifo_empty_;
	bool MsbRxfifoDiff_; 
	bool LsbRxfifoEqual_;

	// Input
	{
		RxWptr_ = rxWptr.read();
		RxRptr_ = rxRptr.read();
	}
	RxFifoPtrCompare_ = RxWptr_ - RxRptr_;
	lsb_rxfifo_full_ = MsbRxfifoDiff_ & LsbRxfifoEqual_;
	msb_rxfifo_empty_ = (!MsbRxfifoDiff_) & LsbRxfifoEqual_;

	// Output
	rxFifoPtrCompare.write(RxFifoPtrCompare_);
	rxFifoFull.write(lsb_rxfifo_full_);
	rxFifoEmplty.write(msb_rxfifo_empty_);
}

void mApbUartReciever::pcRxFifoOv() {
	bool WrRxRifo_;
	bool RxFifoFull_;
	bool RdRxFifo_;
	bool RxFifoOv_;

	rxFifoOv.write(0);
	wait();

	while (true) {
		WrRxRifo_ = wrRxRifo.read();
		RxFifoFull_ = rxFifoFull.read();
		RdRxFifo_ = rdRxFifo.read();

		sc_uint<2> condition_ = (WrRxRifo_ & RxFifoFull_) << 1 | RdRxFifo_;
		switch (condition_)
		{
		case 0x01: case 0x11: 
			RxFifoOv_ = 0; 
			break;

		case 0x10: 
			RxFifoOv_ = 1; 
			break;

		default:
			//RxFifoOv_ = RxFifoOv_;
			break;
		}
        
        rxFifoOv.write(RxFifoOv_);
        for_wait();
        
	}

	// output

}

void mApbUartReciever::pcRxMemArray(){
	sc_uint<10> RxFifoDataOut_;
	sc_uint<10> RxMemArray_[16];
	sc_uint<4> RxWptr_;
	sc_uint<10> DataInRxFifo_;
	bool RxFifoWe_;
    wait();
    
	while (true) {
		RxWptr_ = rxWptr.read();
		DataInRxFifo_ = dataInRxFifo.read();
		RxFifoWe_ = rxFifoWe.read();
		if (RxFifoWe_ == 1) {
			RxMemArray_[RxWptr_] = DataInRxFifo_;
		}
        
        rxMemArray[RxWptr_].write(RxMemArray_[RxWptr_]);
        for_wait();
	}

	// output

}


void mApbUartReciever::pmRxFifoDataOut() {
	sc_uint<4> RxRptr_;
	sc_uint<10> RxFifoDataOut_;
	
	// Input
	{
		RxRptr_ = rxRptr.read();

		RxFifoDataOut_ = rxMemArray[RxRptr_].read();
	}

	// Output
	rxFifoDataOut.write(RxFifoDataOut_);
}
