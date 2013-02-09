/* 
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
 */

#include "wprog.h"
/* #include <stdio.h> */

/* Declare the C equivalent type for the COBOL sub-program */
extern int subp01(char*);

HINSTANCE hInst;
BOOL WINAPI MainDlgProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
   char s[256] = "";
   int r=0, i=0;

   hInst = hInstance;

   InitCommonControls();

/*   fprintf(stdout, "lpCmd=%s;\n", lpCmd); */

   strcat(s, lpCmd);
   i = strlen(s);
   for (i; i < 254; i++) {
      s[i] = ' ';
   }
   s[255] = '\0';

   if (DialogBox(hInst, MAKEINTRESOURCE(IDN_DIALOG), NULL, MainDlgProc) == TRUE)
       r = subp01(s);

   return r;
}

BOOL WINAPI MainDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
   switch(msg)
   {

      case WM_COMMAND:
         if(wParam == IDOK)
         {
           EndDialog(hDlg, TRUE);
           return(TRUE);
         }
         if(wParam == IDCANCEL)
         {
           EndDialog(hDlg, FALSE);
           return(TRUE);
         }
         break;
   }

   return(FALSE);
}

