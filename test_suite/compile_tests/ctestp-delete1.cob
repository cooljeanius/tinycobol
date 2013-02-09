       IDENTIFICATION DIVISION.
       PROGRAM-ID.    CTESTP_DELETE1.
       ENVIRONMENT DIVISION.

       CONFIGURATION SECTION. 
       INPUT-OUTPUT SECTION.
       FILE-CONTROL.
           SELECT ARQ      ASSIGN TO "Testing.dat" 
                  ORGANIZATION IS INDEXED 
                  ACCESS MODE  IS RANDOM
                  RECORD KEY IS X-IND 
                  FILE STATUS  IS FS.

       DATA DIVISION.
       FILE SECTION.

       FD         ARQ
                  LABEL RECORD IS STANDARD.
       01         REG-ARQ.
         03       X-IND                  PIC  9(03).
         03       DESCRIPTION            PIC  X(60).
      
       WORKING-STORAGE SECTION.
       01  FS             PIC  9(02).
       01  ARQ-KEY        PIC  9(03).

       PROCEDURE DIVISION.
       000-MAIN.
            OPEN I-O ARQ.
            READ ARQ.
            DELETE ARQ RECORD
                INVALID KEY
                    MOVE "FAIL" TO DESCRIPTION
                NOT INVALID KEY
                    MOVE "PASS" TO DESCRIPTION
            END-DELETE.
            CLOSE ARQ.
            STOP RUN.
