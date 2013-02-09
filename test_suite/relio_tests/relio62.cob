IDENTIFICATION DIVISION.
PROGRAM-ID.    RELIO62.
ENVIRONMENT DIVISION.
*> Program to write relative records using DYNAMIC access mode.
*> File will be used in subsequent tests in this directory.

CONFIGURATION SECTION. 
INPUT-OUTPUT SECTION.
FILE-CONTROL.
SELECT TEST-FILE 
  ASSIGN TO "reliotest61.dat" 
  ORGANIZATION IS RELATIVE
  ACCESS MODE  IS DYNAMIC
  RELATIVE KEY IS WS-TR-KEY
  FILE STATUS  IS TR-FS.

DATA DIVISION.
FILE SECTION.
 FD  TEST-FILE
*>     LABEL RECORD IS STANDARD
   RECORD IS VARYING 15 TO 72 CHARACTERS.

 01 TEST-REC-1.
   05 TR-KEY-1               PIC 9(03).
   05 FILLER                 PIC X(01).
   05 TR-DESCRIPTION-1       PIC X(06).
   05 TR-BIN-IDX-1           PIC 9(02).
   05 TR-BIN-NUMBER-1        PIC X(03)
      OCCURS 1 TO 20 TIMES DEPENDING ON TR-BIN-IDX-1.

WORKING-STORAGE SECTION.
 01 WS-TR-KEY                  PIC 9(03).
 01 TR-FS                      PIC 9(02).
 01 W-COUNTER                  PIC 9(03).
 01 IDX                        PIC 9(03).

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.

   PERFORM 9000-WRITE-IT 3 TIMES.
   PERFORM B000-HOUSEKEEPING.

   STOP RUN.

A000-INITIALIZE.
   MOVE SPACES    TO TEST-REC-1.
   MOVE 13        TO W-COUNTER.
   MOVE W-COUNTER TO WS-TR-KEY.
   PERFORM A020-INITIALIZE VARYING IDX 
      FROM 1 BY 1 UNTIL IDX EQUAL 21.

   OPEN I-O TEST-FILE.
   DISPLAY "RLO2:(" TR-FS "):(00):RELATIVE DYNAMIC I/O OPEN STATUS".

A020-INITIALIZE.
    MOVE IDX TO TR-BIN-NUMBER-1 (IDX).

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "RLC2:(" TR-FS "):(00):RELATIVE DYNAMIC I/O CLOSE STATUS".

9000-WRITE-IT.

   MOVE ALL 'D'   TO TR-DESCRIPTION-1.
   MOVE W-COUNTER TO WS-TR-KEY TR-KEY-1.
   MOVE 18        TO TR-BIN-IDX-1

   WRITE TEST-REC-1.
   DISPLAY "RLO1:(" TR-FS "):(00):RELATIVE VARIABLE SEQUENTIAL FILE WRITE STATUS".
   DISPLAY "RL22:(" WS-TR-KEY "):(" W-COUNTER "):RELATIVE FILE WRITE".

   ADD 3 TO W-COUNTER.

   MOVE ALL 'E'   TO TR-DESCRIPTION-1.
   MOVE W-COUNTER TO WS-TR-KEY TR-KEY-1.
   MOVE 13        TO TR-BIN-IDX-1

   WRITE TEST-REC-1.
   DISPLAY "RLO1:(" TR-FS "):(00):RELATIVE VARIABLE SEQUENTIAL FILE WRITE STATUS".
   DISPLAY "RL22:(" WS-TR-KEY "):(" W-COUNTER "):RELATIVE FILE WRITE".

   ADD 3 TO W-COUNTER.

   MOVE ALL 'F'   TO TR-DESCRIPTION-1.
   MOVE W-COUNTER TO WS-TR-KEY TR-KEY-1.
   MOVE 3         TO TR-BIN-IDX-1

   WRITE TEST-REC-1.
   DISPLAY "RLO1:(" TR-FS "):(00):RELATIVE VARIABLE SEQUENTIAL FILE WRITE STATUS".
   DISPLAY "RL22:(" WS-TR-KEY "):(" W-COUNTER "):RELATIVE FILE WRITE".

   ADD 3 TO W-COUNTER.
