 IDENTIFICATION DIVISION.
* PROGRAM-ID. TEST02.
 program-id. TEST02.
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.
* SPECIAL-NAMES.
*    CURRENCY SIGN IS '@'.
* DECIMAL-POINT IS COMMA.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
* working-storage section.
* 01	W011-ADD		PIC 9(8). 
 01	W011-ADD.
   05	W011-ADD-1	PIC 9(8) VALUE 99777.
   05	W011-ADD-2	PIC 9(8). 
*   05	W011-ADD-1	PIC 9(8).
* 01	W011-SUB		PIC 9(8).
 01	W011-SUB.
   05	W011-ADD-3	PIC 9(8) VALUE 99888.


 01	W01-ADD		PIC 9(8).
 01	W01-SUB		PIC 9(8).
 01	W01-DIV		PIC 9(8).
 01	W01-MUL		PIC 9(8).
 01	W01-COMPUTE	PIC 9(8).
*	05 W05-HOUR	PIC 9(2).
*	05 W05-MIN	PIC 9(2).
*	05 W05-SEC	PIC 9(2).

* 01	W01-COMPUTE-E0	PIC 9(8) VALUE 30000.
 01	W01-COMPUTE-0	PIC 9(5)V99 USAGE COMP VALUE 98.54.
 01	W01-COMPUTE-1	PIC S9(5)V99 USAGE COMP VALUE 99876.
 01	W01-COMPUTE-E	PIC X(2),X(3) VALUE "**".
 01	W01-COMPUTE-E0	PIC 9(8) VALUE 30000.
 01	W01-COMPUTE-E1	PIC Z(5).Z(3) VALUE 330.
 01	W01-COMPUTE-E2	PIC *Z,ZZZ,ZZZ VALUE 444123.
 01	W01-COMPUTE-E3	PIC Z(3).Z(5).99 VALUE 555512.
 01	W01-COMPUTE-E4	PIC 9(5)V99 VALUE 6622.
 01	W01-COMPUTE-E5	PIC -Z(5),9(3).9 VALUE 7775.

* 01	W01-COMPUTE-E6 OCCURS 10 USAGE COMP.
 01	W01-COMPUTE-E6.
  05	W01-COMPUTE-E6-0 OCCURS 10 TIMES.
* 05	W01-COMPUTE-E6-0 OCCURS 10 TIMES USAGE COMP.
    10	W01-COMPUTE-E6-1	PIC S9(5)V99.
    10	W01-COMPUTE-E6-2	PIC S9(5)V99.
*    10	W01-COMPUTE-E6-1	PIC S9(5)V99 VALUE 199876.
*    10	W01-COMPUTE-E6-2	PIC S9(5)V99 VALUE 299876.

 01     W01-COMPUTE-E7.
    10	W01-COMPUTE-E7-1	PIC S9(5)V99 USAGE COMP VALUE 199876.
    10	W01-COMPUTE-E7-2	PIC S9(5)V99 USAGE COMP VALUE 299876.

 01	W01-COMPUTE-E8	PIC $Z(5).9(2) VALUE 7775.

 01     IDX1                       PIC  99 VALUE 1.
 01     IDX2                       PIC  99 VALUE 1.
 01     IDX3                       PIC  99 VALUE 1 COMP.
* 01     IDX1                       PIC  99 VALUE 1.
* 01     IDX2                       PIC  99 VALUE 1.

 01     TABEL-A.
       10    TAB-A OCCURS 20 TIMES    PIC 9(05).

 01     TABEL-B.
    05    TAB-B1 OCCURS 10 TIMES INDEXED BY X1.
       10    TAB-B2 OCCURS 20 TIMES INDEXED BY X2.
         15    TAB-B3                  PIC 9(05).
         15    TAB-B4                  PIC 9(05).
*    05    TAB-B1 OCCURS 10 TIMES.
*       10    TAB-B2 OCCURS 20 TIMES.

 01     TABEL-C.
    05    TAB-C1 OCCURS 10 TIMES INDEXED BY C1.
       10    TAB-C2 OCCURS 20 TIMES INDEXED BY C2.
         15    TAB-C3 OCCURS 320 TIMES INDEXED BY C3.
           25  TAB-C4                  PIC 9(05).
           25  TAB-C5                  PIC 9(05).

 01     TABEL-D.
    05    TAB-D1 OCCURS 10 TIMES.
         15    TAB-D2                  PIC 9(05).

 01     TABEL-Z.
    05    TAB-Z1 OCCURS 10 TIMES
*                 ASCENDING KEY IS TAB-Z3 
                 INDEXED BY Z1.
         15    TAB-Z3                  PIC 9(05).
         15    TAB-Z4                  PIC 9(05).
*    05    TAB-Z1 OCCURS 10 TIMES.
*       10    TAB-Z2 OCCURS 20 TIMES INDEXED BY Z2.


 COPY 'TEST02.cpy' . 
* COPY TEST02. 
* copy TEST02C REPLACING 
 copy 'TEST02C.cpy' REPLACING 
      W01-COMPUTE-D BY W01-COMPUTE-DD,
      ==X(2)== BY ==X(04)== .


PROCEDURE DIVISION.

A-000.

*  READY TRACE.
 
 PERFORM A-100A.
 PERFORM A-100.
 PERFORM A-300 THRU A-400.
 PERFORM A-100B.
 MOVE  1 TO IDX1.
* PERFORM A-500 UNTIL IDX1 > 20.
*  PERFORM A-500 3 TIMES.
* PERFORM A-500 VARYING IDX1 FROM 1 BY 3
*         UNTIL IDX1 > 20.

 SET C2 TO 19.
 SET C3 TO 20.
 PERFORM A-600 VARYING C1 FROM 1 BY 3 UNTIL C1 > 10.
*         AFTER C2 FROM 1 BY 3 UNTIL C2 > 20.
*         AFTER C3 FROM 1 BY 3 UNTIL C3 > 32.

*  RESET TRACE.

 STOP RUN.

A-100A.

 DISPLAY "ENTER A-100A".

 MOVE IDX1 TO TAB-A(IDX1).
 ADD  1 TO IDX1.
 MOVE IDX1 TO TAB-A(IDX1).

 MOVE 0 TO X2.
 ADD  1 TO X2.
 MOVE 1 TO X1.
 MOVE 33 TO TAB-B3(X1, X2).
 MOVE 44 TO TAB-B4(X1, X2).

* SET C1 TO 1.
* SET C2 TO IDX1.
* SET C2 TO C1.
* SET C1 DOWN BY 1.
* SET C2 UP BY IDX1.

* MOVE 1 TO C1.
* MOVE 1 TO C2.
* MOVE 1 TO C3.

* MOVE 9 TO C1.
* MOVE 19 TO C2.
* MOVE 299 TO C3.

 SET Z1 TO 9.
 SET C1 TO Z1.
 SET C2 TO 19.
 SET C3 TO 20.

 SET C1 DOWN BY 2.
 SET C2 DOWN BY 9.
 SET C3 UP BY 8.

 MOVE 123456 TO TAB-C5(C1, C2, C3).
 MOVE 789012 TO TAB-C4(C1, C2, C3).

 SET Z1 TO 10.
 SET Z1 DOWN BY 9.
* MOVE 1 TO Z1.
 MOVE 3 TO TAB-Z3(Z1).
 MOVE 4 TO TAB-Z4(Z1).

 DISPLAY "EXIT  A-100A".


A-100.

 DISPLAY "ENTER A-100".
 IF ((X1 > IDX1) AND (X2 > IDX2))
   DISPLAY "TRUE:((X1 > IDX1) AND (X2 > IDX2)): " X1 " , " IDX1 " , " X2 " , " IDX2
 ELSE
   DISPLAY "FALSE:((X1 > IDX1) AND (X2 > IDX2)): " X1 " , " IDX1 " , " X2 " , " IDX2.
   
* PERFORM A-100B VARYING IDX1 FROM 1 BY 1 UNTIL IDX1 > 20.
* MOVE 1 TO IDX2.
* MOVE 124 TO (IDX1).
* MOVE 555 TO TAB-A (5).
* MOVE 124 TO TAB-B3(IDX1, IDX2).
* MOVE 124 TO TAB-B3(IDX1,IDX2).
* MOVE 124 TO TAB-B3 (IDX1,IDX2).

 DISPLAY "EXIT  A-100".


A-100B.

 DISPLAY "ENTER A-100B".

 MOVE  1 TO IDX1.
 DISPLAY "TAB-A (IDX1 = " IDX1 ") = " TAB-A(IDX1) ";" UPON CONSOLE.
* DISPLAY "TAB-A (IDX1 - 1 = " IDX1 - 1 ")  = " TAB-A(IDX1 - 1) ";".
 ADD  1 TO IDX1.
 DISPLAY "TAB-A (IDX1 = " IDX1 ") = " TAB-A(IDX1) ";" UPON CONSOLE.
* DISPLAY "TAB-A (5)   = " TAB-A (5).

 DISPLAY "TAB-B3 (X1 = " X1 ", X2 = " X2  ") = " TAB-B3(X1, X2) ";" UPON STD-ERROR.
 DISPLAY "TAB-B4 (X1 = " X1 ", X2 = " X2  ") = " TAB-B4(X1, X2) ";" UPON STD-ERROR.
 
 DISPLAY "TAB-C5 (C1 = " C1 ", C2 = " C2 ", C3 = " C3 ") = " TAB-C5(C1, C2, C3) ";" upon STD-ERROR.
 DISPLAY "TAB-C4 (C1 = " C1 ", C2 = " C2 ", C3 = " C3 ") = " TAB-C4(C1, C2, C3) ";" upon STD-ERROR.


 DISPLAY "TAB-Z3 (Z1 = " Z1 ") = " TAB-Z3(Z1) ";" upon STD-OUTPUT.
 DISPLAY "TAB-Z4 (Z1 = " Z1 ") = " TAB-Z4(Z1) ";" upon STD-OUTPUT.
 
 DISPLAY "EXIT  A-100B".


A-300.

 DISPLAY "ENTER A-300".

 MOVE 100 TO W01-ADD W01-SUB W01-DIV W01-MUL.
 ADD 10 TO W01-ADD.
 DISPLAY "100 + 10 = " W01-ADD.
 SUBTRACT 10 FROM W01-SUB.
 DISPLAY "100 - 10 = " W01-SUB.
 DIVIDE W01-DIV BY 10 GIVING W01-DIV.
 DISPLAY "100 / 10 = " W01-DIV.
 MULTIPLY W01-MUL BY 10 GIVING W01-MUL.
 DISPLAY "100 * 10 = " W01-MUL.
 COMPUTE W01-COMPUTE = (( 100 * 10 ) / ( 9 - 3 )).
 DISPLAY "(( 100 * 10 ) / ( 9 - 3 )) = " W01-COMPUTE.

 DISPLAY "EXIT  A-300".


A-400.

 DISPLAY "ENTER A-400".

* MOVE W01-COMPUTE-E0 TO W01-COMPUTE-E1 W01-COMPUTE-E2 W01-COMPUTE-E3 W01-COMPUTE-E4.
 DISPLAY "W01-COMPUTE-0  = " W01-COMPUTE-0.
 DISPLAY "W01-COMPUTE-1  = " W01-COMPUTE-1.
 DISPLAY "W01-COMPUTE-E  = " W01-COMPUTE-E.
 DISPLAY "W01-COMPUTE-E0 = " W01-COMPUTE-E0.
 DISPLAY "W01-COMPUTE-E1 = " W01-COMPUTE-E1.
 DISPLAY "W01-COMPUTE-E2 = " W01-COMPUTE-E2.
 DISPLAY "W01-COMPUTE-E3 = " W01-COMPUTE-E3.
 DISPLAY "W01-COMPUTE-E4 = " W01-COMPUTE-E4.
 DISPLAY "W01-COMPUTE-E5 = " W01-COMPUTE-E5.
 DISPLAY "W01-COMPUTE-E8 = " W01-COMPUTE-E8.

 MOVE W01-COMPUTE-0 TO W01-COMPUTE-E5.
 DISPLAY "W01-COMPUTE-0  = " W01-COMPUTE-E5.
 MOVE W01-COMPUTE-1 TO W01-COMPUTE-E5.
 DISPLAY "W01-COMPUTE-1  = " W01-COMPUTE-E5.

 DISPLAY "EXIT  A-400".

A-500.

 DISPLAY "ENTER A-500".

 MOVE IDX1 TO TAB-D2(IDX1).
 DISPLAY "TAB-D2 (IDX1 = " IDX1 ") = " TAB-D2(IDX1) ";".
* ADD  1 TO IDX1.
 
 DISPLAY "EXIT  A-500".

A-600.

 DISPLAY "ENTER A-600".

 MOVE 123456 TO TAB-C5(C1, C2, C3).
 DISPLAY "TAB-C5 (C1 = " C1 ", C2 = " C2 ", C3 = " C3 ") = " TAB-C5(C1, C2, C3) ";".
 
 DISPLAY "EXIT  A-600".


* STOP RUN.
