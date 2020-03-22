//--------------------------------------
//Project:  Simple CPU
//Module:   SPCU Testbench - header file
//Function: Provide input for CPU
//Author:   Truong Cong Hoang Viet, Le Hoang Van, Nguyen Hung Quan
//Page:     VLSI Technology
//--------------------------------------

#include "uart_testbench.h"
void uart_testbench::TEST(){
  pResetN.write(0);
  wait(8,SC_NS);
  pResetN.write(1);
  wait();
  //--------------------------------------------
  //Setting UART-TX
  //--------------------------------------------
  //Set baud rate  
  write_apb_Tx(0x08, 0x82);
  read_apb_Tx(0x08, 0x82); 
}

void uart_testbench::write_apb_Tx(unsigned int address, unsigned int data){
    pSel_Tx.write(1);
    pWrite_Tx.write(1);
    pAddr_Tx.write(address);
    pWData_Tx.write(data);
    pStrb_Tx.write(0xF);
    wait();
    pEnable_Tx.write(1);
    wait();
    pSel_Tx.write(0);
    pEnable_Tx.write(0);
    //printf ("Write data to  - Address:%X ,Data: %X - Expected data: %X\n", address, data);
    cout << "Write data to  " << " Address " << std::hex << std::uppercase << address
                            << "-- Data " << std::hex << std::uppercase << data
                            << " at " << sc_time_stamp() 
                            << endl ;
    wait();
}

void uart_testbench::read_apb_Tx(unsigned int address, unsigned int exp_data){
    pSel_Tx.write(1);
    pWrite_Tx.write(0);
    pAddr_Tx.write(address);
    //pWData_Tx.write(data);
    pStrb_Tx.write(0xF);
    wait();
    pEnable_Tx.write(1);
    wait();
    unsigned int data = pRData_Tx.read();
    pSel_Tx.write(0);
    pEnable_Tx.write(0);
    if(data != exp_data){
    //printf ("Read data is not as expected - Address:%X, Actual: %X - Expected data: %X\n", address, data, exp_data);
    cout << "Read data from " << " Address " << std::hex << std::uppercase <<  address
                              << "-- Data " << std::hex << std::uppercase << data 
                              << "-- Expected Data " << exp_data
                              << " at " << sc_time_stamp() 
                              << endl ;
    }
    wait();
}

void uart_testbench::write_apb_Rx(unsigned int address, unsigned int data){
    pSel_Rx.write(1);
    pWrite_Rx.write(1);
    pAddr_Rx.write(address);
    pWData_Rx.write(data);
    pStrb_Rx.write(0xF);
    wait();
    pEnable_Rx.write(1);
    wait();
    pSel_Rx.write(0);
    pEnable_Rx.write(0);
    //printf ("Write data to  - Address:%X ,Data: %X - Expected data: %X\n", address, data);
    cout << "Write data to  " << " Address " << std::hex << std::uppercase << address
                        << "-- Data "    << std::hex << std::uppercase << data 
                        << " at " << sc_time_stamp() 
                        << endl ;
    wait();
}

void uart_testbench::read_apb_Rx(unsigned int address, unsigned int exp_data){
    pSel_Rx.write(1);
    pWrite_Rx.write(0);
    pAddr_Rx.write(address);
    //pWData_Rx.write(data);
    pStrb_Rx.write(0xF);
    wait();
    pEnable_Rx.write(1);
    wait();
    unsigned int data = pRData_Rx.read();
    pSel_Rx.write(0);
    pEnable_Rx.write(0);
    if(data != exp_data){
        //printf ("Read data is not as expected - Address:%X - Actual: %X - Expected data: %X\n", address ,data, exp_data);
    cout << "Read data from " << " Address " << std::hex << std::uppercase << address
                          << "-- Data "    << std::hex << std::uppercase << data 
                          << "-- Expected Data " << std::hex << std::uppercase <<  exp_data
                          << " at " << sc_time_stamp() 
                          << endl ;
    }
    wait();
}

unsigned int uart_testbench::read_apb_Rx_N_cmpr(unsigned int address){
    pSel_Rx.write(1);
    pWrite_Rx.write(0);
    pAddr_Rx.write(address);
    //pWData_Rx.write(data);
    pStrb_Rx.write(0xF);
    wait();
    pEnable_Rx.write(1);
    wait();
    unsigned int data = pRData_Rx.read();
    pSel_Rx.write(0);
    pEnable_Rx.write(0);
    //printf ("Read data - Address:%X ,Data: %X - Expected data: %X\n", address, data);
    cout << "Read data from " << " Address " << std::hex << std::uppercase <<  address
                             << "-- Data "  << std::hex << std::uppercase << data 
                             << " at " << sc_time_stamp() 
                             << endl ;
    wait();
    return data;
}