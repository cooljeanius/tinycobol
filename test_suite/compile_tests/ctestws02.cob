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
* Maximun elementary alphanumeric size is 12750
* This limit can be overcome by using groups items 
 01  WS-VARIABLES.
*     05 WS-LARGE-PICX                     PIC X(51000).
     05 WS-LARGE-PICX                     PIC X(12750).
     05 FILLER                            PIC X(12750).
     05 FILLER                            PIC X(12750).
     05 FILLER                            PIC X(12750).

 01  WS-VARIABLES1.
     05 WS-LARGE-PICX1  PIC X(12750) OCCURS 100.

 PROCEDURE DIVISION.
   STOP RUN.
 A000-EXIT.
     EXIT.
