 IDENTIFICATION DIVISION.
 PROGRAM-ID.    tdb02.  
 AUTHOR. Rildo Pragana.         
* REMARKS.
*    Example PostgreSQL interface program for Cobol.
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

    77  DATABASE-NAME   PIC X(80).
    77  SQL-QUERY       PIC X(200).
    77  DB-HANDLE       PIC 9(12) COMP.
    77  QRY-HANDLE      PIC 9(12) COMP.
    77  NTUPLE          PIC 9(12) COMP.
    77  NFIELD          PIC 9(12) COMP.
    77  MAX-TUPLE       PIC 9(12) COMP.
    77  MAX-FIELD       PIC 9(12) COMP.
    77  COLUMN-VALUE    pic X(80) VALUE SPACES.
    01  TUPLE.
     05 PNOME           PIC X(50).
     05 PPRECO          PIC X(20).
    77  NEW-DB-NAME     PIC X(40) value "mydatabase".
    77  CMD             pic 9.
    77  DB-STATUS       pic 9(12) COMP.
    77  DB-MESSAGE      pic X(200).
    01  MYTBL-RECORD.
     05 MYTBL-NAME      pic X(40).
     05 MYTBL-ADDR      pic X(50).
     05 MYTBL-PHONE     pic X(15).
    
 PROCEDURE DIVISION.
 010-LOOP.
    display "======= M E N U ======="
    display "1- create mydatabase"
    display "2- drop mydatabase"
    display "3- create mytable"
    display "4- insert into mytable"
    display "5- drop mytable"
    display "6- select mytable"
    display "7- perform tests with 'loja' database".
    display "0- end program"
    accept CMD
    
    evaluate CMD
    when 1
        perform 070-CONNECT-TEMPLATE
        string "create database " NEW-DB-NAME ";;" into SQL-QUERY
        perform 090-DO-QUERY
        call "sql_clear_query" using QRY-HANDLE
        perform 050-DISCONNECT
    when 2
        perform 070-CONNECT-TEMPLATE
        string "drop database " NEW-DB-NAME ";;" into SQL-QUERY
        perform 090-DO-QUERY
        call "sql_clear_query" using QRY-HANDLE
        perform 050-DISCONNECT
    when 3
        perform 080-CONNECT-MYDB 
        string "create table mytable", 
            " ( name char(40), address char(50), phone char(15) );;" 
            into SQL-QUERY
        perform 090-DO-QUERY
        call "sql_clear_query" using QRY-HANDLE
        perform 050-DISCONNECT
    when 4
        perform 080-CONNECT-MYDB 
        perform 060-ACCEPT-MYTBL
        string "insert into mytable " 
            "values ( '" MYTBL-NAME
            "','" MYTBL-ADDR
            "','" MYTBL-PHONE
            "' );;" 
            into SQL-QUERY
        perform 090-DO-QUERY
        call "sql_clear_query" using QRY-HANDLE
        perform 050-DISCONNECT
    when 5
        perform 080-CONNECT-MYDB 
        move "drop table mytable;;" to SQL-QUERY
        perform 090-DO-QUERY
        call "sql_clear_query" using QRY-HANDLE
        perform 050-DISCONNECT
    when 6
        perform 080-CONNECT-MYDB 
        move "select * from mytable;;" to SQL-QUERY
        perform 090-DO-QUERY
        perform 300-SHOW-TUPLES
        call "sql_clear_query" using QRY-HANDLE
        perform 050-DISCONNECT
    when 7
        perform 100-LOJA-TESTS
    when 0 
        stop run
    when other
        display "Unknown command!"
    end-evaluate.
    go to 010-LOOP.
   
 050-DISCONNECT.
        call "sql_disconnect_db" using DB-HANDLE.

 060-ACCEPT-MYTBL.
        display "Name: " no advancing
        accept MYTBL-NAME
        display "Address: " no advancing
        accept MYTBL-ADDR
        display "Phone: " no advancing
        accept MYTBL-PHONE.
    
 070-CONNECT-TEMPLATE.
        move "template1" to DATABASE-NAME.
        call "sql_connect_db" using DATABASE-NAME DB-HANDLE DB-STATUS.
        if DB-STATUS not = zeros
            display "Error in database connection!"
            stop run.
    
 080-CONNECT-MYDB.
        move "mydatabase" to DATABASE-NAME.
        call "sql_connect_db" using DATABASE-NAME DB-HANDLE DB-STATUS.
        if DB-STATUS not = zeros
            display "Error in database connection!"
            stop run.
  
 090-DO-QUERY.
        display "Query: " SQL-QUERY
**** A query is a cobol string terminated with ";;", so this substring
**** cannot appear in any fields data. DB-STATUS have two types of
**** valid returned values: 1 or 2 (PGRES_COMMAND_OK or PGRES_TUPLES_OK)
**** depending on the kind of query executed.
        call "sql_exec_query" using DB-HANDLE SQL-QUERY QRY-HANDLE DB-STATUS
        perform 200-CHECK-STATUS.

    100-LOJA-TESTS.
**** This example only works if 'loja.sql' is inserted into the
**** running postgresql server. Please refer to psql manual to
**** see how to get it done.

******* Step 1: connect to the database
        move "loja" to DATABASE-NAME.
        call "sql_connect_db" using DATABASE-NAME  DB-HANDLE DB-STATUS.
        display "connection done!".
 
******* Step 2: start a query, returning a query handle. 
        move "select pnome,ppreco from produto;;" to SQL-QUERY.
        call "sql_exec_query" using DB-HANDLE SQL-QUERY QRY-HANDLE DB-STATUS.
        perform 200-CHECK-STATUS
    
******* Step 3: get some results from the query.
        move zeros to NTUPLE NFIELD
        move spaces to COLUMN-VALUE
        call "sql_get_value" using QRY-HANDLE NTUPLE NFIELD COLUMN-VALUE   
        display "First tuple, first attribute:[" COLUMN-VALUE "]".
       
        add 1 to NFIELD
        move spaces to COLUMN-VALUE
        call "sql_get_value" using QRY-HANDLE NTUPLE NFIELD COLUMN-VALUE   
        display "First tuple, second attribute:[" COLUMN-VALUE "]".

******* Step 3a (optional): read max values from the query handle.
        call "sql_max_tuple" using QRY-HANDLE MAX-TUPLE.
        call "sql_max_field" using QRY-HANDLE MAX-FIELD.
        display "Max tuple: " MAX-TUPLE ", Max field: " MAX-FIELD.
   
******* Step3b: other way to get the tuples.
        display "*********************************************************"
        move zero to NTUPLE
        perform until NTUPLE = MAX-TUPLE
            call "sql_get_tuple" using QRY-HANDLE NTUPLE TUPLE 
            display TUPLE 
            add 1 to NTUPLE
        end-perform

******* Step 4: release query handle after finishing.
        call "sql_clear_query" using QRY-HANDLE.

******* Step 5: disconnect from the database server.
        call "sql_disconnect_db" using DB-HANDLE.
 
 200-CHECK-STATUS.
        display "DB-STATUS = " DB-STATUS.
        if (DB-STATUS not = 1 and DB-STATUS  not = 2)
            move spaces to DB-MESSAGE
**** please use a large (say pic X(200)) to receive the returned
**** message from the postgresql server, or your memory may be
**** corrupted.
            call "sql_status_message" using DB-HANDLE DB-MESSAGE
            display DB-MESSAGE.

 300-SHOW-TUPLES.
        call "sql_max_tuple" using QRY-HANDLE MAX-TUPLE.
        call "sql_max_field" using QRY-HANDLE MAX-FIELD.
        display "Max tuple: " MAX-TUPLE ", Max field: " MAX-FIELD.
        display "*********************************************************"
        move zero to NTUPLE
        perform until NTUPLE = MAX-TUPLE
            call "sql_get_tuple" using QRY-HANDLE NTUPLE MYTBL-RECORD
            display MYTBL-RECORD
            add 1 to NTUPLE
        end-perform.

