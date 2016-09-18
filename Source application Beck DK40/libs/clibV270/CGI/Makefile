#---------------------------------------------------------------------------
# Makefile for CGI.LIB Library
#
#
#  To Build Library:  Invoke this make from subdirectory of CLIB
#                     where this libraries source file resides.
#
#                     Assure DOC_TITLE environment variable is not set.
#
#  To Extract HTML Documentation:
#       Invoke this make with from DOC\CLIBDOC directory with environment 
#       variables set:
#
#       DOC_TITLE - Set to string to pass to AUTODUCK /d argument.
#       
#       and specify make target 'genHTML', e.g.
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/CGI/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/CGI/makefile clean
#
#    Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = CGI
LIB_SRC  = cgiapi.c


# -------------------------------------------------------
#  OBJECTS: *.obj required for RTOS.LIB
#
#    Note: To add an object file, list it here and 
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\cgi01.obj \
        $(OBJDIR)\cgi02.obj \
        $(OBJDIR)\cgi03.obj \
        $(OBJDIR)\cgi04.obj \
        $(OBJDIR)\cgi05.obj \
        $(OBJDIR)\cgi06.obj \
        $(OBJDIR)\cgi07.obj \
        $(OBJDIR)\cgi08.obj \
        $(OBJDIR)\cgi0A.obj \
        $(OBJDIR)\cgi0B.obj \
        $(OBJDIR)\cgi0C.obj \
        $(OBJDIR)\cgi0D.obj \
        $(OBJDIR)\cgi81.obj \
        $(OBJDIR)\cgi82.obj \
        $(OBJDIR)\cgi83.obj \
        $(OBJDIR)\cgi84.obj \
        $(OBJDIR)\cgi85.obj \
        $(OBJDIR)\cgi86.obj \
        $(OBJDIR)\cgiscookie.obj \
        $(OBJDIR)\cgigcookie.obj \
        $(OBJDIR)\cgigetarg.obj \
        $(OBJDIR)\cgiRmContentEncoding.obj \
        $(OBJDIR)\cgiUrlEncode.obj \
        $(OBJDIR)\cgiUrlDecode.obj \
        $(OBJDIR)\cgi0E.obj \
        $(OBJDIR)\cgi0F.obj \
        $(OBJDIR)\cgi10.obj \
        $(OBJDIR)\cgi11.obj \
        $(OBJDIR)\cgi12.obj \
        $(OBJDIR)\cgi13.obj \
        $(OBJDIR)\cgi14.obj \
        $(OBJDIR)\cgi15.obj \
        $(OBJDIR)\cgiRmHeaders.obj 


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
!else
DEPENDS_ON = "$(THISLIB)\$(LIB_SRC)" \
             "$(COMMON_H)\config.h" \
             "$(CCINCL)\dos.h" \
             "$(CCINCL)\STDLIB.h" \
             "$(CLIBDIR)\CGIAPI.h" \
             "$(CLIBDIR)\CGI.h" \
!endif

$(OBJDIR)\cgi01.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi02.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi03.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi04.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi05.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi06.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi07.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi08.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi0A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi0B.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi0C.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi0D.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi81.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi82.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi83.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi84.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi85.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi86.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgiscookie.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgigcookie.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgigetarg.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgiRmContentEncoding.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgiUrlEncode.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgiUrlDecode.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi0E.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi0F.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi10.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi11.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi12.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi13.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi14.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgi15.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\cgiRmHeaders.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)


#############################################################
#   End of Makefile
#############################################################
