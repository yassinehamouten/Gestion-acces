#---------------------------------------------------------------------------
# Makefile for I2C.LIB Library
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
#           nmake /f ../../CLIB/I2C/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/I2C/makefile clean
#
#    Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = I2C
LIB_SRC  = i2c_api.c


# -------------------------------------------------------
#  OBJECTS: *.obj required for I2C.LIB
#
#    Note: To add an object file, list it here and 
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\i2c80.obj  \
        $(OBJDIR)\i2c81.obj  \
        $(OBJDIR)\i2c82r.obj \
        $(OBJDIR)\i2c82t.obj \
        $(OBJDIR)\i2c83r.obj \
        $(OBJDIR)\i2c83t.obj \
        $(OBJDIR)\i2c84.obj  \
        $(OBJDIR)\i2c85.obj  \
        $(OBJDIR)\i2c86r.obj \
        $(OBJDIR)\i2c86t.obj \
        $(OBJDIR)\i2c87r.obj \
        $(OBJDIR)\i2c87t.obj \
        $(OBJDIR)\i2c88.obj  \
        $(OBJDIR)\i2c8b.obj  \
        $(OBJDIR)\i2c8e.obj  \
        $(OBJDIR)\i2c8f.obj  \
        $(OBJDIR)\i2cb0.obj  \
        $(OBJDIR)\i2cb1.obj  \
        $(OBJDIR)\i2cb2.obj  \
        $(OBJDIR)\i2cb3.obj  \
        $(OBJDIR)\i2cb4.obj  \
        $(OBJDIR)\i2cb5.obj  \
        $(OBJDIR)\i2cb6.obj  \
        $(OBJDIR)\i2cb7.obj  \
        $(OBJDIR)\i2cb8.obj

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
             "$(CLIBDIR)\i2c_api.h" \
             "$(THISLIB)\i2c_priv.h"
!endif

$(OBJDIR)\i2c80.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c81.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c82r.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c82t.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c83r.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c83t.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c84.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c85.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c86r.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c86t.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c87r.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c87t.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c88.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c8b.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c8e.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2c8f.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2cb0.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2cb1.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2cb2.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2cb3.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2cb4.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2cb5.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2cb6.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\i2cb7.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)


$(OBJDIR)\i2cb8.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)



#############################################################
#   End of Makefile
#############################################################
