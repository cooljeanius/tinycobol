IDENTIFICATION DIVISION.
PROGRAM-ID. TEST12K.
ENVIRONMENT DIVISION.

*> Indexed start read rewrite using primary key

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "idxiotest01" 
     ORGANIZATION IS INDEXED
     ACCESS MODE  IS DYNAMIC
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
 01 WS-COUNTER-RW              PIC 9(05) COMP-5.

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM C000-MAIN-PROCESS.
   PERFORM B000-HOUSEKEEPING.
   PERFORM Z000-SUMMARY.

   STOP RUN.

A000-INITIALIZE.
   MOVE 0 TO WS-COUNTER WS-COUNTER-RW.
   OPEN I-O TEST-FILE.
   DISPLAY "INDEX I-O OPEN STATUS  " TR-FS.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "INDEX I-O CLOSE STATUS " TR-FS.

C000-MAIN-PROCESS.
   MOVE 15 TO TR-KEY.
   START TEST-FILE.
   DISPLAY "START KEY EQUAL " TR-KEY " FILE STATUS " TR-FS.

   PERFORM D000-READ-NEXT.
   DISPLAY "READ NEXT KEY " TR-KEY " FILE STATUS " TR-FS.

   MOVE "T5"    TO TR-REC-TYPE.
   MOVE ALL "5" TO TR-DESCRIPTION.
   REWRITE TEST-REC.
   DISPLAY "REWRITE STATUS " TR-FS.
   ADD 1 TO WS-COUNTER-RW.

D000-READ-NEXT.
   READ TEST-FILE NEXT
    NOT AT END
      ADD 1 TO WS-COUNTER
   END-READ.

Z000-SUMMARY.
   DISPLAY "NUMBER OF RECORDS READ      " WS-COUNTER.
   DISPLAY "NUMBER OF RECORDS REWRITTEN " WS-COUNTER-RW.
