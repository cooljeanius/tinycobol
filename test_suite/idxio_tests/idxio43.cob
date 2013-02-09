IDENTIFICATION DIVISION.
PROGRAM-ID. IDXIO43.
ENVIRONMENT DIVISION.

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "idxiotest41" 
     ORGANIZATION IS INDEXED
     ACCESS MODE  IS RANDOM
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
   05  TR-GKEY-1.
     10  TR-KEY-1              PIC  9(03).
   05  TR-REC-TYPE-1           PIC  X(02).
   05  TR-DESCRIPTION-1        PIC  X(05).

 01 TEST-REC-2.
   05  TR-KEY-2                PIC  9(03).
   05  TR-REC-TYPE-2           PIC  X(02).
   05  TR-DESCRIPTION-2        PIC  X(10).

WORKING-STORAGE SECTION.
 01 TR-FS                      PIC 9(02).
 01 RECORD-LENGTH              PIC 9(03).         
 01 W-COUNTER                  PIC 9(05).

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM C000-PROCESS.
   PERFORM B000-HOUSEKEEPING.

   STOP RUN.

A000-INITIALIZE.
   OPEN INPUT TEST-FILE.
   MOVE LOW-VALUES TO TR-GKEY-1.
   DISPLAY "ISO2:(" TR-FS "):(00):S/INDEX READ OPEN".
   MOVE 0 TO W-COUNTER.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "ISC2:(" TR-FS "):(00):S/INDEX READ CLOSE".

C000-PROCESS.

   PERFORM D000-READ.
   DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ".
   DISPLAY "IS22:(" TR-REC-TYPE-1 "):(RU):S/INDEX FILE READ".
   DISPLAY "IS23:(" TR-DESCRIPTION-1 "):(UUUUU):S/INDEX FILE READ".
   DISPLAY "IS24:(" RECORD-LENGTH "):(010):S/INDEX FILE READ RECORD LENGTH"

   MOVE 10 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ".
   DISPLAY "IS22:(" TR-REC-TYPE-2 "):(S1):S/INDEX FILE READ".
   DISPLAY "IS23:(" TR-DESCRIPTION-2 "):(AAAAAAAAAA):S/INDEX FILE DATA FROM READ".
   DISPLAY "IS24:(" RECORD-LENGTH "):(015):S/INDEX FILE READ RECORD LENGTH"

   MOVE 20 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ".
   DISPLAY "IS22:(" TR-REC-TYPE-2 "):(S2):S/INDEX FILE READ".
   DISPLAY "IS23:(" TR-DESCRIPTION-2 "):(BBBBBBBBBB):S/INDEX FILE DATA FROM READ".
   DISPLAY "IS24:(" RECORD-LENGTH "):(015):S/INDEX FILE READ RECORD LENGTH"

   MOVE 30 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ".
   DISPLAY "IS22:(" TR-REC-TYPE-2 "):(S3):S/INDEX FILE READ".
   DISPLAY "IS23:(" TR-DESCRIPTION-2 "):(CCCCCCCCCC):S/INDEX FILE DATA FROM READ".
   DISPLAY "IS24:(" RECORD-LENGTH "):(015):S/INDEX FILE READ RECORD LENGTH"

   MOVE 40 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ".
   DISPLAY "IS22:(" TR-REC-TYPE-2 "):(S4):S/INDEX FILE READ".
   DISPLAY "IS23:(" TR-DESCRIPTION-2 "):(DDDDDDDDDD):S/INDEX FILE DATA FROM READ".
   DISPLAY "IS24:(" RECORD-LENGTH "):(015):S/INDEX FILE READ RECORD LENGTH"

   MOVE 50 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ".
   DISPLAY "IS22:(" TR-REC-TYPE-2 "):(S5):S/INDEX FILE READ".
   DISPLAY "IS23:(" TR-DESCRIPTION-2 "):(EEEEEEEEEE):S/INDEX FILE DATA FROM READ".
   DISPLAY "IS24:(" RECORD-LENGTH "):(015):S/INDEX FILE READ RECORD LENGTH"

   MOVE 60 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ".
   DISPLAY "IS22:(" TR-REC-TYPE-2 "):(S6):S/INDEX FILE READ".
   DISPLAY "IS23:(" TR-DESCRIPTION-2 "):(FFFFFFFFFF):S/INDEX FILE DATA FROM READ".
   DISPLAY "IS24:(" RECORD-LENGTH "):(015):S/INDEX FILE READ RECORD LENGTH"

   MOVE 70 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" .
   DISPLAY "IS22:(" TR-REC-TYPE-2 "):(S7):S/INDEX FILE READ".
   DISPLAY "IS23:(" TR-DESCRIPTION-2 "):(GGGGGGGGGG):S/INDEX FILE DATA FROM READ".
   DISPLAY "IS24:(" RECORD-LENGTH "):(015):S/INDEX FILE READ RECORD LENGTH"

   MOVE 80 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" .
   DISPLAY "IS22:(" TR-REC-TYPE-2 "):(S8):S/INDEX FILE READ".
   DISPLAY "IS23:(" TR-DESCRIPTION-2 "):(HHHHHHHHHH):S/INDEX FILE DATA FROM READ".
   DISPLAY "IS24:(" RECORD-LENGTH "):(015):S/INDEX FILE READ RECORD LENGTH"

   MOVE 90 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IS21:(" TR-FS "):(00):S/INDEX FILE STATUS READ" .
   DISPLAY "IS22:(" TR-REC-TYPE-2 "):(S9):S/INDEX FILE READ".
   DISPLAY "IS23:(" TR-DESCRIPTION-2 "):(IIIIIIIIII):S/INDEX FILE DATA FROM READ".
   DISPLAY "IS24:(" RECORD-LENGTH "):(015):S/INDEX FILE READ RECORD LENGTH"

   MOVE 999 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX01:(" TR-FS "):(23):INDEX FILE READ INVALID KEY".

C000-EXIT.
   EXIT.

D000-READ.
   MOVE W-COUNTER TO TR-KEY-1.
   READ TEST-FILE 
   END-READ.
