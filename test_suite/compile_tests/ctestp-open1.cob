 IDENTIFICATION DIVISION.
 PROGRAM-ID. CTESTP_OPEN1.
 AUTHOR.  STEPHEN CONNOLLY.
 INSTALLATION. Tiny Cobol Compiler Project.
 DATE-WRITTEN. 11-21-1999.
 DATE-COMPILED.
 SECURITY. NONE.
* TEST OPEN VERB FULL FORMAT.

 ENVIRONMENT DIVISION.
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
 SELECT FOOBAR ASSIGN TO "./foo.bar"
*        ORGANIZATION IS LINE SEQUENTIAL
        ORGANIZATION IS SEQUENTIAL
        ACCESS MODE  IS SEQUENTIAL
        FILE STATUS  IS WS-FS1.
 
 DATA DIVISION.
 FILE SECTION.
 FD  FOOBAR
     LABEL RECORDS ARE STANDARD.
 01  FOOBAR-REC.
     05  WS-FOOBAR-KEY              PIC 9(2).
     05  WS-FOOBAR-DATA1            PIC X(8).
     05  WS-FOOBAR-DATA2            PIC X(20).

 WORKING-STORAGE SECTION.
 01  WS-SWITCHES.
     05  WS-FS1             PIC 9(2).

 PROCEDURE DIVISION.
 000-MAIN.
     OPEN INPUT FOOBAR
          OUTPUT FOOBAR
          I-O FOOBAR
          EXTEND FOOBAR
     .
     STOP RUN.