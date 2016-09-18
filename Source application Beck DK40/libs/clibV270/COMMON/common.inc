#---------------------------------------------------------------------------
#
# Common portion of makefile shared by each CLIB component library
#
#    Required Path Environment Variables (unless defaults fit):
#
#       PC_BECKPATH  -  If using Paradigm Beck IPC Edition compiler
#       BCPATH       -  If using Borland C compiler
#
#     For HTML build with AUTODUCK the following environment variables
#     must be set before invoking NMAKE.
#       OP           -  Output Path, like: "..\RTOSDOC\CLIB"
#
#
#  NOTE:  A TASM.EXE is required in the Borland BIN directory
#        or a PASM.EXE is required in the Paradigm BIN directory.
#
#---------------------------------------------------------------------------

# Define GEN_ASM_LISTINGS here if you want the *.ASM compiler code 
# documentation to be generated.  It has been turned off for since
# the library code generation time (at least with the Paradigm) was
# taking an excessive amount of time.

# GEN_ASM_LISTINGS = 1

# DYNLINK_API builds the dynamic linking version of the CLIB API library
#   (Comment this out to build statically linked version.)
DYNLINK_API = 1

AUTODUCK = ..\..\..\..\..\Tools\Autoduck\autoduck


!ifdef USE_PARADIGM
# ----------------------------------
# Paradigm Beck Edition compiler
# ----------------------------------
# PC_BECKPATH environment variable provided?
!ifdef PC_BECKPATH
CCPATH  = $(PC_BECKPATH)
!else
CCPATH  = c:\Paradigm
!endif
CC              = "$(CCBIN)\pcc"
LD              = "$(CCBIN)\plink"
LIB             = "$(CCBIN)\plib"
ASM             = "$(CCBIN)\pasm"

# End !ifdef USE_PARADIGM
!else
# ----------------------------------
# BORLAND compiler, linker path
# ----------------------------------

# BCPATH environment variable provided?
!ifdef BCPATH
CCPATH = $(BCPATH)
!else
CCPATH = c:\bc5
!endif
CC              = "$(CCBIN)\bcc"
LD              = "$(CCBIN)\tlink"
LIB             = "$(CCBIN)\tlib"
ASM             = "$(CCBIN)\tasm"

# End !ifdef USE_PARADIGM ... !else ...
!endif


###########################################
# Tool directories
###########################################
CCBIN           = $(CCPATH)\bin
CCLIB           = $(CCPATH)\lib
CCINCL          = $(CCPATH)\include

####################################################
# DOCLIST.EXE creates a list of C-library functions
# for online help mapping to HTM files.
####################################################
DOCLIST_CMD  = ..\..\..\..\..\Tools\DocList\DOCLIST.EXE
!ifndef CLIB_LIST_PATH
CLIB_LIST_PATH = Clib.LST
!endif

#####################################################
#  Source file and include file directories
#####################################################
THISLIB         = $(CLIBDIR)\$(TARG_LIB)
COMMON_H        = $(CLIBDIR)\common
BUILD_DIR       = $(THISLIB)
OUTPUT_DIR      = $(CLIBDIR)\bin
HTML_TARGET     = $(OP)\$(TARG_LIB)\lib_index.htm

#####################################################
#  For documentation extraction with AUTODUCK,
#
#  Environment variable DOC_TITLE must be defined
#####################################################
!ifdef DOC_TITLE
!ifdef CLIB_SRC_PATH
CLIBDIR         = $(CLIB_SRC_PATH)
!else
# Default
CLIBDIR         = ..\..\..\..\CLIB
!endif
XMLDIR          = $(THISLIB)\xml
OBJDIR          = $(OP)\$(TARG_LIB)
INVOKE_AUTODUCK = $(AUTODUCK) /u /RHTML /f../CLIBDOC/CLIB_HTML.txt  \
            /t4 /x"DOC_$(@B)_ $(DOC_FILTER)" /d"Title=$(DOC_TITLE)" \
            /o$(OBJDIR)\$(@B).htm   %s \
            & \
            $(AUTODUCK) /u /RHTML /f../CLIBDOC/XML.txt  \
            /t4 /x"DOC_$(@B)_ $(DOC_FILTER)" /d"filename=$(DOC_PREFIX)/CLIB/$(TARG_LIB)/$(@B).htm" \
            /o$(XMLDIR)\$(@B).xml   %s \
            & \
            type $(XMLDIR)\$(@B).xml >>$(CLIB_XML_LIST_PATH)
INVOKE_COMPILER = $(INVOKE_AUTODUCK)
RUN_COMPILER = $(INVOKE_COMPILER)

# ASSEMBLE is used on API for which only dynamic link assembly code exists
#   (no SWI method that is), plus it has HTML to be extracted for its tag.
ASSEMBLE = $(INVOKE_AUTODUCK)
MAIN_TARGET  = X

# INVOKE_COMPILER_NO_DOC used on redundant C-Lib functions for which DOC
#  has already been produced for the original version of the function.
INVOKE_COMPILER_NO_DOC =

#####################################################
#  For code generation (Not documentation)
#####################################################
!else
# DOC_TITLE not defined, so here to build library code

CLIBDIR         = ..\..\CLIB

# CLIB_INCL_DIR defined in order to make a move of these header files
#   into some subdirectory (some day) easier to do.
CLIB_INCL_DIR     = $(CLIBDIR)

#  C Compiler
INVOKE_COMPILER = $(CC) -m$(MMODEL) $(CFLAGS) @$(COMPILER_CMD_FILE) %s
INVOKE_COMPILER_NO_DOC = $(INVOKE_COMPILER)
!ifdef GEN_ASM_LISTINGS
INVOKE_C2ASM    = $(CC) -m$(MMODEL) $(CFLAGS_C2ASM) @$(COMPILER_CMD_FILE) %s


!endif
# End of "%ifdef GEN_ASM_LISTINGS"

# ASM_ONLY applies to assembly for which no HTML documentation exists.
ASM_ONLY = $(INVOKE_TASM)

# ASSEMBLE is used on API for which only dynamic link assembly code exists
#   (no SWI method that is), plus it has HTML to be extracted for its tag.
ASSEMBLE = $(INVOKE_TASM)

######################################################
#  Dynamic linked API are written in assembly.
#  Switch between invoking assembler or compiler. 
######################################################

!ifdef DYNLINK_API
RUN_ASSEMBLER = $(INVOKE_TASM)
!else
RUN_COMPILER = $(INVOKE_COMPILER)
RUN_ASSEMBLER = $(INVOKE_C2ASM)
!endif

!ifndef SEL_MODEL
# Default to large model
SEL_MODEL = 0
!endif

# Memory Model Selection

!if ($(SEL_MODEL) == 1)
MMODEL_ASM = __MEDIUM__=1
MM_TAG = M
MMODEL = m
!elseif ($(SEL_MODEL) == 2)
MMODEL_ASM = __COMPACT__=1
MM_TAG = C
MMODEL = c
!elseif ($(SEL_MODEL) == 3)
MMODEL_ASM = __SMALL__=1
MM_TAG = S
MMODEL = s
!elseif ($(SEL_MODEL) == 4)
MMODEL_ASM = __HUGE__=1
MM_TAG = H
MMODEL = h
!else
MMODEL_ASM = __LARGE__=1
MM_TAG = L
MMODEL = l
# end !if ($(SEL_MODEL) == 1)
!endif

MAIN_TARGET  = $(OUTPUT_DIR)\$(TARG_LIB)$(MM_TAG).lib
OBJDIR       = $(THISLIB)\obj$(MM_TAG)
ASMDIR       = $(THISLIB)\asm$(MM_TAG)

# end !ifdef DOC_TITLE
!endif

##########################
# Compiler Flags
##########################
# -1 186
# -ml large memory model
# -v ==> "Source Level Debugging"
# -y ==> "Produce Line Number Info"
# -wpar ==> Suppress "Parameter 'ident' is never used" warning.
# -k- ==> Disable standard stack frame
# -O1 ==> Optimize for size

COPTS = -1  -D_$(@B)_ -r -w-par -v  -y -k- -O1
CFLAGS       = -c $(COPTS) -o$(OBJDIR)\$(@B).obj
!ifdef GEN_ASM_LISTINGS
CFLAGS_C2ASM = -S $(COPTS) -o$(ASMDIR)\$(@B).asm
!endif
AFLAGS       = /c /Fo$@         # assembler option flags

##########################
# Linker Flags
##########################
# -m "Map file with publics"
# -l "Include source line numbers"
# -s "Detailed map of segments"
# -c "Case significant in symbols"
# -v "Full symbolic debug information"
LFLAGS = -m -l -s -c -v       # linker flags


###  Assembler Options:  #####################################
#  ASM_EXTRA_OPTIONS (usually empty string) is optional.
# /t  ==> Suppress message if successful assembly.
# /z  ==> Display source line with error messages
# /zi ==> Full debug info
# /ml ==> Case sensitivity on all symbols
# /j.186 ==> Specify 80186 CPU
INVOKE_TASM  = $(ASM) /t /z /zi /j.186 /ml \
    /d$(MMODEL_ASM) $(ASM_EXTRA_OPTIONS)  $(THISLIB)\$(@B).asm, \
    $(OBJDIR)\$(@B).obj



#*****************************************
# Set desired Target and Command File name
#*****************************************
COMPILER_CMD_FILE = $(BUILD_DIR)\cmpopts.cmd


#*****************************************
# Primary Target for this makefile
#*****************************************
mainhere: checkfs $(COMPILER_CMD_FILE) $(MAIN_TARGET)

genHTML:  checkfsdoc $(HTML_TARGET)


checkfsdoc:
	@echo off
	@if not exist $(OBJDIR) 	md $(OBJDIR)
	@if not exist $(XMLDIR) 	md $(XMLDIR)


######################################################################
#  Establish output directories
#
#  Generate cmpopts.cmd file
#
#    This file is passed to the compiler on the command line.
#    It specifies the include file paths using the -I option.
#
#    Note:  It was necessary to list the compiler's include directory,
#          $(CCINCL), last here so that out dated Beck C-library 
#          header files distributed with the Paradigm Beck Edition
#          compiler are overriden by current header files in this
#          CLIB build area.
#
######################################################################
checkfs:
	@echo off
	@if not exist $(OBJDIR)    md $(OBJDIR)
!ifdef GEN_ASM_LISTINGS        
	@if not exist $(ASMDIR)    md $(ASMDIR)
!endif
	@echo -I$(SOURCE) > $(COMPILER_CMD_FILE)
	@echo -I$(COMMON_H) >> $(COMPILER_CMD_FILE)
	@echo -I$(CLIBDIR) >> $(COMPILER_CMD_FILE)
	@echo -I"$(CCINCL)" >> $(COMPILER_CMD_FILE)
	@echo -DCLIB_VERSION=$(CLIBVERSION) >> $(COMPILER_CMD_FILE)


#######################################################################
#  Build Main Target:  *.LIB
# ---------------------------------------------------------------------
$(MAIN_TARGET): $(OBJS) $(CODE_ONLY)
	if exist $@ del $@
	if exist $*.cmd del $*.cmd
	$(LIB) @<<$*.cmd
$@ /P32 &
+$(**: = &^
+)
<<KEEP
        del $*.cmd

clean:
!ifdef DOC_TITLE
	if exist $(OBJDIR)\*.htm del $(OBJDIR)\*.htm
!else
	if exist $(OBJDIR)\*.exe del $(OBJDIR)\*.exe
	if exist $(OBJDIR)\*.cmd del $(OBJDIR)\*.cmd
	if exist $(OBJDIR)\*.asm del $(OBJDIR)\*.asm
	if exist $(OBJDIR)\*.lib del $(OBJDIR)\*.lib
 	if exist $(OBJDIR)\*.obj del $(OBJDIR)\*.obj
        if exist $(ASMDIR)\*.asm del $(ASMDIR)\*.asm
!endif

#######################################################################
#  Extract Documentation:  *.HTM
# ---------------------------------------------------------------------
# DOCLIST command line arguments:
#  -d  -  Define extraction tag to be used by parser
#  -s  -  Path of source files to parse
#  -h  -  Directory path for HTML files
#  -o  -  Name of output file that is appended (BeckCLIB.LST)


$(HTML_TARGET): $(OBJS) $(HTML_ONLY)
    $(AUTODUCK) /u /RHTML /f../CLIBDOC/CLIB_HTML.txt /t4       \
           /x"DOC_INDEX $(DOC_FILTER)"  /d"Title=$(DOC_TITLE)" \
           /o$(HTML_TARGET)  $(THISLIB)\$(LIB_SRC)
    $(DOCLIST_CMD) -d"$(DOC_FILTER)" -s$(THISLIB)\$(LIB_SRC) \
           -hCLIB\$(TARG_LIB) -o$(CLIB_LIST_PATH)


#############################################################
#   End of common.inc
#############################################################
