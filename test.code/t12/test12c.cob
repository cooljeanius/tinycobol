IDENTIFICATION DIVISION.
PROGRAM-ID. TEST12C.
ENVIRONMENT DIVISION.

*> Indexed file random read using primary key

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "idxiotest01" 
     ORGANIZATION IS INDEXED
     ACCESS MODE  IS RANDOM
     RECORD KEY IS TR-KEY
     ALTERNATE RECORD KEY IS TR-REC-TYPE 
       WITH DUPLICATES
     FILE STATUS  IS TR-FS.

DATA DIVISION.
FILE SECTION.
FD  TEST-FILE
    LABEL RECORDS ARE STANDARD.
 01 TEST-REC.
   05 TR-KEY                   PIC  9(03).
   05 TR-REC-TYPE              PIC  X(02).
   05 TR-DESCRIPTION           PIC  X(10).

WORKING-STORAGE SECTION.
 01 TR-FS                      PIC 9(02).
 01 WS-COUNTER                 PIC 9(05) COMP-5.

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM C000-MAIN-PROCESS.
   PERFORM B000-HOUSEKEEPING.
   PERFORM Z000-SUMMARY.

   STOP RUN.

A000-INITIALIZE.
   MOVE 0 TO WS-COUNTER.
   OPEN I-O TEST-FILE.
   DISPLAY "INDEX READ OPEN STATUS  " TR-FS.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "INDEX READ CLOSE STATUS " TR-FS.

C000-MAIN-PROCESS.
   MOVE 0 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE 10 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE 20 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE 30 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE 40 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE 50 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE 60 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE 70 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE 80 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE 90 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE 999 TO TR-KEY.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS.

D000-READ.
   READ TEST-FILE 
     NOT INVALID KEY
       ADD 1 TO WS-COUNTER
   END-READ.

Z000-SUMMARY.
   DISPLAY "NUMBER OF RECORDS READ      " WS-COUNTER.