//    test25c.c  
// 
//    This program will test a COBOL call to a C program for WINAPI functions.
// 
//    David Essex		August 2004


#include "windows.h"
//#include "commctrl.h"
#include <stdio.h>

int WINAPI test25c(char *c1, char *c2, short *c3, char *c4) 
{

 int r=0;
 char *pt; 

 printf("sub  (test25c) C   input  :%c%c%c%c%c%c:%c%c:%02d:%c%c%c:\n",
        c1[0], c1[1], c1[2], c1[3], c1[4], c1[5],
        c2[0], c2[1],
        *c3,
        c4[0], c4[1], c4[2]
        );
         
 pt = c1;
 *pt = 'h';
 pt++;
 *pt = 'i';
 pt++;
 *pt = 'j';
 pt++;
 *pt = 'k';
 pt++;
 *pt = 'l';
 pt++;
 *pt = 'm';


 pt = c2;
 *pt = '5';
 pt++;
 *pt = '3';

 *c3=78; 

 pt = c4;
 *pt = 'a';
 pt++;
 *pt = '3';
 pt++;
 *pt = 'x';
 
 pt = NULL;

 printf("sub  (test25c) C   return :%c%c%c%c%c%c:%c%c:%02d:%c%c%c:\n",
        c1[0], c1[1], c1[2], c1[3], c1[4], c1[5],
        c2[0], c2[1],
        *c3,
        c4[0], c4[1], c4[2]
        );

 return r;

}
