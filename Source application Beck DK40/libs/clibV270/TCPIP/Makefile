#---------------------------------------------------------------------------
# Makefile for TCPIP.LIB Library
#
#
#  To Build Library:  Invoke make from the subdirectory of CLIB where this
#                     library's source files reside.
#
#                     Assure DOC_TITLE environment variable is not set.
#
#  To Extract HTML Documentation:
#       Invoke make from DOC\CLIBDOC directory with environment 
#       variables set:
#
#       DOC_TITLE - Set to string to pass to AUTODUCK /d argument.
#                                                                                           
#       and specify make target 'genHTML', e.g.
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/TCPIP/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/TCPIP/makefile clean
#
#  Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = TCPIP
LIB_SRC  = tcpip.c


# -------------------------------------------------------
#  OBJECTS: *.obj required for TCPIP.LIB
#
#    Note: To add an object file, list it here and
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\bsd25.obj \
        $(OBJDIR)\bsd26.obj \
        $(OBJDIR)\bsd27.obj \
        $(OBJDIR)\bsd28.obj \
        $(OBJDIR)\bsd29.obj \
        $(OBJDIR)\bsd30.obj \
        $(OBJDIR)\bsd31.obj \
        $(OBJDIR)\bsd32.obj \
        $(OBJDIR)\bsd33.obj \
        $(OBJDIR)\bsd34.obj \
        $(OBJDIR)\bsd35.obj \
        $(OBJDIR)\bsd36.obj \
        $(OBJDIR)\bsd37.obj \
        $(OBJDIR)\bsd38.obj \
        $(OBJDIR)\bsd39.obj \
        $(OBJDIR)\bsd40.obj \
        $(OBJDIR)\bsd41.obj \
        $(OBJDIR)\cry00.obj \
        $(OBJDIR)\cry01.obj \
        $(OBJDIR)\cry02.obj \
        $(OBJDIR)\cry03.obj \
        $(OBJDIR)\cry04.obj \
        $(OBJDIR)\cry05.obj \
        $(OBJDIR)\cry06.obj \
        $(OBJDIR)\cry07.obj \
        $(OBJDIR)\cry08.obj \
        $(OBJDIR)\cry09.obj \
        $(OBJDIR)\cry10.obj \
        $(OBJDIR)\cry11.obj \
        $(OBJDIR)\cry12.obj \
        $(OBJDIR)\cry13.obj \
        $(OBJDIR)\cry14.obj \
        $(OBJDIR)\cry15.obj \
        $(OBJDIR)\cry16.obj \
        $(OBJDIR)\cry17.obj \
        $(OBJDIR)\cry18.obj \
        $(OBJDIR)\cry19.obj \
        $(OBJDIR)\cry20.obj \
        $(OBJDIR)\cry21.obj \
        $(OBJDIR)\cry22.obj \
        $(OBJDIR)\cry23.obj \
        $(OBJDIR)\cry24.obj \
        $(OBJDIR)\cry43.obj \
        $(OBJDIR)\cry44.obj \
        $(OBJDIR)\cry45.obj \
        $(OBJDIR)\cry46.obj \
        $(OBJDIR)\cry47.obj \
        $(OBJDIR)\cry48.obj \
        $(OBJDIR)\dev42.obj \
        $(OBJDIR)\ipsec00.obj \
        $(OBJDIR)\ipsec01.obj \
        $(OBJDIR)\ipsec02.obj \
        $(OBJDIR)\ipsec03.obj \
        $(OBJDIR)\ipsec04.obj \
        $(OBJDIR)\ipsec05.obj \
        $(OBJDIR)\ipsec06.obj \
        $(OBJDIR)\ipsec06I.obj \
        $(OBJDIR)\ipsec07.obj \
        $(OBJDIR)\ipsec08.obj \
        $(OBJDIR)\ipsec09.obj \
        $(OBJDIR)\ipsec0A.obj \
        $(OBJDIR)\ipsecX1.obj \
        $(OBJDIR)\FDNext.obj \
        $(OBJDIR)\htonl.obj \
        $(OBJDIR)\htons.obj \
        $(OBJDIR)\soc32.obj \
        $(OBJDIR)\soc33.obj \
        $(OBJDIR)\soc34.obj \
        $(OBJDIR)\soc35.obj \
        $(OBJDIR)\soc37.obj \
        $(OBJDIR)\soc38.obj \
        $(OBJDIR)\soc40.obj \
        $(OBJDIR)\tcpIPR.obj \
        $(OBJDIR)\tcpIPW.obj \
        $(OBJDIR)\tcpPSIp.obj \
        $(OBJDIR)\tcpPCIp.obj \
        $(OBJDIR)\tcpcon.obj \
        $(OBJDIR)\tcpcone.obj \
        $(OBJDIR)\tcp01.obj \
        $(OBJDIR)\tcp02.obj \
        $(OBJDIR)\tcp03.obj \
        $(OBJDIR)\tcp04.obj \
        $(OBJDIR)\tcp05.obj \
        $(OBJDIR)\tcp05e.obj \
        $(OBJDIR)\tcp06.obj \
        $(OBJDIR)\tcp06e.obj \
        $(OBJDIR)\tcp08.obj \
        $(OBJDIR)\tcp09.obj \
        $(OBJDIR)\tcp0C.obj \
        $(OBJDIR)\tcp0D.obj \
        $(OBJDIR)\tcp0E.obj \
        $(OBJDIR)\tcp0F.obj \
        $(OBJDIR)\tcp10.obj \
        $(OBJDIR)\tcp11.obj \
        $(OBJDIR)\tcp12.obj \
        $(OBJDIR)\tcp13.obj \
        $(OBJDIR)\tcp14.obj \
        $(OBJDIR)\tcp15.obj \
        $(OBJDIR)\tcp16.obj \
        $(OBJDIR)\tcp17.obj \
        $(OBJDIR)\tcp18.obj \
        $(OBJDIR)\tcp19.obj \
        $(OBJDIR)\tcp1A.obj \
        $(OBJDIR)\tcp1Am.obj \
        $(OBJDIR)\tcp21.obj \
        $(OBJDIR)\tcp22.obj \
        $(OBJDIR)\tcp23.obj \
        $(OBJDIR)\tcp24.obj \
        $(OBJDIR)\tcp25.obj \
        $(OBJDIR)\tcp26.obj \
        $(OBJDIR)\tcp27.obj \
        $(OBJDIR)\tcp28.obj \
        $(OBJDIR)\tcp28e.obj \
        $(OBJDIR)\tcp29.obj \
        $(OBJDIR)\tcp30.obj \
        $(OBJDIR)\tcp31.obj \
        $(OBJDIR)\tcp32.obj \
        $(OBJDIR)\tcp33.obj \
        $(OBJDIR)\tcp34.obj \
        $(OBJDIR)\tcp35.obj \
        $(OBJDIR)\tcp40.obj \
        $(OBJDIR)\tcp41.obj \
        $(OBJDIR)\tcp42.obj \
        $(OBJDIR)\tcp43.obj \
        $(OBJDIR)\tcp44.obj \
        $(OBJDIR)\tcp45.obj \
        $(OBJDIR)\tcp46.obj \
        $(OBJDIR)\tcp47.obj \
        $(OBJDIR)\tcp50.obj \
        $(OBJDIR)\tcp51.obj \
        $(OBJDIR)\tcp52.obj \
        $(OBJDIR)\tcp53.obj \
        $(OBJDIR)\tcp54.obj \
        $(OBJDIR)\tcp55.obj \
        $(OBJDIR)\tcp56.obj \
        $(OBJDIR)\tcp57.obj \
        $(OBJDIR)\tcp60.obj \
        $(OBJDIR)\tcp60a.obj \
        $(OBJDIR)\tcp65.obj \
        $(OBJDIR)\tcp66.obj \
        $(OBJDIR)\tcp67.obj \
        $(OBJDIR)\tcp70.obj \
        $(OBJDIR)\tcp71.obj \
        $(OBJDIR)\tcp72.obj \
        $(OBJDIR)\tcp73.obj \
        $(OBJDIR)\tcp73a.obj \
        $(OBJDIR)\tcp74.obj \
        $(OBJDIR)\tcp75.obj \
        $(OBJDIR)\tcp76.obj \
        $(OBJDIR)\tcp77.obj \
        $(OBJDIR)\tcp78.obj \
        $(OBJDIR)\tcp79.obj \
        $(OBJDIR)\tcp79a.obj \
        $(OBJDIR)\tcp79b.obj \
        $(OBJDIR)\tcp79c.obj \
        $(OBJDIR)\tcp7a.obj \
        $(OBJDIR)\tcp7b.obj \
        $(OBJDIR)\tcp7c.obj \
        $(OBJDIR)\tcp7d.obj \
        $(OBJDIR)\tcp7f.obj \
        $(OBJDIR)\tcp80.obj \
        $(OBJDIR)\tcp80a.obj \
        $(OBJDIR)\tcp81.obj \
        $(OBJDIR)\tcp82.obj \
        $(OBJDIR)\tcp83.obj \
        $(OBJDIR)\tcp83a.obj \
        $(OBJDIR)\tcp84.obj \
        $(OBJDIR)\tcp88.obj \
        $(OBJDIR)\tcp89.obj \
        $(OBJDIR)\tcp8A.obj \
        $(OBJDIR)\tcp8D.obj \
        $(OBJDIR)\tcp8E.obj \
        $(OBJDIR)\tcp8F.obj \
        $(OBJDIR)\tcp90.obj \
        $(OBJDIR)\tcp91.obj \
        $(OBJDIR)\tcp92.obj \
        $(OBJDIR)\ddv9F.obj \
        $(OBJDIR)\ddvA0.obj \
        $(OBJDIR)\ddvA1.obj \
        $(OBJDIR)\ddvA2.obj \
        $(OBJDIR)\ddvA3.obj \
        $(OBJDIR)\ddvA4.obj \
        $(OBJDIR)\ddvA5.obj \
        $(OBJDIR)\ddvA6.obj \
        $(OBJDIR)\ddvA7.obj \
        $(OBJDIR)\ddvA8.obj \
        $(OBJDIR)\ddvA9.obj \
        $(OBJDIR)\ddvAA.obj \
        $(OBJDIR)\ddvAB.obj \
        $(OBJDIR)\ddvAC.obj \
        $(OBJDIR)\ddvAD.obj \
        $(OBJDIR)\ddvAE.obj \
        $(OBJDIR)\ddvAF.obj \
        $(OBJDIR)\ddvB0.obj \
        $(OBJDIR)\ddvB1.obj \
        $(OBJDIR)\ddvB2.obj \
        $(OBJDIR)\ddvB3.obj \
        $(OBJDIR)\ddvB4.obj \
        $(OBJDIR)\tcpC0.obj \
        $(OBJDIR)\tcpC1.obj \
        $(OBJDIR)\tcpC2.obj \
        $(OBJDIR)\tcpC3.obj \
        $(OBJDIR)\tcpD0.obj \
        $(OBJDIR)\tcpD1.obj \
        $(OBJDIR)\tcpD2.obj \
        $(OBJDIR)\tcpD5.obj \
        $(OBJDIR)\tcpD6.obj \
        $(OBJDIR)\tcpD7.obj \
        $(OBJDIR)\tcpD8.obj \
        $(OBJDIR)\tcpD9.obj \
        $(OBJDIR)\tcpDA.obj \
        $(OBJDIR)\tcpDB.obj \
        $(OBJDIR)\tcpDC.obj \
        $(OBJDIR)\tcpDD.obj \
        $(OBJDIR)\tcpDE.obj \
        $(OBJDIR)\tcpDFA.obj \
        $(OBJDIR)\tcpDFB.obj \
        $(OBJDIR)\tcpDFC.obj \
        $(OBJDIR)\tcpDFD.obj \
        $(OBJDIR)\tcpDFE.obj \
        $(OBJDIR)\tcpDFF.obj \
        $(OBJDIR)\tcpE01.obj \
        $(OBJDIR)\tcpE02.obj \
        $(OBJDIR)\tcpE03.obj \
        $(OBJDIR)\tcpE04.obj \
        $(OBJDIR)\tcp9Fdyn.obj \
        $(OBJDIR)\tcpA0dyn.obj \
        $(OBJDIR)\tcpA1dyn.obj \
        $(OBJDIR)\tcpA2dyn.obj \
        $(OBJDIR)\tcpA3dyn.obj \
        $(OBJDIR)\tcpA4dyn.obj \
        $(OBJDIR)\tcpA5dyn.obj \
        $(OBJDIR)\tcpA6dyn.obj \
        $(OBJDIR)\tcpA7dyn.obj \
        $(OBJDIR)\tcpA8dyn.obj \
        $(OBJDIR)\tcpA9dyn.obj \
        $(OBJDIR)\tcpAAdyn.obj \
        $(OBJDIR)\tcpABdyn.obj \
        $(OBJDIR)\tcpACdyn.obj \
        $(OBJDIR)\tcpADdyn.obj \
        $(OBJDIR)\tcpAEdyn.obj \
        $(OBJDIR)\tcpAFdyn.obj \
        $(OBJDIR)\tcpB0dyn.obj \
        $(OBJDIR)\tcpB1dyn.obj



# -------------------------------------------------
# Common portion of makefile, shared by each CLIB:
# -------------------------------------------------

!ifdef DOC_TITLE
!include ..\..\..\..\CLIB\common\common.inc
!else
!include ..\common\common.inc
!endif



# -------------------------------------------------
#   Dependencies section, maintained by hand
# -------------------------------------------------

!ifdef DOC_TITLE
# Documentation not dependant on include files
DEPENDS_ON = $(THISLIB)\$(LIB_SRC)
ASM_DEPENDS_ON = "$(THISLIB)\$(LIB_SRC)"

!else
DEPENDS_ON = "$(THISLIB)\$(LIB_SRC)" \
             "$(CCINCL)\dos.h" \
             "$(COMMON_H)\config.h" \
             "$(CCINCL)\stdlib.h" \
             "$(CLIBDIR)\tcpipapi.h" \
             "$(CLIBDIR)\TCPIP_Crypto.h" \
             "$(CLIBDIR)\TCPIP_Socket.h" \
             "$(CLIBDIR)\tcpip.h" \
             "$(CLIBDIR)\dnsapi.h"

ASM_DEPENDS_ON = "$(@B).asm" \
        "$(CLIBDIR)\tcpip\tcpipapi.def"

!endif

$(OBJDIR)\FDNext.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\htons.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\htonl.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\tcpIPR.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpIPW.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpPSIp.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpPCIp.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpcon.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpcone.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp01.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp02.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp03.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp04.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp05.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp05e.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp06.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp06e.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp08.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp09.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp0C.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp0D.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp0E.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp0F.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp10.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp11.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp12.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp13.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp14.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp15.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp16.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp17.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp18.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp19.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp1A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp1Am.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp21.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp22.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp23.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp24.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp25.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp26.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp27.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp28.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp28e.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp29.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp40.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp41.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp42.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp43.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp44.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp45.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp46.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp47.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp50.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp51.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp52.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp53.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp54.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp55.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp56.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)
        
$(OBJDIR)\tcp57.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp60.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp60a.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp65.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp66.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp67.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp70.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp71.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp72.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp73.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp73a.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp74.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp75.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp76.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp77.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp78.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp79.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp79a.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp79b.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp79c.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp7A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp7B.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp7C.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp7D.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp7F.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp80.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp80a.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp81.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp82.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp83.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp83a.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)


$(OBJDIR)\tcp84.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp88.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp89.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp8A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp8D.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp8E.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp8F.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp90.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp91.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp92.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

#### Device Driver functions put in separate file below

$(OBJDIR)\tcpC0.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpC1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpC2.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpC3.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpD0.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpD1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpD2.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpD5.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpD6.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpD7.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpD8.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpD9.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpDA.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpDB.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpDC.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpDD.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpDE.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)



##############################################
#  Dynamic link functions which also have
#  C code versions.  (Their HTML is covered by
#  the C code compilation step, not here.)
##############################################

$(OBJDIR)\cry03.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\cry04.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\cry05.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\cry06.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\cry18.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\cry19.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\cry20.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\cry21.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\cry22.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\cry23.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
       

$(OBJDIR)\tcp9Fdyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\tcpA0dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\tcpA1dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\tcpA2dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\tcpA3dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\tcpA4dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\tcpA5dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
        
$(OBJDIR)\tcpA6dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpA7dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpA8dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpA9dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpAAdyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpABdyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpACdyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpADdyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpAEdyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpAFdyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpB0dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\tcpB1dyn.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)



# -------------------------------------------------
#   CAUTION: LIB_SRC is changed here!
# -------------------------------------------------

LIB_SRC  = dnsapi.c

##############################################################
# Special case here for first "object" ...
#
#  Here we append the DOCLIST.EXE tool execution which supports
#  the Paradigm-Beck context sensitive help for Beck API and
#  data structures.  This step is usually performed by the
#  action to create the $(HTML_TARGET) pseudo target defined
#  near the end of the ..\COMMON\COMMON.INC portion of our makefile.
#  But since this area has an extra source file for this library,
#  we must add this step here manually.

$(OBJDIR)\tcp30.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)
!ifdef DOC_TITLE
    $(DOCLIST_CMD) -d"$(DOC_FILTER)" -s$(THISLIB)\$(LIB_SRC) \
           -hCLIB\$(TARG_LIB) -o$(CLIB_LIST_PATH)
!endif

$(OBJDIR)\tcp31.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp32.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp33.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp34.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcp35.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)


# -------------------------------------------------
#   CAUTION: LIB_SRC is changed again!
# -------------------------------------------------

LIB_SRC  = ipsec.c

##############################################################
# Special case here for first "object" ...
#
#  Here we append the
#  HTML extraction step for IP sec's index page here. Usually
#  for libraries this action is to create the $(HTML_TARGET)
#  pseudo target defined near the end of the ..\COMMON\COMMON.INC
#  portion of our makefile.  But since this area has an extra
#  index page to deal with, we add this step here manually.
#  Likewise for DOCLIST.EXE.

$(OBJDIR)\ipsec00.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)
!ifdef DOC_TITLE
        echo At this point LIB_SRC = (LIB_SRC)
    $(AUTODUCK) /u /RHTML /f../CLIBDOC/CLIB_HTML.txt /t4       \
           /x"DOC_INDEX $(DOC_FILTER)"  /d"Title=IP Security API" \
           /o$(OP)\$(TARG_LIB)\ipsec_index.htm  $(THISLIB)\$(LIB_SRC)
    $(DOCLIST_CMD) -d"$(DOC_FILTER)" -s$(THISLIB)\$(LIB_SRC) \
           -hCLIB\$(TARG_LIB) -o$(CLIB_LIST_PATH)
!endif

$(OBJDIR)\ipsec01.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsec02.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsec03.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsec04.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsec05.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsec06.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsec06I.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsec07.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsec08.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsec09.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsec0A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ipsecX1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

# -------------------------------------------------
#   CAUTION: LIB_SRC is changed again!
# -------------------------------------------------

LIB_SRC  = DEVDRV.c

##############################################################
# Special case here for first "object" ...
#
#  Here we append the
#  HTML extraction step for IP sec's index page here. Usually
#  for libraries this action is to create the $(HTML_TARGET)
#  pseudo target defined near the end of the ..\COMMON\COMMON.INC
#  portion of our makefile.  But since this area has an extra
#  index page to deal with, we add this step here manually.
#  Likewise for DOCLIST.EXE.

$(OBJDIR)\ddv9F.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)
!ifdef DOC_TITLE
        echo At this point LIB_SRC = (LIB_SRC)
    $(AUTODUCK) /u /RHTML /f../CLIBDOC/CLIB_HTML.txt /t4       \
           /x"DOC_INDEX $(DOC_FILTER)"  /d"Title=TCP/IP Device Driver API" \
           /o$(OP)\$(TARG_LIB)\devdrv_index.htm  $(THISLIB)\$(LIB_SRC)
    $(DOCLIST_CMD) -d"$(DOC_FILTER)" -s$(THISLIB)\$(LIB_SRC) \
           -hCLIB\$(TARG_LIB) -o$(CLIB_LIST_PATH)
!endif

# Dev_Set_IfaceMTU() has only assembly code.
$(OBJDIR)\dev42.obj: $(DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\ddvA0.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvA1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvA2.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvA3.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvA4.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvA5.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvA6.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvA7.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvA8.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvA9.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvAA.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvAB.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvAC.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvAD.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvAE.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvAF.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvB0.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvB1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvB2.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvB3.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ddvB4.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)



# -------------------------------------------------
#   CAUTION: LIB_SRC is changed again!
# -------------------------------------------------

LIB_SRC  = CRYPT.c

##############################################################
# Special case here for first "object" ...
#
#  Here we append the
#  HTML extraction step for Crypt function index page here. Usually
#  for libraries this action is to create the $(HTML_TARGET)
#  pseudo target defined near the end of the ..\COMMON\COMMON.INC
#  portion of our makefile.  But since this area has extra
#  index pages to deal with, we add this step here manually.
#  Likewise for DOCLIST.EXE.

$(OBJDIR)\tcpDFA.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)
!ifdef DOC_TITLE
        echo At this point LIB_SRC = (LIB_SRC)
    $(AUTODUCK) /u /RHTML /f../CLIBDOC/CLIB_HTML.txt /t4       \
           /x"DOC_INDEX $(DOC_FILTER)"  /d"Title=Cryptographic API" \
           /o$(OP)\$(TARG_LIB)\crypt_index.htm  $(THISLIB)\$(LIB_SRC)
    $(DOCLIST_CMD) -d"$(DOC_FILTER)" -s$(THISLIB)\$(LIB_SRC) \
           -hCLIB\$(TARG_LIB) -o$(CLIB_LIST_PATH)
!endif

$(OBJDIR)\tcpDFB.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpDFC.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpDFD.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpDFE.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpDFF.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpE01.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpE02.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpE03.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\tcpE04.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

###########################################
# Crypt modules with only dynamic linking

$(OBJDIR)\cry00.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry01.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry02.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry07.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry08.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry09.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry10.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry11.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry12.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry13.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry14.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry15.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry16.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry17.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry24.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry43.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry44.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry45.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry46.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry47.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

$(OBJDIR)\cry48.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

# -------------------------------------------------
#   CAUTION: LIB_SRC is changed again!
# -------------------------------------------------

LIB_SRC  = SockBSD.c

#############################################################
# BSD Socket API modules with only dynamic linking
#
#  For each API, the soc*.obj use the INVOKE_COMPILER_NO_DOC 
#  to compile the *_Dyn version of the respective API that
#  replaces the Beck legacy socket functions with C code
#  that uses the BSD dynamic link API.  So for each bsd*.obj
#  here, we also compile a soc*.obj C code section in
#  SockBSD.c.
#  
#######################################################

#######################################################
# Special case here for first "object" ...
#
#  Here we append the
#  HTML extraction step for BSD function index page here. Usually
#  for libraries this action is to create the $(HTML_TARGET)
#  pseudo target defined near the end of the ..\COMMON\COMMON.INC
#  portion of our makefile.  But since this area has extra
#  index pages to deal with, we add this step here manually.
#  Likewise for DOCLIST.EXE.

$(OBJDIR)\bsd25.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
!ifdef DOC_TITLE
        echo At this point LIB_SRC = (LIB_SRC)
    $(AUTODUCK) /u /RHTML /f../CLIBDOC/CLIB_HTML.txt /t4       \
           /x"DOC_INDEX $(DOC_FILTER)"  /d"Title=TCP/IP BSD Socket API" \
           /o$(OP)\$(TARG_LIB)\bsd_index.htm  $(THISLIB)\$(LIB_SRC)
!endif
# accept() not offered as dynamic link

$(OBJDIR)\bsd26.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
# bind() not offered as dynamic link

$(OBJDIR)\bsd27.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
# connect() not offered as dynamic link

$(OBJDIR)\bsd28.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
# closesocket() not offered as dynamic link

$(OBJDIR)\bsd29.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
# getsockopt() not offered as dynamic link

$(OBJDIR)\bsd30.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
# inet_addr() not offered as dynamic link

$(OBJDIR)\bsd31.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
# listen() not offered as dynamic link

$(OBJDIR)\bsd32.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
$(OBJDIR)\soc32.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)

$(OBJDIR)\bsd33.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
$(OBJDIR)\soc33.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)

$(OBJDIR)\bsd34.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
$(OBJDIR)\soc34.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)

$(OBJDIR)\bsd35.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
$(OBJDIR)\soc35.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)

$(OBJDIR)\bsd36.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
# shutdown() not offered as dynamic link

$(OBJDIR)\bsd37.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
$(OBJDIR)\soc37.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)

#  bsd38 and soc38 for recvFromTo_Link() are undocumented
#   dynamic link implementation assembly and C code for
#   optional dynamic linked version of recvfromto() API.
$(OBJDIR)\bsd38.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
$(OBJDIR)\soc38.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)

# bsd39 for get_socketerror_Dyn() not actually a BSD
#   function.   It is provided without corresponding
#   HTML to provide dynamic linked version of 
#   get_socketerror()
$(OBJDIR)\bsd39.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

#  bsd40 and soc40 for sendto_iface_Link() are undocumented
#   dynamic link implementation assembly and C code for
#   optional dynamic linked version of sendto_iface() API.
$(OBJDIR)\bsd40.obj: $(ASM_DEPENDS_ON)
	$(ASM_ONLY)
$(OBJDIR)\soc40.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)


$(OBJDIR)\bsd41.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)

#############################################################
#   End of Makefile
#############################################################
