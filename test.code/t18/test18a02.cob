IDENTIFICATION DIVISION.
PROGRAM-ID.    TEST18A02.
ENVIRONMENT DIVISION.

*> Relative file dynamic mode write 

CONFIGURATION SECTION. 
INPUT-OUTPUT SECTION.
FILE-CONTROL.
SELECT TEST-FILE 
  ASSIGN TO "reliotest01.dat" 
  ORGANIZATION IS RELATIVE
  ACCESS MODE  IS DYNAMIC
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
 01 WS-COUNTER                 PIC 9(03).
 01 WS-COUNTER-REC             PIC 9(05) COMP-5.
 01 WS-TEST-REC.
   05 WS-TEST-REC-KEY          PIC X(03).
   05 FILLER                   PIC X(01) VALUE SPACES.
   05 WS-TEST-REC-DESCRIPTION  PIC X(19) VALUE ALL 'B'.

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM 9000-WRITE-IT 9 TIMES.
   PERFORM B000-HOUSEKEEPING.
   PERFORM Z000-SUMMARY.

   STOP RUN.

A000-INITIALIZE.
   MOVE 0 TO WS-COUNTER-REC.
   MOVE 13 TO WS-COUNTER.
   MOVE WS-COUNTER TO WS-TEST-REC-KEY WS-TR-KEY.
   OPEN I-O TEST-FILE.
   DISPLAY "RELATIVE OPEN I-O STATUS  " TR-FS.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "RELATIVE CLOSE I-O STATUS " TR-FS.

9000-WRITE-IT.
   WRITE TEST-REC FROM WS-TEST-REC.
   ADD 3 TO WS-COUNTER.
   ADD 1 TO WS-COUNTER-REC.
   MOVE WS-COUNTER TO WS-TEST-REC-KEY WS-TR-KEY.

Z000-SUMMARY.
    DISPLAY "NUMBER OF RECORDS WRITTEN " WS-COUNTER-REC.
