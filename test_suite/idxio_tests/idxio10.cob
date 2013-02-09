IDENTIFICATION DIVISION.
PROGRAM-ID. IDXIO10.
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

   PERFORM D000-READ-NEXT.
   DISPLAY "IX24:(" TR-FS "):(00):INDEX FILE READ NEXT".
   DISPLAY "IX25:(" TR-REC-TYPE "):(RU):INDEX FILE READ NEXT".
   DISPLAY "IX26:(" TR-KEY "):(000):INDEX FILE READ NEXT".
   MOVE "Z2"    TO TR-REC-TYPE.
   MOVE ALL "0" TO TR-DESCRIPTION.
   REWRITE TEST-REC.
   DISPLAY "IR03:(" TR-FS "):(00):INDEX FILE REWRITE STATUS".

   MOVE 10 TO W-COUNTER.
   PERFORM D000-READ.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY".
   DISPLAY "IX22:(" TR-REC-TYPE "):(S1):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY "):(010):INDEX FILE READ KEY".
   MOVE "Z2"    TO TR-REC-TYPE.
   MOVE ALL "0" TO TR-DESCRIPTION.
   REWRITE TEST-REC.
   DISPLAY "IR03:(" TR-FS "):(00):INDEX FILE REWRITE STATUS".

   PERFORM D000-READ-PREV.
   DISPLAY "IX27:(" TR-FS "):(00):INDEX FILE READ PREVIOUS".
   DISPLAY "IX28:(" TR-REC-TYPE "):(RU):INDEX FILE READ PREVIOUS".
   DISPLAY "IX29:(" TR-KEY "):(009):INDEX FILE READ PREVIOUS".
   MOVE "Z2"    TO TR-REC-TYPE.
   MOVE ALL "0" TO TR-DESCRIPTION.
   REWRITE TEST-REC.
   DISPLAY "IR03:(" TR-FS "):(00):INDEX FILE REWRITE STATUS".

D000-READ.
   MOVE W-COUNTER TO TR-KEY.
   READ TEST-FILE 
   END-READ.

D000-READ-NEXT.
   READ TEST-FILE NEXT
   END-READ.

D000-READ-PREV.
   READ TEST-FILE PREVIOUS
   END-READ.