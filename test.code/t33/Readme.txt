Tests on the CALL statement using dynamic calls.

Note: 
Reverse function calls, meaning calling fuctions
found in the original calling DLL or binary,
will work when using ELF (UN*X), but
will NOT work when using PE-COFF (Win32).

--------------------------------------------------------------------------------
UN*X:

To build use one the following commands just type,

make 

To run 'dyntest' the TCOB_LD_LIBRARY_PATH and LD_LIBRARY_PATH environment variables 
must be set to include the PWD so tha the shared libraries can be found.

export LD_LIBRARY_PATH=..:./../lib:$LD_LIBRARY_PATH
export TCOB_LD_LIBRARY_PATH=.

Or run rt.sh which well set the environment variables and run the program.

--------------------------------------------------------------------------------
Win32 (MinGW):
The following will work on MinGW. 
It should work on Cygwin with GCC version 3.x (some versions of 2.95.x).

To build use one the following commands.

DOS/CMD:
mingw32-make

MSYS:
make

To run 'dyntest.exe' all paths for executables and DLL's (including the TC 
run-time) must be found in the 'PATH' environment variable.

Example:
DOS/CMD:
set PATH=.;D:\TinyCOBOL;%PATH%
MSYS:
export PATH=".;D:/TinyCOBOL;$PATH"

Or run rt.bat which well set the environment variables and run the program.



