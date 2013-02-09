//    subrotc.c  
// 
//    Program to test both the C and WINAPI (Win32 only) 
//    call converntion from a COBOL program.
// 
//    David Essex		September 2004

#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#else
#define WINAPI
#endif 

void WINAPI subrotw(char *sw) 
{

 fprintf(stdout, "IN subrotw, received: '%s'\n", sw);

}

void subrotc(char *sc) 
{

 fprintf(stdout, "IN subrotc, received: '%s'\n", sc);

}

