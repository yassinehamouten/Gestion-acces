@echo off
REM
REM  This batch builds the Beck C-Libraries
REM
REM   Important Environment Variables:
REM
REM      BCPATH -  Path to Borland compiler area 
REM          or
REM      PC_BECKPATH -  Path to Paradigm Beck Edition compiler area 
REM
REM           (See usage in ..\COMMON\COMMON.INC)
REM
REM 
     
REM set CLIBVERSION environment variable
call SetCLibVersion.bat

REM Select Paradigm Beck Edition compiler by setting the
REM USE_PARADIGM environment variable to non-whitespace.
REM set USE_PARADIGM=YES

REM Skip listing file initialization if being
REM  called from a top level build batch file.
set NOT_OUR_SUMMARY=TRUE
if DEFINED SUMMARY goto AFTER_SIGNON
REM Accumulate all results in SUMMARY.LST
set SUMMARY=..\build\SUMMARY.LST
set NOT_OUR_SUMMARY=

echo %SUMMARY%
del /Q %SUMMARY%

set CREATED_LISTING=TRUE
echo Build Start Time > %SUMMARY%
time /T >> %SUMMARY%
:AFTER_SIGNON

REM
REM  Builds All C Libraries
REM
cd ..\BIOS
echo Building BIOS Library
call ..\build\build_lib.bat

cd ..\CAN
echo Building CAN Library
call ..\build\build_lib.bat

cd ..\CGI
echo Building CGI Library
call ..\build\build_lib.bat

cd ..\EXTDISK
echo Building EXTDISK Library
call ..\build\build_lib.bat

cd ..\FOSSIL
echo Building FOSSIL Library
call ..\build\build_lib.bat

cd ..\HELPER
echo Building HELPER Library
call ..\build\build_lib.bat

cd ..\HW
echo Building HW Library
call ..\build\build_lib.bat

cd ..\I2C
echo Building I2C Library
call ..\build\build_lib.bat

cd ..\PKTDRV
echo Building PKTDRV Library
call ..\build\build_lib.bat

cd ..\RTX
echo Building RTX Library
call ..\build\build_lib.bat

cd ..\SPI
echo Building SPI Library
call ..\build\build_lib.bat

cd ..\TCPIP
echo Building TCPIP Library
call ..\build\build_lib.bat

cd ..\USB
echo Building USB Library
call ..\build\build_lib.bat

if NOT DEFINED USE_PARADIGM goto PAST_BECKHEAP 
cd ..\BeckHeap
echo Building BeckHeap Library
call ..\build\build_lib.bat

:PAST_BECKHEAP

if NOT DEFINED USE_PARADIGM goto PAST_HUGEPTR
cd ..\HugePtr
echo Building HugePtr Library
call ..\build\build_lib.bat

:PAST_HUGEPTR

cd ..\BUILD

if NOT DEFINED CREATED_LISTING goto PAST_SIGNOFF
echo Build End Time >> %SUMMARY%
time /T >> %SUMMARY%

grep -i warn  %SUMMARY%
grep -i error %SUMMARY%
grep -i Fatal %SUMMARY%

:PAST_SIGNOFF

REM
REM  Merge all created lib files now (one specific for
REM  every memory model)
REM
echo Merging Libraries
call BPOOL

REM Erase our additions to the environment
set USE_PARADIGM=

if DEFINED NOT_OUR_SUMMARY goto AFTER_SUMMARY_ERASE
set SUMMARY=
:AFTER_SUMMARY_ERASE

set CREATED_LISTING=

