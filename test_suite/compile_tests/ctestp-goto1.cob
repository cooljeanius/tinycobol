 IDENTIFICATION DIVISION.
 PROGRAM-ID. CTESTP_GOTO1.
 AUTHOR.  STEPHEN CONNOLLY.
 INSTALLATION. Tiny Cobol Compiler Project.
 SECURITY. NONE.
* TEST GO TO DEPENDING ON VERB FORMAT.

 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.

 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS-VARIABLES.
     05 WS-DATA                           PIC X(5).
     05 WS-INT0                           PIC 999  VALUE 4 .
     05 WS-INT1                           PIC S9(4) COMP VALUE 4 .
     05 WS-INT2                           PIC S9(4) COMP VALUE 5 .
     05 WS-INT3                           PIC S9(9) COMP.

 PROCEDURE DIVISION.
 000-MAIN.
     GO TO A1, A2 A3 DEPENDING ON WS-INT0.
     DISPLAY "FAIL"
     GO TO A4.
 A1.
     DISPLAY "PASS A1"
     GO TO A4.
 A2.
     DISPLAY "PASS A2"
     GO TO A4.
 A3.
     DISPLAY "PASS A3".
 A4.
     STOP RUN.