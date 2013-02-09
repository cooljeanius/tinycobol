 IDENTIFICATION DIVISION.
 PROGRAM-ID.     test15a.
 AUTHOR.         D. Essex.
 DATE-WRITTEN.   Dec. 5, 1999.
* REMARKS. test for called COBOL program. 
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

 01 C3-A         PIC 9(2).
 01 WS1          PIC 9(2) COMP VALUE 23.

 LINKAGE SECTION.

 01 C1           PIC X(6).
 01 C2           PIC 9(2).
 01 C3           PIC 9(2) COMP.
 01 C4           PIC 9(3).

 PROCEDURE DIVISION USING C1 C2 C3 C4.
* PROCEDURE DIVISION.

 A100.

   MOVE C3 TO C3-A.
   DISPLAY "sub  (test15a) COB input  :" C1 ":" C2 ":" C3-A ":" C4 ":".

   MOVE 'abcdef' TO C1.
   MOVE 12 TO C2.
*   MOVE 16 TO C3.
*   MOVE C3 TO C3-A.
*   MOVE 16 TO C3-A.
   MOVE 16 TO C3-A.
   MOVE C3-A TO C3.
   MOVE 22 TO C4.
   
   MOVE 7 TO RETURN-CODE.
   
   DISPLAY "sub  (test15a) COB return :" C1 ":" C2 ":" C3-A  ":" C4 ":".

*   MOVE WS1 TO C3-A.
*   DISPLAY "sub  (test15a) COB WS1=" C3-A ":".
  
 
 EXIT PROGRAM.
