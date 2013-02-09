IDENTIFICATION DIVISION.
PROGRAM-ID. TEST12E.
ENVIRONMENT DIVISION.

*> Indexed file dynamic reads using secondary key

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
   DISPLAY "INDEX I-O CLOSE STATUS  " TR-FS.

C000-MAIN-PROCESS.
   MOVE 'RU' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   PERFORM D000-READ-NEXT.
   DISPLAY "READ NEXT SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'S1' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   PERFORM D000-READ-PREV.
   DISPLAY "READ PREVIOUS SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'S2' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   PERFORM D000-READ-NEXT.
   DISPLAY "READ NEXT SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'S3' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   PERFORM D000-READ-PREV.
   DISPLAY "READ PREVIOUS SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'S4' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   PERFORM D000-READ-NEXT.
   DISPLAY "READ NEXT SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'S5' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   PERFORM D000-READ-PREV.
   DISPLAY "READ PREVIOUS SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'S6' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   PERFORM D000-READ-NEXT.
   DISPLAY "READ NEXT SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'S7' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   PERFORM D000-READ-PREV.
   DISPLAY "READ PREVIOUS SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'S8' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   PERFORM D000-READ-NEXT.
   DISPLAY "READ NEXT SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'S9' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   PERFORM D000-READ-PREV.
   DISPLAY "READ PREVIOUS SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'ZZ' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.

   MOVE 'RU' TO TR-REC-TYPE.
   PERFORM D000-READ.
   DISPLAY "READ SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.
   PERFORM D000-READ-PREV.
   DISPLAY "READ PREVIOUS SECONDARY KEY " TR-REC-TYPE " FILE STATUS " TR-FS.


D000-READ.
   READ TEST-FILE 
     KEY IS TR-REC-TYPE
     NOT INVALID KEY
       ADD 1 TO WS-COUNTER
   END-READ.

D000-READ-NEXT.
   READ TEST-FILE NEXT
    NOT AT END
     ADD 1 TO WS-COUNTER
   END-READ.

D000-READ-PREV.
   READ TEST-FILE PREVIOUS
    NOT AT END
     ADD 1 TO WS-COUNTER
   END-READ.

Z000-SUMMARY.
   DISPLAY "NUMBER OF RECORDS READ      " WS-COUNTER.
