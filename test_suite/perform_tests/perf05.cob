 IDENTIFICATION DIVISION.
 PROGRAM-ID.    PERF05.

 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.
* INPUT-OUTPUT SECTION.

 DATA DIVISION.
 FILE SECTION.     
 WORKING-STORAGE SECTION.
 01  WS-COUNTERS.
     05 WS-TEST-COUNTER              PIC  9(4).
     05 WS-PERFORM-COUNT             PIC  9(4).

 PROCEDURE DIVISION.
 0000-PROGRAM-ENTRY.
      MOVE 0              TO WS-TEST-COUNTER.
      PERFORM B000-PERF1 THRU B000-EXIT.
      PERFORM E000-SUMMARY.
      STOP RUN.
      
      DISPLAY "P002:(IL):(FA):PROGRAM RAN PAST STOP RUN".

 B000-PERF1.
      MOVE 27             TO WS-PERFORM-COUNT.

 B000-LOOPER.
      ADD 1             TO WS-TEST-COUNTER.
      SUBTRACT 1 FROM WS-PERFORM-COUNT.
      IF WS-PERFORM-COUNT > 0
         GO TO B000-LOOPER.
 B000-EXIT.
     EXIT.

 E000-SUMMARY.
      DISPLAY "P005:(" WS-TEST-COUNTER "):(0027):"
          "PERFORM PIC 9(4) TIMES TEST".
