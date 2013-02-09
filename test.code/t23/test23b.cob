 IDENTIFICATION DIVISION.
 PROGRAM-ID.    test23b.
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION. 
 SPECIAL-NAMES.
    DECIMAL-POINT IS COMMA
    crt status is status-field.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.
 WORKING-STORAGE SECTION.
 
 01 campo   pic x(5) value spaces.
 01 line-wor       pic s9(4) comp value 14.
 01 col-wor        pic s9(4) comp value 14.
 01 foreground-wor pic s9(4) comp value 7.
 01 background-wor pic s9(4) comp value 1.
 01 color-wor      pic s9(7) comp value 15.
 01 status-field   pic xxxx value all '0'.
 SCREEN SECTION.

  01 screen-scr
           foreground-color foreground-wor
           background-color background-wor.
    02 line line-wor. 
     04 col col-wor value "|". 
     04 value "  Test lin/col  ". 
     04 value "|". 
    02 line - 1. 
     04 col col-wor value "+----------------+". 
    02 line + 2. 
     04 col col-wor value "+----------------+". 
  
  01 input-scr color color-wor.
    02 line 1.
     04 col 1 value "Line :".
     04 col + 1 pic 999 using line-wor.
    02 line + 1.
     04 col 1 value "Col. :".
     04 col + 1 pic 999 using col-wor.
    02 line + 1.
     04 col 1 value "Fore.:".
     04 col + 1 pic 999 using foreground-wor.
    02 line + 1.
     04 col 1 value "Back.:".
     04 col + 1 pic 999 using background-wor.
    02 line + 1.
     04 col 1 value "Color:".
     04 col + 1 pic 999 using color-wor.
    02 line + 2.
     04 col 1 value "Press F3 to exit.".
 PROCEDURE DIVISION.
 INI.
     display screen-scr.
     display input-scr.
     accept input-scr.
     if status-field = "0267"
     	 stop run
     end-if.
     go to ini.
     STOP RUN.

