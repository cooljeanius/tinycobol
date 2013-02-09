 IDENTIFICATION DIVISION.
 PROGRAM-ID.    testgui01.  
 AUTHOR. Rildo Pragana.         
* REMARKS.
*    Example tcl/tk interface program for Cobol.
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

    77  TCLCMD      pic X(80). 
    77  TCLRESULT   pic X(80).

 PROCEDURE DIVISION.
  
  CALL "initTcl".
  
  100-LOOP.
        DISPLAY "tcl> " no advancing
        ACCEPT TCLCMD
        IF TCLCMD = SPACES 
        GO 110-LOOP-END.
        CALL "exec_tcl" USING TCLCMD TCLRESULT
        DISPLAY TCLRESULT
        GO 100-LOOP.
 110-LOOP-END.
        DISPLAY "End TCL interpreter"
        CALL "endTcl"
  STOP RUN.
