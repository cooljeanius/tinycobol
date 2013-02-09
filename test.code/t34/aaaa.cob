 IDENTIFICATION DIVISION.
 PROGRAM-ID.	aaaa.
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION. 
 SPECIAL-NAMES.
    DECIMAL-POINT IS COMMA.
*   crt status is status-field.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.
 WORKING-STORAGE SECTION.
 01 intable.
   02 inelements pic x occurs 80 value spaces.

 01 campo1	    pic x(50) value all '1'.
 01 campo2	    pic x(5) value all '2'.
 01 status-field    pic xxxx value all '0'.
 PROCEDURE DIVISION.
 INI. 
     display "I'm on aaaa".
     display "field passed to 'bbbb' : " campo1 " / " campo2.
     chain "./bbbb" using campo1 campo2. 
     STOP RUN.
