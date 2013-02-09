 IDENTIFICATION DIVISION.
 PROGRAM-ID.    tdb01a.  
 AUTHOR. Rildo Pragana.         
*
* ISAM schema proof of concept, using BDB.
*
* Author:      Rildo Pragana.         
* Modified by: David Essex.
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.
 77  datafile pic x(80).
 77  len1     pic 9(9) comp.
 77  len2     pic 9(9) comp.
 77  len3     pic 9(9) comp.
 77  sel      pic 9(9) comp.
 01  dt-rec.
  05 dt-name  pic x(40).
  05 dt-phone pic x(20).
  05 dt-city  pic x(20).

 PROCEDURE DIVISION.
 display "* libdb test program tdb01"
 
 move length of dt-rec to len1
 move length of dt-name to len2
 move length of dt-city to len3
 
 string "filedb01" low-value into datafile
 call "tcdb_open" using datafile len1
 
* add some records
 move "Rildo Pragana" to dt-name
 move "Camaragibe" to dt-city
 move "3459-1776" to dt-phone
 call "tcdb_put2" using len1 dt-rec len2 dt-name len3 dt-city 
 
 move "Lilian T. Melo" to dt-name
 move "Recife" to dt-city
 move "3251-3912" to dt-phone
 call "tcdb_put2" using len1 dt-rec len2 dt-name len3 dt-city 
 
 move "Bruno Montenegro" to dt-name
 move "Sao Lourenco" to dt-city
 move "3459-1234" to dt-phone
 call "tcdb_put2" using len1 dt-rec len2 dt-name len3 dt-city 
 
* select the first index
 move 0 to sel
 display "* using first index"
* retrieve some records back
 move "Lilian T. Melo" to dt-name
 call "tcdb_qry" using sel len2 dt-name len1 dt-rec
 display dt-rec
 
 move "Rildo Pragana" to dt-name
 call "tcdb_qry" using sel len2 dt-name len1 dt-rec
 display dt-rec
 
 move "Lilian T. Melo" to dt-name
 call "tcdb_qry" using sel len2 dt-name len1 dt-rec
 display dt-rec
 
 move "Bruno Montenegro" to dt-name
 call "tcdb_qry" using sel len2 dt-name len1 dt-rec
 display dt-rec
 
* select the second index
 move 1 to sel
 display "* using second index"

* retrieve some records back by the city
 move "Recife" to dt-city
 call "tcdb_qry" using sel len3 dt-city len1 dt-rec
 display dt-rec

 move "Camaragibe" to dt-city
 call "tcdb_qry" using sel len3 dt-city len1 dt-rec
 display dt-rec

 move "Sao Lourenco" to dt-city
 call "tcdb_qry" using sel len3 dt-city len1 dt-rec
 display dt-rec


 call "tcdb_close".

 stop run.
