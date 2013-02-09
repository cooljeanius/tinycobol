Tests on creating and using static and shared libraries using C functions and
COBOL sub-programs.

First some C functions and COBOL sub-programs are compiled to create a 
static or shared library.

Then the main COBOL program is compiled and linked to the test library.

When run, the main COBOL program will call (by reference) C functions and 
COBOL sub-programs. 

--------------------------------------------------------------------------------

Notes:
Shared library requires the following commands to ensure library is found.
LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH 
export LD_LIBRARY_PATH

To run use rt.sh to set the LD_LIBRARY_PATH environmental variable.

To build use one the following commands.

If htcobol is located in the development directories use the mak.sh script
located in the test.code directory as follows. 

../mak.sh all 

If htcobol has been installed in one the normal bin directories, use the 
Makefile in the test.code/t25 directory as follows. 

make all 
make 
