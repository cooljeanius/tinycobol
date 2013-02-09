 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST20b.
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.
*       SPECIAL-NAMES.
*       DECIMAL-POINT IS PERIOD.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.
 WORKING-STORAGE SECTION.

 01  WS-IDX	        PIC 9(3).
 01  WS-IDX1	        PIC 9(3).
 01  WS-IDX2	        PIC 9(3).
* 01  IDX2	        PIC 9(3) COMP.
* 01  IDX1	        PIC 9(3) COMP.
 01  WS-RCODE	        PIC Z(4)9 VALUE ZERO.

 01 WS-TABLE1-ENTRIES.
* copy TCtable2.
 copy 'TCtable2.cpy'.
 01 WS-TABLE1 REDEFINES WS-TABLE1-ENTRIES.
    05  WS-TABLE1-ENTRY OCCURS 300 TIMES 
	  ASCENDING KEY IS WS-TABLE1-IDX 
	  INDEXED BY IDX1.
        10  WS-TABLE1-IDX	PIC X(3).
        10  WS-TABLE1-DATA	PIC X(17).

 01 WS-TABLE2-ENTRIES.
* copy TCtable3. 
 copy 'TCtable3.cpy'. 
 01 WS-TABLE2 REDEFINES WS-TABLE2-ENTRIES.
    05  WS-TABLE2-ENTRY OCCURS 100 TIMES 
	  DESCENDING KEY IS WS-TABLE2-IDX 
	  INDEXED BY IDX2.
        10  WS-TABLE2-IDX	PIC 9(3).
        10  WS-TABLE2-DATA	PIC X(17).
 
 
PROCEDURE DIVISION.

A-000.

 MOVE 1 TO WS-IDX1.
 PERFORM A-100.
 MOVE 300 TO WS-IDX1.
 PERFORM A-100.
 MOVE 44 TO WS-IDX1.
 PERFORM A-100.
 MOVE 544 TO WS-IDX1.
 PERFORM A-100.

 MOVE 6 TO WS-IDX2.
 PERFORM A-200.
 MOVE 5 TO WS-IDX2.
 PERFORM A-200.
 MOVE 135 TO WS-IDX2.
 PERFORM A-200.
 MOVE 500 TO WS-IDX2.
 PERFORM A-200.


 MOVE RETURN-CODE TO WS-RCODE.
 DISPLAY "WS-RCODE=" WS-RCODE.

 STOP RUN.

A-100.

 DISPLAY "ENTER A-100".
 
 SEARCH ALL WS-TABLE1-ENTRY
   AT END PERFORM A-400
   WHEN WS-IDX1 = WS-TABLE1-IDX (IDX1)
        PERFORM A-300.
*        NEXT SENTENCE.

 DISPLAY "EXIT  A-100".

A-200.

 DISPLAY "ENTER A-200".

  SEARCH ALL WS-TABLE2-ENTRY
   AT END PERFORM A-600
   WHEN WS-IDX2 = WS-TABLE2-IDX (IDX2)
        PERFORM A-500.
*        NEXT SENTENCE.
 
 DISPLAY "EXIT  A-200".

A-300.

 DISPLAY "ENTER A-300".

 MOVE IDX1 TO WS-RCODE.
 DISPLAY "Data WS-IDX1 =" WS-IDX1 " found IDX1=" WS-RCODE " in table WS-TABLE1".
 DISPLAY "WS-TABLE1-IDX  =" WS-TABLE1-IDX (IDX1) ":".
 DISPLAY "WS-TABLE1-DATA =" WS-TABLE1-DATA (IDX1) ":".

 DISPLAY "EXIT  A-300".


A-400.

 DISPLAY "ENTER A-400".

 DISPLAY "Data WS-IDX1 =" WS-IDX1 " not found in table WS-TABLE1".
 MOVE IDX1 TO WS-RCODE.
 DISPLAY "Index max IDX1 =" WS-RCODE.

 DISPLAY "EXIT  A-400".

A-500.

 DISPLAY "ENTER A-500".

 MOVE IDX2 TO WS-RCODE.
 DISPLAY "Data WS-IDX2 =" WS-IDX2 " found IDX2=" WS-RCODE " in table WS-TABLE2".
 DISPLAY "WS-TABLE2-IDX  =" WS-TABLE2-IDX (IDX2) ":".
 DISPLAY "WS-TABLE2-DATA =" WS-TABLE2-DATA (IDX2) ":".

 DISPLAY "EXIT  A-500".


A-600.

 DISPLAY "ENTER A-600".

 DISPLAY "Data WS-IDX2 =" WS-IDX2 " not found in table WS-TABLE2".
 MOVE IDX2 TO WS-RCODE.
 DISPLAY "Index max IDX2 =" WS-RCODE.

 DISPLAY "EXIT  A-600".
