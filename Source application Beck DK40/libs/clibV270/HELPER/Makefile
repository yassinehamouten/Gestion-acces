#---------------------------------------------------------------------------
# Makefile for HELPER.LIB Library
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
#           nmake /f ../../CLIB/HELPER/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/HELPER/makefile clean
#
#    Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = HELPER
LIB_SRC  = helper.c


# -------------------------------------------------------
#  OBJECTS: *.obj required for HELPER.LIB
#
#    Note: To add an object file, list it here and 
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

HTML_ONLY = \
        $(OBJDIR)\helperM1.obj \
        $(OBJDIR)\helperM2.obj \
        $(OBJDIR)\helperM3.obj \
        $(OBJDIR)\helperM4.obj \
        $(OBJDIR)\swap16.obj \
        $(OBJDIR)\swap32.obj \
        $(OBJDIR)\hostToLE16.obj \
        $(OBJDIR)\hostToLE32.obj \
        $(OBJDIR)\hostToBE16.obj \
        $(OBJDIR)\hostToBE32.obj \
        $(OBJDIR)\lEToHost16.obj \
        $(OBJDIR)\lEToHost32.obj \
        $(OBJDIR)\bEToHost16.obj \
        $(OBJDIR)\bEToHost32.obj \
        $(OBJDIR)\helper0B.obj

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\helper01.obj \
        $(OBJDIR)\helper02.obj \
        $(OBJDIR)\helper03.obj \
        $(OBJDIR)\helper04.obj \
        $(OBJDIR)\helper05.obj \
        $(OBJDIR)\helper06.obj \
        $(OBJDIR)\helper06A.obj \
        $(OBJDIR)\helper07.obj \
        $(OBJDIR)\helper08.obj \
        $(OBJDIR)\helper09.obj \
        $(OBJDIR)\helper0A.obj \
        $(OBJDIR)\helper_clibVersion.obj \
        $(OBJDIR)\helper_load_library.obj \
        $(OBJDIR)\helper_unload_library.obj \
        $(OBJDIR)\progParentData.obj

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
             "$(CLIBDIR)\helper.h"

!endif

$(OBJDIR)\helper01.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper02.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper03.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper04.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper05.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper06.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper06A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper07.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper08.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper09.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper0A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\helper_clibVersion.obj: $(DEPENDS_ON) \
           $(CLIBDIR)\Build\SetCLibVersion.BAT
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)
        
$(OBJDIR)\helper_load_library.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)
        
$(OBJDIR)\helper_unload_library.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\progParentData.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)
        
# Following generate only HTML
$(OBJDIR)\helperM1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\helperM2.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\helperM3.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\helperM4.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\swap16.obj: $(DEPENDS_ON)
        echo $(OBJDIR)\swap16.obj
        $(INVOKE_COMPILER)

$(OBJDIR)\swap32.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\hostToLE16.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\hostToLE32.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\hostToBE16.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\hostToBE32.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\lEToHost16.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\lEToHost32.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\bEToHost16.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\bEToHost32.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)

$(OBJDIR)\helper0B.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)


#############################################################
#   End of Makefile
#############################################################
