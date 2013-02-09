 IDENTIFICATION DIVISION.
 PROGRAM-ID.   CTESTP_CLOSE1.
 ENVIRONMENT DIVISION.
* TEST CLOSE WITH LOCK VERB FORMAT
 CONFIGURATION SECTION. 
 SPECIAL-NAMES.
     DECIMAL-POINT IS COMMA.
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
     SELECT GOZOUT ASSIGN TO "./input.dat" 
            ORGANIZATION IS SEQUENTIAL 
            ACCESS       IS SEQUENTIAL
            FILE STATUS  IS FS.

 DATA DIVISION.
 FILE SECTION.

 FD  GOZOUT
     LABEL RECORD IS STANDARD.
 01  GOZOUT-REC.
     03 X-IND                         PIC  9(03).
     03 DESCRIPTION                   PIC  X(20).
     03 FILLER                        PIC  X(57).
      
 WORKING-STORAGE SECTION.
 01  FS                              PIC  9(02).
 01  WS-COUNTERS.
     05 WS-TEST-COUNTER              PIC  9(4).

 PROCEDURE DIVISION.
 000-MAIN.
      OPEN OUTPUT GOZOUT.
      CLOSE GOZOUT WITH LOCK.
      STOP RUN.