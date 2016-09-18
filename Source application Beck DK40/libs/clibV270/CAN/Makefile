#---------------------------------------------------------------------------
# Makefile for CAN.LIB Library
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
#           nmake /f ../../CLIB/CAN/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/CAN/makefile clean
#
#    Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = CAN
LIB_SRC  = can.c


# -------------------------------------------------------
#  OBJECTS: *.obj required for CAN.LIB
#
#    Note: To add an object file, list it here and 
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\can01.obj \
        $(OBJDIR)\can02.obj \
        $(OBJDIR)\can03.obj \
        $(OBJDIR)\can04.obj \
        $(OBJDIR)\can05.obj \
        $(OBJDIR)\can06.obj \
        $(OBJDIR)\can07.obj \
        $(OBJDIR)\can08.obj \
        $(OBJDIR)\can09.obj \
        $(OBJDIR)\can0A.obj \
        $(OBJDIR)\can0B.obj \
        $(OBJDIR)\can0C.obj


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
             "$(COMMON_H)\common.inc" \
             "$(COMMON_H)\config.h" \
             "$(CCINCL)\dos.h" \
             "$(CCINCL)\stdlib.h" \
             "$(CLIBDIR)\can_api.h"
!endif

$(OBJDIR)\can01.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can02.obj: $(DEPENDS_ON) 
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can03.obj: $(DEPENDS_ON) 
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can04.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can05.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can06.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can07.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can08.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can09.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can0A.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can0B.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\can0C.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)


#############################################################
#   End of Makefile
#############################################################
