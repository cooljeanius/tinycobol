 IDENTIFICATION DIVISION.
 PROGRAM-ID.	TEST07.
 ENVIRONMENT DIVISION.

 CONFIGURATION SECTION. 
 SPECIAL-NAMES.
     DECIMAL-POINT IS COMMA.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.

 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
* 01  TEST1  PIC  Z.Z(3).ZZ9,9(2).
* 01  TEST2  PIC  AA-9(7).X(3)/99.
 01  VAR    PIC  X(20) VALUE "Hello from cobol!".
 01  VAR1   PIC  X(20) VALUE "Subroutine in cobol".
 01  RESULT PIC  X(20) VALUE SPACES.

 PROCEDURE DIVISION.

*    display "This program don't run without receiving " NO ADVANCING
*    display "struct fld_desc as argument."

     display spaces.
     display "Will call a subroutine in Cobol".
     display "-------------------------------".
     call "COBSUB" USING VAR1 RESULT.
     display "---- Returned from cobsub -----".
     display "RETURNED: [" RESULT "]".
     display spaces.
     display "Will call a subroutine in C".
     display "---------------------------".
     call "subrot" USING VAR.
     display "---- Returned from subrot -----".
     display spaces.


*    CALL "picExpand" USING TEST1.
*    CALL "picExpand" USING TEST2.
 99-END.
     STOP RUN.
