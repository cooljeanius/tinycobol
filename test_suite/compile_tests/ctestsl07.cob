 IDENTIFICATION DIVISION.
 PROGRAM-ID.    CTESTWS19.
 ENVIRONMENT DIVISION.
*  TEST SELECT FORMAT 4 (INDEXED).

 CONFIGURATION SECTION.
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
     SELECT GOZOUT
            ASSIGN TO "FILLER " 
            ORGANIZATION IS INDEXED
            ACCESS       IS DYNAMIC
            RECORD KEY   IS X-IND 
            FILE STATUS  IS FS.

 DATA DIVISION.
 FILE SECTION.

 FD  GOZOUT
     LABEL RECORD IS STANDARD.
 01  GOZOUT-REC.
     03 X-IND                        PIC  9(03).
     03 DESCRIPTION                  PIC  X(20).
     03 FILLER                       PIC  X(57).

 WORKING-STORAGE SECTION.
 01  FS                              PIC  9(02).
 01  WS-COUNTERS.
     05 WS-TEST-COUNTER              PIC  9(4).
 01  WS-DATA                         PIC X(80).
 01  WS-NAME                         PIC X(80) VALUE "./input.dat" .
 01  WS-RECORD-NO                    PIC 9(9) COMP VALUE 0 .

 PROCEDURE DIVISION.
 0000-MAIN.
      STOP RUN.
