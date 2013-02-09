 IDENTIFICATION DIVISION.
 PROGRAM-ID.    test25.  
 AUTHOR.        D.Essex.
 DATE-WRITTEN.  December 5, 1999.
* REMARKS.
*    Test to call C program from COBOL program.
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

* 01 F1            PIC X(1).
 01 F1.
   05 F1-A            PIC X(5).
   05 F1-B            PIC X(1).
 01 F2            PIC 9(2).
 01 F3            PIC 9(4) COMP.
 01 F3-A          PIC 9(2).
 01 F4            PIC 9(3).
 01 WS1           PIC 9(2) COMP VALUE 23.
 
 PROCEDURE DIVISION.
    
* ----------------------------------------
  MOVE '=====0' TO F1.
  MOVE  6 TO F2.
  MOVE  8 TO F3.
  MOVE 11 TO F4.

  MOVE F3 TO F3-A.
  DISPLAY "main (test25)  COB input  :" F1 ":" F2 ":" F3-A ":" F4 ":".

  CALL "test25a" USING F1 F2 F3 F4.

  MOVE F3 TO F3-A.
  DISPLAY "main (test25)  COB return :" F1 ":" F2 ":" F3-A ":" F4 ":".
* ----------------------------------------
*  The following code can be used on the MinGW platform. 
*  It may work on Cygwin but has not been tested.

*  MOVE '0=====' TO F1.
*  MOVE  7 TO F2.
*  MOVE  9 TO F3.
*  MOVE 33 TO F4.

*  MOVE F3 TO F3-A.
*  DISPLAY "main (test25)  COB input  :" F1 ":" F2 ":" F3-A ":" F4 ":".

*  CALL WINAPI "test25c" USING F1 F2 F3 F4.

*  MOVE F3 TO F3-A.
*  DISPLAY "main (test25)  COB return :" F1 ":" F2 ":" F3-A ":" F4 ":".
* ----------------------------------------
  MOVE '0=====' TO F1.
  MOVE  7 TO F2.
  MOVE  9 TO F3.
  MOVE 33 TO F4.

  MOVE F3 TO F3-A.
  DISPLAY "main (test25)  COB input  :" F1 ":" F2 ":" F3-A ":" F4 ":".

  CALL "test25b" USING F1 F2 F3 F4.

  MOVE F3 TO F3-A.
  DISPLAY "main (test25)  COB return :" F1 ":" F2 ":" F3-A ":" F4 ":".
* ----------------------------------------

  MOVE WS1 TO F3-A.
  DISPLAY "main (test25)  COB WS1=" F3-A ":".
  DISPLAY "RETURN-CODE = " RETURN-CODE

  STOP RUN.
