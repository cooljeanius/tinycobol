 IDENTIFICATION DIVISION.
 PROGRAM-ID.    TEST09. 
 AUTHOR.        Rildo Pragana.
 DATE-WRITTEN.  November 13, 1999.
* REMARKS.
*    This is to exercise variables, specially
*    qualifying as in: var of parentvar of grandparentvar ...
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

 01         ARRAY-VAR     VALUE all "ABC".
   03       ARRAY-1     OCCURS 3.
    05      ARRAY-2     OCCURS 2.
      15    ITEM            PIC X.
      15    ITEM2           PIC XX.    
    05      ARRAY-2A    OCCURS 5.
      15    ITEM            PIC X.
 01         SOME-VALUES.
  03        V1      PIC 9(3)V99.
  03        V2      PIC X(30).
  03        A1      pic A(01).
  03        X6      pic X(06).
* 03        N1      usage is computational-3 pic 9(5)V9(3) value 123.45.
 
  01        FIELD1  PIC X(10) VALUE "1234567890".
  01        FIELD2  PIC X(20) VALUE ALL 'X'.
  01        FIELD3  PIC X(20) VALUE ALL 'Y'.
  01        FIELD4  PIC X(20) VALUE ALL 'Z'.
 
 PROCEDURE DIVISION.
    
*   move "35" to V1.
*    display "35 -> 9(3)V99 ==>" V1 "<"
*    stop run.
    
    DISPLAY "ARRAY-VAR is  [" ARRAY-VAR "]".
    MOVE "TEST" to V2.
    display "normal move '" V2 "'" .
    MOVE HIGH-VALUES TO V2.
    DISPLAY "high-values '" V2 "'".
    move low-values to V2.
    display "low-values  '" V2 "'".
    move all quotes to V2.
    display "quotes      '" V2 "'".
    move all "acbdef" to V2.
    display "all abcdef  '" V2 "'".
    move spaces  to V2.
    display "spaces      '" V2 "'".
    move all "-" to V2.
    display "all -       '" V2 "'".

    DISPLAY "Ref-mods tests begin".

    DISPLAY " ".
    DISPLAY "FIELD1          =" FIELD1 ";".
    DISPLAY "FIELD2 (before) =" FIELD2 ";".
    MOVE FIELD1(5:)  TO FIELD2.
    DISPLAY "-->MOVE FIELD1(5:) TO FIELD2".
    DISPLAY "FIELD2 (after)  =" FIELD2 ";".

    DISPLAY " ".
    DISPLAY "FIELD1          =" FIELD1 ";".
    DISPLAY "FIELD3 (before) =" FIELD3 ";".
    MOVE FIELD1(7:3)  TO FIELD3.
    DISPLAY "-->MOVE FIELD1(7:3) TO FIELD3".
    DISPLAY "FIELD3 (after)  =" FIELD3 ";".

    DISPLAY " ".
    DISPLAY "ARRAY-2 (1, 1)  =" ARRAY-2 (1, 1) ";".
    DISPLAY "FIELD4 (before) =" FIELD4 ";".
    MOVE ARRAY-2 (1, 1) (2:1)  TO FIELD4.
    DISPLAY "-->MOVE ARRAY-2 (1, 1) (2:1)  TO FIELD4".
    DISPLAY "FIELD4 (after)  =" FIELD4 ";".

    DISPLAY " ".
    DISPLAY "Ref-mods tests end".

    stop run.

