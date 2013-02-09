 IDENTIFICATION DIVISION.
 PROGRAM-ID.    dyntest01.  
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.
 01 	VAR-1      	PIC X(10) VALUE '*ARGUMENT*'.
 01 	VAR-2      	PIC X(10) VALUE 'RILDO'.
 01 	VAR-3      	PIC X(10) VALUE 'Pragana'.
 01 	VAR-4      	PIC X(10) VALUE 'Recife'.
 01 	SUBR-NAME.
  05	SUBR-PREFIX	PIC X(4) VALUE "subr".
  05	SUBR-NUMBER	PIC 9(2) VALUE zeros.

 LINKAGE SECTION.
 01 DUMMY-VAR          PIC X(10).

* PROCEDURE DIVISION USING DUMMY-VAR. 
 PROCEDURE DIVISION.

* CALL-LOADLIB is not required on UN*X (ELF) based systems.
* It is no longer required on Win32 as the LD_LIBRARY_PATH and 
* TCOB_LD_LIBRARY_PATH enviroment variable paths are searched.
* Win32 Only: Load DLL so that modules (sub-programs) can be found
*  CALL-LOADLIB "subrots.dll".
*  CALL-LOADLIB "dyntest.dll".

  MOVE 1 TO SUBR-NUMBER
  CALL SUBR-NAME USING VAR-1.
* call several times to see if it was registered 
* (not a benchmark, but it may be interesting to have one)
  CALL SUBR-NAME USING VAR-1.
  CALL SUBR-NAME USING VAR-1.
  CALL SUBR-NAME USING VAR-1.

  ADD 1 TO SUBR-NUMBER
*  CALL SUBR-NAME USING VAR-2.
*  CALL SUBR-NAME USING VAR-2
  CALL SUBR-NAME
   ON EXCEPTION PERFORM C-100
   NOT ON EXCEPTION PERFORM D-100.

*  ADD 1 TO SUBR-NUMBER
  MOVE 33 TO SUBR-NUMBER
  CALL SUBR-NAME USING VAR-3.
  MOVE 3 TO SUBR-NUMBER.

* the following subr does not exists and should give us an error
  ADD 1 TO SUBR-NUMBER
  CALL SUBR-NAME USING VAR-4.

  ADD 1 TO SUBR-NUMBER.
  CALL SUBR-NAME USING VAR-4
   ON OVERFLOW PERFORM E-100.

  ADD 1 TO SUBR-NUMBER.
  CALL SUBR-NAME USING VAR-4
   ON EXCEPTION PERFORM C-100.

  MOVE 22 TO RETURN-CODE.
  
*  STOP RUN.
  EXIT PROGRAM.

 C-100.

  DISPLAY "EXCEPTION condition has occured in calling program SUBR-NAME=" SUBR-NAME.

 D-100.

  DISPLAY "EXCEPTION condition has NOT occured in calling program SUBR-NAME=" SUBR-NAME.

 E-100.

  DISPLAY "OVERFLOW condition has occured in calling program SUBR-NAME=" SUBR-NAME.

 END PROGRAM dyntest01.

 IDENTIFICATION DIVISION.
 PROGRAM-ID. subr33. 
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

 LINKAGE SECTION.
 01 VAR           PIC X(10).

 PROCEDURE DIVISION USING VAR.
 DISPLAY "IN subr33, received: " VAR.
 DISPLAY "This subroutine (subr33) is inside the main module."
 EXIT PROGRAM.

 END PROGRAM subr33.
