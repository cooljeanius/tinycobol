 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST3_FORMATS.
 AUTHOR.  GLEN COLBERT.

 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS-EDITED-FIELDS.
     05 WS-FI-0                      PIC ZZ99.
     05 WS-FI-1                      PIC ZZZZ.ZZ.
     05 WS-FI-2                      PIC ZZ.ZZ.
     05 WS-FI-3                      PIC **99.   
     05 WS-FI-4                      PIC **.**.
     05 WS-FI-5                      PIC $$99.
     05 WS-FI-6                      PIC $$$$$.
     05 WS-FI-7                      PIC $$$$.99.
     05 WS-FI-8                      PIC $$,$$$.$$. 
     05 WS-FI-9                      PIC +9999.   
     05 WS-FI-10                     PIC 9999+.   
     05 WS-FI-11                     PIC -9999.   
     05 WS-FI-12                     PIC ++++9.   
     05 WS-FI-13                     PIC ----.    
     05 WS-FI-14                     PIC ++++.++. 

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

 AN01-TEST.
     MOVE 0                   TO WS-DISPLAY-NUM-0.
     MOVE ".02"               TO WS-DISPLAY-NUM-V2.
     MOVE 2                   TO WS-DISPLAY-NUM-2.
     MOVE "123450"            TO WS-X2.
     MOVE "-123.4"            TO WS-DISPLAY-NUM-NV1.

     DISPLAY "0000:(" WS-DISPLAY-NUM-0 "):(0000):"
             "DISPLAY SOURCE FIELD 9999".

     DISPLAY "0000:(" WS-DISPLAY-NUM-V2 "):(.02):"
             "NOTE DISPLAY SOURCE FIELD V99".

     MOVE "02"                TO WS-X1.
     DISPLAY "0000:(" WS-DISPLAY-NUM-V2 "):(.02):"
             "DISPLAY SOURCE FIELD V99".

     DISPLAY "0000:(" WS-DISPLAY-NUM-2 "):(0002):"
             "DISPLAY SOURCE FIELD 9999".

     DISPLAY "0000:(" WS-DISPLAY-NUM-4V1 "):(1234.50):"
             "DISPLAY SOURCE FIELD 9999V99".

     DISPLAY "0000:(" WS-X3 "):(01234}):"
             "DISPLAY SOURCE FIELD S9(4)V9(2)".

 FI00-INSERT-ZZ99.
     MOVE WS-DISPLAY-NUM-0    TO WS-FI-0.
     DISPLAY "FI01:(" WS-FI-0 "):(  00):"
             "FLOAT-INSERT MOVE 0 TO ZZ99".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-0.
     DISPLAY "FI02:(" WS-FI-0 "):(  00):"
             "FLOAT-INSERT MOVE .02 TO ZZ99".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-0.
     DISPLAY "FI03:(" WS-FI-0 "):(  02):"
             "FLOAT-INSERT MOVE 2 TO ZZ99".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-0.
     DISPLAY "FI04:(" WS-FI-0 "):(1234):"
             "FLOAT-INSERT MOVE 1234.5 TO ZZ99".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-0.
     DISPLAY "FI05:(" WS-FI-0 "):( 123):"
             "FLOAT-INSERT MOVE -123.4 TO ZZ99".

 FI00-INSERT-ZZZZZ.
     MOVE WS-DISPLAY-NUM-0    TO WS-FI-1.
     DISPLAY "FI11:(" WS-FI-1 "):(       ):"
             "FLOAT-INSERT MOVE 0 TO ZZZZ.ZZ".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-1.
     DISPLAY "FI12:(" WS-FI-1 "):(    .02):"
             "FLOAT-INSERT MOVE .02 TO ZZZZ.ZZ".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-1.
     DISPLAY "FI13:(" WS-FI-1 "):(   2.00):"
             "FLOAT-INSERT MOVE 2 TO ZZZZ.ZZ".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-1.
     DISPLAY "FI14:(" WS-FI-1 "):(1234.50):"
             "FLOAT-INSERT MOVE 1234.5 TO ZZZZ.ZZ".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-1.
     DISPLAY "FI15:(" WS-FI-1 "):( 123.40):"
             "FLOAT-INSERT MOVE -123.4 TO ZZZZ.ZZ".

 F200-INSERT-ZZZZ.
     MOVE WS-DISPLAY-NUM-0    TO WS-FI-2.
     DISPLAY "FI21:(" WS-FI-2 "):(     ):"
             "FLOAT-INSERT MOVE 0 TO ZZ.ZZ".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-2.
     DISPLAY "FI22:(" WS-FI-2 "):(  .02):"
             "FLOAT-INSERT MOVE .02 TO ZZ.ZZ".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-2.
     DISPLAY "FI23:(" WS-FI-2 "):( 2.00):"
             "FLOAT-INSERT MOVE 2 TO ZZ.ZZ".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-2.
     DISPLAY "FI24:(" WS-FI-2 "):(34.50):"
             "FLOAT-INSERT MOVE 1234.5 TO ZZ.ZZ".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-2.
     DISPLAY "FI25:(" WS-FI-2 "):(23.40):"
             "FLOAT-INSERT MOVE -123.4 TO ZZ.ZZ".

 F300-ASTERISK-INSERTION.  

     MOVE ZERO TO WS-DISPLAY-NUM-2.
     MOVE WS-DISPLAY-NUM-2 TO WS-FI-3.
     DISPLAY "FI31:(" WS-FI-3 "):(**00):"
             "FLOAT-INSERT MOVE 0 TO **99".
     MOVE "2" TO WS-FI-3.
     DISPLAY "FI32:(" WS-FI-3 "):(**02):"
             "FLOAT-INSERT MOVE 2 TO **99".
     MOVE "23" TO WS-FI-3.
     DISPLAY "FI33:(" WS-FI-3 "):(**23):"
             "FLOAT-INSERT MOVE 23 TO **99".
     MOVE "123" TO WS-FI-3.
     DISPLAY "FI34:(" WS-FI-3 "):(*123):"
             "FLOAT-INSERT MOVE 123 TO **99".
     MOVE "1234" TO WS-FI-3.
     DISPLAY "FI35:(" WS-FI-3 "):(1234):"
             "FLOAT-INSERT MOVE 1234 TO **99".
     MOVE "12345" TO WS-FI-3.
     DISPLAY "FI36:(" WS-FI-3 "):(2345):"
             "FLOAT-INSERT MOVE 12345 TO **99".
     MOVE "+345" TO WS-FI-3.
     DISPLAY "FI37:(" WS-FI-3 "):(*345):"
             "FLOAT-INSERT MOVE +345 TO **99".

 F400-ASTERISTK-INSERTION.

     MOVE ZERO TO WS-DISPLAY-NUM-4V1.
     MOVE WS-DISPLAY-NUM-4V1 TO WS-FI-4.
     DISPLAY "FI41:(" WS-FI-4 "):(**.**):"
             "FLOAT-INSERT MOVE 0 TO **.**".
     MOVE ".02" TO WS-FI-4.
     DISPLAY "FI42:(" WS-FI-4 "):(**.02):"
             "FLOAT-INSERT MOVE .02 TO **.**".
     MOVE ".23" TO WS-FI-4.
     DISPLAY "FI43:(" WS-FI-4 "):(**.23):"
             "FLOAT-INSERT MOVE .23 TO **.**".
     MOVE "1.23" TO WS-FI-4.
     DISPLAY "FI44:(" WS-FI-4 "):(*1.23):"
             "FLOAT-INSERT MOVE 1.23 TO **.**".
     MOVE "12.34" TO WS-FI-4.
     DISPLAY "FI45:(" WS-FI-4 "):(12.34):"
             "FLOAT-INSERT MOVE 12.34 TO **.**".
     MOVE "12.345" TO WS-FI-4.
     DISPLAY "FI46:(" WS-FI-4 "):(12.34):"
             "FLOAT-INSERT MOVE 12.345 TO **.**".
     MOVE "123.45" TO WS-FI-4.
     DISPLAY "FI47:(" WS-FI-4 "):(23.45):"
             "FLOAT-INSERT MOVE 123.45 TO **.**".

 FI50-INSERT-RDD99.
     MOVE 0                   TO WS-DISPLAY-NUM-0.
     MOVE ".02"               TO WS-DISPLAY-NUM-V2.
     MOVE 2                   TO WS-DISPLAY-NUM-2.
     MOVE "123450"            TO WS-X2.
     MOVE "-123.4"            TO WS-DISPLAY-NUM-NV1.

     MOVE WS-DISPLAY-NUM-0    TO WS-FI-5.
     DISPLAY "FI61:(" WS-FI-5 "):( $00):"
             "FLOAT-INSERT MOVE 0 TO $$99".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-5.
     DISPLAY "FI62:(" WS-FI-5 "):( $00):"
             "FLOAT-INSERT MOVE .02 TO $$99".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-5.
     DISPLAY "FI63:(" WS-FI-5 "):( $02):"
             "FLOAT-INSERT MOVE 2 TO $$99".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-5.
     DISPLAY "FI64:(" WS-FI-5 "):($234):"
             "FLOAT-INSERT MOVE 1234.5 TO $$99".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-5.
     DISPLAY "FI65:(" WS-FI-5 "):($123):"
             "FLOAT-INSERT MOVE -123.4 TO $$99".

 FI60-INSERT-RDD99.
     MOVE WS-DISPLAY-NUM-0    TO WS-FI-6.
     DISPLAY "FI61:(" WS-FI-6 "):(     ):"
             "FLOAT-INSERT MOVE 0 TO $$$$$".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-6.
     DISPLAY "FI62:(" WS-FI-6 "):(     ):"
             "FLOAT-INSERT MOVE .02 TO $$$$$".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-6.
     DISPLAY "FI63:(" WS-FI-6 "):(   $2):"
             "FLOAT-INSERT MOVE 2 TO $$$$$".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-6.
     DISPLAY "FI64:(" WS-FI-6 "):($1234):"
             "FLOAT-INSERT MOVE 1234.5 TO $$$$$".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-6.
     DISPLAY "FI65:(" WS-FI-6 "):( $123):"
             "FLOAT-INSERT MOVE -123.4 TO $$$$$".

 FI70-INSERT-RDD99.
     MOVE WS-DISPLAY-NUM-0    TO WS-FI-7.
     DISPLAY "FI71:(" WS-FI-7 "):(   $.00):"
             "FLOAT-INSERT MOVE 0 TO $$$$.99".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-7.
     DISPLAY "FI72:(" WS-FI-7 "):(   $.02):"
             "FLOAT-INSERT MOVE .02 TO $$$$.99".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-7.
     DISPLAY "FI73:(" WS-FI-7 "):(  $2.00):"
             "FLOAT-INSERT MOVE 2 TO $$$$.99".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-7.
     DISPLAY "FI74:(" WS-FI-7 "):($234.50):"
             "FLOAT-INSERT MOVE 1234.5 TO $$$$.99".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-7.
     DISPLAY "FI75:(" WS-FI-7 "):($123.40):"
             "FLOAT-INSERT MOVE -123.4 TO $$$$.99".

 F800-INSERT-FI8X.

     MOVE WS-DISPLAY-NUM-0    TO WS-FI-8.
     DISPLAY "FI81:(" WS-FI-8 "):(         ):"
             "FLOAT-INSERT MOVE 0 TO $$,$$$.$$".

     MOVE WS-DISPLAY-NUM-V2    TO WS-FI-8.
     DISPLAY "FI82:(" WS-FI-8 "):(     $.02):"
             "FLOAT-INSERT MOVE .02 TO $$,$$$.$$".

     MOVE WS-DISPLAY-NUM-2    TO WS-FI-8.
     DISPLAY "FI83:(" WS-FI-8 "):(    $2.00):"
             "FLOAT-INSERT MOVE 2 TO $$,$$$.$$".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-8.
     DISPLAY "FI84:(" WS-FI-8 "):($1,234.50):"
             "FLOAT-INSERT MOVE 1234.5 TO $$,$$$.$$".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-8.
     DISPLAY "FI85:(" WS-FI-8 "):(  $123.40):"
             "FLOAT-INSERT MOVE -123.4 TO $$,$$$.$$".

 F900-FI9X-INSERTION.

     MOVE WS-DISPLAY-NUM-2      TO WS-FI-9.
     DISPLAY "FI91:(" WS-FI-9 "):(+0002):"
             "LEADING-PLUS-SIGN MOVE 2 TO +9999".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-9.
     DISPLAY "FI92:(" WS-FI-9 "):(-0123):"
             "LEADING-PLUS-SIGN MOVE -123.4 TO +9999".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-9.
     DISPLAY "FI93:(" WS-FI-9 "):(+1234):"
             "LEADING-PLUS-SIGN MOVE 1234.5 TO +9999".

     MOVE WS-DISPLAY-NUM-0      TO WS-FI-9.
     DISPLAY "FI94:(" WS-FI-9 "):(+0000):"
             "LEADING-PLUS-SIGN MOVE ZERO TO +9999".

 FA00-FIAX-INSERTION.

     MOVE WS-DISPLAY-NUM-2      TO WS-FI-10.
     DISPLAY "FIA1:(" WS-FI-10 "):(0002+):"
             "LEADING-PLUS-SIGN MOVE 2 TO 9999+".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-10.
     DISPLAY "FIA2:(" WS-FI-10 "):(0123-):"
             "LEADING-PLUS-SIGN MOVE -123.4 TO 9999+".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-10.
     DISPLAY "FIA3:(" WS-FI-10 "):(1234+):"
             "LEADING-PLUS-SIGN MOVE 1234.5 TO 9999+".

     MOVE WS-DISPLAY-NUM-0      TO WS-FI-10.
     DISPLAY "FIA4:(" WS-FI-10 "):(0000+):"
             "LEADING-PLUS-SIGN MOVE ZERO TO 9999+".

 FB00-FIBX-INSERTION.

     MOVE WS-DISPLAY-NUM-2      TO WS-FI-11.
     DISPLAY "FIB1:(" WS-FI-11 "):( 0002):"
             "LEADING-PLUS-SIGN MOVE 2 TO -9999".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-11.
     DISPLAY "FIB2:(" WS-FI-11 "):(-0123):"
             "LEADING-PLUS-SIGN MOVE -123.4 TO -9999".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-11.
     DISPLAY "FIB3:(" WS-FI-11 "):( 1234):"
             "LEADING-PLUS-SIGN MOVE 1234.5 TO -9999".

     MOVE WS-DISPLAY-NUM-0      TO WS-FI-11.
     DISPLAY "FIB4:(" WS-FI-11 "):( 0000):"
             "LEADING-PLUS-SIGN MOVE ZERO TO -9999".

 FC00-FICX-INSERTION.

     MOVE WS-DISPLAY-NUM-2      TO WS-FI-12.
     DISPLAY "FIC1:(" WS-FI-12 "):(   +2):"
             "FLOATING-PLUS-SIGN MOVE 2 TO ++++9".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-12.
     DISPLAY "FIC2:(" WS-FI-12 "):( -123):"
             "FLOATING-PLUS-SIGN MOVE -123.4 TO ++++9".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-12.
     DISPLAY "FIC3:(" WS-FI-12 "):(+1234):"
             "FLOATING-PLUS-SIGN MOVE 1234.5 TO ++++9".

     MOVE WS-DISPLAY-NUM-0      TO WS-FI-12.
     DISPLAY "FIC4:(" WS-FI-12 "):(   +0):"
             "FLOATING-PLUS-SIGN MOVE ZERO TO ++++9".

 FD00-FIDX-INSERTION.

     MOVE WS-DISPLAY-NUM-2      TO WS-FI-13.
     DISPLAY "FID1:(" WS-FI-13 "):(   2):"
             "FLOATING-MINUS-SIGN MOVE 2 TO ----".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-13.
     DISPLAY "FID2:(" WS-FI-13 "):(-123):"
             "FLOATING-MINUS-SIGN MOVE -123.4 TO ----".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-13.
     DISPLAY "FID3:(" WS-FI-13 "):( 234):"
             "FLOATING-MINUS-SIGN MOVE 1234.5 TO ----".

     MOVE WS-DISPLAY-NUM-0      TO WS-FI-13.
     DISPLAY "FID4:(" WS-FI-13 "):(    ):"
             "FLOATING-MINUS-SIGN MOVE ZERO TO ----".

 FE00-FIEX-INSERTION.

     MOVE WS-DISPLAY-NUM-2      TO WS-FI-14.
     DISPLAY "FIE1:(" WS-FI-14 "):(  +2.00):"
             "FLOATING-PLUS-SIGN MOVE 2 TO ++++.++".

     MOVE WS-DISPLAY-NUM-NV1    TO WS-FI-14.
     DISPLAY "FIE2:(" WS-FI-14 "):(-123.40):"
             "FLOATING-PLUS-SIGN MOVE -123.4 TO ++++.++".

     MOVE WS-DISPLAY-NUM-4V1    TO WS-FI-14.
     DISPLAY "FIE3:(" WS-FI-14 "):(+234.50):"
             "FLOATING-PLUS-SIGN MOVE 1234.5 TO ++++.++".

     MOVE WS-DISPLAY-NUM-0      TO WS-FI-14.
     DISPLAY "FIE4:(" WS-FI-14 "):(       ):"
             "FLOATING-PLUS-SIGN MOVE ZERO TO ++++.++".

     MOVE WS-DISPLAY-NUM-V2     TO WS-FI-14.
     DISPLAY "FIE5:(" WS-FI-14 "):(   +.02):"
             "FLOATING-PLUS-SIGN MOVE .02 TO ++++.++".

 A000-EXIT.
     EXIT.
