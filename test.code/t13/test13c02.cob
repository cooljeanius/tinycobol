IDENTIFICATION DIVISION.
PROGRAM-ID. TEST13C02.
ENVIRONMENT DIVISION.

*> Variable length Indexed file (format 3) sequential read

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "idxiotest61" 
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
     RECORD IS VARYING 15 TO 72 CHARACTERS.

 01 TEST-REC-1.
    05  TR-KEY-1               PIC  9(03).
    05  TR-REC-TYPE-1          PIC  X(02).
    05  TR-DESCRIPTION-1       PIC  X(05).
    05  TR-BIN-IDX-1           PIC  9(02).
    05  TR-BIN-NUMBER-1        PIC  X(03)
       OCCURS 1 TO 20 TIMES DEPENDING ON TR-BIN-IDX-1.

WORKING-STORAGE SECTION.
 01 TR-FS                      PIC 9(02).
 01 WS-COUNTER                 PIC 9(05) COMP-5.
 01 WS-COUNTER-0               PIC 9(05) COMP-5.
 01 WS-COUNTER-1               PIC 9(05) COMP-5.
 01 WS-COUNTER-2               PIC 9(05) COMP-5.
 01 WS-COUNTER-3               PIC 9(05) COMP-5.
 01 WS-COUNTER-4               PIC 9(05) COMP-5.
 01 WS-COUNTER-5               PIC 9(05) COMP-5.
 01 WS-COUNTER-6               PIC 9(05) COMP-5.
 01 WS-COUNTER-7               PIC 9(05) COMP-5.
 01 WS-COUNTER-8               PIC 9(05) COMP-5.
 01 WS-COUNTER-9               PIC 9(05) COMP-5.
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
    MOVE ZERO    TO WS-COUNTER 
                    WS-COUNTER-0 
                    WS-COUNTER-1 
                    WS-COUNTER-2
                    WS-COUNTER-3 
                    WS-COUNTER-4 
                    WS-COUNTER-5 
                    WS-COUNTER-6 
                    WS-COUNTER-7 
                    WS-COUNTER-8 
                    WS-COUNTER-9.
   OPEN INPUT TEST-FILE.
   DISPLAY "INDEX OPEN INPUT STATUS  " TR-FS.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "INDEX CLOSE INPUT STATUS " TR-FS.

C000-PROCESS.
   MOVE TR-KEY-1 TO WS-COUNTER-VALUE.
   IF WS-COUNTER-VALUES
   THEN
       PERFORM C900-PROCESS
   ELSE
       ADD 1 TO WS-COUNTER-0
   END-IF.

   PERFORM D000-READ.

C900-PROCESS.
   
   IF TR-KEY-1 = 10
   THEN
       ADD 1 TO WS-COUNTER-1
   END-IF.

   IF TR-KEY-1 = 20
   THEN
       ADD 1 TO WS-COUNTER-2
   END-IF.

   IF TR-KEY-1 = 30
   THEN
       ADD 1 TO WS-COUNTER-3
   END-IF.

   IF TR-KEY-1 = 40
   THEN
       ADD 1 TO WS-COUNTER-4
   END-IF.

   IF TR-KEY-1 = 50
   THEN
       ADD 1 TO WS-COUNTER-5
   END-IF.

   IF TR-KEY-1 = 60
   THEN
       ADD 1 TO WS-COUNTER-6
   END-IF.

   IF TR-KEY-1 = 70
   THEN
       ADD 1 TO WS-COUNTER-7
   END-IF.

   IF TR-KEY-1 = 80
   THEN
       ADD 1 TO WS-COUNTER-8
   END-IF.

   IF TR-KEY-1 = 90
   THEN
       ADD 1 TO WS-COUNTER-9
   END-IF.

D000-READ.
   READ TEST-FILE NEXT
    AT END
      MOVE 'Y' TO WS-SWITCHES-EOF
    NOT AT END
     ADD 1 TO WS-COUNTER
   END-READ.

Z000-SUMMARY.
    DISPLAY "NUMBER OF RECORDS READ        " WS-COUNTER.
    DISPLAY "NUMBER OF RECORDS READ TYPE 0 " WS-COUNTER-0.
    DISPLAY "NUMBER OF RECORDS READ TYPE 1 " WS-COUNTER-1.
    DISPLAY "NUMBER OF RECORDS READ TYPE 2 " WS-COUNTER-2.
    DISPLAY "NUMBER OF RECORDS READ TYPE 3 " WS-COUNTER-3.
    DISPLAY "NUMBER OF RECORDS READ TYPE 4 " WS-COUNTER-4.
    DISPLAY "NUMBER OF RECORDS READ TYPE 5 " WS-COUNTER-5.
    DISPLAY "NUMBER OF RECORDS READ TYPE 6 " WS-COUNTER-6.
    DISPLAY "NUMBER OF RECORDS READ TYPE 7 " WS-COUNTER-7.
    DISPLAY "NUMBER OF RECORDS READ TYPE 8 " WS-COUNTER-8.
    DISPLAY "NUMBER OF RECORDS READ TYPE 9 " WS-COUNTER-9.
