 IDENTIFICATION DIVISION.
 PROGRAM-ID.    subrot2. 
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

 LINKAGE SECTION.
 01 VAR           PIC X(10).

 PROCEDURE DIVISION USING VAR.
 DISPLAY "IN subrot2, received: " VAR ";".
 EXIT PROGRAM.
 END PROGRAM subrot2.

 IDENTIFICATION DIVISION.
 PROGRAM-ID.    subr01. 
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

 LINKAGE SECTION.
 01 VAR           PIC X(10).

 PROCEDURE DIVISION USING VAR.
 DISPLAY "IN subr01, received: " VAR ";".
 EXIT PROGRAM.
 END PROGRAM subr01.

 IDENTIFICATION DIVISION.
 PROGRAM-ID.    subr02. 
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

 LINKAGE SECTION.
 01 VAR           PIC X(10).

 PROCEDURE DIVISION USING VAR.
 DISPLAY "IN subr02, received: " VAR ";".
 EXIT PROGRAM.
 END PROGRAM subr02.
 
 IDENTIFICATION DIVISION.
 PROGRAM-ID.    subr07. 
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.
 01 VAR1.
  05 VAR1A         PIC X(10) VALUE "Aristotle".
  05 VAR1B         PIC X(01) VALUE x"00".
 01 VAR2.
  05 VAR2A         PIC X(10) VALUE "Pheadrus ".
  05 VAR2B         PIC X(01) VALUE x"00".
 01 SUBR-NAME.
  05	SUBR-PREFIX	PIC X(4) VALUE "subr".
  05	SUBR-NUMBER	PIC 9(2) VALUE zeros.
  05	FILLER          PIC X(6) VALUE "      ".

 LINKAGE SECTION.
 01 VAR           PIC X(10).

 PROCEDURE DIVISION USING VAR.
 DISPLAY "IN subr07, received: " VAR ";".

* DISPLAY "subr07 1A: CALL='subr03';".
* CALL 'subr03' USING VAR1.
* DISPLAY "subr07 1B:".

 MOVE 'subr03' TO SUBR-NAME.
 DISPLAY "subr07 2A: CALL=" SUBR-NAME ";".
 CALL SUBR-NAME USING VAR1A.
 DISPLAY "subr07 2B:".
 
 MOVE 'subrotc' TO SUBR-NAME.
 DISPLAY "subr07 3A: CALL=" SUBR-NAME ";".
 CALL SUBR-NAME USING VAR1.
 DISPLAY "subr07 3B:".

 MOVE 'subrotw' TO SUBR-NAME.
 DISPLAY "subr07 4A: CALL=" SUBR-NAME ";".
 CALL WINAPI SUBR-NAME USING VAR2.
 DISPLAY "subr07 4B:".
 
 EXIT PROGRAM.
 END PROGRAM subr07.


