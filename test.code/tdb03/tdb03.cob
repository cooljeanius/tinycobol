 IDENTIFICATION DIVISION.
 PROGRAM-ID.    tdb03.  
 AUTHOR. Rildo Pragana.         
* REMARKS.
*    Example PostgreSQL interface program for Cobol
*    with CGI access.
*
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION. 
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
       SELECT HTML-FORM   ASSIGN TO "./form.html" 
            ORGANIZATION IS LINE SEQUENTIAL
            ACCESS MODE  IS SEQUENTIAL
            FILE STATUS IS FS.

 DATA DIVISION.
    FILE SECTION.
    FD HTML-FORM.
    01 HTML-LINE    PIC X(80).
*
 WORKING-STORAGE SECTION.

    77      WS-MARK         pic XX value "##".
*    77      IX              pic 9(5) COMP.
    77      VN1             pic 9(3).
    77      VN2             pic 9(3).
    77      VN3             pic 9(3).
    77      FS              PIC 99.
    77      DATABASE-NAME   PIC X(80).
    77      SQL-QUERY       PIC X(200).
    77      DB-HANDLE       PIC 9(12) COMP.
    77      QRY-HANDLE      PIC 9(12) COMP.
    77      NTUPLE          PIC 9(12) COMP.
    77      NFIELD          PIC 9(12) COMP.
    77      MAX-TUPLE       PIC 9(12) COMP.
    77      MAX-FIELD       PIC 9(12) COMP.
    77      COLUMN-VALUE    pic X(80) VALUE SPACES.
    01      TUPLE.
     05     PNOME           PIC X(50).
     05     PPRECO          PIC X(20).
    77      NEW-DB-NAME     PIC X(40) value "mydatabase".
    77      CMD             pic 9.
    77      DB-STATUS       pic 9(12) COMP.
    77      DB-MESSAGE      pic X(200).
    01      MYTBL-RECORD.
     05     MYTBL-NAME      pic X(40).
     05     MYTBL-ADDR      pic X(50).
     05     MYTBL-PHONE     pic X(15).
    77      CGI-RESULT      pic 9(12) comp.
    77      CGI-NAME        pic X(80).
    77      CGI-VALUE       pic X(200).
    77      WS-CGI-CMD      pic X(6).
    01      HTML-LINE-CHARS.
     05     HTML-ENTRY occurs 80 indexed by IX.
      10    HTML-CHAR pic X.
    01      FORM-ITEMS-SIZES-ENTRIES.
     05     FILLER  PIC X(18) VALUE "name           020".
     05     FILLER  PIC X(18) VALUE "address        050".
     05     FILLER  PIC X(18) VALUE "phone          015".
     05     FILLER  PIC X(18) VALUE "cmd            010".
    01      FORM-ITEMS-SIZES redefines FORM-ITEMS-SIZES-ENTRIES.
     05     FORM-ITEM-SIZE-ENTRY occurs 20 times indexed by IXSZ.
      10    FORM-ITEM-NAME  pic X(15).
      10    FORM-ITEM-SIZE  pic 9(03).
    77      WS-ITEM-NAME    pic X(15).
    77      END-OF-STRING   pic X value LOW-VALUES.

 PROCEDURE DIVISION.
    display "Content-type: text/html"
    display END-OF-STRING

    call "cgi_init" using CGI-RESULT
    if CGI-RESULT not = zero
        display "Error reading CGI variables!"
        stop run.
    perform 010-CGI-COMMAND.
    call "cgi_quit"
    stop run.
    
    
 010-CGI-COMMAND.
        move spaces to CGI-VALUE
        move "cmd" to CGI-NAME
        call "cgi_get_string" using CGI-NAME CGI-VALUE
        move CGI-VALUE(1:6) to WS-CGI-CMD
        evaluate WS-CGI-CMD
        when "test  "
            perform 400-INSERT-HTML thru 410-INSERT-HTML
        when "listdb"
            perform 030-LIST-MYTABLE
        when "insert"
            perform 020-INSERT-MYTABLE
        when "select"
            perform 025-SELECT-MYTABLE
        when "clear "
            perform 035-CLEAR-FORM
        when other
            perform 400-INSERT-HTML thru 410-INSERT-HTML
        end-evaluate.
    
 020-INSERT-MYTABLE.
        display "<!--"
        perform 080-CONNECT-MYDB 
        move spaces to CGI-VALUE
        move "name" to CGI-NAME
        call "cgi_get_string" using CGI-NAME CGI-VALUE
        move CGI-VALUE to MYTBL-NAME
        move spaces to CGI-VALUE
        move "address" to CGI-NAME
        call "cgi_get_string" using CGI-NAME CGI-VALUE
        move CGI-VALUE to MYTBL-ADDR
        move spaces to CGI-VALUE
        move "phone" to CGI-NAME
        call "cgi_get_string" using CGI-NAME CGI-VALUE
        move CGI-VALUE to MYTBL-PHONE
        string "insert into mytable " 
            "values ( '" MYTBL-NAME
            "','" MYTBL-ADDR
            "','" MYTBL-PHONE
            "' )" END-OF-STRING 
            into SQL-QUERY
        perform 090-DO-QUERY
        call "sql_clear_query" using QRY-HANDLE
        perform 050-DISCONNECT
        display "-->"
        perform 400-INSERT-HTML thru 410-INSERT-HTML
        .
   
 025-SELECT-MYTABLE.
**** leave all postgresql communication log in a html comment
        display "<!--"
        perform 080-CONNECT-MYDB 
        move spaces to CGI-VALUE
        move "name" to CGI-NAME
        call "cgi_get_string" using CGI-NAME CGI-VALUE
        move CGI-VALUE to MYTBL-NAME
        string "select * from mytable where name = '" 
            MYTBL-NAME "'" END-OF-STRING
            into SQL-QUERY
        perform 090-DO-QUERY
        perform 300-SHOW-TUPLES.
        call "sql_clear_query" using QRY-HANDLE
        perform 050-DISCONNECT
        display "-->"
**** use our tricky cgi variables setup to process the form
****  in a far easier way.
        move "address" to CGI-NAME
        string MYTBL-ADDR END-OF-STRING into CGI-VALUE
        call "cgi_set_string" using  CGI-NAME CGI-VALUE 
        move "phone" to CGI-NAME
        string MYTBL-PHONE END-OF-STRING into CGI-VALUE
        call "cgi_set_string" using  CGI-NAME CGI-VALUE 
        perform 400-INSERT-HTML thru 410-INSERT-HTML
        .
   
 030-LIST-MYTABLE.
        display "<PRE>"
        perform 080-CONNECT-MYDB 
        string  "select * from mytable" END-OF-STRING into SQL-QUERY
        perform 090-DO-QUERY
        perform 300-SHOW-TUPLES
        call "sql_clear_query" using QRY-HANDLE
        perform 050-DISCONNECT
        display "</PRE>"
        .

 035-CLEAR-FORM.
        move spaces to MYTBL-RECORD. 
        move "name" to CGI-NAME
        string MYTBL-NAME END-OF-STRING into CGI-VALUE
        call "cgi_set_string" using  CGI-NAME CGI-VALUE 
        move "address" to CGI-NAME
        string MYTBL-ADDR END-OF-STRING into CGI-VALUE
        call "cgi_set_string" using  CGI-NAME CGI-VALUE 
        move "phone" to CGI-NAME
        string MYTBL-PHONE END-OF-STRING into CGI-VALUE
        call "cgi_set_string" using  CGI-NAME CGI-VALUE 
        perform 400-INSERT-HTML thru 410-INSERT-HTML
        .

 050-DISCONNECT.
        call "sql_disconnect_db" using DB-HANDLE.
    
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

 400-INSERT-HTML.
       open input HTML-FORM.
        if FS not = zeros
            display "FS = " FS
            go 410-INSERT-HTML.
 405-INSERT-HTML.
        read HTML-FORM into HTML-LINE-CHARS
            at end go 410-INSERT-HTML.
        if FS not = zeros
            display "FS = " FS
            go 410-INSERT-HTML.
        perform 450-PROCESS-FORM 
        go 405-INSERT-HTML.
 410-INSERT-HTML.
        close HTML-FORM.

 450-PROCESS-FORM.
        set IX to 1
        search HTML-ENTRY varying IX
            when HTML-LINE-CHARS(IX:2) = WS-MARK
                next sentence.
        if IX > 80
            display HTML-LINE-CHARS
            go 455-PROCESS-FORM-END.
        set IX up by 2
        move IX to VN1
        search HTML-ENTRY varying IX
            when HTML-LINE-CHARS(IX:2) = WS-MARK
                next sentence.
        compute VN2 = IX - VN1 
        compute VN3 = VN1 - 3

        display HTML-LINE-CHARS(1:VN3) no advancing
*        display "[[" HTML-LINE-CHARS(VN1:VN2) "]]" no advancing
*** recover data processed by cgi library
        move spaces to CGI-VALUE
        move HTML-LINE-CHARS(VN1:VN2) to CGI-NAME
        call "cgi_get_string" using CGI-NAME CGI-VALUE
**** lookup the field's size in a table        
        move HTML-LINE-CHARS(VN1:VN2) to WS-ITEM-NAME.
        set IXSZ to 1
        search FORM-ITEM-SIZE-ENTRY varying IXSZ
            when FORM-ITEM-NAME(IXSZ) = WS-ITEM-NAME
                next sentence.
        move FORM-ITEM-SIZE(IXSZ) TO VN3.    
        display CGI-VALUE(1:VN3) no advancing.
**** display remaining of the line 
**** FixMe: must continue with variable replacing here
        compute VN2 = 80 - IX - 1
        set IX up by 2
        display HTML-LINE-CHARS(IX:VN2).
 455-PROCESS-FORM-END.

