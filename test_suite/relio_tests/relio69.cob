IDENTIFICATION DIVISION.
PROGRAM-ID. RELIO69.
ENVIRONMENT DIVISION.

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "reliotest61.dat" 
     ORGANIZATION IS RELATIVE
     ACCESS MODE  IS RANDOM
     RECORD KEY IS WS-TR-KEY
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
 01 TR-FS                      PIC 9(02).
 01 WS-TR-KEY                  PIC 9(03).
 01 W-COUNTER                  PIC 9(15).
 01 W01-SWITCHES               PIC X(03).
   88 W01-END VALUE "YES".
   88 W01-MORE VALUE "NO".

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM C000-MAIN-PROCESS.
   PERFORM B000-HOUSEKEEPING.

   STOP RUN.

A000-INITIALIZE.
   OPEN I-O TEST-FILE.
   DISPLAY "RLO2:(" TR-FS "):(00):RELATIVE READ OPEN".
   MOVE "NO" TO W01-SWITCHES.
   MOVE 0 TO W-COUNTER.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "RLC2:(" TR-FS "):(00):RELATIVE READ CLOSE".

C000-MAIN-PROCESS.

   MOVE 4 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TR-KEY "):(004):RELATIVE FILE READ".
   DISPLAY "RL24:(" TR-BIN-IDX-1 "):(20):RELATIVE FILE READ BIN IDX".
   MOVE ALL "R" TO TR-DESCRIPTION-1
   REWRITE TEST-REC-1.
   DISPLAY "RR03:(" TR-FS "):(00):RELATIVE FILE REWRITE STATUS".

   MOVE 19 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TR-KEY "):(019):RELATIVE FILE READ".
   DISPLAY "RL24:(" TR-BIN-IDX-1 "):(03):RELATIVE FILE READ BIN IDX".
   MOVE ALL "R" TO TR-DESCRIPTION-1
   REWRITE TEST-REC-1.
   DISPLAY "RR03:(" TR-FS "):(00):RELATIVE FILE REWRITE STATUS".

D000-READ.
   MOVE W-COUNTER TO WS-TR-KEY.
   READ TEST-FILE
*>      INVALID KEY 
*>        MOVE "YES" TO W01-SWITCHES
   END-READ.