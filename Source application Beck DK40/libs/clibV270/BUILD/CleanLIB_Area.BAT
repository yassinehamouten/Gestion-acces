@echo off
REM
REM   Intended to be invoked by LIBCLEAN.BAT
REM

rd /Q /S %1%\asmC
rd /Q /S %1%\asmL
rd /Q /S %1%\asmM
rd /Q /S %1%\asmS
rd /Q /S %1%\asmH
rd /Q /S %1%\objC
rd /Q /S %1%\objL
rd /Q /S %1%\objM
rd /Q /S %1%\objS
rd /Q /S %1%\objH
rd /Q /S %1%\xml

