[ReadMe for Sourcecode Software Package]


               @CHIP-RTOS API
               ============== 
         (For Borland C++ or Paradigm Beck Edition Compilers)


                 Contents:
                 =========
  
            1.     Introduction
            2.     Directory Structure 
            3.     Name Convention
            4.     How to Build the libs
            5.     How to Build the documentation
            6.     How to add a function


1.Introduction:
---------------

This software package includes the complete source code to build the @CHIP-RTOS
libraries. The libs provide an easy access to the IPC@CHIPs operating system using
the programming language C. Beside the c-source code also the complete documentation
source is integrated into the cfile. It will extacted (to the html docu) using 
AUTODUCK. 
If you do not want to build the Clib files by yourself, you can download the binaries
and the complete docu on our website www.beck-ipc.com.


2.Directory Structure:
----------------------
.\       - lib files / c-header files
.\bin    - binary outputs
.\build  - batchfiles to build the lib(s)
.\common - commons files
.\bios   - c-source: BIOS ints API lib
.\can    - c-source: CAN ints API lib
.\cgi    - c-source: CGI/webserver API lib
.\fossil - c-source: Fossil API lib
.\helper - c-source: Helper functions
.\hw     - c-source: Hardware API lib
.\i2c    - c-source: I2C API lib
.\pktdrv - c-source: Packet driver API lib
.\rtx    - c-source: RTOS API lib
.\spi    - c-source: SPI API lib
.\tcpip  - c-source: TCP/IP API lib
.\clib   - docu: CLIB html documentation


3.Name Convention:
------------------
CLIB[version][model].lib
version: lib version  
model  : C(COMPACT), L(LARGE), M(MEDIUM), S(SMALL), H(HUGE)
 

e.g. CLIB100L.lib    -> Build with Borland  for use with Borland  compiler
     CLIP100L.lib    -> Build with Paradigm for use with Paradigm compiler


4.Build the libs:
-----------------
The requirements to build the CLibs:
  NMAKE   (Microsoft's Make Tool V1.62)
  BCC     (Borland 5.02 C Compiler)
  TLIB    (Borland's Library generation tool)
  TASM    (Borland's Assembler)

As an alternative to the Borland tools, the Paradigm Beck
Edition compiler may be used.  Refer to the USE_PARADIGM
environment variable near the top of the BUILD\BUILD.BAT
for more details how this is done.  Note that if you do not
have an assembler available, then you rebuild the CAN libraries
(which use assembly language dynamic linking code) or the
RTX/PCSEGM.OBJ file.

Before you start to build the libs, you have to set root path
of your borland compiler (e.g. C:\COMPILERS\BC5). You do that
by declare the enviroment variable BCPATH in the command line:
  C:\CLIBS>set BCPATH=C:\COMPILERS\BC5

or for the Paradigm compiler define the PC_BECKPATH environment
variable like:
  C:\CLIBS>set PC_BECKPATH=C:\COMPILERS\Paradigm



Now you can start to build the libs. Change your directory in the
.\BUILD dir. To build all of the C libraries, invoke the BUILD\BUILD.BAT 
batch file.
You find the lib files in the root dir of the clib softare package. 
For every memory model (Compact, Large, Medium, Small, Huge) a seperate
lib file exists.



5.Build the documentation:
--------------------------
At this time it is not supported to create the documention by yourself. Please
use the html documentation which is available with the binary API lib ZIP file.


6.How to add a function:
------------------------
Use the following steps when you adding another function to the library:

1)  Invent a unique compilation switch name such as "_rtx50_".  The leading and
  trailing underscores are important here to the build process.  The convention
  used so far is to include the library name and RTOS interrupt service number
  in the compilation switch name.  When more than one library function uses the
  same RTOS interrupt service, then the switch name can be extended in some 
  manner not to exceed 8 characters between the two underscores.  (The 8
  character limitation is due to the resulting DOS object file will be
  named based on this compilation switch name during the build process.)
  Surround your new library function with this new compilation switch, e.g. ...

#ifdef _newtag_
  my_new_function() { ... }
#endif


2)  Make two new entries in the respecitive libraries MAKEFILE:

  a)  At the  OBJS = \ macro where all the component object files are
    listed, add your new function's object file name to the list.
    Alphabetic order is recommended here.  Take care with usage of the line
    continuation marks, '\', within this macro definition.  The name you
    give the new object file must match the compilation switch name you have
    surrounded your library function with in the source file, with the
    leading and trailing underscores removed.

  b)  Down near the end of the MAKEFILE add a dependancy statement like ...

$(OBJDIR)\rtx55.obj: $(DEPENDS_ON) 
        $(INVOKE_COMPILER)

    Your new statement should immitate exactly one of the existing statements,
    with only the object file name changed.

