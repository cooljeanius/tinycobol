 IDENTIFICATION DIVISION.
 PROGRAM-ID. CTEST01_FEATURES.
 AUTHOR.  GLEN COLBERT.
 INSTALLATION. Tiny Cobol Compiler Project.
 DATE-WRITTEN. 11-21-1999.
 DATE-COMPILED.
 SECURITY. NONE.
* This program should not compile because
* it does not have an env div 

 SPECIAL-NAMES.
 DECIMAL-POINT IS COMMA.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.
 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.

 PROCEDURE DIVISION.
   STOP RUN.
 A000-EXIT.
     EXIT.
