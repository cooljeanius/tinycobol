IDENTIFICATION DIVISION.
PROGRAM-ID. IDXIO13.
ENVIRONMENT DIVISION.

*> Relative file sequential delete

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "reliotest01.dat" 
     ORGANIZATION IS RELATIVE
     ACCESS MODE  IS SEQUENTIAL
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
 01 W-COUNTER                  PIC 9(15).
 01 WS-TEST-REC.
   05 WS-TEST-REC-KEY          PIC X(03).
   05 FILLER                   PIC X(01).
   05 WS-TEST-REC-DESCRIPTION  PIC X(19).
 01 WS-COUNTER-REC             PIC 9(05) COMP-5.
 01 WS-COUNTER-D               PIC 9(05) COMP-5.
 01 WS-EOF-IND                 PIC X(01) VALUE 'N'.
   88 WS-EOF-TRUE              VALUE 'Y'.

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM 0000-LOOP.
   PERFORM B000-HOUSEKEEPING.
   PERFORM Z000-SUMMARY.

   STOP RUN.

0000-LOOP.
   PERFORM D000-READ.
   PERFORM C000-PROCESS UNTIL WS-EOF-TRUE.

A000-INITIALIZE.
   MOVE 0 TO WS-COUNTER-REC WS-COUNTER-D.
   OPEN I-O TEST-FILE.
   DISPLAY "RELATIVE OPEN I-O STATUS  " TR-FS.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "RELATIVE CLOSE I-O STATUS " TR-FS.

C000-PROCESS.
   IF WS-TR-KEY = 7
   THEN
     DISPLAY "READ KEY " WS-TR-KEY " FILE STATUS " TR-FS
     DELETE TEST-FILE
     DISPLAY "DELETE STATUS " TR-FS
     ADD 1 TO WS-COUNTER-D
   END-IF.

   PERFORM D000-READ.

D000-READ.
   READ TEST-FILE NEXT INTO WS-TEST-REC
     AT END 
       MOVE 'Y' TO WS-EOF-IND
     NOT AT END 
       ADD 1 TO WS-COUNTER-REC
   END-READ.

Z000-SUMMARY.
    DISPLAY "NUMBER OF RECORDS READ      " WS-COUNTER-REC.
    DISPLAY "NUMBER OF RECORDS DELETED   " WS-COUNTER-D.
