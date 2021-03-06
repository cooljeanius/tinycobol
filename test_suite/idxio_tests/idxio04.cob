IDENTIFICATION DIVISION.
PROGRAM-ID. IDXIO04.
ENVIRONMENT DIVISION.

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
 01 W-COUNTER                  PIC 9(15).
 01 W01-SWITCHES               PIC X(03).
   88 W01-END VALUE "YES".
   88 W01-MORE VALUE "NO".

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
   PERFORM A000-INITIALIZE.
   PERFORM C000-MAIN-PROCESS.
   PERFORM B000-HOUSEKEEPING.

   STOP RUN.

A000-INITIALIZE.
   OPEN I-O TEST-FILE.
   DISPLAY "IXO2:(" TR-FS "):(00):INDEX READ OPEN".
   MOVE "NO" TO W01-SWITCHES.
   MOVE 0 TO W-COUNTER.

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "IXC2:(" TR-FS "):(00):INDEX READ CLOSE".

C000-MAIN-PROCESS.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(RU):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(000):INDEX FILE READ KEY".

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY "):(001):INDEX FILE READ NEXT".

   MOVE 10 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(S1):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(010):INDEX FILE READ KEY".

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY "):(009):INDEX FILE READ PREVIOUS".

   MOVE 20 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(S2):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(020):INDEX FILE READ KEY".

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY "):(021):INDEX FILE READ NEXT".

   MOVE 30 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(S3):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(030):INDEX FILE READ KEY".

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY "):(029):INDEX FILE READ PREVIOUS".

   MOVE 40 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(S4):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(040):INDEX FILE READ KEY".

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY "):(041):INDEX FILE READ NEXT".

   MOVE 50 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(S5):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(050):INDEX FILE READ KEY".

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY "):(049):INDEX FILE READ PREVIOUS".

   MOVE 60 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(S6):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(060):INDEX FILE READ KEY".

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY "):(061):INDEX FILE READ NEXT".

   MOVE 70 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(S7):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(070):INDEX FILE READ KEY".

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY "):(069):INDEX FILE READ PREVIOUS".

   MOVE 80 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(S8):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(080):INDEX FILE READ KEY".

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY "):(081):INDEX FILE READ NEXT".

   MOVE 90 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(S9):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(090):INDEX FILE READ KEY".

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY "):(089):INDEX FILE READ PREVIOUS".

   MOVE 999 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX23:(" TR-FS "):(23):INDEX FILE READ INVALID KEY".

D000-READ.
   MOVE W-COUNTER TO TR-KEY.
   READ TEST-FILE 
*>      INVALID KEY 
*>        MOVE "YES" TO W01-SWITCHES
   END-READ.

D000-READ-NEXT.
   READ TEST-FILE NEXT
   END-READ.

D000-READ-PREV.
   READ TEST-FILE PREVIOUS
   END-READ.
