@echo off
REM
REM  This batch is used to invoke the Beck C-Libary BUILD.BAT
REM  operation for the Paradigm-Beck compiler version.
REM
REM   Important Environment Variables:
REM
REM      PC_BECKPATH -  Path to Paradigm Beck Edition compiler area 
REM
REM           (See usage in ..\COMMON\COMMON.INC)
REM
REM            
REM 

REM Accumulate all results in SUMMARY.LST
set SUMMARY=..\build\SUMMARY.LST

del /Q %SUMMARY%

REM #####################################################
REM #   Paradigm-Beck Build
REM #####################################################
REM Build library from scratch.  Erase old *.OBJ
call libclean.bat 
set USE_PARADIGM=YES
echo Paradigm Build Start Time >> %SUMMARY%
time /T >> %SUMMARY%
call build.bat
echo Pardigm Build End Time >> %SUMMARY%
time /T >> %SUMMARY%


grep -i warn  %SUMMARY%
grep -i error %SUMMARY%
pause

set USE_PARADIGM=



