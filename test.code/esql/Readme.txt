TinyCOBOL can be used with embedded SQL.
 
COBOL ESQL must first be pre-proccessed so that all SQL statements are converted
to COBOL syntax. Mostly CALL statements.

Note that each SQL database uses a vendor specific API, so the COBOL ESQL pre-proccessor 
is usually supplied by the database vendor.

These examples were tested using the 'Firebird'[1] SQL database. 
Using a similar approach, other SQL databases should work with TinyCOBOL, in theory.

To build the ESQL COBOL sample programs, using 'Firebird', just type 'make'. 
The make file will pre-proccess, compile and link the COBOL ESQL sources to produce
the executables.

example: esql.create
#make esql.create
gpre -co -d demo.gdb esql.create.ecob
mv -i esql.create.ecob.cbl esql.create.cob
htcobol -c -P -I/usr/share/htcobol/copybooks esql.create.cob
gcc -o esql.create esql.create.o -lhtcobol -ldb1 -lncurses -lm -ldl -lcrypt -L/opt/interbase/lib -lgds 

To run the sample programs, using 'Firebird', use the supplied shell script 'resql.sh'.
Use the 'all' option to run all the programs in sequence.

example: esql.create
#resql.sh esql.create
DEMO ESQL PROGRAM 
DATABASE CREATE RETURNS CODE:  000000000


--------------------------------------------------------------------------------------
These are the original notes as supplied by Andrew Cameron.

TinyCOBOL can now compile the COBOL Code Generated by GPRE from the Firebird
SQL DATABASE. This now means that it is possible to write cobol Programs using
ESQL commands and Compile and run the resultant code.

Here is a short write up on how to get started.
Go to http://firebird.sourceforge.net and download and install the Classic
version of Firebird from the Download section. I installed 
FirebirdCS-1.0.0.796-0.i386.rpm.  

The Build Script is an example of how I compile and run the code.
Any file ending in .ecob is the scource code.
The fixit script gets rid of the "-" in column 1 as TinyCOBOL does not like it.

I have noticed that there are a few Bugs in Gpre in that it sometimes does
not declare a variable name or mispells it. Report all such errors on the 
Firebird mailinglist so that they can fix it. I just used redefines to get
around the problem for now. These bugs are now fixed in the latest nightly build.

/opt/interbase/bin/qli Is a command line Interface
To see the Database created by these Programs
/opt/interbase/bin/qli
> ready demo.gdb
> select * from FRIEND;
will display the contents of the Table FRIEND.

Have fun with ESQL.
While you are about it download and Read the Firebird Manuals for assistance.

Regards
Andrew Cameron
