#---------------------------------------------------------------------------
# Makefile for FOSSIL.LIB Library
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
#           nmake /f ../../CLIB/FOSSIL/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/FOSSIL/makefile clean
#
#    Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = Fossil
LIB_SRC  = fossil.c


# -------------------------------------------------------
#  OBJECTS: *.obj required for FOSSIL.LIB
#
#    Note: To add an object file, list it here and 
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\fos00.obj \
        $(OBJDIR)\fos01.obj \
        $(OBJDIR)\fos02.obj \
        $(OBJDIR)\fos03.obj \
        $(OBJDIR)\fos04.obj \
        $(OBJDIR)\fos05.obj \
        $(OBJDIR)\fos08.obj \
        $(OBJDIR)\fos09.obj \
        $(OBJDIR)\fos0A.obj \
        $(OBJDIR)\fos0B.obj \
        $(OBJDIR)\fos0C.obj \
        $(OBJDIR)\fos0F.obj \
        $(OBJDIR)\fos18.obj \
        $(OBJDIR)\fos18A.obj \
        $(OBJDIR)\fos19.obj \
        $(OBJDIR)\fos1B.obj \
        $(OBJDIR)\fos80.obj \
        $(OBJDIR)\fos81.obj \
        $(OBJDIR)\fos82.obj \
        $(OBJDIR)\fos83.obj \
        $(OBJDIR)\fos84.obj \
        $(OBJDIR)\fos85.obj \
        $(OBJDIR)\fos86.obj \
        $(OBJDIR)\fos87.obj \
        $(OBJDIR)\fosA0.obj \
        $(OBJDIR)\fosA1.obj \
        $(OBJDIR)\fosA2.obj \
        $(OBJDIR)\fosA2_ext.obj \
        $(OBJDIR)\fosA3.obj \
        $(OBJDIR)\fosA4.obj \
        $(OBJDIR)\fosA4_old.obj \
        $(OBJDIR)\fosA5.obj \
        $(OBJDIR)\fosA6.obj

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
             "$(COMMON_H)\common.h" \
             "$(CLIBDIR)\hwapi.h" \
             "$(CLIBDIR)\HW\hw_priv.h" \
             "$(CLIBDIR)\fossil.h"
!endif

$(OBJDIR)\fos00.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos01.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos02.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos03.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos04.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos05.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos08.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos09.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos0A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos0B.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos0C.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos0F.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos18.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos18A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos19.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos1B.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos80.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos81.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos82.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos83.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos84.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos85.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos86.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fos87.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fosA0.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fosA1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fosA2.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fosA2_ext.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fosA3.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fosA4.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fosA4_old.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fosA5.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\fosA6.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)


#############################################################
#   End of Makefile
#############################################################
