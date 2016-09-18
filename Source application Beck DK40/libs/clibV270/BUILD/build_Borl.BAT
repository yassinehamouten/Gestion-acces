@echo off
REM
REM  This batch is used to invoke the Beck C-Libary BUILD.BAT
REM  operation for the Borland C 5.02 compiler version
REM  of the library. Since Windows 7 64 Bit, this batch needs 
REM  to be invoked from the Windows XP mode (virtual machine).
REM  In this virtual machine the Z: drive is mapped to the 
REM  host drive C:. 
REM
REM   Important Environment Variables:
REM
REM      BCPATH -  Path to Borland compiler area 
REM
REM           (See usage in ..\COMMON\COMMON.INC)
REM
REM            
REM 

REM Accumulate all results in SUMMARY.LST
set SUMMARY=..\build\SUMMARY.LST

del /Q %SUMMARY%

REM #####################################################
REM #   Borland C 5.02 Build
REM #####################################################
REM Build library from scratch.  Erase old *.OBJ
call libclean.bat 
set USE_PARADIGM=
echo Borland 5.02 Build Start Time > %SUMMARY%
time /T >> %SUMMARY%
call build.bat
echo Borland 5.02 Build End Time >> %SUMMARY%
time /T >> %SUMMARY%

grep -i warn  %SUMMARY%
grep -i error %SUMMARY%
pause

set USE_PARADIGM=



