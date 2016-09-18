@echo off
cd  ..

del /Q /S cmpopts.cmd
del /Q /S libbuild.lst
del /Q /S *.bak
del /Q /S *.obr

del /Q bin\*.*
del contlib?.txt

REM *.ASM files are only deleted from the asm* subdirectories
REM to avoid deleting ASM source files used by the dynamic
REM links

call build/CleanLIB_Area BIOS
call build/CleanLIB_Area CAN
call build/CleanLIB_Area CGI
call build/CleanLIB_Area EXTDISK
call build/CleanLIB_Area FOSSIL
call build/CleanLIB_Area HELPER
call build/CleanLIB_Area HW
call build/CleanLIB_Area I2C
call build/CleanLIB_Area PKTDRV
call build/CleanLIB_Area RTX
call build/CleanLIB_Area SPI
call build/CleanLIB_Area TCPIP
call build/CleanLIB_Area USB
call build/CleanLIB_Area BeckHeap
call build/CleanLIB_Area HugePtr

cd build
