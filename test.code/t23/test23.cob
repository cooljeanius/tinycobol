 IDENTIFICATION DIVISION.
 PROGRAM-ID. TEST23.
 ENVIRONMENT DIVISION.
* INPUT-OUTPUT SECTION.
 DATA DIVISION.
 FILE SECTION.
 WORKING-STORAGE SECTION.
  01  WS-FIELD-1                   PIC X(10).
  01  WS-FIELD-2-FROM              PIC S9(05)V99.
  01  WS-FIELD-2-TO                PIC S9(05)V99.
  01  WS-FIELD-3                   PIC S9(06)V99 COMP-3.
  01  WS-FIELD-4                   PIC 9(06) COMP.
  01  WS-FIELD-5                   PIC X(30).
  01  WS-FIELD-QUIT                PIC X(01).
  01  WS-FIELD-DISPLAY             PIC 9(06).99-.
 SCREEN SECTION.
  01  SCREEN-1.
      03  FILLER                   PIC X(30)
          blank screen
          LINE 1 COLUMN 1
          FOREGROUND-COLOR 1
          BACKGROUND-COLOR 2
          HIGHLIGHT
          VALUE "WS-FIELD-1 - PIC X(10)".
      03  SS-FIELD-1               PIC X(10)
          LINE 1 COLUMN 32
          foreground-color 1
          background-color 3
          AUTO
          SECURE
          USING WS-FIELD-1.  
      03  FILLER                   PIC X(30)
          LINE 2 COLUMN 1
          foreground-color 2
          background-color 1
          VALUE "WS-FIELD-2 - PIC *(5).99".
      03  SS-FIELD-2               PIC *(5).99
          LINE 2 COLUMN 32
          foreground-color 2
          background-color 3
          FROM WS-FIELD-2-FROM
          TO WS-FIELD-2-TO.
      03  FILLER                   PIC X(30)
          LINE 3 COLUMN 1
          BLINK
          foreground-color 3
          background-color 4
          VALUE "WS-FIELD-3 - PIC ZZZ,ZZZ.99CR".
      03  SS-FIELD-3               PIC ZZZ,ZZZ.99CR
          line 3 column 32
          foreground-color 3
          background-color 5
          USING WS-FIELD-3.
      03  FILLER                   PIC X(30)
          LINE 4 COLUMN 1
          foreground-color 4
          background-color 5
          VALUE "WS-FIELD-4 - PIC 9(06) B ON Z".
      03  SS-FIELD-4               PIC 9(06)
          LINE 4 COLUMN 32
          BLANK WHEN ZERO
          foreground-color 4
          background-color 6
          USING WS-FIELD-4.
      03  FILLER                   PIC X(30)
          FOREGROUND-COLOR 5
          BACKGROUND-COLOR 6
          LINE 5
          COLUMN 1
          VALUE "WS-FIELD-5 - PIC X(30)".
      03  SS-FIELD-5               PIC X(30)
          FOREGROUND-COLOR 5
          BACKGROUND-COLOR 7
          LINE 5
          COLUMN 32
          USING WS-FIELD-5.
      03  FILLER                   PIC X(04)
          FOREGROUND-COLOR 6
          BACKGROUND-COLOR 7
          LINE 7
          COLUMN 1
          VALUE "Quit".
      03  SS-FIELD-QUIT            PIC X(01)
          LINE 7
          COLUMN 6
          FOREGROUND-COLOR 6
          BACKGROUND-COLOR 0
          USING WS-FIELD-QUIT.
      03  filler                   PIC X(03)
          line 8 column 1
          foreground-color 0
          background-color 1
          value " 1 ".
      03  filler                   PIC X(03)
          line 8 column 4
          foreground-color 0
          background-color 2
          value " 2 ".
      03  filler                   PIC X(03)
          line 8 column 7
          foreground-color 0
          background-color 3
          value " 3 ".
      03  filler                   PIC X(03)
          line 8 column 10
          foreground-color 0
          background-color 4
          value " 4 ".
      03  filler                   PIC X(03)
          line 8 column 13
          foreground-color 0
          background-color 5
          value " 5 ".
      03  filler                   PIC X(03)
          line 8 column 16
          foreground-color 0
          background-color 6
          value " 6 ".
      03  filler                   PIC X(03)
          line 8 column 19
          foreground-color 0
          background-color 7
          value " 7 ".
      03  filler                   PIC X(03)
          line 8 column 22
          foreground-color 7
          background-color 0
          value " 0 ".
  01  SCREEN-2.
      03  FILLER                   PIC X(10)
          LINE 10 COLUMN 1
          VALUE "WS-FIELD-1".
      03  SS-2-FIELD-1             PIC X(20)
          LINE 10 COLUMN 12.
      03  FILLER                   PIC X(10)
          LINE 10 COLUMN 41
          VALUE "WS-FIELD-2".
      03  SS-2-FIELD-2             PIC X(20)
          line 10 column 52.
      03  filler                   PIC X(10)
          line 11 column 1
          value "WS-FIELD-3".
      03  SS-2-FIELD-3             PIC X(20)
          line 11 column 12.
      03  filler                   PIC X(10)
          line 11 column 41
          value "WS-FIELD-4".
      03  SS-2-FIELD-4             PIC X(20)
          line 11 column 52.
      03  filler                   PIC X(10)
          line 12 column 1
          value "WS-FIELD-5".
      03  SS-2-FIELD-5             PIC X(30)
          line 12 column 12.
  01  SCREEN-3.
      03  FILLER                   PIC X(01)
          LINE 23 COLUMN 1 VALUE " ".
      03  SS-3-FIELD-1             PIC X(01)
          LINE 23 COLUMN 2
          USING WS-FIELD-QUIT.
 PROCEDURE DIVISION.
 MAIN-LOGIC SECTION.
 PROGRAM-BEGIN.
      move "abcd" to WS-FIELD-1.
      MOVE "-54.32" to WS-FIELD-2-FROM.
      move "-12345.67" to WS-FIELD-3.
      move ZERO to WS-FIELD-4.
      move "This is a test" to WS-FIELD-5.
 loopit.
      move spaces to WS-FIELD-QUIT.
      display SCREEN-1.
      accept SCREEN-1.
      if WS-FIELD-QUIT = "q"
      or WS-FIELD-QUIT = "Q"
          go to endit.
      move WS-FIELD-1 to SS-2-FIELD-1.
      move WS-FIELD-2-TO to WS-FIELD-DISPLAY.
      move WS-FIELD-DISPLAY to SS-2-FIELD-2.
      move WS-FIELD-3 to WS-FIELD-DISPLAY.
      move WS-FIELD-DISPLAY to SS-2-FIELD-3.
      move WS-FIELD-4 to WS-FIELD-DISPLAY.
      move WS-FIELD-DISPLAY to SS-2-FIELD-4.
      move WS-FIELD-5 to SS-2-FIELD-5.
      display SCREEN-2.
      accept SCREEN-3.
      go to loopit.
 endit.
 PROGRAM-DONE.
      STOP RUN.
