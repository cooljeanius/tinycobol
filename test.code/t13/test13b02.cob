IDENTIFICATION DIVISION.
PROGRAM-ID. TEST13B02.
ENVIRONMENT DIVISION.

*> Variable length Indexed file (format 2) sequential read

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "idxiotest41" 
     ORGANIZATION IS INDEXED
     ACCESS MODE  IS SEQUENTIAL
     RECORD KEY   IS TR-KEY-1
     ALTERNATE RECORD KEY IS TR-REC-TYPE-1
       WITH DUPLICATES
     FILE STATUS  IS TR-FS.

DATA DIVISION.
FILE SECTION.
FD  TEST-FILE
*>     LABEL RECORD IS STANDARD
     RECORD IS VARYING IN SIZE FROM 10 TO 15 CHARACTERS
     DEPENDING ON RECORD-LENGTH.

 01 TEST-REC-1.
   05  TR-KEY-1                PIC  9(03).
   05  TR-REC-TYPE-1           PIC  X(02).
   05  TR-DESCRIPTION-1        PIC  X(05).

 01 TEST-REC-2.
   05  TR-KEY-2                PIC  9(03).
   05  TR-REC-TYPE-2           PIC  X(02).
   05  TR-DESCRIPTION-2        PIC  X(10).

WORKING-STORAGE SECTION.
 01 TR-FS                      PIC 9(02).
 01 RECORD-LENGTH              PIC 9(03).         
 01 WS-COUNTER                 PIC 9(05) COMP-5.
 01 WS-COUNTER-1               PIC 9(05) COMP-5.
 01 WS-COUNTER-2               PIC 9(05) COMP-5.
 01 WS-SWITCHES-EOF            PIC X(01) VALUE 'N'.
   88 WS-EOF       VALUE 'Y'.
 01 WS-COUNTER-VALUE           PIC 9(02).
    88 WS-COUNTER-VALUES VALUES ARE 10, 20, 30, 40, 50, 60, 70, 80, 90.

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM 0000-LOOP.
   PERFORM B000-HOUSEKEEPING.
   PERFORM Z000-SUMMARY.

   STOP RUN.

0000-LOOP.
   PERFORM D000-READ.
   PERFORM C000-PROCESS UNTIL WS-EOF.

A000-INITIALIZE.
   MOVE ZERO TO WS-COUNTER WS-COUNTER-1 WS-COUNTER-2.
   OPEN INPUT TEST-FILE.
   DISPLAY "INDEX OPEN INPUT STATUS  " TR-FS.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "INDEX CLOSE INPUT STATUS " TR-FS.

C000-PROCESS.
   MOVE TR-KEY-1 TO WS-COUNTER-VALUE.
   IF WS-COUNTER-VALUES
   THEN
       ADD 1 TO WS-COUNTER-2
   ELSE
       ADD 1 TO WS-COUNTER-1
   END-IF.

   PERFORM D000-READ.

D000-READ.
   READ TEST-FILE NEXT
    AT END
      MOVE 'Y' TO WS-SWITCHES-EOF
    NOT AT END
     ADD 1 TO WS-COUNTER
   END-READ.

Z000-SUMMARY.
    DISPLAY "NUMBER OF RECORDS READ        " WS-COUNTER.
    DISPLAY "NUMBER OF RECORDS READ TYPE 1 " WS-COUNTER-1.
    DISPLAY "NUMBER OF RECORDS READ TYPE 2 " WS-COUNTER-2.