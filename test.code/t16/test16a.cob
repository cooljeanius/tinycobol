 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST16A.
 AUTHOR.  DESSEX.
 INSTALLATION. Tiny Cobol Compiler Project.
 SECURITY. NONE.
* TEST GO TO ON VERB FORMAT.

 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.

 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS-VARIABLES.
*     05 WS-DATA                           PIC X(5).
     05 WS-INT OCCURS 3 TIMES             PIC 99.
     05 WS-INT0                           PIC 999  VALUE 3 .
*     05 WS-INT1                           PIC S9(4) COMP VALUE 4 .
*     05 WS-INT2                           PIC S9(4) COMP VALUE 5 .
*     05 WS-INT3                           PIC S9(9) COMP.

 PROCEDURE DIVISION.
 000-MAIN.
*     MOVE 1 TO WS-INT (1).
*     DISPLAY "WS-INT (1) =" WS-INT (1) ";".
     MOVE 2 TO WS-INT (2).
*     MOVE 3 TO WS-INT (3).
     GO TO A1, A2 A3 DEPENDING ON WS-INT(2).
     DISPLAY "FAIL GO TO 1"
     GO TO Z9.
 A1.
     DISPLAY "PASS A1".
     GO TO A4.
 A2.
     DISPLAY "PASS A2".
     GO TO A4.
 A3.
     DISPLAY "PASS A3".

 A4.
     GO TO B1, B2 B3 DEPENDING ON WS-INT0.
     DISPLAY "FAIL GO TO 2"
     GO TO Z9.
 B1.
     DISPLAY "PASS B1".
     GO TO Z9.
 B2.
     DISPLAY "PASS B2".
     GO TO Z9.
 B3.
     DISPLAY "PASS B3".

 Z9.
     DISPLAY "PROGRAM END Z9".
     STOP RUN.
