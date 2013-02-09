 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST17.
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.
*       SPECIAL-NAMES.
*       DECIMAL-POINT IS PERIOD.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.

 01	W01-NUMBER	PIC 9(4).
 01	W01-NUMBER1	PIC 9(9) COMP-5.
 01	W01-A	        PIC X(8)  VALUE '$$$$$$$$'.
 01	W01-B	        PIC X(8)  VALUE '$$$$$$$$'.
 01	W01-C	        PIC X(8)  VALUE '$$$$$$$$'.
 01	W01-D	        PIC X(8)  VALUE '$$$$$$$$'.
 01	W02-1	        PIC X(25) VALUE '$$$$$$$$$$$$$$$$$$$$$$$$$'.
 01	W02-2	        PIC X(25) VALUE '$$$$$$$$$$$$$$$$$$$$$$$$$'.
 01	W02-3	        PIC X(25) VALUE '$$$$$$$$$$$$$$$$$$$$$$$$$'.
 01	W02-4	        PIC X(25) VALUE '$$$$$$$$$$$$$$$$$$$$$$$$$'.

* 01	WS-RCODE	PIC Z(4)9 VALUE 0.
 01	WS-RCODE	PIC Z(4)9 VALUE ZERO.
 01     CMDLINE-PARMS   PIC X(50).
* 01	CMDLINE-PARMS   PIC X(15).
 01	ENVAR-PARMS     PIC X(182).
* 01	ENVAR-PARMS     PIC X(82).

 PROCEDURE DIVISION.

 A-000.

     PERFORM A-100.

     PERFORM A-400.

* MOVE 22 TO RETURN-CODE.
     MOVE RETURN-CODE TO WS-RCODE.
     DISPLAY "WS-RCODE=" WS-RCODE.

     STOP RUN.

 A-100.

     DISPLAY "ENTER A-100".

     MOVE 1 TO W01-NUMBER. 

     ACCEPT CMDLINE-PARMS FROM COMMAND-LINE.

     DISPLAY "CMDLINE-PARMS =" CMDLINE-PARMS ";".

     IF RETURN-CODE = 0
     THEN
       PERFORM A-200
     ELSE 
       DISPLAY "COMMAND LINE truncation ERROR has occured " 
       MOVE RETURN-CODE TO WS-RCODE
       DISPLAY "WS-RCODE=" WS-RCODE
     END-IF.
 
     DISPLAY "EXIT  A-100".

 A-200.

     DISPLAY "ENTER A-200".
 
     UNSTRING CMDLINE-PARMS DELIMITED BY ' ' INTO W01-A W01-B W01-C W01-D.

     DISPLAY "W01-A =" W01-A ";".
     DISPLAY "W01-B =" W01-B ";".
     DISPLAY "W01-C =" W01-C ";".
     DISPLAY "W01-D =" W01-D ";".
 
     DISPLAY "EXIT  A-200".

 A-400.

     DISPLAY "ENTER A-400".

     ACCEPT ENVAR-PARMS FROM ENVIRONMENT-VARIABLE "PATH".
     DISPLAY "ENVAR-PARMS =" ENVAR-PARMS ";".

     IF RETURN-CODE = 0
     THEN
        PERFORM A-500
     ELSE 
        IF RETURN-CODE = 1
        THEN
           DISPLAY "ENVIRONMENT VARIABLE was not found " 
        END-IF
        IF RETURN-CODE = 2
        THEN
           DISPLAY "ENVIRONMENT VARIABLE truncation ERROR has occured " 
        END-IF
        MOVE RETURN-CODE TO WS-RCODE
        DISPLAY "WS-RCODE=" WS-RCODE
     END-IF.
 
     DISPLAY "EXIT  A-400".

 A-500.

     DISPLAY "ENTER A-500".

     UNSTRING  ENVAR-PARMS DELIMITED BY ':' INTO W02-1 W02-2 W02-3 W02-4.

     DISPLAY "W02-1 =" W02-1 ";".
     DISPLAY "W02-2 =" W02-2 ";".
     DISPLAY "W02-3 =" W02-3 ";".
     DISPLAY "W02-4 =" W02-4 ";".

     DISPLAY "EXIT  A-500".
