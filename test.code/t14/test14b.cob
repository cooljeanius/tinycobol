 IDENTIFICATION DIVISION.
 PROGRAM-ID.    TestVariable. 
 AUTHOR.        Rildo Pragana.
 DATE-WRITTEN.  November 23, 1999.
* REMARKS.  Exercising the STRING statement.
*
 ENVIRONMENT DIVISION.
 
 DATA DIVISION.

 WORKING-STORAGE SECTION.
    01      VARIABLES.
     03     VAR1    PIC X(4) VALUE "AAAA".
     03     VAR2    PIC X(8) VALUE "BBBXABBB".
     03     STRVAR  PIC X(25) VALUE SPACES.
     03     PTR     PIC 9(3) VALUE 5.

 PROCEDURE DIVISION.
    display "Before: [" STRVAR "]"
    string "test", VAR1, 123.45 delimited by "." 
        VAR2 DELIMITED BY "XA" "pqrstuvwxyz" INTO STRVAR
        ON OVERFLOW
            display "string overflow found!"
        NOT ON OVERFLOW
            DISPLAY "string operation successful!"
            .
    display    "After : [" STRVAR "]"
    string "-- with POINTER --" into STRVAR
        with pointer PTR
        ON OVERFLOW
            DISPLAY "too large to be placed here!"
            go to end-pgm.
    display "Pointer:[" STRVAR "]"
    string "test" VAR1 123.45 delimited by "." 
        VAR2 DELIMITED BY "XA" "pqrstuvwxyz123" INTO STRVAR
        ON OVERFLOW
            DISPLAY "too large to be placed here!"
            go to end-pgm
        NOT ON OVERFLOW
            display "string operation scceeded!".
    display "After(2): [" STRVAR "]"
    .
 end-pgm.
    stop run
    .

