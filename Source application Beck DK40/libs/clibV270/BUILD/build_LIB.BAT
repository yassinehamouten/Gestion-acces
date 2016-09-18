@echo off

REM
REM  Builds C Library in current working directory for four memory models.
REM
REM   Invoke as:
REM
REM    ..\BUILD\BUILD_LIB.BAT
REM
REM  See Build.BAT used to invoke this batch for each C library
REM

rem SEL_MODEL: 0=Large, 1=Medium, 2=Compact, 3=Small, 4=Huge

echo CLIBVERSION = %CLIBVERSION%
set SEL_MODEL=0
nmake /f makefile > libbuild.lst

echo Medium Memory Model (big code)
set SEL_MODEL=1
nmake /f makefile >> libbuild.lst

echo Compact Memory Model (big data)
set SEL_MODEL=2
nmake /f makefile >> libbuild.lst

echo Small Memory Model
set SEL_MODEL=3
nmake /f makefile >> libbuild.lst

echo Huge Memory Model
set SEL_MODEL=4
nmake /f makefile >> libbuild.lst

set SEL_MODEL=
grep -i warn libbuild.lst
grep -i error libbuild.lst
grep -i Fatal libbuild.lst

REM Accumulate total protocol in SUMMARY.LST
copy %SUMMARY% + libbuild.lst %SUMMARY%