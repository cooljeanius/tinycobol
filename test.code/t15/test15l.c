/*    
 *  test15l.c  
 *
 *  Sample C program called from COBOL main-program (test15k.cob)
 *  using advanced features.
 *
 *  David Essex
*/

#include <stdio.h>
#include <stdarg.h>

/* Function declarations */
void STEST1901(int j, ...);
void STEST1902(char *s);
void STEST1903(char *s);
void STEST1904(char *s);

/* To avoid x86 (32-bit) 4 byte alignment problems */
#pragma pack(1)
struct wsWorkareas
{
/* wsStructWorkarea */
/*   int *ipt1;   / filler  pointer  */
/*   int *ipt2;   / filler  pointer  */
/*   int *ipt3;   / filler  pointer  */
   short  n;      /* wsStruct-n   9(4) COMP-5 */
   char   ch[10]; /* wsStruct-ch  Group item { X(09)+X(1)=10 } */
   int    num;    /* wsStruct-num 9(9) COMP-5 */
};
#pragma pack()


/* Example using a variable length list */
void STEST1901(int j, ...) 
{
  int i;
  char buf1[32];
  char buf2[128];
  va_list arg_ptr;

  /* Build the string list */
  strcpy(buf2, "");
  va_start(arg_ptr, j);

  for(i=1; i<=j; i++) {
    sprintf(buf1, "%s:", va_arg(arg_ptr, char*));
    strcat(buf2, buf1);
  }
  va_end (arg_ptr);
  fprintf(stdout, "sub  (test15l) C1901: ( input):          s=%s\n", buf2);

}

/* Example using a pointer calling a variable length list function */
void STEST1902(char *s) 
{
  char buf1[32] = "void STEST1902(void) 1";
  char buf2[32] = "void STEST1902(void) 2";

  fprintf(stdout, "sub  (test15l) C1902: ( input):          s=%s\n", s);
  fprintf(stdout, "sub  (test15l) C1902: (C1901 input):     s=%s:%s:%s\n", s, buf2, buf1);
  STEST1901(3, s, buf2, buf1);  
  fprintf(stdout, "sub  (test15l) C1902: (output):          s=%s\n", s);
}

/* Example using a null terminated string */
void STEST1903(char *s) 
{
  fprintf(stdout, "sub  (test15l) C1903: ( input):          s=%s\n", s);
  strcpy(s, "WS-PARM-3S     WS-PARM-2S     WS-PARM-1S     "); /* Copy new string */ 
  fprintf(stdout, "sub  (test15l) C1903: (output):          s=%s\n", s);
}

/* Example using a structure */
void STEST1904(char *s) 
{
  struct wsWorkareas *wa;
  wa = (struct wsWorkareas*)s;

  fprintf(stdout, "sub  (test15l) C1904 ( input):          n=%04d          ch =%s          num=%09d\n", wa->n, wa->ch, wa->num);
  /* Copy new string */
  strcpy(wa->ch, "IHGFEDCBA"); /* ABCDEFGHI */
  wa->n = 65;
  fprintf(stdout, "sub  (test15l) C1904 (output):          n=%04d          ch =%s          num=%09d\n", wa->n, wa->ch, wa->num);
}

