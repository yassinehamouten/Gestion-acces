#---------------------------------------------------------------------------
# Makefile for PKTDRV.LIB Library
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
#           nmake /f ../../CLIB/PKTDRV/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/PKTDRV/makefile clean
#
#    Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = PKTDRV
LIB_SRC  = pktdrv.c



# -------------------------------------------------------
#  OBJECTS: *.obj required for PKTDRV.LIB
#
#    Note: To add an object file, list it here and 
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\pkt01.obj \
        $(OBJDIR)\pkt02.obj \
        $(OBJDIR)\pkt03.obj \
        $(OBJDIR)\pkt04.obj \
        $(OBJDIR)\pkt06.obj \
        $(OBJDIR)\pkt14.obj \
        $(OBJDIR)\pkt15.obj \
        $(OBJDIR)\pkt28.obj \
        $(OBJDIR)\pkt16_27.obj \
        $(OBJDIR)\pktAvail.obj


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
             "$(CCINCL)\stdlib.h" \
             "$(CLIBDIR)\pktdrv.h" 
!endif

$(OBJDIR)\pkt01.obj: $(DEPENDS_ON)
	$(INVOKE_COMPILER)
	$(INVOKE_C2ASM)

$(OBJDIR)\pkt02.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
	$(INVOKE_C2ASM)

$(OBJDIR)\pkt03.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
	$(INVOKE_C2ASM)

$(OBJDIR)\pkt04.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
	$(INVOKE_C2ASM)

$(OBJDIR)\pkt06.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
	$(INVOKE_C2ASM)

$(OBJDIR)\pkt14.obj: $(DEPENDS_ON)
	$(INVOKE_COMPILER)
	$(INVOKE_C2ASM)

$(OBJDIR)\pkt15.obj: $(DEPENDS_ON)
	$(INVOKE_COMPILER)
	$(INVOKE_C2ASM)

$(OBJDIR)\pkt28.obj: $(DEPENDS_ON)
	$(INVOKE_COMPILER)
	$(INVOKE_C2ASM)

$(OBJDIR)\pkt16_27.obj: $(DEPENDS_ON)
	$(INVOKE_COMPILER)
	$(INVOKE_C2ASM)

$(OBJDIR)\pktAvail.obj: $(DEPENDS_ON)
	$(INVOKE_COMPILER)
	$(INVOKE_C2ASM)


#############################################################
#   End of Makefile
#############################################################
