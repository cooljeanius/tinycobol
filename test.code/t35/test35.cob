 IDENTIFICATION DIVISION.
 PROGRAM-ID. test35.

 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.

 SPECIAL-NAMES.
      decimal-point is comma.
* INPUT-OUTPUT SECTION.

* FILE-CONTROL.
 DATA DIVISION.

 FILE SECTION.
 WORKING-STORAGE SECTION.
 
 
 01 car       pic x value spaces.
 01 num       pic s9(10)v999 value 0.
 01 txt       pic x(50) value spaces.
 01 int       pic 9(6) value 0.


 PROCEDURE DIVISION.

 PROGRAMA SECTION.
 PROGRAMA-ENTRY.
    move -1,23 to num.
    display "num	= " num. 
    move function abs (num) to num.
    display "abs(num)	= " num. 

    display " ".
    move -0,23 to num.
    display "num	= " num. 
    move function acos (num) to num.
    display "acos(num)  = " num. 

    display " ".
    move function annuity (5 , 2) to num.
    display "annuity(5 , 2) = " num. 

    display " ".
    move 0,9 to num.
    display "num	= " num. 
    move function asin (num) to num.
    display "asin(num)  = " num. 

    display " ".
    move 2,50 to num.
    display "num	= " num. 
    move function atan (num) to num.
    display "atan(num)  = " num. 

    display " ".
    move 2,50 to num.
    display "num	= " num. 
    move function cos (num) to num.
    display "cos(num)	= " num. 

    display " ".
    move function current-date to txt.
    display "current-date = " txt.

    display " ".
    move function date-of-integer(0) to txt.
    display "date-of-integer(0)    = " txt.
    move 500 to num.
    display "num	= " num. 
    move function date-of-integer(num) to txt.
    display "date-of-integer(num)  = " txt.

    display " ".
    move 520823 to num.
    display "num	= " num. 
    move function date-to-yyyymmdd(num) to txt.
    display "date-to-yyyymmdd(num) = " txt.
    move function date-to-yyyymmdd(num , 60) to txt.
    display "date-to-yyyymmdd(num,60) = " txt.

    display " ".
    move function day-of-integer(0) to txt.
    display "day-of-integer(0)    = " txt.
    move 500 to num.
    display "num	= " num. 
    move function day-of-integer(num) to txt.
    display "day-of-integer(num)  = " txt.

    display " ".
    move 52123 to num.
    display "num		    = " num. 
    move function day-to-yyyyddd(num) to txt.
    display "day-to-yyyyddd(num)    = " txt.
    move function day-to-yyyyddd(num , 60) to txt.
    display "day-to-yyyyddd(num,60) = " txt.

    display " ".
    move 10 to num.
    display "num	    = " num. 
    move function factorial(num) to num.
    display "factorial(num) = " num.

    display " ".
    move 10,23 to num.
    display "num	  = " num. 
    move function integer(num) to num.
    display "integer(num) = " num.
    move -10,23 to num.
    display "num	  = " num. 
    move function integer(num) to num.
    display "integer(num) = " num.

    display " ".
    move 20020813 to num.
    display "num		  = " num. 
    move function integer-of-date(num) to num.
    display "integer-of-date(num) = " num.
    move function date-of-integer(num) to num.
    display "date-of-integer(num) = " num.

    display " ".
    move 2002225 to num.
    display "num		  = " num. 
    move function integer-of-day(num) to num.
    display "integer-of-day(num)  = " num.
    move function day-of-integer(num) to num.
    display "day-of-integer(num)  = " num.


    display " ".
    move 10,23 to num.
    display "num	       = " num. 
    move function integer-part(num) to num.
    display "integer-part(num) = " num.
    move -10,23 to num.
    display "num	       = " num. 
    move function integer-part(num) to num.
    display "integer-part(num) = " num.

    display " ".
    move function length (txt) to num.
    display "length (txt)      = " num.

    display " ".
    move function log (225) to num.
    display "log (225)         = " num.

    display " ".
    move function log10 (225) to num.
    display "log10 (225)       = " num.

    display " ".
    move function lower-case ("THIS is a TEST with numbers 123") to txt.
    display 'lower-case ("THIS is a TEST with numbers 123") = ' txt.

    stop run.
