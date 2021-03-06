 IDENTIFICATION DIVISION.
 PROGRAM-ID.    TEST08ug.
 ENVIRONMENT DIVISION.

 CONFIGURATION SECTION. 
 SPECIAL-NAMES.
     DECIMAL-POINT IS COMMA.
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
  SELECT ARQ      ASSIGN TO "TEST08Raw.dat" 
      ORGANIZATION IS SEQUENTIAL
      ACCESS MODE  IS SEQUENTIAL
      FILE STATUS  IS FS.
  SELECT OUT-REC ASSIGN TO "TEST08ugSorted.dat"
      ORGANIZATION IS SEQUENTIAL    
      ACCESS MODE IS SEQUENTIAL
      FILE STATUS IS FS.

  SELECT SORT-REC ASSIGN TO "TEST08ugSort.dat".


 DATA DIVISION.
 FILE SECTION.

 FD ARQ
    LABEL RECORD IS STANDARD.
 01 REG-ARQ.
   03 P-IND		     PIC  9(03).
   03 DESCRIPTION	     PIC  X(60).
 
 FD OUT-REC.
 01 MAIN-RECORD      PIC X(63).    
 
 SD SORT-REC.
 01 MAIN-REC.
  03 INDICATOR       PIC 9(03).
  03 DESC            PIC X(60).

 WORKING-STORAGE SECTION.
  01 FS              PIC X(02).
  01 W-COUNTER       PIC 9(15).
  01 REM             PIC 9(5).
  01 W01-SWITCHES    PIC X(03).
    88 W01-END       VALUE "YES".
    88 W01-MORE      VALUE "NO".

 PROCEDURE DIVISION.
 MAIN SECTION.
     MOVE 0 TO W-COUNTER REM.
     SORT SORT-REC ASCENDING KEY INDICATOR 
       DESCENDING KEY DESC
       USING ARQ
       GIVING OUT-REC.

     STOP RUN.
