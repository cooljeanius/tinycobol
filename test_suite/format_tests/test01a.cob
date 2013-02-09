 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST01A.
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

 01  WS-ALPHA-EDIT-FIELDS.
     05 WS-ANE-1                     PIC XXBXXX.
     05 WS-ANE-2                     PIC XBXX.
     05 WS-ANE-3                     PIC XX/XXX.
     05 WS-ANE-4                     PIC X/XX.
     05 WS-ANE-5                     PIC XXBXXBXX.
     05 WS-ANE-6                     PIC XX/XX/XX.

 PROCEDURE DIVISION.
 0000-PROGRAM-ENTRY-POINT.
     DISPLAY "TEST1-FORMATS program entry."

     PERFORM A000-ALPHANUMERIC-TESTS THRU A000-EXIT.

     STOP RUN.

 A000-ALPHANUMERIC-TESTS.
     MOVE "ABCDEFGHIJKLMONPQRSTUVWXYZ"
                     TO WS-ALPHA-26.

 A001-TEST.
     MOVE "ABCDE"             TO WS-ALPHA-5.
     MOVE WS-ALPHA-5          TO WS-ANE-1.
     DISPLAY "A010:(" WS-ANE-1 "):(AB CDE):"
             "ALPHA SPACE FORMAT TEST MOVE A(5) TO XXBXXX".

     MOVE "ABCDE"             TO WS-ALPHA-5.
     MOVE WS-ALPHA-5          TO WS-ANE-2.
     DISPLAY "A011:(" WS-ANE-2 "):(A BC):"
             "ALPHA SPACE FORMAT TEST MOVE A(5) TO XBXX".

     MOVE "ABCDE"             TO WS-ALPHA-5.
     MOVE WS-ALPHA-5          TO WS-ANE-5.
     DISPLAY "A012:(" WS-ANE-5 "):(AB CD E ):"
             "ALPHA MULTI-SPACE FORMAT TEST MOVE A(5) TO XXBXXBXX".

     MOVE "ABCDEF"            TO WS-ALPHA-6.
     MOVE WS-ALPHA-6          TO WS-ANE-5.
     DISPLAY "A013:(" WS-ANE-5 "):(AB CD EF):"
             "ALPHA MULTI-SPACE FORMAT TEST MOVE A(6) TO XXBXXBXX".

     MOVE WS-ALPHA-26         TO WS-ANE-5.
     DISPLAY "A014:(" WS-ANE-5 "):(AB CD EF):"
             "ALPHA MULTI-SPACE FORMAT TEST MOVE A(26) TO XXBXXBXX".

 A000-EXIT.
     EXIT.
