IDENTIFICATION DIVISION.
PROGRAM-ID. TEST12N.
ENVIRONMENT DIVISION.

*> Indexed random delete using secondary key

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
 01 WS-COUNTER-D               PIC 9(05) COMP-5.

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM C000-MAIN-PROCESS.
   PERFORM B000-HOUSEKEEPING.
   PERFORM Z000-SUMMARY.

   STOP RUN.

A000-INITIALIZE.
   OPEN I-O TEST-FILE.
   DISPLAY "INDEX I-O OPEN STATUS  " TR-FS.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "INDEX I-O CLOSE STATUS " TR-FS.

C000-MAIN-PROCESS.
   MOVE 'T9' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ KEY " TR-KEY " FILE STATUS " TR-FS

   DELETE TEST-FILE.
   DISPLAY "DELETE STATUS " TR-FS.
   ADD 1 TO WS-COUNTER-D.

D000-READ.
   READ TEST-FILE 
     KEY IS TR-REC-TYPE
     NOT INVALID KEY
       ADD 1 TO WS-COUNTER
   END-READ.

Z000-SUMMARY.
   DISPLAY "NUMBER OF RECORDS READ      " WS-COUNTER.
   DISPLAY "NUMBER OF RECORDS DELETED   " WS-COUNTER-D.