 IDENTIFICATION DIVISION.
 PROGRAM-ID.	TEST23A.
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION. 
 SPECIAL-NAMES.
    DECIMAL-POINT IS COMMA
    CRT STATUS IS status-field.
*    DISPLAY-SCREEN STATUS IS status-field.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.
 WORKING-STORAGE SECTION.

 01  status-field   pic 9(04) value 0.
 01  campo	    pic x(20) value spaces.

 SCREEN SECTION.

 01 screen-scr.
     02 filler  	    line 10 col 10 value "Input field :".
     02 input-scr pic x(20) line 10 col 25 using campo.
     02 filler  	    line 12 col 10 value "Status Code :".
     02 filler    pic 9(04) line 12 col 25 using status-field. 
     02   line 14 col 10 value "Press F3 to exit".

 PROCEDURE DIVISION.
 INI.
      display screen-scr.
      ACCEPT input-scr.
      display screen-scr.
*      if status-field = "0027"
      if status-field = "0267"
	  stop run
      end-if.
      go to ini.
      STOP RUN.

