IDENTIFICATION DIVISION.
PROGRAM-ID.    RELIO02.
ENVIRONMENT DIVISION.
*> Program to write relative records using DYNAMIC access mode.
*> File will be used in subsequent tests in this directory.

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
 01 W-COUNTER                  PIC 9(03).
 01 WS-TEST-REC.
   05 WS-TEST-REC-KEY          PIC X(03).
   05 FILLER                   PIC X(01) VALUE SPACES.
   05 WS-TEST-REC-DESCRIPTION  PIC X(19) VALUE ALL 'B'.

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.

   PERFORM 9000-WRITE-IT 9 TIMES.
   PERFORM B000-HOUSEKEEPING.

   STOP RUN.

A000-INITIALIZE.
   MOVE 13 TO W-COUNTER.
   MOVE W-COUNTER TO WS-TEST-REC-KEY WS-TR-KEY.
   OPEN I-O TEST-FILE.
   DISPLAY "RLO2:(" TR-FS "):(00):RELATIVE DYNAMIC I/O OPEN STATUS".

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "RLC2:(" TR-FS "):(00):RELATIVE DYNAMIC I/O CLOSE STATUS".

9000-WRITE-IT.
   WRITE TEST-REC FROM WS-TEST-REC.
   DISPLAY "RL02:(" WS-TR-KEY "):(" W-COUNTER "):RELATIVE FILE WRITE".
   ADD 3 TO W-COUNTER.
   MOVE W-COUNTER TO WS-TEST-REC-KEY WS-TR-KEY.

