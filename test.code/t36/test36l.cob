IDENTIFICATION DIVISION.
PROGRAM-ID. test36l.
ENVIRONMENT DIVISION.
CONFIGURATION SECTION.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
 SELECT ARQ  ASSIGN TO "fileTEST36l" 
           ORGANIZATION IS INDEXED 
           ACCESS MODE  IS DYNAMIC
           RECORD KEY IS ARQ-KEY 
           FILE STATUS  IS FS.

DATA DIVISION.
FILE SECTION.

 FD   ARQ
      LABEL RECORD IS STANDARD.
 01   REG-ARQ.
   03 ARQ-KEY          PIC  9(03).
   03 DESCRIPTION      PIC  X(60) VALUE "AAAAAAAAAAAAAAA".
 
 
WORKING-STORAGE SECTION.
  01 FS           PIC 9(02).
  01 W-COUNTER    PIC 9(15).
  01 REM          PIC 9(5).
  01 W01-SWITCHES PIC X(03).
  88      W01-END VALUE "YES".
  88      W01-MORE VALUE "NO".
  01 FNAME	PIC X(128) VALUE LOW-VALUES.
  01 FKEY	PIC X(128) VALUE LOW-VALUES.
  01 PID	PIC X(128) VALUE LOW-VALUES.
  01 USERNAME   PIC X(128) VALUE LOW-VALUES.
 
PROCEDURE DIVISION.
MAIN SECTION.
   OPEN I-O ARQ.
   MOVE "NO" TO W01-SWITCHES.
   PERFORM READ-IT UNTIL W01-END.
   UNLOCK ARQ.
   CLOSE ARQ.
   STOP RUN.

WRITE-IT.
   ADD 1 TO W-COUNTER.
   MOVE W-COUNTER TO ARQ-KEY.
   WRITE REG-ARQ.

READ-IT.
   DISPLAY "Enter the Record to Lock (1-998) 0 to Stop".
   ACCEPT W-COUNTER.
   MOVE W-COUNTER TO ARQ-KEY.
   IF W-COUNTER = 0
          MOVE "YES" TO W01-SWITCHES.
   READ ARQ AT END 
          MOVE "YES" TO W01-SWITCHES.
   DISPLAY "FS FOR STANDARD READ " FS.
   IF FS = "51" PERFORM DISPLAY-LOCK.
   READ ARQ WITH IGNORE LOCK AT END 
          MOVE "YES" TO W01-SWITCHES.
   DISPLAY "FS FOR IGNORE LOCK " FS.
   IF FS = "51" PERFORM DISPLAY-LOCK.
   IF W01-MORE 
          DISPLAY REG-ARQ
          MOVE W-COUNTER TO ARQ-KEY 
          READ ARQ WITH LOCK.
   display "FS FOR READ WITH LOCK " FS.
   IF FS = "51" PERFORM DISPLAY-LOCK.
 
DISPLAY-LOCK.
   MOVE LOW-VALUES TO FNAME.
   MOVE LOW-VALUES TO FKEY.
   STRING "Raw.dat" DELIMITED BY LOW-VALUES INTO FNAME.
   STRING ARQ-KEY DELIMITED BY LOW-VALUES INTO FKEY.
   MOVE LOW-VALUES TO PID.
   MOVE LOW-VALUES TO USERNAME.
   CALL "show_lock" USING FNAME, FKEY, PID, USERNAME.
   DISPLAY "Pid: " PID.
   DISPLAY "Username: " USERNAME.
