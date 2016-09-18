REM
REM  Builds C Library in current working directory for LARGE memory model.
REM
REM   Invoke as:
REM
REM    ..\BUILD\TRIAL.BAT
REM
REM  Intended for use during library development
REM

rem 0=Large, 1=Medium, 2=Compact, 3=Small, 4=Huge
set USE_PARADIGM=YES
set SEL_MODEL=3

@echo off

REM Start build
nmake /f makefile > libbuild.lst


REM Check for arguments
if "X%1" == "X/i" goto installClib
goto end

REM Install CLIB into IDE
:installClib
@echo Installing CLIB into IDE now
REM keep current directory and change into build directory
pushd ..\build

REM Setup CLIB Version number
call SetCLibVersion.bat

REM Build CLIB Pool and install into IDE
call bpool.bat

REM Restore user directory 
popd


:end
grep -i warn libbuild.lst
grep -i error libbuild.lst
