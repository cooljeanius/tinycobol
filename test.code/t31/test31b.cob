 IDENTIFICATION DIVISION.
 PROGRAM-ID. Test31b.
 ENVIRONMENT DIVISION.
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
  SELECT PHONE-FILE
    ASSIGN TO "file31b.dat"
    ORGANIZATION IS SEQUENTIAL
*    ORGANIZATION IS LINE SEQUENTIAL
    FILE STATUS IS W01-STATUS.

 DATA DIVISION.
 FILE SECTION.

 FD PHONE-FILE
    LABEL RECORDS ARE STANDARD
    RECORD CONTAINS 10 TO 60 CHARACTERS
*    RECORD CONTAINS 10 TO 1000 CHARACTERS
 .

 01 PHONE-RECORD-10.
   05 PHONE-RECORD-TYPE     PIC X(01).
*   05 FILLER                PIC X(9999).
*   05 FILLER                PIC X(999).
*   05 FILLER                PIC X(99).
   05 FILLER                PIC X(09).

 01 PHONE-RECORD-60.
   05 FILLER                PIC X(60).

 01 PHONE-RECORD-20.
   05 FILLER                PIC X(20).
 
 WORKING-STORAGE SECTION.
 
 01 W01-STATUS      PIC XX.
 01 W01-CNT         PIC 99.
 01 W01-WRITE-CNT   PIC 99 VALUE ZERO.
 01 W01-WRITE-CNT-A PIC 99 VALUE ZERO.
 01 W01-WRITE-CNT-B PIC 99 VALUE ZERO.
 01 W01-WRITE-CNT-C PIC 99 VALUE ZERO.
 01 W01-READ-CNT    PIC 99 VALUE ZERO.
 01 W01-READ-CNT-A  PIC 99 VALUE ZERO.
 01 W01-READ-CNT-B  PIC 99 VALUE ZERO.
 01 W01-READ-CNT-C  PIC 99 VALUE ZERO.
 01 EOF-SW          PIC X VALUE 'N'.
    88 EOF          VALUE 'Y'.

 PROCEDURE DIVISION.
 A000.
   MOVE ZEROES TO W01-STATUS.
   OPEN OUTPUT PHONE-FILE.
   IF W01-STATUS NOT = "00"
      DISPLAY "ERROR IN OPENING FILE STATUS=" W01-STATUS ";"
   ELSE
      PERFORM A100-CREATE-FILE
          VARYING W01-CNT FROM 1 BY 1
          UNTIL W01-CNT > 25
*      DISPLAY "CLOSE: FILE STATUS=" W01-STATUS ";"
      CLOSE PHONE-FILE
      ADD W01-WRITE-CNT-A W01-WRITE-CNT-B W01-WRITE-CNT-C TO W01-WRITE-CNT
   END-IF.
                        
   MOVE ZEROES TO W01-STATUS.
   OPEN INPUT PHONE-FILE.
   IF W01-STATUS NOT = "00"
      DISPLAY "ERROR IN OPENING FILE STATUS=" W01-STATUS ";"
   ELSE
*      DISPLAY "RE-OPEN: FILE STATUS=" W01-STATUS ";"
      MOVE 'N' TO EOF-SW
      PERFORM A100-READ-FILE
*      DISPLAY "LENGTH : RECORD"
      PERFORM A200-READ-LOOP UNTIL EOF
      CLOSE PHONE-FILE
   END-IF.
   PERFORM A300-AUDIT-SUMMARY.
   STOP RUN.

 A300-AUDIT-SUMMARY.
   DISPLAY "Test31b Audit Summary :".
   DISPLAY "Total Records Written  " W01-WRITE-CNT.
   DISPLAY "Records Written Type A " W01-WRITE-CNT-A.
   DISPLAY "Records Written Type B " W01-WRITE-CNT-B.
   DISPLAY "Records Written Type C " W01-WRITE-CNT-C.
   DISPLAY "Total Records Read     " W01-READ-CNT.
   DISPLAY "Records Read Type A    " W01-READ-CNT-A.
   DISPLAY "Records Read Type B    " W01-READ-CNT-B.
   DISPLAY "Records Read Type C    " W01-READ-CNT-C.

 A200-READ-LOOP.
   EVALUATE PHONE-RECORD-TYPE
      WHEN 'A' 
*       DISPLAY "RECORD-LENGTH=60 :" PHONE-RECORD-60 ":"
       ADD 1 TO W01-READ-CNT-A
      WHEN 'B'  
*       DISPLAY "RECORD-LENGTH=10 :" PHONE-RECORD-10 ":"
       ADD 1 TO W01-READ-CNT-B
     WHEN  'C'
*       DISPLAY "RECORD-LENGTH=20 :" PHONE-RECORD-20 ":"
       ADD 1 TO W01-READ-CNT-C
     WHEN OTHER 
       DISPLAY "INVALID RECORD TYPE :" PHONE-RECORD-TYPE ":"
   END-EVALUATE.
   PERFORM A100-READ-FILE.
 
 A100-READ-FILE.       
   MOVE SPACES TO PHONE-RECORD-60
                  PHONE-RECORD-10
                  PHONE-RECORD-20.
*   DISPLAY "BEFORE READ: FILE W01-STATUS=" W01-STATUS
   READ PHONE-FILE 
    AT END 
       MOVE 'Y' TO EOF-SW .
   IF NOT EOF
     IF W01-STATUS NOT = "00"
        DISPLAY "ERROR IN READING RECORD W01-STATUS=" W01-STATUS
     ELSE
        ADD 1 TO W01-READ-CNT
     END-IF   
   END-IF.    

 A100-CREATE-FILE.       
   MOVE ALL "A" TO PHONE-RECORD-60.
   WRITE PHONE-RECORD-60.
   IF W01-STATUS NOT = "00"
   THEN
      DISPLAY "ERROR IN WRITING PHONE-RECORD-60 W01-STATUS=" W01-STATUS
   ELSE
      ADD 1 TO W01-WRITE-CNT-A
   END-IF.    

   MOVE ALL "B" TO PHONE-RECORD-10.
   WRITE PHONE-RECORD-10.
   IF W01-STATUS NOT = "00"
   THEN
      DISPLAY "ERROR IN WRITING PHONE-RECORD-10 W01-STATUS=" W01-STATUS
   ELSE
      ADD 1 TO W01-WRITE-CNT-B
   END-IF.    

   MOVE ALL "C" TO PHONE-RECORD-20.
   WRITE PHONE-RECORD-20.
   IF W01-STATUS NOT = "00"
   THEN
      DISPLAY "ERROR IN WRITING PHONE-RECORD-20 W01-STATUS=" W01-STATUS
   ELSE
      ADD 1 TO W01-WRITE-CNT-C
   END-IF.    