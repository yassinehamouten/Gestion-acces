
REM
REM   This batch file is used for compiling a specific library during development
REM

REM set CLIB Version
set CLIBVERSION=1

REM EXTMODE=x indicates build code for the DSTniEX CPU
set EXTMODE=x


cd ..\CAN
del objSx\*.* /Q
REM call ..\build\build_lib.bat
set SEL_MODEL=3
nmake /f makefile > libbuild.lst

cd ..\BUILD
