 IDENTIFICATION DIVISION.
 PROGRAM-ID. CTEST_PIX.
 AUTHOR.  GLEN COLBERT.
 INSTALLATION. Tiny Cobol Compiler Project.
 SECURITY. NONE.
* Pares tests for pictures.

 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.

 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS-VARIABLES.
     05 WS-LARGE-PIC9                     PIC 9(16).

 PROCEDURE DIVISION.
   STOP RUN.
 A000-EXIT.
     EXIT.