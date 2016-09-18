@echo off
REM
REM  This batch is used to invoke the Beck C-Libary BUILD.BAT
REM  operation twice.  One time for Borland C 5.02 compiler version
REM  of the library and another time for the Paradigm-Beck compiler
REM  version. This batch does no longer work from Windows 7 64 Bit.
REM  The Borland C 5.02 version needs to be build from the Windows
REM  XP mode, see build_borl.bat.
REM
REM   Important Environment Variables:
REM
REM      BCPATH -  Path to Borland compiler area 
REM          and
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



