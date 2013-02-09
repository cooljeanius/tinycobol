 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST03D.
 AUTHOR.  GLEN COLBERT.

 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.
 SPECIAL-NAMES.
     CURRENCY SIGN IS "£".
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS-EDITED-FIELDS.
     05 WS-FI-5                      PIC ££99.
     05 WS-FI-6                      PIC £££££.
     05 WS-FI-7                      PIC ££££.99.
     05 WS-FI-8                      PIC ££,£££.££. 

 01  WS-NUMERIC-FIELDS.
     05 WS-DISPLAY-NUM-0             PIC 9999.
     05 WS-DISPLAY-NUM-V2            PIC V99.
     05 WS-X1 REDEFINES WS-DISPLAY-NUM-V2
                                     PIC XX.
     05 WS-DISPLAY-NUM-2             PIC 9999.
     05 WS-DISPLAY-NUM-4V1           PIC 9999V99.
     05 WS-X2 REDEFINES WS-DISPLAY-NUM-4V1
                                     PIC X(6).
     05 WS-DISPLAY-NUM-NV1           PIC S9(4)V99.
     05 WS-X3 REDEFINES WS-DISPLAY-NUM-NV1
                                     PIC X(6).

 PROCEDURE DIVISION.
 0000-PROGRAM-ENTRY-POINT.
     DISPLAY "TEST03 FORMATS program entry."

     PERFORM A000-ALPHANUMERIC-TESTS THRU A000-EXIT.

     STOP RUN.

 A000-ALPHANUMERIC-TESTS.

 FI50-INSERT-RDD99.
     MOVE 0                   TO WS-DISPLAY-NUM-0.
     MOVE ".02"               TO WS-DISPLAY-NUM-V2.
     MOVE 2                   TO WS-DISPLAY-NUM-2.
     MOVE "123450"            TO WS-X2.
     MOVE "-123.4"            TO WS-DISPLAY-NUM-NV1.

     MOVE WS-DISPLAY-NUM-0    TO WS-FI-5.
     DISPLAY "FI61:(" WS-FI-5 "):( £00):"
             "FLOAT-INSERT MOVE 0 TO ££99".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-5.
     DISPLAY "FI62:(" WS-FI-5 "):( £00):"
             "FLOAT-INSERT MOVE .02 TO ££99".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-5.
     DISPLAY "FI63:(" WS-FI-5 "):( £02):"
             "FLOAT-INSERT MOVE 2 TO ££99".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-5.
     DISPLAY "FI64:(" WS-FI-5 "):(£234):"
             "FLOAT-INSERT MOVE 1234.5 TO ££99".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-5.
     DISPLAY "FI65:(" WS-FI-5 "):(£123):"
             "FLOAT-INSERT MOVE -123.4 TO ££99".

 FI60-INSERT-RDD99.
     MOVE WS-DISPLAY-NUM-0    TO WS-FI-6.
     DISPLAY "FI61:(" WS-FI-6 "):(     ):"
             "FLOAT-INSERT MOVE 0 TO £££££".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-6.
     DISPLAY "FI62:(" WS-FI-6 "):(     ):"
             "FLOAT-INSERT MOVE .02 TO £££££".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-6.
     DISPLAY "FI63:(" WS-FI-6 "):(   £2):"
             "FLOAT-INSERT MOVE 2 TO £££££".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-6.
     DISPLAY "FI64:(" WS-FI-6 "):(£1234):"
             "FLOAT-INSERT MOVE 1234.5 TO £££££".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-6.
     DISPLAY "FI65:(" WS-FI-6 "):( £123):"
             "FLOAT-INSERT MOVE -123.4 TO £££££".

 FI70-INSERT-RDD99.
     MOVE WS-DISPLAY-NUM-0    TO WS-FI-7.
     DISPLAY "FI71:(" WS-FI-7 "):(   £.00):"
             "FLOAT-INSERT MOVE 0 TO ££££.99".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-7.
     DISPLAY "FI72:(" WS-FI-7 "):(   £.02):"
             "FLOAT-INSERT MOVE .02 TO ££££.99".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-7.
     DISPLAY "FI73:(" WS-FI-7 "):(  £2.00):"
             "FLOAT-INSERT MOVE 2 TO ££££.99".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-7.
     DISPLAY "FI74:(" WS-FI-7 "):(£234.50):"
             "FLOAT-INSERT MOVE 1234.5 TO ££££.99".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-7.
     DISPLAY "FI75:(" WS-FI-7 "):(£123.40):"
             "FLOAT-INSERT MOVE -123.4 TO ££££.99".

 F800-INSERT-FI8X.

     MOVE WS-DISPLAY-NUM-0    TO WS-FI-8.
     DISPLAY "FI81:(" WS-FI-8 "):(         ):"
             "FLOAT-INSERT MOVE 0 TO ££,£££.££".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-8.
     DISPLAY "FI82:(" WS-FI-8 "):(     £.02):"
             "FLOAT-INSERT MOVE .02 TO ££,£££.££".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-8.
     DISPLAY "FI83:(" WS-FI-8 "):(    £2.00):"
             "FLOAT-INSERT MOVE 2 TO ££,£££.££".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-8.
     DISPLAY "FI84:(" WS-FI-8 "):(£1,234.50):"
             "FLOAT-INSERT MOVE 1234.5 TO ££,£££.££".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-8.
     DISPLAY "FI85:(" WS-FI-8 "):(  £123.40):"
             "FLOAT-INSERT MOVE -123.4 TO ££,£££.££".

 A000-EXIT.
     EXIT.
