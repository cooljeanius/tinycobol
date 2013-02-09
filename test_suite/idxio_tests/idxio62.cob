IDENTIFICATION DIVISION.
PROGRAM-ID. IDXIO62.
ENVIRONMENT DIVISION.

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
 01 RECORD-LENGTH              PIC 9(03).         
 01 W-COUNTER                  PIC 9(05).
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
   MOVE SPACES  TO TEST-REC-1.
   MOVE "NO"    TO W01-SWITCHES.
   MOVE 0       TO W-COUNTER.
   OPEN INPUT TEST-FILE.
   DISPLAY "ISO2:(" TR-FS "):(00):S/INDEX READ OPEN".

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "ISC2:(" TR-FS "):(00):S/INDEX READ CLOSE".

C000-PROCESS.

   IF TR-KEY-1 = 0
   THEN
      DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ"
      DISPLAY "IS22:(" TR-REC-TYPE-1 "):(RU):S/INDEX FILE READ"
      DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(UUUUU):S/INDEX FILE DATA FROM READ"
      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(20):S/INDEX FILE READ BIN IDX"
   END-IF.
   
   IF TR-KEY-1 = 10
   THEN
      DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" 
      DISPLAY "IS22:(" TR-REC-TYPE-1 "):(S1):S/INDEX FILE READ"
      DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(AAAAA):S/INDEX FILE DATA FROM READ"
      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(01):S/INDEX FILE READ BIN IDX"
   END-IF.

   IF TR-KEY-1 = 20
   THEN
      DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ"
      DISPLAY "IS22:(" TR-REC-TYPE-1 "):(S2):S/INDEX FILE READ"
      DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(BBBBB):S/INDEX FILE DATA FROM READ"
*>      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(02):S/INDEX FILE READ BIN IDX"
*> This is to avoid a BUG with VB-ISAM variable length records
      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(12):S/INDEX FILE READ BIN IDX"
   END-IF.

   IF TR-KEY-1 = 30
   THEN
      DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" 
      DISPLAY "IS22:(" TR-REC-TYPE-1 "):(S3):S/INDEX FILE READ"
      DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(CCCCC):S/INDEX FILE DATA FROM READ"
      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(03):S/INDEX FILE READ BIN IDX"
   END-IF.

   IF TR-KEY-1 = 40
   THEN
      DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" 
      DISPLAY "IS22:(" TR-REC-TYPE-1 "):(S4):S/INDEX FILE READ"
      DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(DDDDD):S/INDEX FILE DATA FROM READ"
      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(04):S/INDEX FILE READ BIN IDX"
   END-IF.

   IF TR-KEY-1 = 50
   THEN
      DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" 
      DISPLAY "IS22:(" TR-REC-TYPE-1 "):(S5):S/INDEX FILE READ"
      DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(EEEEE):S/INDEX FILE DATA FROM READ"
      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(05):S/INDEX FILE READ BIN IDX"
   END-IF.

   IF TR-KEY-1 = 60
   THEN
      DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" 
      DISPLAY "IS22:(" TR-REC-TYPE-1 "):(S6):S/INDEX FILE READ"
      DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(FFFFF):S/INDEX FILE DATA FROM READ"
      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(06):S/INDEX FILE READ BIN IDX"
   END-IF.

   IF TR-KEY-1 = 70
   THEN
      DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" 
      DISPLAY "IS22:(" TR-REC-TYPE-1 "):(S7):S/INDEX FILE READ"
      DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(GGGGG):S/INDEX FILE DATA FROM READ"
      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(07):S/INDEX FILE READ BIN IDX"
   END-IF.

   IF TR-KEY-1 = 80
   THEN
      DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" 
      DISPLAY "IS22:(" TR-REC-TYPE-1 "):(S8):S/INDEX FILE READ"
      DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(HHHHH):S/INDEX FILE DATA FROM READ"
      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(08):S/INDEX FILE READ BIN IDX"
   END-IF.

   IF TR-KEY-1 = 90
   THEN
      DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" 
      DISPLAY "IS22:(" TR-REC-TYPE-1 "):(S9):S/INDEX FILE READ"
      DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(IIIII):S/INDEX FILE DATA FROM READ"
      DISPLAY "IS24:(" TR-BIN-IDX-1 "):(09):S/INDEX FILE READ BIN IDX"
   END-IF.

   PERFORM D000-READ.

C000-EXIT.
   EXIT.

D000-READ.

   READ TEST-FILE NEXT
    AT END
      DISPLAY "IX10:(" TR-FS "):(10):INDEX FILE READ AT EOF"
      MOVE "YES" TO W01-SWITCHES
   END-READ.