IDENTIFICATION DIVISION.
PROGRAM-ID.    SEQIO08.
ENVIRONMENT DIVISION.

CONFIGURATION SECTION. 
SPECIAL-NAMES.
*>     DECIMAL-POINT IS COMMA.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
     SELECT GOZINOUT ASSIGN TO "seqdata01.dat" 
            ORGANIZATION IS SEQUENTIAL 
            ACCESS MODE     SEQUENTIAL
            FILE STATUS  IS FS.

DATA DIVISION.
FILE SECTION.

 FD  GOZINOUT
     LABEL RECORD IS STANDARD.
 01  GOZINOUT-REC.
     03 X-IND             PIC  9(03).
     03 DESCRIPTION       PIC  X(20).
     03 FILLER            PIC  X(57).
      
WORKING-STORAGE SECTION.
 01  FS                   PIC  9(02).

PROCEDURE DIVISION.
0000-PROGRAM-ENTRY.
      PERFORM B000-INITIALIZE THRU B000-EXIT.
      PERFORM C000-MAIN-LOGIC THRU C000-EXIT.
      PERFORM D000-CLEANUP THRU D000-EXIT.
      STOP RUN.

B000-INITIALIZE.
      OPEN I-O GOZINOUT.
      DISPLAY "SQ01:(" FS "):(00):"
          "SEQUENTIAL I/O OPEN STATUS".
B000-EXIT.
     EXIT.

C000-MAIN-LOGIC.
      READ GOZINOUT.
      DISPLAY "SR02:(" FS "):(00):"
          "SEQUENTIAL I/O READ STATUS".
      DISPLAY "SR08:(" X-IND "):(001):"
          "DATA FROM READ".
      DISPLAY "SR08:(" DESCRIPTION "):(FIRST RECORD        ):"
          "DATA FROM READ".

      READ GOZINOUT.
      DISPLAY "SR02:(" FS "):(00):"
          "SEQUENTIAL I/O READ STATUS".
      DISPLAY "SR08:(" X-IND "):(002):"
          "DATA FROM READ".
      DISPLAY "SR08:(" DESCRIPTION "):(SECOND RECORD       ):"
          "DATA FROM READ".
      
      MOVE 999 TO X-IND.
      MOVE "ZZZ RECORD" TO DESCRIPTION.
      REWRITE GOZINOUT-REC.
      DISPLAY "SR03:(" FS "):(00):"
          "SEQUENTIAL I/O REWRITE STATUS".
      
      READ GOZINOUT.
      DISPLAY "SR02:(" FS "):(00):"
          "SEQUENTIAL I/O READ STATUS".
      DISPLAY "SR08:(" X-IND "):(003):"
          "DATA FROM READ".
      DISPLAY "SR08:(" DESCRIPTION "):(THIRD RECORD        ):"
          "DATA FROM READ".
C000-EXIT.
      EXIT.

D000-CLEANUP.
      CLOSE GOZINOUT.
      DISPLAY "SR04:(" FS "):(00):"
          "SEQUENTIAL I/O CLOSE STATUS".

D000-EXIT.
     EXIT.  