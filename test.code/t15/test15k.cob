 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST15k.
 AUTHOR.  David Essex.
 INSTALLATION. TinyCOBOL.
 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.

 01 WS-PARM-0.
    05 FILLER       PIC X.
 01 WS-PARM-1.
    05 WS-PARM-1W   PIC X(09) value "WS-PARM-1".
    05 FILLER       PIC X VALUE x"00".
 01 WS-PARM-2.
    05 WS-PARM-2W   PIC X(09) value "WS-PARM-2".
    05 FILLER       PIC X VALUE x"00".
 01 WS-PARM-3.
    05 WS-PARM-3W   PIC X(09) value "WS-PARM-3".
    05 FILLER       PIC X VALUE x"00".
 01 WS-PARM-4.
    05 FILLER       PIC X VALUE x"00".
 01 WS-PARM.
    05 WS-PARM-1S   PIC X(45).
*     10 WS-PARM-1S1 OCCURS 3 TIMES PIC X(15).
*    05 WS-PARM-1S   PIC X(15) value "WS-PARM-1S :".
*    05 WS-PARM-2S   PIC X(15) value "WS-PARM-2S :".
*    05 WS-PARM-3S   PIC X(15) value "WS-PARM-3S :".
    05 FILLER       PIC X VALUE x"00".

 01 WS-NUM          PIC 9(9) COMP-5 VALUE ZERO.
 01 WS-RCODE        PIC Z(4)9 VALUE ZERO.

 01 wsWorkareas.
    05 wsStructWorkarea.
*      10 filler        pointer value x"00".
*      10 filler        pointer value x"00".
*      10 filler        pointer value x"00".
      10 wsStruct-n       pic 9(4)  comp-5 value 56.
      10 wsStruct-ch.
         15 wsStruct-ch1  pic X(09) value "ABCDEFGHI".
         15 filler        pic X     value x"00".
      10 wsStruct-num     pic 9(9)  comp-5 value 324.

 PROCEDURE DIVISION.

*   Call to C-function (using a variable length list) using a pointer 
    DISPLAY "--------------------------------------------------". 
    DISPLAY "main (test15k) COB    ( input): WS-PARM-1W=" WS-PARM-1W.
    CALL "STEST1902" USING BY REFERENCE WS-PARM-1. 
    DISPLAY "main (test15k) COB    (output): WS-PARM-1W=" WS-PARM-1W.

*   Call to C-function using a variable length list
    DISPLAY "--------------------------------------------------". 
    MOVE 3 TO WS-NUM.
    DISPLAY "main (test15k) COB    ( input): WS-PARM-1W=" WS-PARM-1W " WS-PARM-2W=" WS-PARM-2W  
            " WS-PARM-3W=" WS-PARM-3W.
    CALL "STEST1901"  USING 
         BY VALUE WS-NUM 
         BY REFERENCE WS-PARM-1 
         BY REFERENCE WS-PARM-2 
         BY REFERENCE WS-PARM-3
         BY REFERENCE WS-PARM-4
    END-CALL.
    DISPLAY "main (test15k) COB    (output): WS-PARM-1W=" WS-PARM-1W " WS-PARM-2W=" WS-PARM-2W  
            " WS-PARM-3W=" WS-PARM-3W.

*   Call to C-function using a NULL terminated string
    DISPLAY "--------------------------------------------------". 
    MOVE "WS-PARM-1S     WS-PARM-2S     WS-PARM-3S     " TO WS-PARM-1S.
    DISPLAY "main (test15k) COB    ( input): WS-PARM-1S=" WS-PARM-1S.
    CALL "STEST1903" USING BY REFERENCE WS-PARM. 
    DISPLAY "main (test15k) COB    (output): WS-PARM-1S=" WS-PARM-1S.

*   Call to C-function using a structure
    DISPLAY "--------------------------------------------------". 
    DISPLAY "main (test15k) COB   ( input): wsStruct-n=" wsStruct-n " wsStruct-ch1=" wsStruct-ch1 
            " wsStruct-num=" wsStruct-num.
    CALL "STEST1904" USING BY REFERENCE wsStructWorkarea. 
    DISPLAY "main (test15k) COB   (output): wsStruct-n=" wsStruct-n " wsStruct-ch1=" wsStruct-ch1 
            " wsStruct-num=" wsStruct-num.

    DISPLAY "--------------------------------------------------". 

    MOVE RETURN-CODE TO WS-RCODE.
    DISPLAY "WS-RCODE=" WS-RCODE.
    STOP RUN.
