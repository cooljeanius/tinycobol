 IDENTIFICATION DIVISION.
 PROGRAM-ID. CTEST01_FC.
 AUTHOR.  GLEN COLBERT.
 INSTALLATION. Tiny Cobol Compiler Project.
 DATE-WRITTEN. 11-21-1999.
 DATE-COMPILED.
 SECURITY. NONE.
* Tests for f-c scans.

 ENVIRONMENT DIVISION.
 INPUT-OUTPUT SECTION.
 FILE-CONTROL.
 SELECT FOOBAR ASSIGN TO "./foo.bar"
        ORGANIZATION IS LINE SEQUENTIAL
        ACCESS MODE  IS SEQUENTIAL
        FILE STATUS  IS WS-FOOBAR-STAT.
 
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
     05  WS-FOOBAR-STAT             PIC 9(2).


 PROCEDURE DIVISION.
   STOP RUN.
 A000-EXIT.
     EXIT.
