#---------------------------------------------------------------------------
# Makefile for SPI.LIB Library
#
#
#  To Build Library:  Invoke make from the subdirectory of CLIB where this
#                     library's source files reside.
#
#                     Assure DOC_TITLE environment variable is not set.
#
#  To Extract HTML Documentation:
#       Invoke make from DOC\CLIBDOC directory with environment 
#       variables set:
#
#       DOC_TITLE - Set to string to pass to AUTODUCK /d argument.
#
#       and specify make target 'genHTML', e.g.
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/SPI/makefile genHTML
#
#       or to clear out existing documentation for a full rebuild
#
#           set DOC_TITLE=The Title
#           nmake /f ../../CLIB/SPI/makefile clean
#
#  Required Path Environment Variables (unless defaults found deep
#             inside ../COMMON/COMMON.INC fit your environment):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#           
#---------------------------------------------------------------------------

TARG_LIB = SPI
LIB_SRC  = spiapi.c



# -------------------------------------------------------
#  OBJECTS: *.obj required for SPI.LIB
#
#    Note: To add an object file, list it here and
#         add a dependancy statement for the new file
#         down below.
# ------------------------------------------------------

# Full set of files to be built and linked
OBJS = \
        $(OBJDIR)\spi90.obj  \
        $(OBJDIR)\spi90A.obj \
        $(OBJDIR)\spi95.obj  \
        $(OBJDIR)\spi95A.obj \
        $(OBJDIR)\spi96.obj  \
        $(OBJDIR)\spi96A.obj \
        $(OBJDIR)\spi97.obj  \
        $(OBJDIR)\spi97A.obj \
        $(OBJDIR)\spiA0.obj  \
        $(OBJDIR)\spiA5.obj  \
        $(OBJDIR)\spiA6.obj  \
        $(OBJDIR)\spiA7.obj  \
        $(OBJDIR)\spiA8.obj  \
        $(OBJDIR)\spiA8A.obj \
        $(OBJDIR)\spiA8B.obj \
        $(OBJDIR)\spiA8C.obj \
        $(OBJDIR)\spiA8D.obj \
        $(OBJDIR)\spi90dyn.obj \
        $(OBJDIR)\spi91dyn.obj \
        $(OBJDIR)\spi92dyn.obj \
        $(OBJDIR)\spi93dyn.obj \
        $(OBJDIR)\spi94dyn.obj \
        $(OBJDIR)\spi95dyn.obj \
        $(OBJDIR)\spi96dyn.obj \
        $(OBJDIR)\spi97dyn.obj \
        $(OBJDIR)\spi98dyn.obj \
        $(OBJDIR)\spi99dyn.obj \
        $(OBJDIR)\spi9Adyn.obj \
        $(OBJDIR)\spi9Bdyn.obj \
        $(OBJDIR)\spi9Cdyn.obj \
        $(OBJDIR)\spi9Ddyn.obj \
        $(OBJDIR)\spi9Edyn.obj \
        $(OBJDIR)\spi9Fdyn.obj \
        $(OBJDIR)\spiA0dyn.obj


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
             "$(CLIBDIR)\spiapi.h" \
             "$(THISLIB)\spi_priv.h"
!endif

$(OBJDIR)\spi90.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spi90A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spi95.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spi95A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spi96.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spi96A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spi97.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spi97A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spiA0.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spiA5.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spiA6.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spiA7.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spiA8.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spiA8A.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spiA8B.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spiA8C.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spiA8D.obj: $(DEPENDS_ON)
        $(INVOKE_COMPILER)
        $(INVOKE_C2ASM)

$(OBJDIR)\spi90dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi91dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi92dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi93dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi94dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi95dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi96dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi97dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi98dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi99dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi9Adyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi9Bdyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi9Cdyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi9Ddyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi9Edyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spi9Fdyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)

$(OBJDIR)\spiA0dyn.obj: $(DEPENDS_ON)
	$(ASM_ONLY)


#############################################################
#   End of Makefile
#############################################################
