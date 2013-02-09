 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST15g.
 AUTHOR.  David Essex.
 INSTALLATION. Tiny Cobol Compiler Project.
 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.

 01 WS-PARM-1    PIC 9(1).
 01 WS-PARM-2    PIC X(3).
 01 WS-PARM-3    PIC X(7).
 01  WS-RCODE	 PIC Z(4)9 VALUE ZERO.

 PROCEDURE DIVISION.

    DISPLAY "--------------------------------------------------". 

    MOVE 0 TO WS-PARM-1.
    DISPLAY "main (test15g) COB  input : WS-PARM-1 =" WS-PARM-1 .
    CALL "TEST15h" USING WS-PARM-1 WS-PARM-2 WS-PARM-3.
    DISPLAY "main (test15g) COB return : WS-PARM-1 =" WS-PARM-1 .

    DISPLAY "--------------------------------------------------". 

    MOVE 1      TO WS-PARM-1.
    MOVE '010'  TO WS-PARM-2.
    MOVE SPACES TO WS-PARM-3.
    DISPLAY "main (test15g) COB  input : WS-PARM-1 =" WS-PARM-1 
            " WS-PARM-2 =" WS-PARM-2 " WS-PARM-3 =" WS-PARM-3  ":".
    CALL "TEST15h" USING WS-PARM-1 WS-PARM-2 WS-PARM-3.
    DISPLAY "main (test15g) COB return : WS-PARM-1 =" WS-PARM-1 
            " WS-PARM-2 =" WS-PARM-2 " WS-PARM-3 =" WS-PARM-3  ":".

    DISPLAY "--------------------------------------------------". 

    MOVE 1      TO WS-PARM-1.
    MOVE '020'  TO WS-PARM-2.
    MOVE SPACES TO WS-PARM-3.
    DISPLAY "main (test15g) COB  input : WS-PARM-1 =" WS-PARM-1 
            " WS-PARM-2 =" WS-PARM-2 " WS-PARM-3 =" WS-PARM-3  ":".
    CALL "TEST15h" USING WS-PARM-1 WS-PARM-2 WS-PARM-3.
    DISPLAY "main (test15g) COB return : WS-PARM-1 =" WS-PARM-1 
            " WS-PARM-2 =" WS-PARM-2 " WS-PARM-3 =" WS-PARM-3  ":".

    DISPLAY "--------------------------------------------------". 

    MOVE RETURN-CODE TO WS-RCODE.
    DISPLAY "WS-RCODE=" WS-RCODE.
    STOP RUN.
