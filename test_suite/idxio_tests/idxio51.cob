IDENTIFICATION DIVISION.
PROGRAM-ID. IDXIO51.
ENVIRONMENT DIVISION.

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>    DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT TEST-FILE 
     ASSIGN TO "idxiotest41" 
     ORGANIZATION IS INDEXED
     ACCESS MODE  IS DYNAMIC
     RECORD KEY IS TR-KEY-1
     ALTERNATE RECORD KEY IS TR-REC-TYPE-1 
       WITH DUPLICATES
     FILE STATUS IS TR-FS.

DATA DIVISION.
FILE SECTION.
FD  TEST-FILE
*>     LABEL RECORD IS STANDARD
     RECORD IS VARYING IN SIZE FROM 10 TO 15 CHARACTERS
     DEPENDING ON RECORD-LENGTH.

01  TEST-REC-1.
    05  TR-KEY-1               PIC  9(03).
    05  TR-REC-TYPE-1          PIC  X(02).
    05  TR-DESCRIPTION-1       PIC  X(05).

01  TEST-REC-2.
    05  TR-KEY-2               PIC  9(03).
    05  TR-REC-TYPE-2          PIC  X(02).
    05  TR-DESCRIPTION-2       PIC  X(10).

WORKING-STORAGE SECTION.
 01 TR-FS                      PIC 9(02).
 01 RECORD-LENGTH              PIC 9(03).         
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

B000-HOUSEKEEPING.
   CLOSE TEST-FILE.
   DISPLAY "IXC2:(" TR-FS "):(00):INDEX READ CLOSE".

C000-MAIN-PROCESS.
   MOVE 15 TO TR-KEY-1.
   START TEST-FILE.
   DISPLAY "IX01:(" TR-FS "):(00):INDEX FILE START WITH PRIMARY KEY EQUAL".
   DISPLAY "IX02:(" TR-KEY-1 "):(015):INDEX FILE START KEY DEFAULT EQUAL".

   PERFORM D000-READ-NEXT.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ KEY STATUS".
   DISPLAY "IX22:(" TR-REC-TYPE-1 "):(RU):INDEX FILE READ KEY".
   DISPLAY "IX23:(" TR-KEY-1 "):(015):INDEX FILE READ KEY".

   MOVE "T5"    TO TR-REC-TYPE-1.
   MOVE ALL "5" TO TR-DESCRIPTION-1.
   REWRITE TEST-REC-1.
   DISPLAY "IR03:(" TR-FS "):(00):INDEX FILE REWRITE STATUS".

D000-READ-NEXT.
   READ TEST-FILE NEXT
   END-READ.
