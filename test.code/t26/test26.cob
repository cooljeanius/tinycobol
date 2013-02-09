 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST26.
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.
* INPUT-OUTPUT SECTION.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
  01  W-1   PIC X(10) VALUE "testing".
  01  W-2   PIC X(10).
 
 PROCEDURE DIVISION.
 A100.
     display W-1 line 1 position 2
     accept W-2 line 5 position 2
        display "<-- OK"
        display W-1 line 12 position 5
     accept W-2 line 1 position 1   
     STOP RUN.
