//    test25b.c  
// 
//    This program will test a COBOL call to a C program.
// 
//    David Essex		December 1999


#include <stdio.h>

int test25b(char *c1, char *c2, short *c3, char *c4) 
{

 int r=0;
 char *pt; 
 
 printf("sub  (test25b) C   input  :%c%c%c%c%c%c:%c%c:%02d:%c%c%c:\n",
        c1[0], c1[1], c1[2], c1[3], c1[4], c1[5],
        c2[0], c2[1],
        *c3,
        c4[0], c4[1], c4[2]
        );
         
 pt = c1;
 *pt = 'p';
 pt++;
 *pt = 'q';
 pt++;
 *pt = 'r';
 pt++;
 *pt = 's';
 pt++;
 *pt = 't';
 pt++;
 *pt = 'y';


 pt = c2;
 *pt = '1';
 pt++;
 *pt = '4';

 *c3=18; 

 pt = c4;
 *pt = '1';
 pt++;
 *pt = '4';
 pt++;
 *pt = '4';
 
 pt = NULL;

 printf("sub  (test25b) C   return :%c%c%c%c%c%c:%c%c:%02d:%c%c%c:\n",
        c1[0], c1[1], c1[2], c1[3], c1[4], c1[5],
        c2[0], c2[1],
        *c3,
        c4[0], c4[1], c4[2]
        );

 return r;

}
