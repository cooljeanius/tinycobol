 IDENTIFICATION DIVISION.
 PROGRAM-ID. test28a.
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

    77      TPTR    pic Z(5)9.
    
 LINKAGE SECTION.
    77   PTR1   usage pointer.
    77   PTR2   usage pointer.
    77   TMP     pic X(40).
    01   LS-BLOCK.
     05  BLOCK-1    pic X(14).
     05  BLOCK-2.
      10 BLOCK-2A   pic X(16).
      10 BLOCK-2B   pic X(10).
    01   LS-ARRAY.
     05  FILLER OCCURS 4.
      10 ITEM PIC X(10).

 PROCEDURE DIVISION USING PTR1 PTR2 TMP. 
   
    display "Received:            [" TMP "]".
    set address of TMP to PTR1.
    display "After first change:  [" TMP "]".
    set address of TMP to PTR2.
    display "After second change: [" TMP "]".
***** example of non-argument linkage section variable
    display "----------------------------------------"
    set address of LS-BLOCK to PTR1
    perform 10-display-blk.
    display "----------------------------------------"
    set address of LS-BLOCK to PTR2 
    perform 10-display-blk.
    display "----------------------------------------"
    set address of LS-ARRAY to PTR2 
    display "ITEM(1) = [" ITEM(1) "]"
    display "ITEM(2) = [" ITEM(2) "]"
    display "ITEM(3) = [" ITEM(3) "]"
    display "ITEM(4) = [" ITEM(4) "]"
    display "----------------------------------------"
***** now some pointer arithmetic    
    subtract PTR1 from PTR2.
    move PTR2 to TPTR.
    display "Diff of the two pointers: " TPTR.
    exit program. 
    
 10-display-blk.
    display "BLOCK-1 : [" BLOCK-1 "]".
    display "BLOCK-2A: [" BLOCK-2A "]".
    display "BLOCK-2B: [" BLOCK-2B "]".

