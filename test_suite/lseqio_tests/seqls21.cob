 IDENTIFICATION DIVISION.
 PROGRAM-ID.    SEQLS21.
 ENVIRONMENT DIVISION.

 CONFIGURATION SECTION. 
 SPECIAL-NAMES.
*>     DECIMAL-POINT IS COMMA.
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
     SELECT GOZIN ASSIGN TO "lineseq19.dat" 
            ORGANIZATION IS LINE SEQUENTIAL 
            ACCESS MODE     SEQUENTIAL
            FILE STATUS  IS FS.

 DATA DIVISION.
 FILE SECTION.

 FD  GOZIN
*>     LABEL RECORD IS STANDARD
*>    RECORD CONTAINS 18 TO 75 CHARACTERS
     RECORD IS VARYING 18 TO 75 CHARACTERS.
 01 GOZOUT-REC-1.
     03 X-IND-1                      PIC  9(03).
     03 DESCRIPTION-1                PIC  X(10).
     03 BIN-IDX-1                    PIC  9(02).
     03 BIN-NUMBER-1                 PIC  X(03)
        OCCURS 1 TO 20 TIMES DEPENDING ON BIN-IDX-1.
      
 WORKING-STORAGE SECTION.
 01 FS                               PIC  9(02).

 PROCEDURE DIVISION.
 0000-PROGRAM-ENTRY.
      PERFORM B000-INITIALIZE THRU B000-EXIT.
      PERFORM C000-MAIN-LOGIC THRU C000-EXIT.
      PERFORM D000-CLEANUP THRU D000-EXIT.
      STOP RUN.

 B000-INITIALIZE.
      OPEN INPUT GOZIN.
      DISPLAY "SO17:(" FS "):(00):"
          "SEQUENTIAL VARIABLE INPUT OPEN STATUS".
 B000-EXIT.
     EXIT.

 C000-MAIN-LOGIC.
      READ GOZIN.
      DISPLAY "SR02:(" FS "):(00):"
          "SEQUENTIAL VARIABLE INPUT READ STATUS".
      DISPLAY "SR03:(" X-IND-1 "):(001):"
          "DATA FROM READ".
      DISPLAY "SR03:(" DESCRIPTION-1 "):(AAAAAAAAAA):"
          "DATA FROM READ".
      DISPLAY "SR03:(" BIN-IDX-1 "):(01):"
          "BIN IDX FROM READ".

      READ GOZIN.
      DISPLAY "SR02:(" FS "):(00):"
          "SEQUENTIAL VARIABLE INPUT STATUS".
      DISPLAY "SR03:(" X-IND-1 "):(002):"
          "DATA FROM READ".
      DISPLAY "SR03:(" DESCRIPTION-1 "):(BBBBBBBBBB):"
          "DATA FROM READ".
      DISPLAY "SR03:(" BIN-IDX-1 "):(03):"
          "BIN IDX FROM READ".

      READ GOZIN.
      DISPLAY "SR02:(" FS "):(00):"
          "SEQUENTIAL VARIABLE INPUT STATUS".
      DISPLAY "SR03:(" X-IND-1 "):(003):"
          "DATA FROM READ".
      DISPLAY "SR03:(" DESCRIPTION-1 "):(CCCCCCCCCC):"
          "DATA FROM READ".
      DISPLAY "SR03:(" BIN-IDX-1 "):(05):"
          "BIN IDX FROM READ".

      READ GOZIN.
      DISPLAY "SR02:(" FS "):(00):"
          "SEQUENTIAL VARIABLE INPUT STATUS".
      DISPLAY "SR03:(" X-IND-1 "):(004):"
          "DATA FROM READ".
      DISPLAY "SR03:(" DESCRIPTION-1 "):(DDDDDDDDDD):"
          "DATA FROM READ".
      DISPLAY "SR03:(" BIN-IDX-1 "):(11):"
          "BIN IDX FROM READ".

 C000-EXIT.
      EXIT.

 D000-CLEANUP.
      CLOSE GOZIN.
      DISPLAY "SC17:(" FS "):(00):"
          "SEQUENTIAL VARIABLE INPUT CLOSE STATUS".

 D000-EXIT.
     EXIT.  
