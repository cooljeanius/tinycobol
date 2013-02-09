 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST15e.
 AUTHOR.  Bernard GIROUD.
 INSTALLATION. Tiny Cobol Compiler Project.
 DATE-WRITTEN. 05-AUG-2000.
 DATE-COMPILED.
 SECURITY. NONE.

 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01 PARM01 PIC X(20) VALUE "TEST".
 01 PARM03 PIC S9(9) COMP.
 01 G-PARM02.
    05 PARM02 PIC X(3).
    05 FILLER PIC X VALUE LOW-VALUES.
 01 G-PARM04.
    05 PARM04 PIC X(3).

 01 PARM05 PIC S9(18) COMP.
 01 RPARM05 REDEFINES PARM05.
    05 RPAR05L PIC S9(9) COMP.
    05 RPAR05H PIC S9(9) COMP.

 01 WRES01 PIC S9(4) COMP.
 01 WRES02 PIC S9(8) COMP.
 01 WERES01 PIC 9(4).
 01 WERES02 PIC 9(9).
*    05 FILLER PIC X VALUE LOW-VALUES.

 01 WRES05  PIC S9(18) COMP.
* 01 WRES05  PIC S9(9) COMP.
 01 WERES05 PIC S9(4) .

 01 W-PARM05 PIC S9(4) COMP.
 01 W-PARM06 PIC S9(15) COMP.

 01 WS-PARM03  PIC 9(9).
 01 WS-PARM05  PIC 9(4).
 01 WS-PARM06  PIC 9(15).
 01 WS-PARM05A PIC S9(18).

 01 PARM02Z.
    05 PARM02Z1 PIC X(4)  VALUE "ABCD".
    05 FILLER   PIC X     VALUE LOW-VALUE.
 01 PARM03Z.
    05 PARM03Z1 PIC X(4)  VALUE "0123".
    05 FILLER   PIC X     VALUE LOW-VALUE.
 01 PARM04Z.
    05 PARM04Z1 PIC X(4)  VALUE "EFGH".
    05 FILLER   PIC X     VALUE LOW-VALUE.
 01 PARM05Z.
    05 PARM05Z1 PIC X(4)  VALUE "4567".
    05 FILLER   PIC X     VALUE LOW-VALUE.

 PROCEDURE DIVISION.

    MOVE "ABCDEFGHIJ0123456789" TO PARM01.
    MOVE "XYZ" TO PARM02.
    MOVE "123" TO PARM04.
    DISPLAY "main (test15e) COB  input :" PARM01 ":".
    CALL "STEST901" USING PARM01.
    DISPLAY "main (test15e) COB return :" PARM01 ":".

    DISPLAY "--------------------------------------------------". 

    MOVE 3 TO PARM03.
    MOVE 5 TO W-PARM05.
    MOVE 6666666666 TO W-PARM06.
    MOVE PARM03 TO WS-PARM03.
    MOVE W-PARM05 TO WS-PARM05.
    MOVE W-PARM06 TO WS-PARM06.
*     DISPLAY "main (test15e) COB  input : WS-PARM03=" WS-PARM03 ":". 
    DISPLAY "main (test15e) COB    input: WS-PARM03=" WS-PARM03 
             ", WS-PARM05=" WS-PARM05
             ", WS-PARM06=" WS-PARM06 ":".
    CALL "STEST902" USING BY VALUE PARM03, W-PARM05, W-PARM06.
*     CALL "STEST902" USING BY VALUE PARM03.
    MOVE PARM03 TO WS-PARM03.
    MOVE W-PARM05 TO WS-PARM05.
    MOVE W-PARM06 TO WS-PARM06.
*     DISPLAY "main (test15e) COB return : PARM03=" WS-PARM03 ":".
    DISPLAY "main (test15e) COB   return: PARM03=" WS-PARM03
             ", PARM05=" WS-PARM05
             ", PARM06=" WS-PARM06 ":".

    DISPLAY "--------------------------------------------------". 

    DISPLAY "main (test15e) COB  input :5:".
    CALL "STEST903" USING BY VALUE 5.
    DISPLAY "main (test15e) COB return :5:".

    DISPLAY "--------------------------------------------------". 

    MOVE PARM03 TO WS-PARM03.
    DISPLAY "main (test15e) COB  input :" PARM02 ":"
    	     WS-PARM03 ":5:" PARM02 ":" PARM04 ":".

    CALL "STEST904" USING G-PARM02 BY VALUE PARM03 5
    	     BY REFERENCE G-PARM02 G-PARM04.
    MOVE PARM03 TO WS-PARM03.
    DISPLAY "main (test15e) COB return :" PARM02 ":"
    	     WS-PARM03 ":5:" PARM02 ":" PARM04 ":".

    DISPLAY "--------------------------------------------------". 

    DISPLAY "main (test15e) COB  input :" 1234567890123 .
    CALL "STEST905" USING BY VALUE 1234567890123.
    DISPLAY "main (test15e) COB return :" 1234567890123 .

    DISPLAY "--------------------------------------------------". 

    MOVE 1234567890123 TO PARM05.
*     MOVE 287 TO RPAR05H.
*     MOVE 19 TO RPAR05L.
    MOVE PARM05 TO WS-PARM05A.
    DISPLAY "main (test15e) COB  input : WS-PARM05A=" WS-PARM05A. 
    CALL "STEST906" USING BY VALUE PARM05.
    DISPLAY "main (test15e) COB return : WS-PARM05A=" WS-PARM05A. 

    DISPLAY "--------------------------------------------------". 

    MOVE 0 TO WRES01.
    MOVE WRES01 TO WERES01.
    DISPLAY "main (test15e) COB  input :" 5 ": Returning WRES01 (size short) ="
              WERES01 .
    CALL "STEST907" USING BY VALUE 5 RETURNING WRES01.
    MOVE WRES01 TO WERES01.
    DISPLAY "main (test15e) COB return :" 5 ": Returning WRES01 (size short) ="
              WERES01 .

    DISPLAY "--------------------------------------------------". 

    MOVE 0 TO WRES02.
    MOVE WRES02 TO WERES02.
    DISPLAY "main (test15e) COB  input :" 5 ": Returning WRES02 (size int)="
             WERES02.
    CALL "STEST908" USING BY VALUE 5 RETURNING WRES02.
    MOVE WRES02 TO WERES02.
    DISPLAY "main (test15e) COB return :" 5 ": Returning WRES02 (size int) ="
             WERES02 .

*    DISPLAY "--------------------------------------------------". 
*    MOVE 0 TO WRES05.
*    MOVE WRES05 TO WERES05.
*    DISPLAY "main (test15e) COB  input :" 5 ": Returning WERES05 (size long long)="
*                WERES05.
**    CALL "STEST909" USING BY VALUE 5 RETURNING WERES05.
*    CALL "STEST909" USING BY VALUE 5 RETURNING WRES05.
*    MOVE WRES05 TO WERES05.
*    DISPLAY "main (test15e) COB return :" 5 ": Returning WERES05 (size long long)="
*                WERES05.

    DISPLAY "--------------------------------------------------". 
    DISPLAY "main (test15e) COB  input : PARM02Z1=" PARM02Z1
            " PARM03Z1=" PARM03Z1
            " PARM04Z1=" PARM04Z1 " PARM05Z1=" PARM05Z1 . 
    CALL "STEST910" USING PARM02Z BY CONTENT PARM03Z 
            BY REFERENCE PARM04Z  BY CONTENT PARM05Z .
    DISPLAY "main (test15e) COB output : PARM02Z1=" PARM02Z1
            " PARM03Z1=" PARM03Z1
            " PARM04Z1=" PARM04Z1 " PARM05Z1=" PARM05Z1 . 

*    DISPLAY "--------------------------------------------------". 
    
    MOVE 5 TO RETURN-CODE.
    STOP RUN.
