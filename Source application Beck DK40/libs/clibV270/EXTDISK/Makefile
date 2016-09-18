#---------------------------------------------------------------------------
# Makefile for EXTDISK.LIB Library
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
#           nmake /f ../../CLIB/EXTDISK/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/EXTDISK/makefile clean
#
#    Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = EXTDISK
LIB_SRC  = extdisk.c


# -------------------------------------------------------
#  OBJECTS: *.obj required for EXTDISK.LIB
#
#    Note: To add an object file, list it here and 
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\ext01.obj  \
        $(OBJDIR)\ext02.obj  \
        $(OBJDIR)\ext03.obj  \
        $(OBJDIR)\ext04.obj  \
        $(OBJDIR)\ext05.obj  \
        $(OBJDIR)\ext06.obj

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
             "$(CCINCL)\dos.h" \
             "$(COMMON_H)\common.h" \
             "$(COMMON_H)\config.h" \
             "$(CLIBDIR)\extdisk.h" \
             "$(THISLIB)\ext_priv.h"
!endif

$(OBJDIR)\ext01.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ext02.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ext03.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ext04.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ext05.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\ext06.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

#############################################################
#   End of Makefile
#############################################################
