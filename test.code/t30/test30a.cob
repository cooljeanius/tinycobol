 IDENTIFICATION DIVISION.
 PROGRAM-ID.    multiseg.
 ENVIRONMENT DIVISION.

 CONFIGURATION SECTION. 
 SPECIAL-NAMES.
    DECIMAL-POINT IS COMMA.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.

 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  TEST1  PIC  Z.Z(3).ZZ9,9(2).
 01  TEST2  PIC  AA-9(7).X(3)/99.
 01  VAR    PIC  X(20) VALUE "Hello from cobol!".
 01  VAR1   PIC  X(20) VALUE "Subroutine in cobol".
 01  RESULT PIC  X(20) VALUE SPACES.

 PROCEDURE DIVISION.

     display "Will call a subroutine in Cobol".
     display "-------------------------------".
     call "COBSUB" USING VAR1 RESULT.
     display "---- Returned from cobsub -----".
     display "RETURNED: [" RESULT "]".

 99-END.
     STOP RUN.
 END PROGRAM multiseg.

 IDENTIFICATION DIVISION.
 PROGRAM-ID.    COBSUB.
 ENVIRONMENT DIVISION.

 CONFIGURATION SECTION. 

 DATA DIVISION.

 WORKING-STORAGE SECTION.
 01  VAR3   PIC X(20) value "String to return.".

 LINKAGE SECTION.
 01  VAR1   PIC X(20).
 01  VAR2   PIC X(20).


 PROCEDURE DIVISION USING VAR1 VAR2.
 
     display "Received from main cobol program: [" VAR1 "]".
     move VAR3 to VAR2.

 EXIT PROGRAM.
 END PROGRAM COBSUB.

