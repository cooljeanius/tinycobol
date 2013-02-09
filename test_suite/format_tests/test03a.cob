 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST3_FORMATS.
 AUTHOR.  GLEN COLBERT.

 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS-ALPHANUM-FIELDS.
     05 WS-ALPHANUM-1                PIC X(01).
     05 WS-ALPHANUM-2                PIC X(02).
     05 WS-ALPHANUM-3                PIC X(03).
     05 WS-ALPHANUM-4                PIC X(04).
     05 WS-ALPHANUM-5                PIC X(05).
     05 WS-ALPHANUM-6                PIC X(06).
     05 WS-ALPHANUM-7                PIC X(07).
     05 WS-AB-5                      PIC XXBXXX.
     05 WS-AB-3                      PIC XBXX.

 01  WS-NUMERIC-FIELDS.
     05 WS-DISPLAY-NUM-1             PIC 9.
     05 WS-DISPLAY-NUM-2             PIC 9(2).
     05 WS-DISPLAY-NUM-3             PIC 9(3).
     05 WS-DISPLAY-NUM-4             PIC 9(4).
     05 WS-DISPLAY-NUM-5             PIC 9(5).
     05 WS-DISPLAY-NUM-6             PIC 9(6).
     05 WS-DISPLAY-NUM-7             PIC 9(7).
     05 WS-DISPLAY-NUM-V5            PIC 9(3)V99.
     05 WS-DISPLAY-NUM-R5 REDEFINES WS-DISPLAY-NUM-V5
                                     PIC X(5).

 PROCEDURE DIVISION.
 0000-PROGRAM-ENTRY-POINT.
     DISPLAY "TEST02 FORMATS program entry."

     PERFORM A000-ALPHANUMERIC-TESTS THRU A000-EXIT.

     STOP RUN.

 A000-ALPHANUMERIC-TESTS.

 AN01-TEST.
     MOVE 9                   TO WS-DISPLAY-NUM-1.
     MOVE 89                  TO WS-DISPLAY-NUM-2.
     MOVE 789                 TO WS-DISPLAY-NUM-3.
     MOVE 6789                TO WS-DISPLAY-NUM-4.
     MOVE 56789               TO WS-DISPLAY-NUM-5.
     MOVE 456789              TO WS-DISPLAY-NUM-6.
     MOVE 3456789             TO WS-DISPLAY-NUM-7.

     MOVE WS-DISPLAY-NUM-1    TO WS-ALPHANUM-6.
     DISPLAY "AN01:(" WS-ALPHANUM-6 "):(9     ):"
             "LEFT ALIGNMENT MOVE TEST MOVE 9(1) TO X(6)".

     MOVE WS-DISPLAY-NUM-4    TO WS-ALPHANUM-6.
     DISPLAY "AN02:(" WS-ALPHANUM-6 "):(6789  ):"
             "LEFT ALIGNMENT MOVE TEST MOVE 9(4) TO X(6)".

     MOVE WS-DISPLAY-NUM-6    TO WS-ALPHANUM-6.
     DISPLAY "AN03:(" WS-ALPHANUM-6 "):(456789):"
             "LEFT ALIGNMENT MOVE TEST MOVE 9(6) TO X(6)".

     MOVE WS-DISPLAY-NUM-7    TO WS-ALPHANUM-6.
     DISPLAY "AN04:(" WS-ALPHANUM-6 "):(345678):"
             "LEFT ALIGNMENT MOVE TEST MOVE 9(7) TO X(6)".

     MOVE WS-DISPLAY-NUM-5    TO WS-DISPLAY-NUM-7
     DISPLAY "AN05:(" WS-DISPLAY-NUM-7 "):(0056789):"
             "RIGHT ALIGNMENT MOVE TEST MOVE 9(5) TO 9(7)".

     MOVE WS-DISPLAY-NUM-5    TO WS-DISPLAY-NUM-2
     DISPLAY "AN06:(" WS-DISPLAY-NUM-2 "):(89):"
             "RIGHT ALIGNMENT MOVE TEST MOVE 9(5) TO 9(2)".

     MOVE WS-DISPLAY-NUM-5    TO WS-DISPLAY-NUM-1
     DISPLAY "AN07:(" WS-DISPLAY-NUM-1 "):(9):"
             "RIGHT ALIGNMENT MOVE TEST MOVE 9(5) TO 9(1)".

     MOVE WS-DISPLAY-NUM-5    TO WS-DISPLAY-NUM-V5
     DISPLAY "AN08:(" WS-DISPLAY-NUM-R5 "):(78900):"
             "RIGHT ALIGNMENT MOVE TEST MOVE 9(5) TO 9(3)V99".

     MOVE 12345               TO WS-DISPLAY-NUM-5.
     MOVE WS-DISPLAY-NUM-5    TO WS-ALPHANUM-2.
     DISPLAY "AN22:(" WS-ALPHANUM-2 "):(12):"
             "MOVE TEST MOVE 9(5) TO X(2)".

     MOVE 12345               TO WS-DISPLAY-NUM-5.
     MOVE WS-DISPLAY-NUM-5    TO WS-ALPHANUM-6.
     DISPLAY "AN23:(" WS-ALPHANUM-6 "):(12345 ):"
             "MOVE TEST MOVE 9(5) TO X(6)".

     MOVE 0                   TO WS-DISPLAY-NUM-4.
     DISPLAY "AC01:(" WS-DISPLAY-NUM-4 "):(0000):"
             "CONSTANT MOVE TEST MOVE 0 TO 9(4)".

     MOVE ".02"              TO WS-DISPLAY-NUM-4.
     DISPLAY "AC02:(" WS-DISPLAY-NUM-4 "):(0000):"
             "CONSTANT MOVE TEST MOVE .02 TO 9(4)".

     MOVE 2                 TO WS-DISPLAY-NUM-4.
     DISPLAY "AC03:(" WS-DISPLAY-NUM-4 "):(0002):"
             "CONSTANT MOVE TEST MOVE 2 TO 9(4)".

     MOVE "1234.5"           TO WS-DISPLAY-NUM-4.
     DISPLAY "AC04:(" WS-DISPLAY-NUM-4 "):(1234):"
             "CONSTANT MOVE TEST MOVE 1234.5 TO 9(4)".

     MOVE "-123.4"           TO WS-DISPLAY-NUM-4.
     DISPLAY "AC05:(" WS-DISPLAY-NUM-4 "):(0123):"
             "CONSTANT MOVE TEST MOVE -123.4 TO 9(4)".

 A000-EXIT.
     EXIT.