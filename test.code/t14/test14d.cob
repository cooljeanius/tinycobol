 IDENTIFICATION DIVISION.
 PROGRAM-ID.  TEST14d.
 AUTHOR.      Jim Noeth.
 ENVIRONMENT DIVISION.
 CONFIGURATION SECTION.
 DATA DIVISION.
 WORKING-STORAGE SECTION.
 01  STRING-1                   PIC X(60)
     VALUE "THIS IS  A    TEST       STRING".
 01  STRING-2                   PIC X(60)
     VALUE "THIS IS  A----TEST - - - STRING".
 01  STRING-3                   PIC X(60)
     VALUE "THIS,IS..A----TEST$$$$$$$STRING".
 01  UNSTRING-1                PIC X(20).
 01  UNSTRING-2                PIC X(20).
 01  UNSTRING-3                PIC X(20).
 01  UNSTRING-4                PIC X(20).
 01  UNSTRING-5                PIC X(20).
 01  UNSTRING-6                PIC X(20).
 01  US-DELIM-1                PIC X(10).
 01  US-DELIM-2                PIC X(10).
 01  US-DELIM-3                PIC X(10).
 01  US-DELIM-4                PIC X(10).
 01  US-DELIM-5                PIC X(10).
 01  US-DELIM-6                PIC X(10).
 01  US-COUNT-1                PIC 9(04).
 01  US-COUNT-2                PIC 9(04).
 01  US-COUNT-3                PIC 9(04).
 01  US-COUNT-4                PIC 9(04).
 01  US-COUNT-5                PIC 9(04).
 01  US-COUNT-6                PIC 9(04).
 PROCEDURE DIVISION.
* 0000-BEGIN-IT-ALL SECTION.
 0000-BEGIN.
     PERFORM 1000-CLEAR-VARIABLES.
*
*
*
     DISPLAY "INPUT STRING = """, STRING-1, """".
     UNSTRING STRING-1
     DELIMITED BY ALL SPACES
     INTO
         UNSTRING-1
         DELIMITER IN US-DELIM-1
         COUNT IN US-COUNT-1
         UNSTRING-2
         DELIMITER IN US-DELIM-2
         COUNT IN US-COUNT-2
         UNSTRING-3
         DELIMITER IN US-DELIM-3
         COUNT IN US-COUNT-3
         UNSTRING-4
         DELIMITER IN US-DELIM-4
         COUNT IN US-COUNT-4
         UNSTRING-5
         DELIMITER IN US-DELIM-5
         COUNT IN US-COUNT-5
         UNSTRING-6
         DELIMITER IN US-DELIM-6
         COUNT IN US-COUNT-6.
     PERFORM 2000-DISPLAY-RESULTS.
*
*
     DISPLAY "INPUT STRING = """, STRING-2, """".
     UNSTRING STRING-2
     DELIMITED BY ALL SPACES  OR  ALL "-"
     INTO
         UNSTRING-1
         DELIMITER IN US-DELIM-1
         COUNT IN US-COUNT-1
         UNSTRING-2
         DELIMITER IN US-DELIM-2
         COUNT IN US-COUNT-2
         UNSTRING-3
         DELIMITER IN US-DELIM-3
         COUNT IN US-COUNT-3
         UNSTRING-4
         DELIMITER IN US-DELIM-4
         COUNT IN US-COUNT-4
         UNSTRING-5
         DELIMITER IN US-DELIM-5
         COUNT IN US-COUNT-5
         UNSTRING-6
         DELIMITER IN US-DELIM-6
         COUNT IN US-COUNT-6.
     PERFORM 2000-DISPLAY-RESULTS.
*
*
     DISPLAY "INPUT STRING = """, STRING-2, """".
     UNSTRING STRING-2
     DELIMITED BY SPACES  OR "-"
     INTO
         UNSTRING-1
         DELIMITER IN US-DELIM-1
         COUNT IN US-COUNT-1
         UNSTRING-2
         DELIMITER IN US-DELIM-2
         COUNT IN US-COUNT-2
         UNSTRING-3
         DELIMITER IN US-DELIM-3
         COUNT IN US-COUNT-3
         UNSTRING-4
         DELIMITER IN US-DELIM-4
         COUNT IN US-COUNT-4
         UNSTRING-5
         DELIMITER IN US-DELIM-5
         COUNT IN US-COUNT-5
         UNSTRING-6
         DELIMITER IN US-DELIM-6
         COUNT IN US-COUNT-6.
     PERFORM 2000-DISPLAY-RESULTS.
     DISPLAY "INPUT STRING = """, STRING-2, """".
     UNSTRING STRING-2
     DELIMITED BY
         ALL "- " OR
         ALL "-" OR
         ALL SPACES
     INTO
         UNSTRING-1
         DELIMITER IN US-DELIM-1
         COUNT IN US-COUNT-1
         UNSTRING-2
         DELIMITER IN US-DELIM-2
         COUNT IN US-COUNT-2
         UNSTRING-3
         DELIMITER IN US-DELIM-3
         COUNT IN US-COUNT-3
         UNSTRING-4
         DELIMITER IN US-DELIM-4
         COUNT IN US-COUNT-4
         UNSTRING-5
         DELIMITER IN US-DELIM-5
         COUNT IN US-COUNT-5
         UNSTRING-6
         DELIMITER IN US-DELIM-6
         COUNT IN US-COUNT-6.
     PERFORM 2000-DISPLAY-RESULTS.
*
*
     DISPLAY "INPUT STRING = """, STRING-2, """".
     UNSTRING STRING-2
     DELIMITED BY
         ALL SPACES OR
         ALL "-" OR
         ALL "- "
     INTO
         UNSTRING-1
         DELIMITER IN US-DELIM-1
         COUNT IN US-COUNT-1
         UNSTRING-2
         DELIMITER IN US-DELIM-2
         COUNT IN US-COUNT-2
         UNSTRING-3
         DELIMITER IN US-DELIM-3
         COUNT IN US-COUNT-3
         UNSTRING-4
         DELIMITER IN US-DELIM-4
         COUNT IN US-COUNT-4
         UNSTRING-5
         DELIMITER IN US-DELIM-5
         COUNT IN US-COUNT-5
         UNSTRING-6
         DELIMITER IN US-DELIM-6
         COUNT IN US-COUNT-6.
     PERFORM 2000-DISPLAY-RESULTS.
     STOP RUN.
*
*
*
*
 1000-CLEAR-VARIABLES.
     MOVE ZERO TO US-COUNT-1, US-COUNT-2, US-COUNT-3,
     US-COUNT-4, US-COUNT-5, US-COUNT-6.
     MOVE SPACES TO US-DELIM-1, US-DELIM-2, US-DELIM-3,
     US-DELIM-4, US-DELIM-5, US-DELIM-6.
 1000-CLEAR-EXIT.
     EXIT.
*
*
*
*
 2000-DISPLAY-RESULTS.
     DISPLAY "UNSTRING-1 = """, UNSTRING-1, """".
     DISPLAY "    US-DELIM-1 = """, US-DELIM-1, """",
     ", US-COUNT-1 = ", US-COUNT-1.
     DISPLAY "UNSTRING-2 = """, UNSTRING-2, """".
     DISPLAY "    US-DELIM-2 = """, US-DELIM-2, """",
     ", US-COUNT-2 = ", US-COUNT-2.
     DISPLAY "UNSTRING-3 = """, UNSTRING-3, """".
     DISPLAY "    US-DELIM-3 = """, US-DELIM-3, """",
     ", US-COUNT-3 = ", US-COUNT-3.
     DISPLAY "UNSTRING-4 = """, UNSTRING-4, """".
     DISPLAY "    US-DELIM-4 = """, US-DELIM-4, """",
     ", US-COUNT-4 = ", US-COUNT-4.
     DISPLAY "UNSTRING-5 = """, UNSTRING-5, """".
     DISPLAY "    US-DELIM-5 = """, US-DELIM-5, """",
     ", US-COUNT-5 = ", US-COUNT-5.
     DISPLAY "UNSTRING-6 = """, UNSTRING-6, """".
     DISPLAY "    US-DELIM-6 = """, US-DELIM-6, """",
     ", US-COUNT-6 = ", US-COUNT-6.
     DISPLAY " ".
     DISPLAY " ".
 2000-DISPLAY-EXIT.
     EXIT.