 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST27.
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
    SELECT sales-file
         ASSIGN TO "sales.dat"
         ORGANIZATION IS LINE SEQUENTIAL 
         ACCESS MODE  IS SEQUENTIAL.
    SELECT printing-file
         ASSIGN TO "printing.text".

 DATA DIVISION.
 FILE SECTION.
    FD sales-file.
    01 sales-record.
     05     sales-vendor-name      pic X(20).
     05     sales-value            pic S9(6).
     05     sales-number           pic X(6).
     05     sales-type             pic X.
     05     sales-vendor-region    pic X(17).
     05     sales-vendor-city      pic X(20).

    FD printing-file
        report is sales-report.
    01 filler   pic X(133).
    
 WORKING-STORAGE SECTION.
    77      data-end-flag       pic X(3).    
*    77      page-counter        pic S999.
    01      transaction-area.
     05     vendor-name-tr      pic X(20).
     05     value-tr            pic S9(6).
     05     number-tr           pic X(6).
     05     type-tr             pic X.
     05     vendor-region-tr    pic X(17).
     05     vendor-city-tr      pic X(20).
     
 REPORT SECTION.
 RD sales-report
    controls are final vendor-city-tr vendor-name-tr
    page limit is 50 lines
    heading 1
    first detail 5
    last detail 45
    footing 48.
  01    type is page heading.
   05   line number 1.
    10  column number 61 pic X(4)
            value 'Page'.
    10  column number 66 pic ZZZZZ9
            source page-counter.
   05   line number + 2.
    10  column number 22 pic X(31)
            value 'Control break example'.
  01    type is control heading vendor-city-tr.
   05   line number 5.
    10  column number 25 pic X(18)
            value 'Sales in the city of'.
    10  column number 44 pic X(20)
            source vendor-city-tr.
   05   line number 7.
    10  column number 6 pic X(8)
            value 'Salesperson'.
    10  column number 24 pic X(13)
            value 'Transaction #'.
    10  column number 40 pic X(7)
            value 'Value'.
  01    transaction-line type is detail.
   05   line number plus 1.
    10  column number 2 pic X(20)
            source vendor-name-tr.
    10  column number 27 pic X(6)
            source number-tr.
  01    type is control footing vendor-name-tr.
   05   line number plus 1.
    10  column number 4 pic X(15)
            value 'Salesperson total'.
    10  vendor-total
            column number 48 pic $$$,$$9
                sum value-tr.
  01    type is control footing vendor-city-tr.
   05   line number plus 2.
    10  column number 48 pic X(10)
            value '..........'.
*            value all '.'.
   05   line number plus 1.
    10  column number 4 pic X(14)
            value 'City total'.
    10  city-total
            column number 48 pic $$$,$$9
            sum vendor-total.
  01    type is control footing final.
   05   line number plus 5.
    10  column number 10 pic X(29)
            value '... Grand Total of all cities'.
    10  column number 40 pic $$$,$$9
                sum city-total.

 PROCEDURE DIVISION.
 10-create-report.
        open input sales-file
        open output printing-file 
        move 'no' to data-end-flag.
        initiate sales-report
        read sales-file into transaction-area
            at end
                move 'yes' to data-end-flag.
        perform 20-process-total-transaction
            until data-end-flag = 'yes'.
        terminate sales-report
        close sales-file
        close printing-file
        stop run.
 20-process-total-transaction.
        perform 30-display-record
        generate transaction-line
        read sales-file into transaction-area
            at end
                move 'yes' to data-end-flag.
 30-display-record.
        display "---------------------------------------"
        display "Salesperson: " vendor-name-tr
        display "Value: " value-tr
        display "Number: " number-tr
        display "Type: " type-tr
        display "Region: " vendor-region-tr
        display "City: " vendor-city-tr.

