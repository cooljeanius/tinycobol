 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST31d.
 ENVIRONMENT DIVISION.
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
  SELECT PARTS-FILE
    ASSIGN TO "file31d.dat"
    ORGANIZATION IS SEQUENTIAL
*    ORGANIZATION IS LINE SEQUENTIAL
    FILE STATUS IS W01-STATUS.

 DATA DIVISION.
 FILE SECTION.

FD  PARTS-FILE
    RECORD VARYING 26 TO 53 CHARACTERS
    .
01  PARTS-RECORD.
    05 PARTS-PART-INFO.
      10 PARTS-PART-INFO-1 PIC X(01).
      10 FILLER            PIC X(19).
*    05 PARTS-BIN-IDX       PIC 999 value 1.
    05 PARTS-BIN-IDX       PIC 999.
    05 PARTS-BIN-NUMBER    PIC X(3)
       OCCURS 1 TO 10 TIMES DEPENDING ON PARTS-BIN-IDX.

 WORKING-STORAGE SECTION.
 
 01 W01-STATUS        PIC XX.
 01 W01-CNT           PIC 999.
 01 W01-WRITE-CNT     PIC 99 VALUE ZERO.
 01 W01-WRITE-CNT-A   PIC 99 VALUE ZERO.
 01 W01-WRITE-CNT-B   PIC 99 VALUE ZERO.
 01 W01-WRITE-CNT-C   PIC 99 VALUE ZERO.
 01 W01-READ-CNT      PIC 99 VALUE ZERO.
 01 W01-READ-CNT-A    PIC 99 VALUE ZERO.
 01 W01-READ-CNT-B    PIC 99 VALUE ZERO.
 01 W01-READ-CNT-C    PIC 99 VALUE ZERO.
 01 WS-IDX            PIC 99.
 01 EOF-SW            PIC X VALUE 'N'.
    88 EOF         VALUE 'Y'.
 01 WS-BIN-NUMBER.
   05 WS-BIN-NUMBER-1 PIC X(1).
   05 WS-BIN-NUMBER-2 PIC 9(2).

 PROCEDURE DIVISION.
 A000.
   MOVE ZEROES TO W01-STATUS.
*  Bug fix: Supress RTL warning
   MOVE 1 TO PARTS-BIN-IDX.
*   MOVE SPACES TO PARTS-RECORD.
   OPEN OUTPUT PARTS-FILE.
   IF W01-STATUS NOT = "00"
      DISPLAY "ERROR IN OPENING FILE STATUS=" W01-STATUS ";"
   ELSE
*      DISPLAY "A000 : before A100-CREATE-FILE perform "  UPON STD-ERROR
      PERFORM A100-CREATE-FILE
          VARYING W01-CNT FROM 1 BY 1
          UNTIL W01-CNT > 25
*      DISPLAY "A000 : CLOSE: FILE STATUS=" W01-STATUS ";"
      CLOSE PARTS-FILE
      ADD W01-WRITE-CNT-A W01-WRITE-CNT-B W01-WRITE-CNT-C TO W01-WRITE-CNT
   END-IF.
                        
   MOVE ZEROES TO W01-STATUS.
   OPEN INPUT PARTS-FILE.
   IF W01-STATUS NOT = "00"
      DISPLAY "ERROR IN OPENING FILE STATUS=" W01-STATUS ";"
   ELSE
*      DISPLAY "RE-OPEN: FILE STATUS=" W01-STATUS ";"
      MOVE 'N' TO EOF-SW
      PERFORM R100-READ-FILE
*      DISPLAY "LENGTH : RECORD"
      PERFORM A200-LOOP UNTIL EOF
      CLOSE PARTS-FILE
   END-IF.
   PERFORM A300-AUDIT-SUMMARY.
   STOP RUN.

 A300-AUDIT-SUMMARY.
   DISPLAY "Test31d Audit Summary :".
   DISPLAY "Total Records Written  " W01-WRITE-CNT.
   DISPLAY "Records Written Type A " W01-WRITE-CNT-A.
   DISPLAY "Records Written Type B " W01-WRITE-CNT-B.
   DISPLAY "Records Written Type C " W01-WRITE-CNT-C.
   DISPLAY "Total Records Read     " W01-READ-CNT.
   DISPLAY "Records Read Type A    " W01-READ-CNT-A.
   DISPLAY "Records Read Type B    " W01-READ-CNT-B.
   DISPLAY "Records Read Type C    " W01-READ-CNT-C.

 A200-LOOP.
   EVALUATE PARTS-BIN-IDX
     WHEN 6 
*       DISPLAY PARTS-BIN-IDX "   :" PARTS-RECORD ":"
       ADD 1 TO W01-READ-CNT-A
     WHEN 1  
*       DISPLAY PARTS-BIN-IDX "   :" PARTS-RECORD ":"
       ADD 1 TO W01-READ-CNT-B
     WHEN 10
*       DISPLAY PARTS-BIN-IDX "   :" PARTS-RECORD ":"
       ADD 1 TO W01-READ-CNT-C
     WHEN OTHER 
       DISPLAY "INVALID PARTS-BIN-IDX=" PARTS-BIN-IDX 
   END-EVALUATE.
   PERFORM R100-READ-FILE.
 
 R100-READ-FILE.       
   MOVE SPACES TO PARTS-RECORD.
*   MOVE 1 TO PARTS-BIN-IDX.
*   DISPLAY "BEFORE READ: FILE W01-STATUS=" W01-STATUS
   READ PARTS-FILE 
    AT END 
       MOVE 'Y' TO EOF-SW.
   IF NOT EOF
     IF W01-STATUS NOT = "00"
      DISPLAY "ERROR IN READING RECORD W01-STATUS=" W01-STATUS
     ELSE
        ADD 1 TO W01-READ-CNT
     END-IF   
   END-IF.    

 A100-CREATE-FILE.       
*   DISPLAY "A100-CREATE-FILE :  W01-CNT=" W01-CNT UPON STD-ERROR
   MOVE SPACES TO PARTS-RECORD.
   MOVE ALL "A" TO PARTS-PART-INFO.
   MOVE 6 TO PARTS-BIN-IDX.
   MOVE 1 TO WS-IDX.
   MOVE "A" TO WS-BIN-NUMBER-1.
   PERFORM UNTIL WS-IDX > PARTS-BIN-IDX
*     MOVE PARTS-BIN-IDX TO WS-BIN-NUMBER-2
     MOVE WS-IDX TO WS-BIN-NUMBER-2
     MOVE WS-BIN-NUMBER TO PARTS-BIN-NUMBER(WS-IDX)
     ADD 1 TO WS-IDX
   END-PERFORM.
   WRITE PARTS-RECORD.
   IF W01-STATUS NOT = "00"
   THEN
      DISPLAY "ERROR IN WRITING PARTS-RECORD W01-STATUS=" W01-STATUS
   ELSE
      ADD 1 TO W01-WRITE-CNT-A
   END-IF.    

   MOVE SPACES TO PARTS-RECORD.
   MOVE ALL "B" TO PARTS-PART-INFO.
   MOVE 1 TO PARTS-BIN-IDX.
   MOVE 1 TO WS-IDX.
   MOVE "B" TO WS-BIN-NUMBER-1.
   PERFORM UNTIL WS-IDX > PARTS-BIN-IDX
*     MOVE PARTS-BIN-IDX TO WS-BIN-NUMBER-2
     MOVE WS-IDX TO WS-BIN-NUMBER-2
     MOVE WS-BIN-NUMBER TO PARTS-BIN-NUMBER(WS-IDX)
     ADD 1 TO WS-IDX
   END-PERFORM.
   WRITE PARTS-RECORD.
   IF W01-STATUS NOT = "00"
   THEN
      DISPLAY "ERROR IN WRITING PARTS-RECORD W01-STATUS=" W01-STATUS
   ELSE
      ADD 1 TO W01-WRITE-CNT-B
   END-IF.    

   MOVE SPACES TO PARTS-RECORD.
   MOVE ALL "C" TO PARTS-PART-INFO.
   MOVE 10 TO PARTS-BIN-IDX.
   MOVE 1 TO WS-IDX.
   MOVE "C" TO WS-BIN-NUMBER-1.
   PERFORM UNTIL WS-IDX > PARTS-BIN-IDX
*     MOVE PARTS-BIN-IDX TO WS-BIN-NUMBER-2
     MOVE WS-IDX TO WS-BIN-NUMBER-2
     MOVE WS-BIN-NUMBER TO PARTS-BIN-NUMBER(WS-IDX)
     ADD 1 TO WS-IDX
   END-PERFORM.
   WRITE PARTS-RECORD.
   IF W01-STATUS NOT = "00"
   THEN
      DISPLAY "ERROR IN WRITING PARTS-RECORD W01-STATUS=" W01-STATUS
   ELSE
      ADD 1 TO W01-WRITE-CNT-C
   END-IF.    
