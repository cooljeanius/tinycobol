 IDENTIFICATION DIVISION.
 PROGRAM-ID.    CTESTP_START1.
 ENVIRONMENT DIVISION.
*  TEST START VERB FORMAT.

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
      OPEN OUTPUT GOZOUT.
      MOVE 0 TO X-IND
* This does not conform to the COBOL-85 standard
*      MOVE 101 TO X-IND
*      START GOZOUT  KEY IS EQUAL TO WS-RECORD-NO
      START GOZOUT  KEY IS EQUAL TO X-IND
          INVALID KEY
              MOVE "FAIL" TO DESCRIPTION
*          NOT INVALID KEY
*              MOVE "PASS" TO DESCRIPTION
      END-START.
      CLOSE GOZOUT.
      STOP RUN.
