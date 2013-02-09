Notes:
The 'EXTERNAL' clause in the 'SELECT' statement can be used to
relate internal to external filenames at run time, by using 
environment variables.

The syntax is a follows.
 SELECT ... ASSIGN TO EXTERNAL { variable | literal }

In example 'test19b.cob' the following can be used.

 SELECT TEST-FILE-OUT ASSIGN TO EXTERNAL WS-FILENAME-OUT
 SELECT TEST-FILE-OUT ASSIGN TO EXTERNAL "FILENAMEOUT" 
 
In this case the stored value of the literal or variable
is used as an environment variable which is used to determined 
the actual filename.

If no environment variable is found or is empty, then the 
filename defaults to the value stored in the literal or variable.

To run type(example):
test19 
test19 output-filename
test19a
test19b
test19b output-filename
