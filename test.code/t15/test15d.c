/*    
 *  test15d.c  
 *
 *  Sample program to call a COBOL sub-program (C-function) from C.
 *
 *   David Essex	        March 2000
*/

#include <stdio.h>

/*    
 *  HOW-TO CALL COBOL sub-program(s) (C-functions) from C main program:  
 *  1) 
 *  Using the COBOL sub-program(s) as a reference, 
 *  declare all the COBOL sub-program(s) as C-functions (extern int). 
 *  2)
 *  Declare the terminate TC Run-Time run-unit C-function call as
 *  'extern void tcob_stop_run(void)'. 
 *  3)
 *  Using the COBOL sub-program(s) as a reference, 
 *  define the equivalent COBOL types in C.
 *  This depends on the COBOL types and the type of CALL (value or reference).
 *  4)
 *  Add the C-function (COBOL sub-program) calls to your program. 
 *  5) IMPORTANT:
 *  At the end of all COBOL calls, add the terminate TC Run-Time 
 *  run-unit C-function call to your program. 
 *  
*/

/* Declare the COBOL sub-program as a C-type function */ 
extern int test15a(char *f1, char *f2, unsigned int *f3, char *f4);

/* IMPORTANT: Initialize the TC Run-Time run-unit */ 
extern void tcob_init(int arc, char *arv[]);

/* IMPORTANT: Terminate TC Run-Time run-unit */ 
extern void tcob_stop_run(void);

int main(int ac, char *av[]) 
{ 

 int r=0; 

 /* Since this is a COBOL CALL BY REFERENCE (default)
    char *c1, char *c2, unsigned int *c3, char *c4
    is equivalent to (==)
    X(6), 9(2), 9(2) COMP, 9(3) 
    NOTE: COBOL PICTURE X types do have a C-string like NULL delimiter */
 /* Define the equivalent COBOL types in C */
 unsigned int c3; 
 char c1[6], c2[2], c4[3];

 c1[0] = '=';
 c1[1] = '=';
 c1[2] = '=';
 c1[3] = '=';
 c1[4] = '=';
 c1[5] = '=';

 c2[0] = '0';
 c2[1] = '6';

 c3=84; 

 c4[0] = '1';
 c4[1] = '4';
 c4[2] = '4';

 /* IMPORTANT: Initialize the TC run-unit */ 
 tcob_init(ac, av);

 /* COBOL PICTURE X types do have a C-tring NULL delimiter */
 printf("main (test15d) C   input  :%c%c%c%c%c%c:%c%c:%02d:%c%c%c:\n",
        c1[0], c1[1], c1[2], c1[3], c1[4], c1[5],
        c2[0], c2[1],
        c3,
        c4[0], c4[1], c4[2]
        );
         
 /* This is a COBOL CALL BY REFERENCE and returns an int type */
 /* char*, char*, unsigned int*, char* == X(6), 9(2), 9(2) COMP, 9(3) */
 r = test15a(c1, c2, &c3, c4);
 
 printf("main (test15d) C   return :%c%c%c%c%c%c:%c%c:%02d:%c%c%c:\n",
        c1[0], c1[1], c1[2], c1[3], c1[4], c1[5],
        c2[0], c2[1],
        c3,
        c4[0], c4[1], c4[2]
        );
 
 /* IMPORTANT: Terminate TC run-unit */ 
 tcob_stop_run();

 printf("program return code: %d\n", r);
 return r;

}
