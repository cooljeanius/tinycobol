IDENTIFICATION DIVISION.
PROGRAM-ID. RELIO06.
ENVIRONMENT DIVISION.

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "reliotest01.dat" 
     ORGANIZATION IS RELATIVE
     ACCESS MODE  IS DYNAMIC
     RECORD KEY   IS WS-TR-KEY
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
   OPEN INPUT TEST-FILE.
   DISPLAY "RLO2:(" TR-FS "):(00):RELATIVE READ OPEN".
   MOVE "NO" TO W01-SWITCHES.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "RLC2:(" TR-FS "):(00):RELATIVE READ CLOSE".

C000-MAIN-PROCESS.
   MOVE 4 TO WS-TR-KEY.
   START TEST-FILE.
   DISPLAY "RL01:(" TR-FS "):(00):RELATIVE FILE START STATUS".
*>   DISPLAY "RL02:(" WS-TR-KEY "):(004):RELATIVE FILE START KEY EQUAL".
   PERFORM D000-READ-NEXT.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TEST-REC-KEY "):(004):RELATIVE FILE READ KEY".

*> FIXME: What is the correct START value 
   MOVE 2 TO WS-TR-KEY.
   START TEST-FILE KEY IS NOT EQUAL TO WS-TR-KEY.
   DISPLAY "RL01:(" TR-FS "):(99):RELATIVE FILE START NOT EQUAL STATUS".
*>   DISPLAY "RL02:(" WS-TR-KEY "):(002):RELATIVE FILE READ KEY".

   MOVE 6 TO WS-TR-KEY.
   START TEST-FILE KEY IS EQUAL TO WS-TR-KEY.
   DISPLAY "RL01:(" TR-FS "):(00):RELATIVE FILE START EQUAL STATUS".
*>   DISPLAY "RL02:(" WS-TR-KEY "):(006):RELATIVE FILE START KEY EQUAL".
   PERFORM D000-READ-NEXT.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TEST-REC-KEY "):(006):RELATIVE FILE READ KEY".

   MOVE 15 TO WS-TR-KEY.
   START TEST-FILE KEY IS LESS THAN WS-TR-KEY.
   DISPLAY "RL01:(" TR-FS "):(00):RELATIVE FILE START LESS THAN STATUS".
*>   DISPLAY "RL02:(" WS-TR-KEY "):(013):RELATIVE FILE START KEY LESS THAN".
   PERFORM D000-READ-NEXT.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TEST-REC-KEY "):(013):RELATIVE FILE READ KEY".

   MOVE 18 TO WS-TR-KEY.
   START TEST-FILE KEY IS GREATER THAN WS-TR-KEY.
   DISPLAY "RL01:(" TR-FS "):(00):RELATIVE FILE START GREATER THAN STATUS".
*>   DISPLAY "RL02:(" WS-TR-KEY "):(019):RELATIVE FILE START KEY GREATER THAN".
   PERFORM D000-READ-NEXT.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TEST-REC-KEY "):(019):RELATIVE FILE READ KEY".

   MOVE 25 TO WS-TR-KEY.
   START TEST-FILE KEY IS NOT LESS THAN WS-TR-KEY.
   DISPLAY "RL01:(" TR-FS "):(00):RELATIVE FILE START NOT LESS THAN STATUS".
*>   DISPLAY "RL02:(" WS-TR-KEY "):(025):RELATIVE FILE START KEY NOT LESS THAN".
   PERFORM D000-READ-NEXT.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TEST-REC-KEY "):(025):RELATIVE FILE READ KEY".

   MOVE 29 TO WS-TR-KEY.
   START TEST-FILE KEY IS NOT GREATER THAN WS-TR-KEY.
   DISPLAY "RL01:(" TR-FS "):(00):RELATIVE FILE START NOT GREATER THAN STATUS".
*>   DISPLAY "RL02:(" WS-TR-KEY "):(028):RELATIVE FILE START KEY NOT GREATER THAN".
   PERFORM D000-READ-NEXT.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TEST-REC-KEY "):(028):RELATIVE FILE READ KEY".

   MOVE 35 TO WS-TR-KEY.
   START TEST-FILE KEY IS LESS THAN OR EQUAL TO WS-TR-KEY.
   DISPLAY "RL01:(" TR-FS "):(00):RELATIVE FILE START LESS THAN OR EQUAL STATUS".
*>   DISPLAY "RL02:(" WS-TR-KEY "):(034):RELATIVE FILE START KEY LESS THAN OR EQUAL".
   PERFORM D000-READ-NEXT.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TEST-REC-KEY "):(034):RELATIVE FILE READ KEY".

   MOVE 1 TO WS-TR-KEY.
   START TEST-FILE KEY IS GREATER THAN OR EQUAL TO WS-TR-KEY.
   DISPLAY "RL01:(" TR-FS "):(00):RELATIVE FILE START GREATER THAN OR EQUAL STATUS".
*>   DISPLAY "RL02:(" WS-TR-KEY "):(001):RELATIVE FILE START KEY GREATER THAN OR EQUAL".
   PERFORM D000-READ-NEXT.
   DISPLAY "RL21:(" TR-FS "):(00):RELATIVE FILE READ STATUS".
   DISPLAY "RL23:(" WS-TEST-REC-KEY "):(001):RELATIVE FILE READ KEY".

   MOVE 999 TO WS-TR-KEY.
   START TEST-FILE KEY IS EQUAL TO WS-TR-KEY.
   DISPLAY "RL01:(" TR-FS "):(23):RELATIVE FILE START KEY EQUAL INVALID KEY".
*>   DISPLAY "RL02:(" WS-TEST-REC-KEY "):(999):RELATIVE FILE START KEY EQUAL INVALID KEY ".

D000-READ-NEXT.
   READ TEST-FILE NEXT INTO WS-TEST-REC
   END-READ.