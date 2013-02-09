How to build (make) sample test programs:

Run the 'configure' script (tconfig.mingw.sh) in the source root directory.
Build (make or tcbuild.mingw.bat) and install (sudo make install OR copy/paste) the 
TC binaries.
To generate the 'test.code' make files run the 'mconfig.sh' script.

The generated make files will use the 'configure' setup 

To build all the samples just type 'make' from 
the 'test.code' directory.

The individual sample programs can be build from the individual directories.
Example (test.code/t03): 
#cd test03
#make test03 - to build test03 (CMD.EXE : mingw32-make)
#make - to build all in directory (UN*X or MSYS only)

To clean all type 'make clean' from the 'test.code' directory.

Type 'make cleanall' to clean and delete make files from the 'test.code' sub-directories.

------------------------------------------------------------------------------
How to run sample test programs:

From the individual test directory type program-name.
Example (test.code/t03): 
#cd test03
#./test03
 
Some programs (t25 t33) will require setting of the LD_LIBRARY_PATH and TCOB_LD_LIBRARY_PATH 
environment variables. 
The enclosed 'rt.sh' script can be used to set and run the programs. 

------------------------------------------------------------------------------
Sample test programs:

t00: ACCEPT/DISPLAY statement.

t01: Math verbs tests ADD, SUBTRACT, MULTIPLY, DIVIDE, COMPUTE.

t02: PERFORM and COPY/COPY REPLACING statements.

t03: ACCEPT/DISPLAY statement from DATE/DISPLAY, stdin/stdout.  

t04: Sequential file IO.

t05: Branching (Simple PERFORMs and WITH TEST AFTER/BEFORE option).

t06: Variable length sequential file IO.

t07: Calling C and COBOL programs from COBOL.

t08: Sort file I/O.

t09: Program to test MOVE verb with reference modification.

t10: Sequential and line sequential file I/O.

t11: Sequential, line sequential and print file I/O.

t12: Indexed file I/O.

t13: Indexed variable length file I/O.

t14: STRING, UNSTRING and INSPECT statements.

t15: Calling (Reference Value) C and COBOL programs from COBOL.

t16: GO TO label-1 ... label-n DEPENDING ON variable .                 

t17: ACCEPT FROM command line, environment variables. Set RETURN-CODE variable.

t18: Relative file I/O (Fixed and variable length).

t19: Multi sequential file I/O with run time file name using command 
     line arguments. And external file name assignments using non-standard 
     extensions in SELECT and FD statements.

t20: SEARCH and SEARCH ALL statements. 

t21: COBOL-85 scope delimiters (END-*) and in-line PERFORM tests. 

t22: IF/ELSE conditional statements test.

t23: ACCEPT/DISPLAY Screens.

t24: EVALUATE statement.
 
t25: Tests on creating and using static and shared libraries using C functions 
     and COBOL sub-programs.

t26: Program to test the ACCEPT/DISPLAY LINE POSITION statement. 
 
t27: Program to test REPORT generator and statements (Experimantal: does not work). 

t28: Program to test USAGE POINTER types. 

t29: The CORRESPONDING option of the MOVE, ADD, SUBTRACT statements. 

t30: Sequence of COBOL source programs.

t31: Variable record size sequential file IO.

t32: Variable size and multi-dimentional arrays.

t33: CALL statement using dynamic calls.

t34: CHAIN statement, CHAINING procedure.
 
t35: Intrinsic functions.
 
t36: Indexed and relative file IO using write 'WITH LOCK' 
   (Experimantal: does not work).
 
tdb01: ISAM proof of concept using muti-index BDB file.
   (Deprecated: replaced with VB-ISAM).

tdb02: Sample programs to test Postgres SQL interface.

tdb03: Sample programs to test CGI interface.

tgui01: Program to test GUI using tcl/tk. 

tgui02: Examples on how to integrate TC programs with a (GTK and Win32) GUI front ends. 

ReportGen: Sample report generator extensions.

esql: Sample ESQL Code for Use with Firebird [1] SQL. 

------------------------------------------------------------------------------
Links:

1) Firebird SQL
http://www.firebirdsql.org
