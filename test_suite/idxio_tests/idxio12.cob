IDENTIFICATION DIVISION.
PROGRAM-ID. IDXIO12.
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

   MOVE 'RU' TO TR-REC-TYPE.
   START TEST-FILE KEY IS EQUAL TO TR-REC-TYPE.
   DISPLAY "IX01:(" TR-FS "):(00):INDEX FILE START STATUS WITH SECONDARY KEY EQUAL".
   DISPLAY "IX02:(" TR-REC-TYPE "):(RU):INDEX FILE SECONDARY KEY".

   PERFORM D000-READ-NEXT.
   DISPLAY "IX21:(" TR-FS "):(00):INDEX FILE READ STATUS".
   DISPLAY "IX22:(" TR-REC-TYPE "):(RU):INDEX FILE READ SECONDARY KEY".
   DISPLAY "IX23:(" TR-KEY "):(001):INDEX FILE READ KEY".

   MOVE "T6"    TO TR-REC-TYPE.
   MOVE ALL "6" TO TR-DESCRIPTION.
   REWRITE TEST-REC.
   DISPLAY "IR03:(" TR-FS "):(00):INDEX FILE REWRITE STATUS".

D000-READ-NEXT.
   READ TEST-FILE NEXT
   END-READ.
