#---------------------------------------------------------------------------
# Makefile for USB.LIB Library
#
#
#  To Build Library:  Invoke make from the subdirectory of CLIB where this
#                     library's source file resides.
#
#                     Assure DOC_TITLE environment variable is not set.
#
#  To Extract HTML Documentation:
#       Invoke make from DOC\CLIBDOC directory with environment variables set:
#
#       DOC_TITLE - Set to string to pass to AUTODUCK /d argument.
#
#       and specify make target 'genHTML', e.g.
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/USB/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/USB/makefile clean
#
#  Required Path Environment Variables (unless defaults found deep inside
#  ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = USB
LIB_SRC  = usb_api.c


# -------------------------------------------------------
# OBJECTS: *.obj required for USB.LIB
#
# Note: To add an object file, list it here and add a dependancy
# statement for the new file below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\usb01.obj \
        $(OBJDIR)\usb02.obj \
        $(OBJDIR)\usb03.obj \
        $(OBJDIR)\usb04.obj \
        $(OBJDIR)\usb10.obj \
        $(OBJDIR)\usb11.obj \
        $(OBJDIR)\usb12.obj \
        $(OBJDIR)\usb13.obj \
        $(OBJDIR)\usb14.obj \
        $(OBJDIR)\usb15.obj \
        $(OBJDIR)\usb16.obj \
        $(OBJDIR)\usb17.obj \
        $(OBJDIR)\usb18.obj \
        $(OBJDIR)\usb19.obj \
        $(OBJDIR)\usb1A.obj \
        $(OBJDIR)\usb20.obj \
        $(OBJDIR)\usb21.obj \
        $(OBJDIR)\usb22.obj \
        $(OBJDIR)\usb23.obj \
        $(OBJDIR)\usb24.obj \
        $(OBJDIR)\usb25.obj \
        $(OBJDIR)\usb26.obj \
        $(OBJDIR)\usb27.obj \
        $(OBJDIR)\usb28.obj \
        $(OBJDIR)\usb29.obj \
        $(OBJDIR)\usb2A.obj \
        $(OBJDIR)\usb2B.obj \
        $(OBJDIR)\usb2C.obj \
        $(OBJDIR)\usb2D.obj


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
             "$(CLIBDIR)\usb_api.h"
!endif


$(OBJDIR)\usb01.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb02.obj: $(DEPENDS_ON) 
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb03.obj: $(DEPENDS_ON) 
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb04.obj: $(DEPENDS_ON) 
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb10.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb11.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb12.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb13.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb14.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb15.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb16.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb17.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb18.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb19.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb1A.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb20.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb21.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb22.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb23.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb24.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb25.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb26.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb27.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb28.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb29.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb2A.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb2B.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb2C.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)

$(OBJDIR)\usb2D.obj: $(DEPENDS_ON)
	$(RUN_COMPILER)
	$(RUN_ASSEMBLER)


#############################################################
#   End of Makefile
#############################################################
