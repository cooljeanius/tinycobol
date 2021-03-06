 IDENTIFICATION DIVISION.
 PROGRAM-ID. PERF06.
 AUTHOR. STEPHEN CONNOLLY.
 DATE-WRITTEN. 2001/04/24 .
 ENVIRONMENT DIVISION.
 DATA DIVISION.
 WORKING-STORAGE SECTION.
 77  QT1      PICTURE XXXX VALUE SPACE.
 77  QT2      PICTURE XXXX VALUE SPACE.
 77  QT3      PICTURE XXXX VALUE SPACE.
 77  QT4      PICTURE XXXX VALUE SPACE.
 77  QT5      PICTURE XXXX VALUE SPACE.
 77  WRK-DS-01V00                PICTURE S9.
 77  ONE                PICTURE 9    VALUE 1.
 77  TWO                PICTURE S9   VALUE 2.
 77  THREE              PICTURE S9   VALUE 3.
 77  FOUR               PICTURE S9   VALUE 4.
 77  FIVE               PICTURE S9   VALUE 5.
 77  SIX                PICTURE S9   VALUE 6.
 77  SEVEN              PICTURE S9   VALUE 7.
 77  EIGHT              PICTURE 9    VALUE 8.
 77  NINE               PICTURE S9   VALUE 9.
 77  TEN                PICTURE S99  VALUE 10.
 77  FIFTEEN            PICTURE S99  VALUE 15.
 77  TWENTY             PICTURE S99  VALUE 20.
 77  TWENTY-5           PICTURE S99  VALUE 25.
 01  MOVE54.
     02 MOVE55 PICTURE X VALUE "W".
     02 MOVE56 PICTURE X VALUE "X".
     02 MOVE57.
         03 MOVE58 PICTURE X VALUE "Y".
         03 MOVE59 PICTURE X VALUE "Z".
 01  MOVE60.
     02 MOVE56 PICTURE X.
     02 MOVE57.
         03 MOVE58 PICTURE X.
         03 MOVE64.
             04 MOVE65 PICTURE X VALUE "A".
 01  GRP-FOR-QUAL-FROM.
     02  QUAL-TEST-SUB-GRP-1.
     03  QUAL-TEST-1             PICTURE X(26) VALUE
     "ABCDEFGHIJKLMNOPQRSTUVWXYZ".
     03  QUAL-TEST-1-FROM REDEFINES QUAL-TEST-1 PICTURE X(26).
     03  QUAL-TEST-2             PICTURE S9(10) VALUE +9999999999.
     03  QUAL-TEST-2-FROM REDEFINES QUAL-TEST-2 PICTURE S9(10).
     03  QUAL-TEST-3             PICTURE S999  VALUE 2.
     03  QUAL-TEST-3-FROM REDEFINES QUAL-TEST-3 PICTURE S999.
     02  QUAL-TEST-SUB-GRP-2.
     03  QUAL-TEST-4             PICTURE X OCCURS 5 TIMES.
     03  QUAL-TEST-4-FROM        PICTURE X OCCURS 4 TIMES.
 01  GRP-FOR-QUAL-TO.
     02  DUMMY-LEVELZ.
     03  QUAL-TEST-1             PICTURE X(26).
     03  QUAL-TEST-1-TO REDEFINES QUAL-TEST-1 PICTURE X(26).
     03  QUAL-TEST-2             PICTURE S9(10).
     03  QUAL-TEST-2-TO REDEFINES QUAL-TEST-2 PICTURE S9(10).
     03  QUAL-TEST-3             PICTURE S999.
     03  QUAL-TEST-3-TO REDEFINES QUAL-TEST-3 PICTURE S999.
     02  QUAL-TEST1.
     03  QUAL-TEST-4             PICTURE X OCCURS 5 TIMES.
     02  QUAL-TEST2.
     03  QUAL-TEST-4-TO          PICTURE X OCCURS 4 TIMES.
 01  GRP-MOVE-CORR-1.
     09  MOVE-CORR-5              PICTURE 999    VALUE 555.
     09  MOVE-CORR-3              PICTURE 999    VALUE 333.
     09  MOVE-CORR-2              PICTURE 999    VALUE 222.
     09  MOVE-CORR-1              PICTURE 999    VALUE 111.
     09  FILLER                   PICTURE XXX    VALUE ZEROS.
     09  MOVE-CORR-4              PICTURE XXX    VALUE "XYZ".
     09  MOVE-CORR-6              PICTURE XXX    VALUE ALL "6".
     09  MOVE-CORR-7              PICTURE 999    VALUE 777.
 01  GRP-MOVE-CORR-R.
     05  FILLER                   PICTURE XXX.
     05  MOVE-CORR-1              PICTURE XXX.
     05  MOVE-CORR-2              PICTURE 999.
     05  MOVE-CORR-3              PICTURE ZZZ.
     05  MOVE-CORR-4.
         06 FILLER                PICTURE 999.
         06 FILLER                PICTURE XXX.
 01  GRP-TO-MOVE-CORR.
     03  GRP-TO-MOVE-CORR-1.
         05  MOVE-CORR-G1.
             06  MOVE-CORR-G2.
                 09  MOVE-CORR-E1 PICTURE 999    VALUE 111.
                 09  MOVE-CORR-E2 PICTURE 999    VALUE 222.
                 09  FILLER       PICTURE 999    VALUE 333.
             06  MOVE-CORR-G3.
                 07  MOVE-CORR-E3 PICTURE XXX    VALUE "123".
                 07  MOVE-CORR-G4.
                     08  MOVE-CORR-G5.
                         09  MOVE-CORR-E4 PICTURE XXX VALUE "ABC".
                         09  MOVE-CORR-E5 PICTURE 99  VALUE 45.
 01  GRP-TO-MOVE-CORR-TO.
     02 MOVE-CORR-G1.
         04 MOVE-CORR-G2.
             05 MOVE-CORR-E1      PICTURE XXX.
             05 MOVE-CORR-E2      PICTURE 999    OCCURS 2.
             05 FILLER            PICTURE 999.
         04 MOVE-CORR-G3.
             06 MOVE-CORR-E3      PICTURE 999.
             06 MOVE-CORR-G4.
                 07 MOVE-CORR-G5  PICTURE X(5).
 01  CORR-DATA-1.
     03 XYZ-1                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-2                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-3                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-4                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-5                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-6                PICTURE IS 99     VALUE IS ZERO.
 01  CORR-DATA-2.
     03 XYZ-1                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-2                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-3                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-4                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-5                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-6                PICTURE IS 99     VALUE IS ZERO.
 01  CORR-DATA-3.
     03 XYZ-4                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-3                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-6                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-5                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-2                PICTURE IS 99     VALUE IS ZERO.
     03 XYZ-1                PICTURE IS 99     VALUE IS ZERO.
 01  CORR-DATA-4.
     03 XYZ-11               PICTURE IS 99.
     03 XYZ-12               PICTURE IS 99.
     03 XYZ-13               PICTURE IS 99.
     03 XYZ-14               PICTURE IS 99.
     03 XYZ-15               PICTURE IS 99.
     03 XYZ-16               PICTURE IS 99.
 01  CORR-DATA-5.
     03 XYZ-1                PICTURE    99.
     03 XYZ-2                PICTURE    99.
     03 XYZ-13               PICTURE IS 99.
     03 XYZ-14               PICTURE IS 99.
     03 FILLER               PICTURE IS 99.
     03 XYZ-11               PICTURE IS 99.
     03 XYZ-12               PICTURE IS 99.
 01  CORR-DATA-6.
     03 XYZ-11               PICTURE IS 99.
     03 XYZ-12               PICTURE IS 99.
     03 FILLER               PICTURE IS 99.
     03 XYZ-1                PICTURE IS 99.
     03 XYZ-2                PICTURE IS 9(2).
     03 FILLER               PICTURE IS 99.
 01  CORR-DATA-7.
     02 XYZ-1                PICTURE 99V99     VALUE 10.45.
     02 XYZ-6                PICTURE 999V9     VALUE 100.5.
     02 XYZ-11               PICTURE 99V9      VALUE ZERO.
     02 XYZ-2                PICTURE 99V9      VALUE 0.9.

 PROCEDURE DIVISION.
 CCVS1 SECTION.
 MAIN-LOOP.
     PERFORM QUAL-SECTION-1.
     STOP RUN.

 QUAL-SECTION-1 SECTION.
 PAR-INIT-F2-1.
     PERFORM PAR-1A OF QUAL-SECTION-1.
     DISPLAY "Q001:(" QT1 "):(PASS):"
             "PERFORM QUALIFIED PARAGRAPH IN SAME SECTION.".

 PAR-INIT-F2-4.
     PERFORM PAR-2A OF QUAL-SECTION-2.
     DISPLAY "Q002:(" QT2 "):(PASS):"
             "PERFORM QUALIFIED PARAGRAPH IN OTHER SECTION.".

 PAR-TEST-F2-3.
     GO TO PAR-3B IN QUAL-SECTION-1.
 PAR-1A.
     MOVE "PASS" TO QT1.
 PAR-2A.
     MOVE "FAIL" TO QT2.
 PAR-3A.
     MOVE "FAIL" TO QT3.
 PAR-3B.
     MOVE "PASS" TO QT3.
 PAR-3C.
     DISPLAY "Q003:(" QT3 "):(PASS):"
             "GO TO QUALIFIED PARAGRAPH IN SAME SECTION.".

     GO TO PAR-4B IN QUAL-SECTION-2.
*    GO TO IN DIFFERENT SECTION.
 PAR-4A.
     MOVE "FAIL" TO QT4.
     GO TO PAR-4C.
 PAR-4B.
     MOVE "FAIL" TO QT4.
 PAR-4C.
     DISPLAY "Q004:(" QT4 "):(PASS):"
             "GO TO QUALIFIED PARAGRAPH IN OTHER SECTION.".

 QUAL-SECTION-2 SECTION.
 PAR-1A.
     MOVE "FAIL" TO QT1.
 PAR-2A.
     MOVE "PASS" TO QT2.
 PAR-3B.
     MOVE "FAIL" TO QT3.
     GO TO PAR-3C OF QUAL-SECTION-1.
 PAR-3C.
     MOVE "FAIL" TO QT1 QT2 QT3 QT4 QT5.
*    NOTE  THIS PARAGRAPH SHOULD NEVER BE ENTERED.
     GO TO PAR-INIT-F2-4 IN QUAL-SECTION-1.
 PAR-4.
     GO TO QUAL-EXIT.
*                  IF
*    GO TO DIFFERENT SECTION FAILS END QUALIFICATION TEST.
 PAR-4B.
     MOVE "PASS" TO QT4.
     GO TO PAR-4C IN QUAL-SECTION-1.
 QUAL-EXIT.
     EXIT.

