IDENTIFICATION DIVISION.
PROGRAM-ID. RELIO09.
ENVIRONMENT DIVISION.

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "reliotest01.dat" 
     ORGANIZATION IS RELATIVE
     ACCESS MODE  IS RANDOM
     RECORD KEY IS WS-TR-KEY
     FILE STATUS  IS TR-FS.

DATA DIVISION.
FILE SECTION.
FD  TEST-FILE
    LABEL RECORDS ARE STANDARD.
 01 TEST-REC.
   05 FILLER                   PIC X(23).

WORKING-STORAGE SECTION.
 01 TR-FS                      PIC 9(02).
 01 WS-TR-KEY                  PIC 9(03).
 01 W-COUNTER                  PIC 9(15).
 01 WS-TEST-REC.
   05 WS-TEST-REC-KEY          PIC X(03).
   05 FILLER                   PIC X(01).
   05 WS-TEST-REC-DESCRIPTION  PIC X(19).
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
   MOVE ALL "R" TO WS-TEST-REC-DESCRIPTION
   REWRITE TEST-REC FROM WS-TEST-REC.
   DISPLAY "RR03:(" TR-FS "):(00):RELATIVE FILE REWRITE STATUS".

   MOVE 19 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TR-KEY "):(019):RELATIVE FILE READ".
   MOVE ALL "R" TO WS-TEST-REC-DESCRIPTION
   REWRITE TEST-REC FROM WS-TEST-REC.
   DISPLAY "RR03:(" TR-FS "):(00):RELATIVE FILE REWRITE STATUS".

D000-READ.
   MOVE W-COUNTER TO WS-TR-KEY.
   READ TEST-FILE INTO WS-TEST-REC
*>      INVALID KEY 
*>        MOVE "YES" TO W01-SWITCHES
   END-READ.
