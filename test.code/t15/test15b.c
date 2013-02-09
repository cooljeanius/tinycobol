/*    
 *  test15b.c  
 *
 *  Sample C program called from COBOL main-program (test15.cob).
 *
 *  David Essex	        December 1999
*/

#include <stdio.h>

/*    
 *  HOW-TO CALL C-functions (COBOL sub-program) from COBOL programs:  
 *  1) 
 *  Using the COBOL program(s) as a reference, 
 *  declare the C-functions returning a type (default type int). 
 *  2)
 *  Using the COBOL program(s) as a reference, 
 *  define the equivalent C-functions types in C.
 *  This depends on the COBOL types and the type of CALL (value or reference).
 *  3)
 *  Add the C-functions to your source. 
 *  
*/

/*  
  CALL 'test15b' USING F1 F2 F3 F4. (default=BY REFERENCE)
  01 F1. Group item F1=X(5)+X(1)=X(6)
    05 F1-A        PIC X(5).
    05 F1-B        PIC X(1).
  01 F2            PIC 9(2).
  01 F3            PIC 9(5) COMP.
  01 F4            PIC 9(3).

  X(6), 9(2), 9(5) COMP, 9(3) 
  is equivalent to (==)
  char *c1, char *c2, unsigned short *c3, char *c4 

  NOTE: COBOL PICTURE X types do have a C-string like NULL delimiter 
*/

int test15b(char *c1, char *c2, unsigned short *c3, char *c4);

/* This is a COBOL CALL BY REFERENCE and returns an int type */
int test15b(char *c1, char *c2, unsigned short *c3, char *c4) 
{

 int r=0;

 char *pt; 
 
 printf("sub  (test15b) C   input  :%c%c%c%c%c%c:%c%c:%02d:%c%c%c:\n",
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

 printf("sub  (test15b) C   return :%c%c%c%c%c%c:%c%c:%02d:%c%c%c:\n",
        c1[0], c1[1], c1[2], c1[3], c1[4], c1[5],
        c2[0], c2[1],
        *c3,
        c4[0], c4[1], c4[2]
        );

 return r;

}
