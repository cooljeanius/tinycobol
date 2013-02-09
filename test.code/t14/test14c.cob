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
    move 2 to PTR
    move "abcde-x-x-xfghi   jklm.nopqrstuvwxyz" TO STRVAR.
    display "Before VAR1 = [" VAR1 "]"
    display "Before VAR2 = [" VAR2 "]"
    display "Before VAR3 = [" VAR3 "]"
    display "Before VAR4 = [" VAR4 "]"
    unstring STRVAR
        delimited by "." 
            or all "-x" 
            or all spaces
        into 
            VAR1 
                delimiter in DLM1 
                count in CNT1 
            VAR2 
            VAR3
                delimiter in DLM3
            VAR4
                delimiter in DLM4
                count in CNT4
        with pointer PTR
        tallying in TALLY 
        on overflow
            display "***** unstring operation overflow *****"
        not on overflow
            display "unstring successful"
        .
    display "VAR1 = [" VAR1 "], CNT1 = [" CNT1 "] DLM1 = [" DLM1 "]"
    display "VAR2 = [" VAR2 "]"
    display "VAR3 = [" VAR3 "], DLM3 = [" DLM3 "]"
    display "VAR4 = [" VAR4 "], CNT4 = [" CNT4 "] DLM4 = [" DLM4 "]"
*    display "VAR4 = [" VAR4 "], CNT4 = [" CNT4 "]"
    display "TALLY = [" TALLY "]".
 end-pgm.
    stop run
    .

