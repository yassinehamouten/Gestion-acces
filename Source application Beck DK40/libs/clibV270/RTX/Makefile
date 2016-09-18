#---------------------------------------------------------------------------
# Makefile for RTX.LIB Library
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
#           nmake /f ../../CLIB/RTX/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/RTX/makefile clean
#
#    Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = RTX
LIB_SRC  = rtos.c


# -------------------------------------------------------
#  OBJECTS: *.obj required for RTX.LIB
#
#    Note: To add an object file, list it here and 
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\pcsegm.obj \
        $(OBJDIR)\rtx00.obj \
        $(OBJDIR)\rtx01.obj \
        $(OBJDIR)\rtx01A.obj \
        $(OBJDIR)\rtx02.obj \
        $(OBJDIR)\rtx03.obj \
        $(OBJDIR)\rtx04.obj \
        $(OBJDIR)\rtx05.obj \
        $(OBJDIR)\rtx06.obj \
        $(OBJDIR)\rtx07.obj \
        $(OBJDIR)\rtx08.obj \
        $(OBJDIR)\rtx08A.obj \
        $(OBJDIR)\rtx09.obj \
        $(OBJDIR)\rtx0A.obj \
        $(OBJDIR)\rtx0B.obj \
        $(OBJDIR)\rtx0C.obj \
        $(OBJDIR)\rtx0D.obj \
        $(OBJDIR)\rtx0E.obj \
        $(OBJDIR)\rtx0F.obj \
        $(OBJDIR)\rtx10.obj \
        $(OBJDIR)\rtx11.obj \
        $(OBJDIR)\rtx11A.obj \
        $(OBJDIR)\rtx12.obj \
        $(OBJDIR)\rtx13.obj \
        $(OBJDIR)\rtx13A.obj \
        $(OBJDIR)\rtx14.obj \
        $(OBJDIR)\rtx15.obj \
        $(OBJDIR)\rtx16.obj \
        $(OBJDIR)\rtx17.obj \
        $(OBJDIR)\rtx18.obj \
        $(OBJDIR)\rtx19.obj \
        $(OBJDIR)\rtx1A.obj \
        $(OBJDIR)\rtx1B.obj \
        $(OBJDIR)\rtx1C.obj \
        $(OBJDIR)\rtx1D.obj \
        $(OBJDIR)\rtx1DA.obj \
        $(OBJDIR)\rtx1E.obj \
        $(OBJDIR)\rtx20.obj \
        $(OBJDIR)\rtx21.obj \
        $(OBJDIR)\rtx28.obj \
        $(OBJDIR)\rtx29.obj \
        $(OBJDIR)\rtx2A.obj \
        $(OBJDIR)\rtx2AA.obj \
        $(OBJDIR)\rtx2B.obj \
        $(OBJDIR)\rtx2BA.obj \
        $(OBJDIR)\rtx2F.obj \
        $(OBJDIR)\rtx2FA.obj \
        $(OBJDIR)\rtx30.obj \
        $(OBJDIR)\rtx30A.obj \
        $(OBJDIR)\rtx31.obj \
        $(OBJDIR)\rtx32.obj \
        $(OBJDIR)\rtx33.obj \
        $(OBJDIR)\rtx34.obj \
        $(OBJDIR)\rtx34A.obj \
        $(OBJDIR)\rtx35.obj \
        $(OBJDIR)\rtx40.obj \
        $(OBJDIR)\rtx41.obj \
        $(OBJDIR)\rtx42.obj \
        $(OBJDIR)\rtx43.obj \
        $(OBJDIR)\rtx43A.obj \
        $(OBJDIR)\rtx44.obj \
        $(OBJDIR)\rtx45.obj \
        $(OBJDIR)\rtx46.obj \
        $(OBJDIR)\rtx50.obj \
        $(OBJDIR)\rtx51.obj \
        $(OBJDIR)\rtx52.obj \
        $(OBJDIR)\rtx53.obj \
        $(OBJDIR)\rtx54.obj \
        $(OBJDIR)\rtx54A.obj \
        $(OBJDIR)\rtx55.obj \
        $(OBJDIR)\rtxtf1.obj \
        $(OBJDIR)\rtxtf2.obj \
        $(OBJDIR)\rtxtf3.obj \
        $(OBJDIR)\rtxdyn00.obj \
        $(OBJDIR)\rtxdyn01.obj \
        $(OBJDIR)\rtxdyn02.obj \
        $(OBJDIR)\rtxdyn03.obj


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

# CAUTION:  The AUTODUCK uses the first dependancy file
#        as the container for the documentation source.

DEPENDS_ON     = "$(THISLIB)\$(LIB_SRC)"

ASM_DEPENDS_ON = "$(THISLIB)\$(LIB_SRC)"

!else
DEPENDS_ON = "$(THISLIB)\$(LIB_SRC)" \
             "$(CCINCL)\dos.h" \
             "$(COMMON_H)\common.h" \
             "$(COMMON_H)\config.h" \
             "$(CLIBDIR)\rtos.h" \
             "$(CLIBDIR)\rtxapi.h" \
             "$(THISLIB)\rtx_priv.h"

ASM_DEPENDS_ON = "$(@B).asm" \
        "$(CLIBDIR)\rtx\rtxDLapi.def"
!endif

$(OBJDIR)\pcsegm.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\rtx00.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx01.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx01A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx02.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx03.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx04.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx05.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx06.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx07.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx08.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx08A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx09.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx0A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx0B.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx0C.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx0D.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx0E.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx0F.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx10.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx11.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx11A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx12.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx13.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx13A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx14.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx15.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx16.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx17.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx18.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx19.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx1A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx1B.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx1C.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx1D.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx1DA.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx1E.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx20.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx21.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx28.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx29.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx2A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx2AA.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx2B.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx2BA.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx2F.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx2FA.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx30.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx30A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx31.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx32.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx33.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx34.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx34A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx35.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx40.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx41.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx42.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx43.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx43A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx44.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx45.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx46.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx50.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx51.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx52.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx53.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx54.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx54A.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtx55.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtxtf1.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtxtf2.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtxtf3.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\rtxdyn00.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
        
$(OBJDIR)\rtxdyn01.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
        
$(OBJDIR)\rtxdyn02.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
        
$(OBJDIR)\rtxdyn03.obj: $(ASM_DEPENDS_ON)
	$(ASSEMBLE)
        

#############################################################
#   End of Makefile
#############################################################
