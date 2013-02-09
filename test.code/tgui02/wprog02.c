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

extern int subp01(char*);

int main(int ac, char *av[])  
{
   char s[256] = "";
   int r=0, i;

   for (i=0; i< ac; i++) {
     strcat(s, av[i]);
     strcat(s, " ");
   }

   i = 0;
   if ((i = MessageBox (NULL, IDCH_DIALOG_MSG, IDCH_DIALOG_CAPTION, MB_YESNO | MB_ICONEXCLAMATION)) == IDYES)
       r = subp01(s);
  
/*  fprintf(stdout, "MessageBox return code=%d;\n", i); */

   return r;
}

