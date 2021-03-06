IDENTIFICATION DIVISION.
PROGRAM-ID.    TEST18A04.
ENVIRONMENT DIVISION.

*> Relative file random read

CONFIGURATION SECTION. 
INPUT-OUTPUT SECTION.
FILE-CONTROL.
SELECT TEST-FILE 
  ASSIGN TO "reliotest01.dat" 
  ORGANIZATION IS RELATIVE
  ACCESS MODE  IS RANDOM
  RELATIVE KEY IS WS-TR-KEY
  FILE STATUS  IS TR-FS.

DATA DIVISION.
FILE SECTION.
FD  TEST-FILE
    LABEL RECORDS ARE STANDARD.
01  TEST-REC.
   05 FILLER                   PIC X(23).

WORKING-STORAGE SECTION.
 01 WS-TR-KEY                  PIC 9(03).
 01 TR-FS                      PIC 9(02).
 01 WS-COUNTER-REC             PIC 9(05) COMP-5.
 01 WS-TEST-REC.
   05 WS-TEST-REC-KEY          PIC X(03).
   05 FILLER                   PIC X(01) VALUE SPACES.
   05 WS-TEST-REC-DESCRIPTION  PIC X(19) VALUE ALL 'C'.

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM C000-PROCESS.
   PERFORM B000-HOUSEKEEPING.
   PERFORM Z000-SUMMARY.

   STOP RUN.

A000-INITIALIZE.
   OPEN INPUT TEST-FILE.
   DISPLAY "RELATIVE OPEN INPUT STATUS  " TR-FS.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "RELATIVE CLOSE INPUT STATUS " TR-FS.

C000-PROCESS.

   MOVE 6 TO WS-TR-KEY.
   PERFORM 9000-READ-KEY.
   DISPLAY "READ KEY " WS-TR-KEY " FILE STATUS " TR-FS.

   MOVE 13 TO WS-TR-KEY.
   PERFORM 9000-READ-KEY.
   DISPLAY "READ KEY " WS-TR-KEY " FILE STATUS " TR-FS.

   MOVE 14 TO WS-TR-KEY.
   PERFORM 9000-READ-KEY.
   DISPLAY "READ KEY " WS-TR-KEY " FILE STATUS " TR-FS.

9000-READ-KEY.
   READ TEST-FILE  RECORD INTO WS-TEST-REC
     NOT INVALID KEY
       ADD 1 TO WS-COUNTER-REC
   END-READ.

Z000-SUMMARY.
    DISPLAY "NUMBER OF RECORDS READ " WS-COUNTER-REC.
