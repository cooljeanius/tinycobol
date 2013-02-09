 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST1_FORMATS.
 AUTHOR.  GLEN COLBERT.

 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS-ALPHA-FIELDS.
     05 WS-ALPHA-6                   PIC A(06).
     05 WS-ALPHA-5                   PIC A(05).
     05 WS-ALPHA-2                   PIC A(02).

 01  WS-ALPHANUM-FIELDS.
     05 WS-ALPHANUM-1                PIC X(01).
     05 WS-ALPHANUM-2                PIC X(02).
     05 WS-ALPHANUM-3                PIC X(03).
     05 WS-ALPHANUM-4                PIC X(04).
     05 WS-ALPHANUM-5                PIC X(05).
     05 WS-ALPHANUM-6                PIC X(06).
     05 WS-ALPHANUM-36               PIC X(36).
     05 WS-AB-5                      PIC XXBXXX.
     05 WS-AB-3                      PIC XBXX.
     05 WS-AS-5                      PIC XX/XXX.
     05 WS-AS-3                      PIC X/XX.

 01  WS-NUMERIC-FIELDS.
     05 WS-DISPLAY-NUM-1             PIC 9.
     05 WS-DISPLAY-NUM-4             PIC 9(4).
     05 WS-DISPLAY-NUM-V5            PIC 9(3)V99.

 PROCEDURE DIVISION.
 0000-PROGRAM-ENTRY-POINT.
     DISPLAY "TEST02 FORMATS program entry."

     PERFORM A000-ALPHANUMERIC-TESTS THRU A000-EXIT.

     STOP RUN.

 A000-ALPHANUMERIC-TESTS.
     MOVE "A"                 TO WS-ALPHANUM-1.
     MOVE "AB"                TO WS-ALPHANUM-2.
     MOVE "ABC"               TO WS-ALPHANUM-3.
     MOVE "ABCD"              TO WS-ALPHANUM-4.
     MOVE "ABCDE"             TO WS-ALPHANUM-5.
     MOVE "ABCDEFGHIJKLMNOPQRSTUVWZYZ0123456789" TO
           WS-ALPHANUM-36.

 AN01-TEST.
     MOVE WS-ALPHANUM-5       TO WS-ALPHANUM-6.
     DISPLAY "AN01:(" WS-ALPHANUM-6 "):(ABCDE ):"
             "ALPHANUMERIC MOVE TEST MOVE X(5) TO X(6)".

     MOVE WS-ALPHANUM-5       TO WS-ALPHA-5.
     DISPLAY "AN02:(" WS-ALPHA-5 "):(ABCDE):"
             "ALPHANUMERIC MOVE TEST MOVE X(5) TO A(5)".

     MOVE WS-ALPHANUM-5       TO WS-ALPHANUM-4.
     DISPLAY "AN03:(" WS-ALPHANUM-4 "):(ABCD):"
             "ALPHANUMERIC MOVE TEST MOVE X(5) TO X(4)".

     MOVE WS-ALPHANUM-5       TO WS-AB-5.         
     DISPLAY "AB01:(" WS-AB-5 "):(AB CDE):"
             "MOVE TEST MOVE X(5) TO XXBXXX".

     MOVE WS-ALPHANUM-5       TO WS-AB-3.         
     DISPLAY "AB02:(" WS-AB-3 "):(A BC):"
             "MOVE TEST MOVE X(5) TO XBXX".

     MOVE WS-ALPHANUM-5       TO WS-AS-5.         
     DISPLAY "AS01:(" WS-AS-5 "):(AB/CDE):"
             "MOVE TEST MOVE X(5) TO XX/XXX".

     MOVE WS-ALPHANUM-5       TO WS-AS-3.         
     DISPLAY "AS02:(" WS-AS-3 "):(A/BC):"
             "MOVE TEST MOVE X(5) TO X/XX".

 A000-EXIT.
     EXIT.
