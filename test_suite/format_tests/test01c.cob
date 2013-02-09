 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST1_FORMATS.
 AUTHOR.  JIM NOETH.
 INSTALLATION. Tiny Cobol Project
 DATE-WRITTEN. 03 January, 2000.

 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS-COMP-VALUE           PIC S9(9) COMP.
 01  WS-DISPLAY-5            PIC 9(05).
 01  WS-DISPLAY-WITH-FRAC    PIC 9(05)V9999.
 01  WS-DISPLAY-WITH-SIGN    PIC S9(07).
 01  WS-ANOTHER-COMP         PIC 9(04) COMP.
 01  WS-PACKED               PIC 9(07)V99 COMP-3.
 01  WS-EDITED-1             PIC $$$$,$$9-.
 01  WS-CHARACTER-SHORT      PIC X(08).
 01  WS-CHARACTER-LONG       PIC X(15).
*
*
 01  WS-DUMP-COUNT           PIC 9(04).
 01  WS-DUMP-OUT-8           PIC X(08).
 01  WS-DUMP-OUT-10          PIC X(10).

 PROCEDURE DIVISION.
 0000-PROGRAM-ENTRY-POINT.
     DISPLAY "TEST1_FORMATS.program entry."

     PERFORM A000-COMPUTATIONAL-TESTS THRU A000-EXIT.

     STOP RUN.

 A000-COMPUTATIONAL-TESTS.
 A001-TEST.
     MOVE "-5432" TO WS-COMP-VALUE.

     MOVE WS-COMP-VALUE TO WS-DISPLAY-5.
     DISPLAY "A301:(" WS-DISPLAY-5 "):(05432):"
             "COMP MOVE -5432 TO 9(05)".

     MOVE WS-COMP-VALUE TO WS-DISPLAY-WITH-FRAC.
     DISPLAY "A302:(" WS-DISPLAY-WITH-FRAC "):(05432.0000):"
             "COMP MOVE -5432 TO 9(05)V9(04)".

     MOVE WS-COMP-VALUE TO WS-DISPLAY-WITH-SIGN.
     DISPLAY "A303:(" WS-DISPLAY-WITH-SIGN "):(-0005432):"
             "COMP MOVE -5432 TO S9(07)".

     MOVE WS-COMP-VALUE TO WS-ANOTHER-COMP.
     DISPLAY "A304:(" WS-ANOTHER-COMP "):(5432):"
             "COMP MOVE -5432 TO 9(04) COMP".

     MOVE WS-COMP-VALUE TO WS-PACKED.
     DISPLAY "A305:(" WS-PACKED "):(0005432.00):"
             "COMP MOVE -5432 TO 9(7)V99 COMP-3".

     MOVE WS-COMP-VALUE TO WS-EDITED-1.
     DISPLAY "A306:(" WS-EDITED-1 "):(  $5,432-):"
             "COMP MOVE -5432 TO $$$$,$$9-".

     MOVE 97531 TO WS-COMP-VALUE.
     MOVE WS-COMP-VALUE TO WS-DISPLAY-WITH-SIGN.
     MOVE WS-DISPLAY-WITH-SIGN TO WS-ANOTHER-COMP.
     DISPLAY "A307:(" WS-ANOTHER-COMP "):(7531):"
         "MOVE 97531 AS S9(07) TO 9(04) COMP".


     MOVE "-8642975" TO WS-COMP-VALUE.
     MOVE WS-COMP-VALUE TO WS-PACKED.
     MOVE WS-PACKED TO WS-ANOTHER-COMP.
     DISPLAY "A308:(" WS-ANOTHER-COMP "):(2975):"
         "MOVE -8642975 AS 9(07)V9(04) COMP-3 TO 9(04) COMP".

 A000-EXIT.
     EXIT.