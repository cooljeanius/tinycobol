 IDENTIFICATION DIVISION.
 PROGRAM-ID.    SRTIO04.
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION. 
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
     SELECT ARQ      ASSIGN TO "input.dat" 
            ORGANIZATION IS SEQUENTIAL
            ACCESS MODE  IS SEQUENTIAL
            FILE STATUS  IS FS.
     SELECT OUT-REC ASSIGN TO "sorted.dat"
            ORGANIZATION IS SEQUENTIAL    
            ACCESS MODE IS SEQUENTIAL
            FILE STATUS IS FS.
     SELECT SORT-REC ASSIGN TO "sort.dat".
 DATA DIVISION.
 FILE SECTION.
 FD ARQ
     LABEL RECORD IS STANDARD.
       01  REG-ARQ.
         03 P-IND                  PIC  9(03).
         03 DESCRIPTION            PIC  X(20).
         03 N-KEY2                 PIC  9(02).
         03 DESC2                  PIC  X(04).
 FD OUT-REC.
       01      MAIN-RECORD        PIC X(29).    
 SD SORT-REC.
       01 MAIN-REC.
         03 INDICATOR       PIC 9(03).
         03 DESC            PIC X(20).
         03 SF-KEY2         PIC 9(02).
         03 SF-DESC2        PIC X(04).
 WORKING-STORAGE SECTION.
        01 FS        PIC X(02).
        01 W-CNT-IN    PIC S9(4) COMP.
        01 W-CNT-OUT   PIC S9(4) COMP.
        01 REM        PIC 9(5).
        01 W01-SWITCHES    PIC X(03).
          88 W01-END  VALUE "YES".
          88 W01-MORE VALUE "NO".
       01  WSRT-REC.
         03 WSRT-IND                  PIC  9(03).
         03 WSRT-DESC                 PIC  X(20).
         03 WSRT-KEY2                 PIC  9(02).
         03 WSRT-DESC2                PIC  X(04).
     01 EXPECTED-SEQUENCE-RESULT-CONST.
        05 FILLER PIC S9(4) COMP VALUE 20.
        05 FILLER PIC S9(4) COMP VALUE 10.
        05 FILLER PIC S9(4) COMP VALUE 19.
        05 FILLER PIC S9(4) COMP VALUE 9.
        05 FILLER PIC S9(4) COMP VALUE 18.
        05 FILLER PIC S9(4) COMP VALUE 8.
        05 FILLER PIC S9(4) COMP VALUE 17.
        05 FILLER PIC S9(4) COMP VALUE 7.
        05 FILLER PIC S9(4) COMP VALUE 16.
        05 FILLER PIC S9(4) COMP VALUE 6.
        05 FILLER PIC S9(4) COMP VALUE 15.
        05 FILLER PIC S9(4) COMP VALUE 5.
        05 FILLER PIC S9(4) COMP VALUE 14.
        05 FILLER PIC S9(4) COMP VALUE 13.
        05 FILLER PIC S9(4) COMP VALUE 4.
        05 FILLER PIC S9(4) COMP VALUE 3.
        05 FILLER PIC S9(4) COMP VALUE 12.
        05 FILLER PIC S9(4) COMP VALUE 2.
        05 FILLER PIC S9(4) COMP VALUE 11.
        05 FILLER PIC S9(4) COMP VALUE 1.
     01 EXPECTED-RESULT-REDEF REDEFINES EXPECTED-SEQUENCE-RESULT-CONST.
        05 ESR-ENT OCCURS 20.
	   10 ESR-VAL PIC S9(4) COMP.
     01 GSR-TAB.
        05 GSR-ENT OCCURS 20.
	   10 GSR-VAL PIC S9(4) COMP.
 PROCEDURE DIVISION.
 MAIN SECTION.
     MOVE 0 TO W-CNT-IN W-CNT-OUT REM.
     SORT SORT-REC ASCENDING KEY SF-KEY2 
          DESCENDING KEY INDICATOR
          INPUT PROCEDURE IN-ARQ
          GIVING OUT-REC

     PERFORM IN-SRT
     PERFORM CHECK-RESULTS
     STOP RUN.
     
 CHECK-RESULTS SECTION.
     PERFORM VARYING W-CNT-OUT FROM 1 BY 1 UNTIL W-CNT-OUT > 20
        DISPLAY "SRTIO04:(" GSR-VAL(W-CNT-OUT) "):(" ESR-VAL(W-CNT-OUT)
	        "):Record no " W-CNT-OUT
     END-PERFORM
     .
     
 IN-ARQ SECTION.
     MOVE "NO" TO W01-SWITCHES.
     OPEN INPUT ARQ.
     PERFORM READ-INPUT
             UNTIL W01-END.
     CLOSE ARQ.
 READ-INPUT.
     READ ARQ
             AT END MOVE "YES" TO W01-SWITCHES
     IF (FS NOT = "00") AND W01-MORE 
        DISPLAY "Error on Reading Input File " FS  W01-SWITCHES
        STOP RUN.
     IF NOT W01-END 
        MOVE REG-ARQ TO MAIN-REC
        RELEASE MAIN-REC
        ADD 1 TO W-CNT-IN
        .
 IN-SRT SECTION.
     MOVE "NO" TO W01-SWITCHES.
     OPEN INPUT OUT-REC
     PERFORM READ-SRT
             UNTIL W01-END.
     CLOSE OUT-REC.
 READ-SRT.
     READ OUT-REC INTO WSRT-REC
             AT END MOVE "YES" TO W01-SWITCHES
     IF (FS NOT = "00") AND W01-MORE 
        DISPLAY "Error on Reading Sorted File " FS  W01-SWITCHES
        STOP RUN.
     IF NOT W01-END 
        ADD 1 TO W-CNT-OUT
        MOVE WSRT-IND TO GSR-VAL(W-CNT-OUT)
        .
