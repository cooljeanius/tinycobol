IDENTIFICATION DIVISION.
PROGRAM-ID.    IDXIO61.
ENVIRONMENT DIVISION.

*> Create variable length indexed file using sequential write 

CONFIGURATION SECTION. 
INPUT-OUTPUT SECTION.
FILE-CONTROL.
SELECT TEST-FILE 
     ASSIGN TO "idxiotest61" 
     ORGANIZATION IS INDEXED
     ACCESS MODE  IS SEQUENTIAL
     RECORD KEY IS TR-KEY-1
     ALTERNATE RECORD KEY IS TR-REC-TYPE-1
       WITH DUPLICATES
     FILE STATUS IS TR-FS.

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
 01  TR-FS                     PIC 9(02).
 01  W-COUNTER                 PIC 9(05).
 01  IDX                       PIC 9(03).
 01  W-COUNTER-VALUE           PIC 9(02).
    88 W-COUNTER-VALUES VALUES ARE 10, 20, 30, 40, 50, 60, 70, 80, 90.
    
PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
     PERFORM A000-INITIALIZE.

     PERFORM 9000-WRITE-IT 100 TIMES.
     PERFORM B000-HOUSEKEEPING.

     STOP RUN.

A000-INITIALIZE.
    MOVE ZERO    TO W-COUNTER.
    MOVE SPACES  TO TEST-REC-1.
    OPEN OUTPUT TEST-FILE.
    DISPLAY "IXO1:(" TR-FS "):(00):INDEX WRITE OPEN".

    PERFORM A020-INITIALIZE VARYING IDX 
          FROM 1 BY 1 UNTIL IDX EQUAL 21.

A020-INITIALIZE.
    MOVE IDX TO TR-BIN-NUMBER-1 (IDX).

B000-HOUSEKEEPING.
    CLOSE TEST-FILE.
    DISPLAY "IXC1:(" TR-FS "):(00):INDEX WRITE CLOSE".

9000-WRITE-IT.
    MOVE W-COUNTER  TO W-COUNTER-VALUE.
    MOVE W-COUNTER  TO TR-KEY-1.
    IF W-COUNTER-VALUES
    THEN
       PERFORM 9100-WRITE-IT
    ELSE
       MOVE 20            TO TR-BIN-IDX-1
       MOVE "RU"          TO TR-REC-TYPE-1
       MOVE ALL "U"       TO TR-DESCRIPTION-1
       WRITE TEST-REC-1
    END-IF.
    ADD 1 TO W-COUNTER.

9100-WRITE-IT.

    IF W-COUNTER = 10
    THEN
       MOVE "S1"       TO TR-REC-TYPE-1
       MOVE ALL "A"    TO TR-DESCRIPTION-1
       MOVE 1          TO TR-BIN-IDX-1
    END-IF.

    IF W-COUNTER = 20
    THEN
       MOVE "S2"       TO TR-REC-TYPE-1
       MOVE ALL "B"    TO TR-DESCRIPTION-1
*>       MOVE 2          TO TR-BIN-IDX-1
*> This is to avoid a BUG with VB-ISAM variable length records
       MOVE 12         TO TR-BIN-IDX-1
    END-IF.

    IF W-COUNTER = 30
    THEN
       MOVE "S3"       TO TR-REC-TYPE-1
       MOVE ALL "C"    TO TR-DESCRIPTION-1
       MOVE 3          TO TR-BIN-IDX-1
    END-IF.

    IF W-COUNTER = 40
    THEN
       MOVE "S4"       TO TR-REC-TYPE-1
       MOVE ALL "D"    TO TR-DESCRIPTION-1
       MOVE 4          TO TR-BIN-IDX-1
    END-IF.

    IF W-COUNTER = 50
    THEN
       MOVE "S5"       TO TR-REC-TYPE-1
       MOVE ALL "E"    TO TR-DESCRIPTION-1
       MOVE 5          TO TR-BIN-IDX-1
    END-IF.

    IF W-COUNTER = 60
    THEN
       MOVE "S6"       TO TR-REC-TYPE-1
       MOVE ALL "F"    TO TR-DESCRIPTION-1
       MOVE 6          TO TR-BIN-IDX-1
    END-IF.

    IF W-COUNTER = 70
    THEN
       MOVE "S7"       TO TR-REC-TYPE-1
       MOVE ALL "G"    TO TR-DESCRIPTION-1
       MOVE 7          TO TR-BIN-IDX-1
    END-IF.

    IF W-COUNTER = 80
    THEN
       MOVE "S8"       TO TR-REC-TYPE-1
       MOVE ALL "H"    TO TR-DESCRIPTION-1
       MOVE 8          TO TR-BIN-IDX-1
    END-IF.

    IF W-COUNTER = 90
    THEN
       MOVE "S9"       TO TR-REC-TYPE-1
       MOVE ALL "I"    TO TR-DESCRIPTION-1
       MOVE 9          TO TR-BIN-IDX-1
    END-IF.

    WRITE TEST-REC-1.
    
    DISPLAY "IX01:(" TR-FS "):(00):INDEX FILE STATUS WRITE".
