# apbUartUvmSystemC
A SystemC UVM environment for UART-APB
Current status: On-going (processing)

--------------------------------------

1/ ENV structure

doc: specification document

sim:

  - run.csh : RUN script
  
  - testTop.cpp : TOP of environment
  
  - dut_top.cpp : TOP of DUT
  
  - mApbUart* : APB-UART is described by SystemC in CA (Cycle Accuracy) model
  
  - mPeripheral.cpp : Clock/Reset supplier
  
  - uart_define.h : common defines
  
uvm_comp: UVM components, interfaces and macros
