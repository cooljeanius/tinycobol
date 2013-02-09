 IDENTIFICATION DIVISION.
 PROGRAM-ID.    report_example.  
 AUTHOR. Rildo Pragana.         
* REMARKS.
*    Example report.
*
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.             
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
    SELECT sales-file
         ASSIGN TO "sales.dat"
         ORGANIZATION IS LINE SEQUENTIAL 
         ACCESS MODE  IS SEQUENTIAL.

 DATA DIVISION.
 FILE SECTION.
    FD sales-file.
    01 sales-record.
     05     sales-vendor-name      pic X(20).
     05     sales-value            pic S9(6).
     05     sales-number           pic X(13).
     05     sales-type             pic X.
     05     sales-vendor-region    pic X(17).
     05     sales-vendor-city      pic X(20).
     05     sales-comments         pic X(60).

 WORKING-STORAGE SECTION.
    77      data-end-flag       pic X.    
    77      REPORT-OUTPUT-NAME  pic X(80).
    77      REPORT-LAYOUT-NAME  pic X(80).
    77      END-OF-STRING       pic X value low-values.
 
  01      transaction-dsp.
* This is temporary fix due to some bug in the preprocessor
* which causes a seg fault.
*    COPY displayable.
    COPY 'displayable.cpy'.
  77      transaction-eos    pic X value low-values.
  01      totals-accumulators.
     05     vendor-total        pic 9(12) comp.
     05     city-total          pic 9(12) comp.
     05     region-total        pic 9(12) comp.
     05     grand-total         pic 9(12) comp.
 
 PROCEDURE DIVISION.

  move zeros to vendor-total city-total region-total
  string "repoutput.pdf" END-OF-STRING into REPORT-OUTPUT-NAME 
  string "report.layout" END-OF-STRING into REPORT-LAYOUT-NAME
  CALL "rep_initiate" using REPORT-OUTPUT-NAME REPORT-LAYOUT-NAME.
*
  open input sales-file
  move 'N' to data-end-flag
  read sales-file
  perform 200-CONV-DISPLAY
  perform 100-GENERATE
    until data-end-flag = 'Y'.
  close sales-file
  perform 200-CONV-DISPLAY
  call "rep_terminate" 
*  display "vendor-total = " vendor-total ", city-total = " city-total
  STOP RUN.

  100-GENERATE.
  perform 200-CONV-DISPLAY
*  display "COBOL record: [" transaction-dsp "]"
  call "rep_generate" using transaction-dsp vendor-total
        city-total region-total grand-total-dsp
  add  sales-value to 
      vendor-total, city-total, region-total, grand-total
    read sales-file
    at end
        move 'Y' to data-end-flag.
  
  200-CONV-DISPLAY.
  move sales-vendor-name   to vendor-name-dsp   
  move sales-value         to value-dsp
  move sales-number        to number-dsp
  move sales-type          to type-dsp
  move sales-vendor-region to vendor-region-dsp
  move sales-vendor-city   to vendor-city-dsp
  move sales-comments      to comments-dsp
  move vendor-total        to vendor-total-dsp
  move city-total          to city-total-dsp  
  move region-total        to region-total-dsp
  move grand-total         to grand-total-dsp
  .

