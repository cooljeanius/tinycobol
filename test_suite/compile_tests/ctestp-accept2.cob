 IDENTIFICATION DIVISION.
 PROGRAM-ID. CTESTP_ACCEPT2.
 AUTHOR.  STEPHEN CONNOLLY.
 INSTALLATION. Tiny Cobol Compiler Project.
 SECURITY. NONE.
* TEST ACCEPT FROM TIME VERB FORMAT.

 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.

 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS-VARIABLES.
     05 WS-DATA                           PIC X(6).
     05 WS-INT1                           PIC S9(4) COMP VALUE 4 .
     05 WS-INT2                           PIC S9(4) COMP VALUE 5 .
     05 WS-INT3                           PIC S9(9) COMP.

 PROCEDURE DIVISION.
 000-MAIN.
     ACCEPT WS-DATA FROM TIME.
     DISPLAY WS-DATA.
     STOP RUN.
