IDENTIFICATION DIVISION.
PROGRAM-ID.    TEST06B.
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
 01 GOZIN-REC-1.
     03 FILLER                       PIC  X(80).
 01 GOZIN-REC-2.
     03 FILLER                       PIC  X(120).
 01 GOZIN-REC-3.
     03 FILLER                       PIC  X(30).
 01 GOZIN-REC-4                      PIC  X(50).
      
WORKING-STORAGE SECTION.
 01 FS                               PIC  9(02).
 01 WS-COUNTER                       PIC  9(04) COMP-5.
 01 WS-EOF-SW                        PIC  X(01) VALUE 'N' .
   88  WS-EOF VALUE 'Y'.
 01 WS-GOZIN-REC-1.
     03 WS-X-IND-1                   PIC  9(03).
     03 WS-DESCRIPTION-1             PIC  X(10).
     03 FILLER                       PIC  X(67).
 01 WS-GOZIN-REC-2.
     03 WS-X-IND-2                   PIC  9(03).
     03 WS-DESCRIPTION-2             PIC  X(10).
     03 FILLER                       PIC  X(107).
 01 WS-GOZIN-REC-3.
     03 WS-X-IND-3                   PIC  9(03).
     03 WS-DESCRIPTION-3             PIC  X(10).
     03 FILLER                       PIC  X(17).
 01 WS-GOZIN-REC-4.
     03 WS-X-IND-4                   PIC  9(03).
     03 WS-DESCRIPTION-4             PIC  X(10).
     03 FILLER                       PIC  X(37).

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
      DISPLAY "SEQUENTIAL INPUT OPEN STATUS " FS.

C000-MAIN-LOGIC.
     READ GOZIN
       AT END
         MOVE 'Y' TO WS-EOF-SW 
       NOT AT END
         ADD 1    TO WS-COUNTER
     END-READ.

D000-CLEANUP.
      CLOSE GOZIN.
      DISPLAY "SEQUENTIAL INPUT CLOSE STATUS " FS.

E000-SUMMARY.
      DISPLAY "NUMBER OF RECORDS READ " WS-COUNTER.