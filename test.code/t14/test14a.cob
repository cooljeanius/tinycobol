 IDENTIFICATION DIVISION.
 PROGRAM-ID.    TEST14a. 
 AUTHOR.        Rildo Pragana.
 DATE-WRITTEN.  November 23, 1999.
* REMARKS.   Exercising the STRING statement.
*
 ENVIRONMENT DIVISION.
 
 DATA DIVISION.

 WORKING-STORAGE SECTION.
    01      VARIABLES.
     03     VAR1    PIC X(4) VALUE "AAAA".
     03     VAR2    PIC X(8) VALUE "BBBXABBB".
     03     VAR3    PIC X(3) value spaces.
     03     VAR4    PIC X(5) value spaces.
     03     STRVAR  PIC X(36) VALUE "abcdefghijklmnopqrstuvwxyz".
     03     TALLY     PIC 9(2) value zeroes.
     03     CNT1    PIC 9(5) value zeros.
     03     CNT2    PIC 9(6) value zeros.
     03     CNT3    PIC 9(6) value zeros.
     03     CNT4    PIC 9(6) value zeros.
     03     PTR     pic 9(7).
     03     DLM1    pic X(10) value spaces.
     03     DLM2    pic X(10) value spaces.
     03     DLM3    pic X(10) value spaces.
     03     DLM4    pic X(10) value spaces.

 PROCEDURE DIVISION.
    move 2 to PTR.
*    move "abcde-x-x-xfghi   jklm.nopqrstuvwxyz" TO STRVAR.
    move "XXXXXAAABCDAAAXX**XYZAAA" to STRVAR.
    display "Before: " STRVAR.
    inspect STRVAR 
        tallying CNT1 for characters
*           CNT2 for all "x" before "g"
        replacing 
            all "A" by "Z" after 'BC' before 'Z'
                "A" by "U"
                "Z" by "-" after 'C'
            leading "XX" by "-x". 
    
    display "After : " STRVAR.
 end-pgm.
    stop run
    .

