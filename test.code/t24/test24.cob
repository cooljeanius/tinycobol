 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST24.
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

 01  WS-RCODE	              PIC ZZZ9.
 
 
 PROCEDURE DIVISION.

 A-000.
 
 DISPLAY "BEGIN: EVALUATE TESTS".

 MOVE 1   TO WS-A100. 
 PERFORM A-100.
 MOVE 8   TO WS-A100. 
 PERFORM A-150.

 MOVE 2   TO WS-A200. 
 PERFORM A-200.

 MOVE 2   TO WS-A200. 
 PERFORM A-250.
 MOVE 12  TO WS-A200. 
 PERFORM A-250.
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

 DISPLAY "END  : EVALUATE TESTS".

 MOVE RETURN-CODE TO WS-RCODE.
 DISPLAY "WS-RCODE=" WS-RCODE.

 STOP RUN.


 A-100.

 DISPLAY "ENTER A-100:".

 EVALUATE WS-A100
     WHEN 1 
           DISPLAY "WS-A100 [1] = " WS-A100
           PERFORM Z-900 THRU Z-910
     WHEN 2 
           DISPLAY "WS-A100 [2] = " WS-A100 
           PERFORM Z-910 THRU Z-920
     WHEN OTHER 
           DISPLAY "OTHER WS-A100=" WS-A100 
 END-EVALUATE.

 DISPLAY "EXIT  A-100".

 A-150.

 DISPLAY "ENTER A-150:".

 EVALUATE WS-A100
     WHEN 1 
     WHEN 2 
     WHEN 3 
     WHEN 5 
     WHEN 7 
           DISPLAY "WS-A100 [1,2,3,5,7] = " WS-A100
           PERFORM Z-900 THRU Z-910
     WHEN 4 
     WHEN 6 
     WHEN 8 
           DISPLAY "WS-A100 [4,6,8] = " WS-A100 
           PERFORM Z-910 THRU Z-920
     WHEN OTHER 
           DISPLAY "OTHER WS-A100 = " WS-A100 
 END-EVALUATE.

 DISPLAY "EXIT  A-150".

 A-200.

 DISPLAY "ENTER A-200:".

 EVALUATE WS-A200
     WHEN 1 THRU 10
           DISPLAY "WS-A200 [1-10]  = " WS-A200 
     WHEN 11 THRU 99 
           DISPLAY "WS-A200 [11-99] = " WS-A200 
     WHEN OTHER 
           DISPLAY "OTHER   WS-A200 = " WS-A200 
 END-EVALUATE.

 DISPLAY "EXIT  A-200".

 A-250.

 DISPLAY "ENTER A-250:".

 EVALUATE WS-A200
*    WHEN 1 THRU 5
*            DISPLAY "WS-A250 [1 - 5]  = " WS-A200 
    WHEN 6 THRU 10
           DISPLAY "WS-A250 [6 - 10]  = " WS-A200 
*           DISPLAY "WS-A250 [1 - 10]  = " WS-A200 
     WHEN 11 THRU 99 
           DISPLAY "WS-A250 [11 - 99] = " WS-A200 
     WHEN OTHER 
           DISPLAY "OTHER     WS-A200 = " WS-A200 
 END-EVALUATE.

 DISPLAY "EXIT  A-250".

A-300.

 DISPLAY "ENTER A-300:".

 EVALUATE WS-AGE-GROUP
     WHEN WS-MINOR
          DISPLAY "WS-MINOR  [1 - 18]  = " WS-AGE-GROUP 
     WHEN WS-YADULT 
          DISPLAY "WS-YADULT [19 - 20] = " WS-AGE-GROUP 
     WHEN WS-ADULT  
          DISPLAY "WS-ADULT  [21 - 99] = " WS-AGE-GROUP 
     WHEN OTHER 
          DISPLAY "OTHER               = " WS-AGE-GROUP 
 END-EVALUATE.

 DISPLAY "EXIT  A-300".


A-400.

 DISPLAY "ENTER A-400:".

 EVALUATE WS-AGE-GROUP <= 20
     WHEN TRUE
          DISPLAY "MINOR  [1 - 20]  = " WS-AGE-GROUP 
     WHEN FALSE
          DISPLAY "ADULT  [21 - 99] = " WS-AGE-GROUP 
 END-EVALUATE.

 DISPLAY "EXIT  A-400".

A-500.

 DISPLAY "ENTER A-500:".

 EVALUATE WS-A100 ALSO WS-A200
     WHEN 1 ALSO 1 THRU 10
           DISPLAY "WS-A100 [1] = " WS-A100 ", WS-A200 [1 - 10]  = " WS-A200 
     WHEN 2 ALSO 11 THRU 99 
           DISPLAY "WS-A100 [2] = " WS-A100 ", WS-A200 [11 - 99] = " WS-A200 
     WHEN OTHER 
           DISPLAY "OTHER WS-A100=" WS-A100 ", WS-A200 = " WS-A200 
 END-EVALUATE.

 DISPLAY "EXIT  A-500".

A-600.

 DISPLAY "ENTER A-600:".

 EVALUATE TRUE
     WHEN DATA-ISVALID 
          DISPLAY "Data is valid            DATA-VALIDATION [0] = " DATA-VALIDATION 
     WHEN DATA-NOTNUMERIC
          DISPLAY "Data is not numeric      DATA-VALIDATION [1] = " DATA-VALIDATION 
     WHEN DATA-ISOUTOFBOUNDS
          DISPLAY "Data is out of bounds    DATA-VALIDATION [2] = " DATA-VALIDATION 
     WHEN OTHER 
          DISPLAY "Error: Unknown data code DATA-VALIDATION [?] = " DATA-VALIDATION 
 END-EVALUATE.

 DISPLAY "EXIT  A-600".

A-700.

 DISPLAY "ENTER A-700:".

 IF DATA-ISVALID
 THEN 
     DISPLAY "Data is valid            DATA-VALIDATION [0] = " DATA-VALIDATION 
 ELSE
     DISPLAY "Data is not valid        DATA-VALIDATION     = " DATA-VALIDATION 
 END-IF.
 
 DISPLAY "EXIT  A-700".


 DISPLAY "ENTER A-800:".

 EVALUATE WS-AGE-GROUP = 19 OR 20
     WHEN TRUE
          DISPLAY "TRUE : YADULT  [19 OR 20]  = " WS-AGE-GROUP 
     WHEN FALSE
          DISPLAY "FALSE: YADULT  [19 OR 20]  = " WS-AGE-GROUP 
 END-EVALUATE.

 DISPLAY "EXIT  A-800".

Z-900.

 DISPLAY "ENTER Z-900".
 DISPLAY "EXIT  Z-900".

Z-910.

 DISPLAY "ENTER Z-910".
 DISPLAY "EXIT  Z-910".

Z-920.

 DISPLAY "ENTER Z-920".
 DISPLAY "EXIT  Z-920".
