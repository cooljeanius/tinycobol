 IDENTIFICATION DIVISION. 
 PROGRAM-ID. COND03. 
 ENVIRONMENT DIVISION. 
 CONFIGURATION SECTION. 
* INPUT-OUTPUT SECTION. 
* FILE-CONTROL. 
 DATA DIVISION. 
 FILE SECTION. 
 WORKING-STORAGE SECTION. 
  
  01  WS-A100	              PIC 9(3). 
  01  WS-A200	              PIC 9(3). 
 
  01  WS-AGE-GROUP	      PIC 9(2). 
      88 WS-MINOR              VALUE 1 THRU 18. 
      88 WS-YADULT             VALUE 19, 20. 
      88 WS-ADULT              VALUE 21 THRU 99. 
 
  01 DATA-VALIDATION           PIC 9. 
      88 DATA-ISVALID          VALUE 0. 
      88 DATA-NOTNUMERIC       VALUE 1. 
      88 DATA-ISOUTOFBOUNDS    VALUE 2. 
 
  01 WS-TOT-TRACE. 
     05 WS-EV-TRACE            PIC 9(2). 
     05 WS-Z-TRACE             PIC 9. 
  01 WS-EXPECTED               PIC 9(3). 

 PROCEDURE DIVISION. 
 A-000. 
  
     MOVE 1   TO WS-A100.  
     PERFORM A-100. 
     MOVE 8   TO WS-A100.  
     PERFORM A-150. 
 
     MOVE 0 TO WS-Z-TRACE. 
     MOVE 2   TO WS-A200.  
     PERFORM A-200. 
 
     MOVE 10  TO WS-EV-TRACE. 
     MOVE 140 TO WS-EXPECTED. 
     MOVE 2   TO WS-A200.  
     PERFORM A-250. 
     MOVE 20  TO WS-EV-TRACE. 
     MOVE 220 TO WS-EXPECTED. 
     MOVE 12  TO WS-A200.  
     PERFORM A-250. 
     MOVE 30  TO WS-EV-TRACE. 
     MOVE 340 TO WS-EXPECTED. 
     MOVE 166 TO WS-A200.  
     PERFORM A-250. 
 
     MOVE 19  TO WS-AGE-GROUP.  
     PERFORM A-300. 
     PERFORM A-400. 
     PERFORM A-500. 
 
     MOVE 0  TO DATA-VALIDATION.  
     PERFORM A-600. 
 
     MOVE 0  TO DATA-VALIDATION.  
     PERFORM A-700. 
 
     STOP RUN. 
 
 A-100. 
     MOVE 0 TO WS-Z-TRACE. 
     EVALUATE WS-A100 
         WHEN 1  
               MOVE 1 TO WS-EV-TRACE 
               PERFORM Z-900 THRU Z-910 
         WHEN 2  
               MOVE 2 TO WS-EV-TRACE 
               PERFORM Z-910 THRU Z-920 
         WHEN OTHER  
               MOVE 3 TO WS-EV-TRACE 
     END-EVALUATE. 
     DISPLAY "EV01:(" WS-TOT-TRACE "):(013):(Simple)". 
 
 A-150. 
     MOVE 0 TO WS-Z-TRACE. 
     EVALUATE WS-A100 
         WHEN 1  
         WHEN 2  
         WHEN 3  
         WHEN 5  
         WHEN 7  
               MOVE 1 TO WS-EV-TRACE 
               PERFORM Z-900 THRU Z-910 
         WHEN 4  
         WHEN 6  
         WHEN 8  
               MOVE 2 TO WS-EV-TRACE 
               PERFORM Z-910 THRU Z-920 
         WHEN OTHER  
               MOVE 3 TO WS-EV-TRACE 
     END-EVALUATE. 
     DISPLAY "EV02:(" WS-TOT-TRACE "):(026):(Multiple WHEN)". 
 
 A-200. 
     EVALUATE WS-A200 
         WHEN 1 THRU 10 
               MOVE 1 TO WS-EV-TRACE 
         WHEN 11 THRU 99  
               MOVE 2 TO WS-EV-TRACE 
         WHEN OTHER  
               MOVE 3 TO WS-EV-TRACE 
     END-EVALUATE. 
     DISPLAY "EV03:(" WS-TOT-TRACE "):(010):(THRU conditions)". 
 
 A-250. 
     EVALUATE WS-A200 
         WHEN 6 THRU 10 
               ADD  1 TO WS-EV-TRACE 
         WHEN 11 THRU 99  
               ADD  2 TO WS-EV-TRACE 
         WHEN OTHER  
               ADD  4 TO WS-EV-TRACE 
     END-EVALUATE. 
     DISPLAY "EV04:(" WS-TOT-TRACE "):(" WS-EXPECTED 
             "):(THRU conditions, OTHER branch)". 
 
 A-300. 
     EVALUATE WS-AGE-GROUP 
         WHEN WS-MINOR 
              MOVE 1 TO WS-EV-TRACE 
         WHEN WS-YADULT  
              MOVE 2 TO WS-EV-TRACE 
         WHEN WS-ADULT   
              MOVE 3 TO WS-EV-TRACE 
         WHEN OTHER  
              MOVE 4 TO WS-EV-TRACE 
     END-EVALUATE. 
     DISPLAY "EV05:(" WS-TOT-TRACE "):(020):(88 conditions)". 
 
 A-400. 
     EVALUATE WS-AGE-GROUP <= 20 
         WHEN TRUE 
              MOVE 1 TO WS-EV-TRACE 
         WHEN FALSE 
              MOVE 2 TO WS-EV-TRACE 
     END-EVALUATE. 
     DISPLAY "EV06:(" WS-TOT-TRACE "):(010):(88 conditions)". 
 
 A-500. 
     EVALUATE WS-A100 ALSO WS-A200 
         WHEN 1 ALSO 1 THRU 10 
              MOVE 1 TO WS-EV-TRACE 
         WHEN 2 ALSO 11 THRU 99  
              MOVE 2 TO WS-EV-TRACE 
         WHEN OTHER  
              MOVE 3 TO WS-EV-TRACE 
     END-EVALUATE. 
     DISPLAY "EV07:(" WS-TOT-TRACE "):(030):(ALSO conditions)". 
 
 A-600. 
     EVALUATE TRUE 
         WHEN DATA-ISVALID  
              MOVE 1 TO WS-EV-TRACE 
         WHEN DATA-NOTNUMERIC 
              MOVE 2 TO WS-EV-TRACE 
         WHEN DATA-ISOUTOFBOUNDS 
              MOVE 3 TO WS-EV-TRACE 
         WHEN OTHER  
              MOVE 4 TO WS-EV-TRACE 
     END-EVALUATE. 
     DISPLAY "EV08:(" WS-TOT-TRACE "):(010):(Simple 88)". 
 
 A-700. 
     IF DATA-ISVALID 
     THEN  
         MOVE 1 TO WS-EV-TRACE 
     ELSE 
         MOVE 2 TO WS-EV-TRACE 
     END-IF. 
     DISPLAY "EV09:(" WS-TOT-TRACE "):(010):(IF 88 condition)". 
 
 Z-900. 
     ADD 1 TO WS-Z-TRACE. 
 
 Z-910. 
     ADD 2 TO WS-Z-TRACE. 
 
 Z-920. 
     ADD 4 TO WS-Z-TRACE. 

