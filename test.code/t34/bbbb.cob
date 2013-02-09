 IDENTIFICATION DIVISION.
 PROGRAM-ID.	bbbb.
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
 01 campo1	    pic x(5) value spaces.
 01 campo2	    pic x(10) value spaces.
 01 status-field    pic xxxx value all '0'.
 PROCEDURE DIVISION chaining campo1 campo2.
 INI. 
     display "I'm on bbbb".
     if campo1 = spaces and campo2 = spaces
       display "I'm invoked directly from the shell"
     else
       display "I came from chain"
       display "1st field passed : " campo1
       display "2nd field passed : " campo2
     end-if.
     STOP RUN.

