#---------------------------------------------------------------------------
# Makefile for HW.LIB Library
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
#           nmake /f ../../CLIB/HW/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/HW/makefile clean
#
#    Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = HW
LIB_SRC  = hwapi.c


# -------------------------------------------------------
#  OBJECTS: *.obj required for HW.LIB
#
#    Note: To add an object file, list it here and 
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\pfe80.obj \
        $(OBJDIR)\pfe81.obj \
        $(OBJDIR)\pfe81e.obj \
        $(OBJDIR)\pfe82.obj \
        $(OBJDIR)\pfe82e.obj \
        $(OBJDIR)\pfe82r.obj \
        $(OBJDIR)\pfe82rA.obj\
        $(OBJDIR)\pfe83.obj \
        $(OBJDIR)\pfe84.obj \
        $(OBJDIR)\pfe85.obj \
        $(OBJDIR)\pfe86.obj \
        $(OBJDIR)\pfe87.obj \
        $(OBJDIR)\pfe88.obj \
        $(OBJDIR)\pfe89.obj \
        $(OBJDIR)\pfe8A.obj \
        $(OBJDIR)\pfe8B.obj \
        $(OBJDIR)\pfe8C.obj \
        $(OBJDIR)\pfe8D.obj \
        $(OBJDIR)\pfe90.obj \
        $(OBJDIR)\hal80.obj \
        $(OBJDIR)\hal80A.obj \
        $(OBJDIR)\hal81.obj \
        $(OBJDIR)\hal81A.obj \
        $(OBJDIR)\hal82.obj \
        $(OBJDIR)\hal82A.obj \
        $(OBJDIR)\hal83.obj \
        $(OBJDIR)\hal83A.obj \
        $(OBJDIR)\hal84.obj \
        $(OBJDIR)\hal84A.obj \
        $(OBJDIR)\hal85.obj \
        $(OBJDIR)\hal86.obj \
        $(OBJDIR)\hal87.obj \
        $(OBJDIR)\hal88.obj \
        $(OBJDIR)\hal89.obj \
        $(OBJDIR)\hal8A.obj \
        $(OBJDIR)\hal8B.obj \
        $(OBJDIR)\hal8C.obj \
        $(OBJDIR)\hal8D.obj \
        $(OBJDIR)\hal8E.obj \
        $(OBJDIR)\hal8F.obj \
        $(OBJDIR)\hal90.obj \
        $(OBJDIR)\hal91.obj \
        $(OBJDIR)\hal94.obj \
        $(OBJDIR)\hal95.obj \
        $(OBJDIR)\hal96.obj \
        $(OBJDIR)\hal92.obj \
        $(OBJDIR)\halA0.obj \
        $(OBJDIR)\halA1.obj \
        $(OBJDIR)\halB0.obj \
        $(OBJDIR)\halB1.obj \
        $(OBJDIR)\halB2.obj \
        $(OBJDIR)\halC0.obj \
        $(OBJDIR)\halC1.obj \
        $(OBJDIR)\halC2.obj \
        $(OBJDIR)\halC3.obj

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
             "$(CLIBDIR)\hwapi.h" \
             "$(THISLIB)\hw_priv.h"
!endif

$(OBJDIR)\pfe80.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe81.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe81e.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe82.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe82e.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe82r.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe82rA.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe83.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe84.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe85.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe86.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe87.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe88.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe89.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe8A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe8B.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe8C.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe8D.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\pfe90.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal80.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal80A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal81.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal81A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER_NO_DOC)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal82.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal82A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal83.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal83A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal84.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal84A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal85.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal86.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal87.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal88.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal89.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal8A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal8B.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal8C.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal8D.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal8E.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal8F.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal90.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal91.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal94.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal95.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal96.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\hal92.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\halA0.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\halA1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\halB0.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\halB1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\halB2.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\halC0.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\halC1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\halC2.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\halC3.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

#############################################################
#   End of Makefile
#############################################################
