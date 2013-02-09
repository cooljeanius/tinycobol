* 
*  Copyright (C) 2004 Rildo Pragana, David Essex.
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
 identification division.
 program-id. wprog03.
 environment division.
 data division.

 working-storage section.

 01 ws-wparms.
*  HWND hWnd - handle of owner window
   05 ws-wparms-hWnd           pic 9(6) comp-5 value 0.
*   05 ws-wparms-hWnd           pic x(2) value x"0000".
*  LPCTSTR lpText - address of text in message box
   05 ws-wparms-lpText.
      10 ws-wparms-lpText-1    pic x(35) value "Run the COBOL sub-program subp01 ?".
      10 filler                pic x(02) value x"0000".
*  LPCTSTR lpCaption - address of title of message box 
   05 ws-wparms-pCaption.
      10 ws-wparms-pCaption-1  pic x(14) value "TinyCOBOL test".
      10 filler                pic x(02) value x"0000".
*   UINT uType - style of message box
*   MB_YESNO 4 | MB_ICONEXCLAMATION 0x30 (48) = 52
   05 ws-wparms-uType          pic 9(6) comp-5 value 52.
*  int MessageBoxA(...) - return type
   05 ws-wparms-mBoxRet        pic 9(5) comp-5.
      88 IDYES                 value 6.
 
 01 cmdline-parms   pic x(50).
* 01	cmdline-parms   pic x(15).
 
 procedure division.
 A000.
 
    move 0 to ws-wparms-mBoxRet.
    accept cmdline-parms from command-line.

*   #define MessageBox MessageBoxA
*   MessageBox (NULL, "text in message box", "title of message box", MB_YESNO | MB_ICONEXCLAMATION)
*   int MessageBoxA(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
*   Real function name is 'MessageBoxA@16'
*
    call WINAPI 'MessageBoxA' using 
         by value ws-wparms-hWnd 
         by reference ws-wparms-lpText 
         by reference ws-wparms-pCaption
         by value ws-wparms-uType
         returning ws-wparms-mBoxRet.

*    display "ws-wparms-mBoxRet=" ws-wparms-mBoxRet ";".

*
*   IDYES == 6
*
*   if ws-wparms-mBoxRet EQUAL 6
    if IDYES
    then
       call 'subp01' using by reference cmdline-parms 
    end-if.

*    move 22 to return-code
    stop run.
*

