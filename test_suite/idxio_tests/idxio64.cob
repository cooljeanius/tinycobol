IDENTIFICATION DIVISION.
PROGRAM-ID. IDXIO64.
ENVIRONMENT DIVISION.

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "idxiotest61" 
     ORGANIZATION IS INDEXED
     ACCESS MODE  IS DYNAMIC
     RECORD KEY IS TR-KEY-1
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
 01 W-COUNTER                  PIC 9(15).

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM C000-MAIN-PROCESS.
   PERFORM B000-HOUSEKEEPING.

   STOP RUN.

A000-INITIALIZE.
   OPEN INPUT TEST-FILE.
   DISPLAY "IXO2:(" TR-FS "):(00):INDEX READ OPEN".
   MOVE 0 TO W-COUNTER.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "IXC2:(" TR-FS "):(00):INDEX READ CLOSE".

C000-MAIN-PROCESS.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(000):INDEX FILE READ KEY".
   DISPLAY "IS24:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY-1 "):(001):INDEX FILE READ NEXT".
   DISPLAY "IS27:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   MOVE 10 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(S1):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(010):INDEX FILE READ KEY".
   DISPLAY "IS24:(" TR-BIN-IDX-1 "):(01):INDEX FILE READ BIN IDX"

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY-1 "):(009):INDEX FILE READ PREVIOUS".
   DISPLAY "IS30:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   MOVE 20 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(S2):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(020):INDEX FILE READ KEY".
*> This is to avoid a BUG with VB-ISAM variable length records
   DISPLAY "IS24:(" TR-BIN-IDX-1 "):(12):INDEX FILE READ BIN IDX"

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY-1 "):(021):INDEX FILE READ NEXT".
   DISPLAY "IS27:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   MOVE 30 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(S3):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(030):INDEX FILE READ KEY".
   DISPLAY "IS24:(" TR-BIN-IDX-1 "):(03):INDEX FILE READ BIN IDX"

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY-1 "):(029):INDEX FILE READ PREVIOUS".
   DISPLAY "IS30:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   MOVE 40 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(S4):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(040):INDEX FILE READ KEY".
   DISPLAY "IS24:(" TR-BIN-IDX-1 "):(04):INDEX FILE READ BIN IDX"

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY-1 "):(041):INDEX FILE READ NEXT".
   DISPLAY "IS27:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   MOVE 50 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(S5):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(050):INDEX FILE READ KEY".
   DISPLAY "IS24:(" TR-BIN-IDX-1 "):(05):INDEX FILE READ BIN IDX"

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY-1 "):(049):INDEX FILE READ PREVIOUS".
   DISPLAY "IS30:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   MOVE 60 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(S6):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(060):INDEX FILE READ KEY".
   DISPLAY "IS24:(" TR-BIN-IDX-1 "):(06):INDEX FILE READ BIN IDX"

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY-1 "):(061):INDEX FILE READ NEXT".
   DISPLAY "IS27:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   MOVE 70 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(S7):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(070):INDEX FILE READ KEY".
   DISPLAY "IS24:(" TR-BIN-IDX-1 "):(07):INDEX FILE READ BIN IDX"

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY-1 "):(069):INDEX FILE READ PREVIOUS".
   DISPLAY "IS30:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   MOVE 80 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(S8):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(080):INDEX FILE READ KEY".
   DISPLAY "IS24:(" TR-BIN-IDX-1 "):(08):INDEX FILE READ BIN IDX"

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY-1 "):(081):INDEX FILE READ NEXT".
   DISPLAY "IS27:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   MOVE 90 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(S9):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(090):INDEX FILE READ KEY".
   DISPLAY "IS24:(" TR-BIN-IDX-1 "):(09):INDEX FILE READ BIN IDX"

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY-1 "):(089):INDEX FILE READ PREVIOUS".
   DISPLAY "IS30:(" TR-BIN-IDX-1 "):(20):INDEX FILE READ BIN IDX"

   MOVE 999 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX23:(" TR-FS "):(23):INDEX FILE READ INVALID KEY".

D000-READ.
   MOVE W-COUNTER TO TR-KEY-1.
   READ TEST-FILE 
   END-READ.

D000-READ-NEXT.
   READ TEST-FILE NEXT
   END-READ.

D000-READ-PREV.
   READ TEST-FILE PREVIOUS
   END-READ.
