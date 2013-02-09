IDENTIFICATION DIVISION.
PROGRAM-ID. IDXIO33.
ENVIRONMENT DIVISION.

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "idxiotest21" 
     ORGANIZATION IS INDEXED
     ACCESS MODE  IS SEQUENTIAL
     RECORD KEY   IS TR-KEY-1
     ALTERNATE RECORD KEY IS TR-REC-TYPE-1
       WITH DUPLICATES
     FILE STATUS  IS TR-FS.

DATA DIVISION.
FILE SECTION.
FD  TEST-FILE
    LABEL RECORDS ARE STANDARD.
01  TEST-REC-1.
    05  TR-KEY-1               PIC  9(03).
    05  TR-REC-TYPE-1          PIC  X(02).
    05  TR-DESCRIPTION-1       PIC  X(05).

01  TEST-REC-2.
    05  TR-KEY-2               PIC  9(03).
    05  TR-REC-TYPE-2          PIC  X(02).
    05  TR-DESCRIPTION-2       PIC  X(10).

WORKING-STORAGE SECTION.
 01 TR-FS                      PIC 9(02).
 01 W-COUNTER                  PIC 9(15).
 01 W01-SWITCHES               PIC X(03).
   88 W01-END VALUE "YES".
   88 W01-MORE VALUE "NO".

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM 0000-LOOP.
   PERFORM B000-HOUSEKEEPING.

   STOP RUN.

0000-LOOP.
   PERFORM D000-READ.
   PERFORM C000-PROCESS THRU C000-EXIT UNTIL W01-END.

A000-INITIALIZE.
   OPEN I-O TEST-FILE.
   DISPLAY "ISO2:(" TR-FS "):(00):S/INDEX READ OPEN".
   MOVE "NO" TO W01-SWITCHES.
   MOVE 0 TO W-COUNTER.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "ISC2:(" TR-FS "):(00):S/INDEX READ CLOSE".

C000-PROCESS.

   IF TR-KEY-1 = 45
   THEN
     DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE READ STATUS" 
     DISPLAY "IS22:(" TR-REC-TYPE-1 "):(RU):S/INDEX FILE READ"
     DELETE TEST-FILE
     DISPLAY "IR03:(" TR-FS "):(00):S/INDEX DELETE STATUS"
   END-IF.

   PERFORM D000-READ.

C000-EXIT.
   EXIT.

D000-READ.

   READ TEST-FILE NEXT
    AT END
      DISPLAY "IX10:(" TR-FS "):(10):S/INDEX FILE READ STATUS AT EOF"
      MOVE "YES" TO W01-SWITCHES
   END-READ.
