 IDENTIFICATION DIVISION.
 PROGRAM-ID.	TEST00.
 ENVIRONMENT DIVISION.

 CONFIGURATION SECTION. 
 SPECIAL-NAMES.
     DECIMAL-POINT IS COMMA.
* INPUT-OUTPUT SECTION.
* FILE-CONTROL.

 DATA DIVISION.
 FILE SECTION.

 WORKING-STORAGE SECTION.
 01  WS.
  05  WS1		    PIC  X(03).
  05  WS2.
   10  WS2A		    PIC  X(03) VALUE 'abc'.
   10  WS2B		    PIC  X(03).
  05  WS3		    PIC  X(03).
 01  TABELA.
  05 TAB OCCURS 10	    PIC  9(05).
 01  I  		    PIC  99.
 01  BB 		    PIC  9(5)V99.
 01  FILE-STATUS	    PIC  9(02).
 01  TECLA		    PIC  X(01).
 01  TERMINAL-WS	    PIC  9(02).
 77  FN-KEY		    PIC  9(4) COMP.

 PROCEDURE DIVISION.
 INICIO.
      MOVE 1  TO I.
      MOVE 101 TO TAB(1).
      MOVE 102 TO TAB(2).
      MOVE 103 TO TAB(3).
      MOVE 104 TO TAB(4).
      MOVE 105 TO TAB(5).
      MOVE 106 TO TAB(6).
      MOVE 107 TO TAB(7).
      MOVE 108 TO TAB(8).
      MOVE 109 TO TAB(9).	     
      MOVE 110 TO TAB(10).
 LOOP.
      DISPLAY "Indice: " I line 1 position 1.
      ACCEPT TECLA 
	  ON EXCEPTION FN-KEY 
	  MOVE 12345 TO TAB(I).
      ADD 1 TO I
      IF I < 3
	 GO LOOP.
      DISPLAY "Pronto 1 !" line 2 position 1.
      ACCEPT TECLA .
      MOVE 1 TO I.
 LOOP2.
      DISPLAY "Antes I = " I line 3 position 1.
      DISPLAY "TAB(I) = " TAB(I) NO ADVANCING line 4 position 1.
      ACCEPT TECLA .
      MOVE ZEROS TO TAB(I).
      DISPLAY "Depois I = " I ERASE line 5 position 1.
      DISPLAY "TAB(I) = " TAB(I) NO ADVANCING line 6 position 1.
      ACCEPT TECLA.
      ADD 1 TO I.
      IF I < 3
	 GO LOOP2.
      DISPLAY "Pronto 2 !" line 2 position 1.
      ACCEPT TECLA .
      STOP RUN.

