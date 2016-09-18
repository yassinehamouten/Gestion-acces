
  Invoke BUILD.BAT from this directory to build all the C libraries.
This builds libraries for each of the five memory models supported. 
The BUILD.BAT batch file invokes the BUILD_LIB.BAT for each library.

  The libraries build batch and makefiles are prepared to build with
either the Borland C 5.02 compiler or the Paradigm Beck Edition compiler.
The compile is selected with the USE_PARADIGM environment variable either
being defined or not up near the top of the BUILD.BAT file.  NMAKE is
used to process the various makefiles for each component library.

  Refer to notes in BUILD.BAT for more details.

  The heirarchy of BATCH files used to build the libraries is as 
follows:

   BUILD.BAT
     |--  BUILD_LIB.BAT - Executed in each individual lib's sub directory
     |      |-- NMAKE   - Invoked for each of 5 memory models
     |
     |--  BPOOL.BAT     - Combines the libraries into a single LIB for each
                          memory model.


  There is a LIBCLEAN.BAT which can be used to clear out all the intermediate
files to force a full rebuild.