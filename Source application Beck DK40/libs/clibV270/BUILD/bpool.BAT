@echo off
REM
REM  Merge all lib files into one LibPool
REM

REM ###### Set LIB_TOOL for either TLIB or PLIB #####

if DEFINED USE_PARADIGM goto SET_TOOL50
set LIBNAME=CLIB%CLIBVERSION%
if DEFINED BCPATH goto SET_TOOL20
set LIB_TOOL=TLIB
goto SET_TOOL99

:SET_TOOL20
set LIB_TOOL=%BCPATH%\bin\TLIB
goto SET_TOOL99

:SET_TOOL50
REM Note: Name length is restricted to 8 chars
set LIBNAME=CLIP%CLIBVERSION%
if DEFINED PC_BECKPATH goto SET_TOOL70
set LIB_TOOL=PLIB
goto SET_TOOL99

:SET_TOOL70
set LIB_TOOL=%PC_BECKPATH%\bin\PLIB
goto SET_TOOL99

:SET_TOOL99

REM ########## End of LIB_TOOL setting ###########


cd ..

REM  Model Compact
del  %LIBNAME%C.LIB
"%LIB_TOOL%" %LIBNAME%C.LIB + .\bin\biosc.lib  + .\bin\canc.lib + .\bin\cgic.lib + .\bin\extdiskc.lib + .\bin\fossilc.lib + .\bin\hwc.lib + .\bin\i2cc.lib + .\bin\rtxc.lib + .\bin\tcpipc.lib + .\bin\pktdrvc.lib + .\bin\spic.lib + .\bin\helperc.lib + .\bin\usbc.lib, contlibc.txt

REM  Model Large
del  %LIBNAME%L.LIB
"%LIB_TOOL%" %LIBNAME%L.LIB + .\bin\biosl.lib  + .\bin\canl.lib + .\bin\cgil.lib + .\bin\extdiskl.lib + .\bin\fossill.lib + .\bin\hwl.lib + .\bin\i2cl.lib + .\bin\rtxl.lib + .\bin\tcpipl.lib + .\bin\pktdrvl.lib + .\bin\spil.lib + .\bin\helperl.lib + .\bin\usbl.lib, contlibl.txt

REM  Model Medium
del  %LIBNAME%M.LIB
"%LIB_TOOL%" %LIBNAME%M.LIB + .\bin\biosm.lib  + .\bin\canm.lib + .\bin\cgim.lib + .\bin\extdiskm.lib + .\bin\fossilm.lib + .\bin\hwm.lib + .\bin\i2cm.lib + .\bin\rtxm.lib + .\bin\tcpipm.lib + .\bin\pktdrvm.lib + .\bin\spim.lib + .\bin\helperm.lib + .\bin\usbm.lib, contlibm.txt

REM  Model Small
del  %LIBNAME%S.LIB
"%LIB_TOOL%" %LIBNAME%S.LIB + .\bin\bioss.lib  + .\bin\cans.lib + .\bin\cgis.lib + .\bin\extdisks.lib + .\bin\fossils.lib + .\bin\hws.lib + .\bin\i2cs.lib + .\bin\rtxs.lib + .\bin\tcpips.lib + .\bin\pktdrvs.lib + .\bin\spis.lib + .\bin\helpers.lib + .\bin\usbs.lib, contlibs.txt

REM  Model Huge
del  %LIBNAME%H.LIB
"%LIB_TOOL%" %LIBNAME%H.LIB + .\bin\biosh.lib  + .\bin\canh.lib + .\bin\cgih.lib + .\bin\extdiskh.lib + .\bin\fossilh.lib + .\bin\hwh.lib + .\bin\i2ch.lib + .\bin\rtxh.lib + .\bin\tcpiph.lib + .\bin\pktdrvh.lib + .\bin\spih.lib + .\bin\helperh.lib + .\bin\usbh.lib, contlibh.txt


REM Install LIB's into Paradigm-Beck environment 
if NOT DEFINED PC_BECKPATH goto NO_PARADIGM
copy %LIBNAME%C.LIB "%PC_BECKPATH%\Lib\Beck\CLIBC.LIB"
copy %LIBNAME%L.LIB "%PC_BECKPATH%\Lib\Beck\CLIBL.LIB"
copy %LIBNAME%M.LIB "%PC_BECKPATH%\Lib\Beck\CLIBM.LIB"
copy %LIBNAME%S.LIB "%PC_BECKPATH%\Lib\Beck\CLIBS.LIB"
copy %LIBNAME%H.LIB "%PC_BECKPATH%\Lib\Beck\CLIBH.LIB"

copy bin\BeckHeap?.LIB "%PC_BECKPATH%\Lib\Beck\*.*"
copy bin\HugePtr?.LIB  "%PC_BECKPATH%\Lib\Beck\*.*"

del /Q "%PC_BECKPATH%\Include\Beck\*.*"
copy *.h "%PC_BECKPATH%\Include\Beck\*.*"
copy BeckHeap\Beck_heap.h "%PC_BECKPATH%\Include\Beck\*.*"

:NO_PARADIGM

cd BUILD

set LIBNAME=
set LIB_TOOL=
