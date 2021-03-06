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
 DISPLAY "IN subr01, received: " VAR.
 EXIT PROGRAM.
 END PROGRAM subr01.

 IDENTIFICATION DIVISION.
 PROGRAM-ID.    subr02.  
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.
 01 CMDLINE-PARMS  PIC X(50).
 01 	VAR-4      	PIC X(10) VALUE 'Recife'.
 01 	SUBR-NAME.
  05	SUBR-PREFIX	PIC X(4) VALUE "subr".
  05	SUBR-NUMBER	PIC 9(2) VALUE zeros.

* LINKAGE SECTION.
* 01 VAR           PIC X(10).

* PROCEDURE DIVISION USING VAR.
 PROCEDURE DIVISION.
* DISPLAY "IN subr02, received: " VAR.
 DISPLAY "IN subr02".
 ACCEPT CMDLINE-PARMS FROM COMMAND-LINE.
 DISPLAY "IN subr02, COMMAND-LINE=" CMDLINE-PARMS.

 MOVE 33 TO SUBR-NUMBER
 DISPLAY "IN subr02 before call to " SUBR-NAME.
 CALL SUBR-NAME USING VAR-4.
 DISPLAY "IN subr02 after call to " SUBR-NAME.

 MOVE 2 TO RETURN-CODE.
 EXIT PROGRAM.
 END PROGRAM subr02.
 
