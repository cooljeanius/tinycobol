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
     05 WS-LARGE-PIC9                     PIC S9(16)
              USAGE IS COMPUTATIONAL-3.
     05 WS-NORMAL-PIC9                     PIC S9(6)
              USAGE IS COMP-3.

 PROCEDURE DIVISION.
   MOVE 0     TO WS-LARGE-PIC9.
   MOVE 0     TO WS-NORMAL-PIC9.
   STOP RUN.
 A000-EXIT.
     EXIT.