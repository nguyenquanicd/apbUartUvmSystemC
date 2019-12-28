#!/usr/bin/csh

setenv SYSTEMCLIB cygdrive/d/20.Project/0.Library/001_SystemC/002_Lib/SystemC233_lib
setenv UVMLIB cygdrive/d/20.Project/0.Library/001_SystemC/002_Lib/UvmSystemC_lib
setenv WDIR cygdrive/d/20.Project/3.Github/apbUartUvmSystemC

g++ \
 -I/$SYSTEMCLIB/include \
 -L/$SYSTEMCLIB/lib-cygwin \
 -I/$UVMLIB/include \
 -L/$UVMLIB/lib-cygwin \
 -I/$WDIR/uvm_comp \
 -o testTop *.cpp -lscv -luvm-systemc -lsystemc -lm

