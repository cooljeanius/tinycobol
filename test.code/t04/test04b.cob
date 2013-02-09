IDENTIFICATION DIVISION.
PROGRAM-ID.    TEST04B.
ENVIRONMENT DIVISION.

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>     DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
     SELECT GOZIN ASSIGN TO "seqdata01.dat" 
            ORGANIZATION IS SEQUENTIAL 
            ACCESS MODE     SEQUENTIAL
            FILE STATUS  IS FS.

DATA DIVISION.
FILE SECTION.

 FD  GOZIN
     LABEL RECORD IS STANDARD.
 01  GOZIN-REC.
     03 X-IND                         PIC  9(03).
     03 DESCRIPTION                   PIC  X(07).
      
WORKING-STORAGE SECTION.
 01  FS                              PIC  9(02).
 01  WS-COUNTER                      PIC  9(04) COMP-5.
 01  WS-EOF-SW                       PIC  X(01) VALUE 'N' .
   88  WS-EOF VALUE 'Y'.

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
      PERFORM B000-INITIALIZE.
      PERFORM C000-MAIN-LOGIC UNTIL WS-EOF.
      PERFORM D000-CLEANUP.
      PERFORM E000-SUMMARY.
      STOP RUN.

B000-INITIALIZE.
      MOVE 0      TO WS-COUNTER.
      OPEN INPUT GOZIN.
      DISPLAY "SEQUENTIAL INPUT OPEN  STATUS " FS.

C000-MAIN-LOGIC.
      READ GOZIN
       AT END
         MOVE 'Y' TO WS-EOF-SW 
       NOT AT END
         ADD 1    TO WS-COUNTER
      END-READ.

*>      DISPLAY "SEQUENTIAL I/O READ STATUS " FS.
*>      DISPLAY "DATA FROM READ " X-IND DESCRIPTION.

D000-CLEANUP.
      CLOSE GOZIN.
      DISPLAY "SEQUENTIAL INPUT CLOSE STATUS " FS.

E000-SUMMARY.
      DISPLAY "NUMBER OF RECORDS READ " WS-COUNTER.
