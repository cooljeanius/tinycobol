 IDENTIFICATION DIVISION.
 PROGRAM-ID. PTEST03.
 AUTHOR.  Bernard GIROUD.
 INSTALLATION. Tiny Cobol Compiler Project.
 DATE-WRITTEN. 03-SEP-2000.
 DATE-COMPILED.
 SECURITY. NONE.

 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01 W-IDX   PIC 99.
 01 W-ELEM1 PIC X(5).
 01 W-BINARY PIC S9(9) COMP.
 01 W-GROUP1.
    05 FILLER PIC X(3).
    05 W-ELEM2 PIC X(4).
    05 W-GTAB.
       10 W-CHAR OCCURS 4 PIC X.
 01 WFUNC PIC 9.
 01 WVAL  PIC 99.

 PROCEDURE DIVISION.
     MOVE "ABCD" TO W-ELEM1.
     MOVE "CDEF" TO W-ELEM2.
     MOVE 4 TO W-BINARY.
     DISPLAY "MR01:(" W-ELEM1 "):(ABCD ):ELEM1".
     DISPLAY "MR02:(" W-ELEM2 "):(CDEF):ELEM2".
     MOVE SPACE TO W-GTAB.
     MOVE "X" TO W-CHAR(2).
     DISPLAY "MR03:(" W-GTAB "):( X  ):OCCURS LIT".
     MOVE SPACE TO W-GTAB.
     MOVE 3 TO W-IDX.
     MOVE "X" TO W-CHAR(W-IDX).
     DISPLAY "MR04:(" W-GTAB "):(  X ):OCCURS VAR".
     MOVE 1 TO WFUNC.
     MOVE 2 TO WVAL.
     CALL "STEST02" USING WFUNC WVAL.
     CALL "STEST02" USING WFUNC WVAL.
     MOVE 2 TO WFUNC.
     CALL "STEST02" USING WFUNC WVAL.
     STOP RUN.