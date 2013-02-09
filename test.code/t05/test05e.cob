 IDENTIFICATION DIVISION.
 PROGRAM-ID.	TEST05e.
* Program to test PERFORM's 
*  using abbreviated relational conditionals.

 ENVIRONMENT DIVISION.

 CONFIGURATION SECTION. 
* INPUT-OUTPUT SECTION.
  
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01 INDX.
    05  IDX	  PIC  9(05).
    05  IDX1	  PIC  9(05).
    05  IDX2	  PIC  9(05).
    05  IDX3	  PIC  9(05).
 01 WS-DATA-TABLE.
    05  WS-DATA   OCCURS 5 TIMES  PIC  X(01).

 PROCEDURE DIVISION.

     PERFORM A-000.
       
     DISPLAY "BEGIN: PERFORM VARYING with standard conditionals - TEST BEFORE".
     PERFORM A-100.  
     DISPLAY "END  : PERFORM VARYING with standard conditionals - TEST BEFORE".

     DISPLAY "BEGIN: PERFORM VARYING with standard conditionals - TEST AFTER".
     PERFORM A-200.  
     DISPLAY "END  : PERFORM VARYING with standard conditionals - TEST AFTER".

     DISPLAY "BEGIN: PERFORM VARYING with abbreviated conditionals - TEST BEFORE".
     PERFORM A-300.  
     DISPLAY "END  : PERFORM VARYING with abbreviated conditionals - TEST BEFORE".

     DISPLAY "BEGIN: PERFORM VARYING with abbreviated conditionals - TEST AFTER".
     PERFORM A-400.  
     DISPLAY "END  : PERFORM VARYING with abbreviated conditionals - TEST AFTER".

     DISPLAY "BEGIN: PERFORM(In-line) VARYING with standard conditionals - TEST AFTER".
     PERFORM A-500.  
     DISPLAY "END  : PERFORM(In-line) VARYING with standard conditionals - TEST AFTER".

     DISPLAY "BEGIN: PERFORM(In-line) VARYING with standard conditionals - TEST BEFORE".
     PERFORM A-600.  
     DISPLAY "END  : PERFORM(In-line) VARYING with standard conditionals - TEST BEFORE".

     DISPLAY "BEGIN: PERFORM(In-line) VARYING with abbreviated conditionals - TEST AFTER".
     PERFORM A-700.  
     DISPLAY "END  : PERFORM(In-line) VARYING with abbreviated conditionals - TEST AFTER".

     DISPLAY "BEGIN: PERFORM(In-line) VARYING with abbreviated conditionals - TEST BEFORE".
     PERFORM A-800.  
     DISPLAY "END  : PERFORM(In-line) VARYING with abbreviated conditionals - TEST BEFORE".

     DISPLAY "BEGIN: PERFORM VARYING with standard conditionals - TEST BEFORE".
     PERFORM A-1100.  
     DISPLAY "END  : PERFORM VARYING with standard conditionals - TEST BEFORE".

     DISPLAY "BEGIN: PERFORM VARYING with standard conditionals - TEST AFTER".
     PERFORM A-1200.  
     DISPLAY "END  : PERFORM VARYING with standard conditionals - TEST AFTER".

     DISPLAY "BEGIN: PERFORM VARYING with abbreviated conditionals - TEST BEFORE".
     PERFORM A-1300.  
     DISPLAY "END  : PERFORM VARYING with abbreviated conditionals - TEST BEFORE".

     DISPLAY "BEGIN: PERFORM VARYING with abbreviated conditionals - TEST AFTER".
     PERFORM A-1400.  
     DISPLAY "END  : PERFORM VARYING with abbreviated conditionals - TEST AFTER".


     STOP RUN.

 A-000.
     DISPLAY "ENTER A-000".
     MOVE "a" TO WS-DATA (1).
     MOVE "b" TO WS-DATA (2).
     MOVE "c" TO WS-DATA (3).
     MOVE "d" TO WS-DATA (4).
     MOVE "e" TO WS-DATA (5).
     DISPLAY "EXIT  A-000".

 A-100.
     DISPLAY "ENTER A-100".
     PERFORM A-900  
	WITH TEST BEFORE
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	OR WS-DATA (IDX) = "c" 
	OR WS-DATA (IDX) = "d".
     DISPLAY "EXIT  A-100".

 A-200.
     DISPLAY "ENTER A-200".
     PERFORM A-900  
	WITH TEST AFTER
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	OR WS-DATA (IDX) EQUAL "d"
	OR WS-DATA (IDX) EQUAL "c".
     DISPLAY "EXIT  A-200".

 A-300.
     DISPLAY "ENTER A-300".
     PERFORM A-900  
	WITH TEST BEFORE
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	OR WS-DATA (IDX) = "c" OR "d" OR "p" OR "q".
     DISPLAY "EXIT  A-300".

 A-400.
     DISPLAY "ENTER A-400".
     PERFORM A-900  
	WITH TEST AFTER
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	OR WS-DATA (IDX) EQUAL "d" OR "c" OR "p" OR "q".
     DISPLAY "EXIT  A-400".
     
 A-500.
     DISPLAY "ENTER A-500".
     PERFORM  
	WITH TEST AFTER
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	OR WS-DATA (IDX) = "c" 
	OR WS-DATA (IDX) = "d"
	DISPLAY "A-500 - IDX =" IDX
     END-PERFORM.
     DISPLAY "EXIT  A-500".

 A-600.
     DISPLAY "ENTER A-600".
     PERFORM  
	WITH TEST BEFORE
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	OR WS-DATA (IDX) = "c" 
	OR WS-DATA (IDX) = "d"
	DISPLAY "A-600 - IDX =" IDX
     END-PERFORM.
     DISPLAY "EXIT  A-600".

 A-700.
     DISPLAY "ENTER A-700".
     PERFORM  
	WITH TEST AFTER
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	OR WS-DATA (IDX) = "c" OR "d" OR "p" OR "q"
	DISPLAY "A-700 - IDX =" IDX
     END-PERFORM.
     DISPLAY "EXIT  A-700".

 A-800.
     DISPLAY "ENTER A-800".
     PERFORM  
	WITH TEST BEFORE
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	OR WS-DATA (IDX) = "c" OR "d" OR "p" OR "q"
	DISPLAY "A-800 - IDX =" IDX
     END-PERFORM.
     DISPLAY "EXIT  A-800".

 A-900.
     DISPLAY "ENTER A-900".
     DISPLAY "A-900 - IDX =" IDX.
     DISPLAY "EXIT  A-900".
     
* ------------------------------------- *

 A-1100.
     DISPLAY "ENTER A-1100".
     PERFORM A-900  
	WITH TEST BEFORE
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	AND NOT 
	( WS-DATA (IDX) = "e" 
	  AND WS-DATA (IDX) = "d").
     DISPLAY "EXIT  A-1100".

 A-1200.
     DISPLAY "ENTER A-1200".
     PERFORM A-900  
	WITH TEST AFTER
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	AND NOT 
	( WS-DATA (IDX) = "e" 
	  AND WS-DATA (IDX) = "d").
     DISPLAY "EXIT  A-1200".

 A-1300.
     DISPLAY "ENTER A-1300".
     PERFORM A-900  
	WITH TEST BEFORE
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	AND NOT 
	( WS-DATA (IDX) = "e" AND "d" ).
     DISPLAY "EXIT  A-1300".

 A-1400.
     DISPLAY "ENTER A-1400".
     PERFORM A-900  
	WITH TEST AFTER
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	AND NOT 
	( WS-DATA (IDX) = "e" AND "d" ).
     DISPLAY "EXIT  A-1400".

 A-1500.
     DISPLAY "ENTER A-1500".
     PERFORM  
	WITH TEST AFTER
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	AND NOT 
	( WS-DATA (IDX) = "e" 
	  AND WS-DATA (IDX) = "d")
	DISPLAY "A-1500 - IDX =" IDX
     END-PERFORM.
     DISPLAY "EXIT  A-1500".

 A-1600.
     DISPLAY "ENTER A-1600".
     PERFORM  
	WITH TEST BEFORE
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	AND NOT 
	( WS-DATA (IDX) = "e" 
	  AND WS-DATA (IDX) = "d")
	DISPLAY "A-1600 - IDX =" IDX
     END-PERFORM.
     DISPLAY "EXIT  A-1600".

 A-1700.
     DISPLAY "ENTER A-1700".
     PERFORM  
	WITH TEST AFTER
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	AND NOT 
	( WS-DATA (IDX) = "e" AND "d" )
	DISPLAY "A-1700 - IDX =" IDX
     END-PERFORM.
     DISPLAY "EXIT  A-1700".

 A-1800.
     DISPLAY "ENTER A-1800".
     PERFORM  
	WITH TEST BEFORE
	VARYING IDX FROM 5 BY -1
	UNTIL IDX < 2
	AND NOT 
	( WS-DATA (IDX) = "e" AND "d" )
	DISPLAY "A-1800 - IDX =" IDX
     END-PERFORM.
     DISPLAY "EXIT  A-1800".

* ------------------------------------- *
