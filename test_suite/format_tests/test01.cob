 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST1_FORMATS.
 AUTHOR.  GLEN COLBERT.
 INSTALLATION. Tiny Cobol Project
 DATE-WRITTEN. 12 November, 1999.

 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS-ALPHA-FIELDS.
     05 WS-ALPHA-1                   PIC A(01).
     05 WS-ALPHA-2                   PIC A(02).
     05 WS-ALPHA-3                   PIC A(03).
     05 WS-ALPHA-4                   PIC A(04).
     05 WS-ALPHA-5                   PIC A(05).
     05 WS-ALPHA-6                   PIC A(06).
     05 WS-ALPHA-7                   PIC A(07).
     05 WS-ALPHA-26                  PIC X(26).

 01  WS-ALPHANUM-FIELDS.
     05 WS-ALPHANUM-1                PIC X(01).
     05 WS-ALPHANUM-2                PIC X(02).
     05 WS-ALPHANUM-3                PIC X(03).
     05 WS-ALPHANUM-4                PIC X(04).
     05 WS-ALPHANUM-5                PIC X(05).
     05 WS-ALPHANUM-6                PIC X(06).
     05 WS-ALPHANUM-8                PIC X(08) JUST RIGHT.

 01  WS-ALPHA-EDIT-FIELDS.
     05 WS-ANE-1                     PIC XXBXXX.
     05 WS-ANE-2                     PIC XBXX.
     05 WS-ANE-3                     PIC XX/XXX.
     05 WS-ANE-4                     PIC X/XX.
     05 WS-ANE-5                     PIC XXBXXBXX.
     05 WS-ANE-6                     PIC XX/XX/XX.

 PROCEDURE DIVISION.
 0000-PROGRAM-ENTRY-POINT.
     DISPLAY "TEST1_FORMATS.program entry."

     PERFORM A000-ALPHANUMERIC-TESTS THRU A000-EXIT.

     STOP RUN.

 A000-ALPHANUMERIC-TESTS.
     MOVE "ABCDEFGHIJKLMONPQRSTUVWXYZ"
                     TO WS-ALPHA-26.

 A001-TEST.
     MOVE "A"                 TO WS-ALPHA-1.
     MOVE WS-ALPHA-1          TO WS-ALPHANUM-6.
     DISPLAY "A001:(" WS-ALPHANUM-6 "):(A     ):"
             "ALPHA LEFT ALIGN TEST MOVE A(1) TO X(6)".

     MOVE "ABCDE"             TO WS-ALPHA-5.
     MOVE WS-ALPHA-5          TO WS-ALPHANUM-6.
     DISPLAY "A002:(" WS-ALPHANUM-6 "):(ABCDE ):"
             "ALPHA LEFT ALIGN MOVE TEST MOVE A(5) TO X(6)".

     MOVE "ABCDEF"            TO WS-ALPHA-6.
     MOVE WS-ALPHA-6          TO WS-ALPHANUM-6.
     DISPLAY "A003:(" WS-ALPHANUM-6 "):(ABCDEF):"
             "ALPHA LEFT ALIGN MOVE TEST MOVE A(6) TO X(6)".

     MOVE WS-ALPHA-26         TO WS-ALPHANUM-6.
     DISPLAY "A004:(" WS-ALPHANUM-6 "):(ABCDEF):"
             "ALPHA LEFT ALIGN MOVE TEST MOVE A(26) TO X(6)".

     MOVE "ABCDEFGHIJ" TO WS-ALPHANUM-8.
     DISPLAY "A005:(" WS-ALPHANUM-8 "):(CDEFGHIJ):"
         "MOVE ABCDEFGHIJ TO X(8) RIGHT".

     MOVE "ABCDE" TO WS-ALPHANUM-8.
     DISPLAY "A006:(" WS-ALPHANUM-8 "):(   ABCDE):"
         "MOVE ABCDE TO X(8) RIGHT".

 A000-EXIT.
     EXIT.
