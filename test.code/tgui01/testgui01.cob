* 
*  Copyright (C) 2004 Rildo Pragana.
* 
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2, or (at your option)
*  any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with this software; see the file COPYING.  If not, write to
*  the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
*  Boston, MA 02111-1307 USA
*
 IDENTIFICATION DIVISION.
 PROGRAM-ID.    testgui01.  
 AUTHOR. Rildo Pragana.         
* REMARKS.
*    Example tcl/tk GUI program for Cobol.
*
 ENVIRONMENT DIVISION.
 DATA DIVISION.
*
 WORKING-STORAGE SECTION.

    01      DATA-BLOCK.
        05  NAME        PIC X(40).
        05  W-ADDRESS     PIC X(50).
        05  PHONE       PIC X(15).
		05	END-PGM		PIC X.
	01      DATA-BLOCK-SIZE COMP PIC 9(12) VALUE 106.
    01      SITE-INFO.
        05  TITLE       PIC X(20).
        05  URL         PIC X(50).
    01      SITE-INFO-SIZE COMP PIC 9(12) VALUE 70.
    77  GUI-01  PIC X(64) VALUE "testgui03.tcl".
    77  GUI-02  PIC X(64) VALUE "testgui03a.tcl".

 PROCEDURE DIVISION.
 
  CALL "initTcl" 
   
  MOVE "Your name here" to NAME
  MOVE "Your address" TO W-ADDRESS
  MOVE "Phone number" to PHONE
* this variable tells Cobol that the user required an exit
  MOVE "0" to END-PGM.

	100-restart.
* call C wrapper, passing data block and size of data
  CALL "testgui02" USING DATA-BLOCK DATA-BLOCK-SIZE GUI-01
  
  DISPLAY "Returned data:"
  DISPLAY "NAME    [" NAME "]"
  DISPLAY "ADDRESS [" W-ADDRESS "]"
  DISPLAY "PHONE   [" PHONE "]"
* if not end of program required, loop 
  if END-PGM = 0
	  go to 100-restart.
* to start a new GUI (graphical interface), call this first
  call "newGui"
  MOVE "Title of the site" to TITLE
  MOVE "URL (http://..., ftp://..., etc)" to URL
* now we may draw other main window...
  CALL "testgui02" USING SITE-INFO SITE-INFO-SIZE GUI-02
  DISPLAY "Returned data:"
  DISPLAY "TITLE   [" TITLE "]"
  DISPLAY "URL     [" URL "]"

  STOP RUN.
