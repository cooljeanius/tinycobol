/* 
 * Copyright (C) 2001, Ferran Pegueroles 
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1,
 * or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING.LIB.  If
 * not, write to the Free Software Foundation, Inc., 59 Temple Place,
 * Suite 330, Boston, MA 02111-1307 USA

 *
 * TinyCOBOL Run Time Library -- Runtime error functions
 *

*/

//#include "htcoblib.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "rterrors.h"
#include "htcoblib.h"

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                      table of messages                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/
static struct _msg {
  int msg_num;
  char *msg_text;
} rt_messages[] = {
  { TCB_RTERR_RESOLVE_STUB, "cannot resolve lib '%s': %s\n"},
  /* Empty Message */	
  { TCB_RTERR_EMPTY, "%s"} ,
  /*  Generic Messages  */
  { TCB_RTERR_NO_MEM, "cannot allocate memory\n"},
  { TCB_RTERR_NOT_IMPLEMENTED, "function not implemented\n"},
  /* Chain / chaining */
  { TCB_RTERR_GEN_NOPIPE, "cannot open pipe to pass data in chain: %s\n"},
  { TCB_RTERR_GEN_BADDATA, "error passing data to program: %s\n"},
  { TCB_RTERR_GEN_NOEXEC, "cannot execute program on chain: %s\n"},
  { TCB_RTERR_GEN_BAD_ARG, "error getting parameters passed from caller: %s\n"},
  { TCB_RTERR_GEN_SIZE_ERR, "size error on parameters passed on chain\n"},
  { TCB_RTERR_GEN_BAD_PIPE, "error opening descriptor 100 for chaining: %s\n"},
  { TCB_RTERR_GEN_RUNELEMENT, "error entering runelement\n"},
  /*  Dynamic calls */
  { 301, "error opening '%s': %s\n"},
  /* Intrinsic functions */
  { TCB_RTERR_INTRINSIC_BAD_ARG,"Bad arguments calling intrinsic function"},
  { -1, NULL}
};
/*
 * Alloc memory and report the error if cannot allocate
 */
void *tcob_rt_malloc(char *function,size_t size){
	void *p;
	p = malloc(size);
	if (p) return p;
	tcob_rt_error(function,TCB_RTERR_NO_MEM);
	tcob_rt_abort();
	return NULL;
}
/*
 * Exit the program with error closing all the files.
 *
 */
void tcob_rt_abort(){
	tcob_stop_run();
	exit(1);
}
	
static void tcob_rt_print_stack(){}
/*------------------------------------------------------------------------*\
 |                                                                        |
 |                      _format_message                                   |
 |                                                                        |
\*------------------------------------------------------------------------*/

static char * _format_message (int msg_num, va_list ap) {
  unsigned int i, size = 100;
  int n;
  char *p, *fmt = NULL;

  for (i=0; rt_messages[i].msg_num != -1; i++) {
      if (rt_messages[i].msg_num == msg_num) {
	  fmt = rt_messages[i].msg_text;
	  break;
      }
  }
  if (fmt == NULL)
    return "Undefined message";
  if ((p = malloc (size)) == NULL)
    return "Cannot allocate message";
  while (1)
    {
      /* Try to print in the allocated space. */
#ifndef __MINGW32__	    
      n = vsnprintf (p, size, fmt, ap);
#else      
      n = _vsnprintf (p, size, fmt, ap);
#endif      
      /* If that worked, return the string. */
      if (n > -1 && n < (int)size)
	return p;
      /* Else try again with more space. */
      if (n > -1)		/* glibc 2.1 */
	size = n + 1;		/* precisely what is needed */
      else			/* glibc 2.0 */
	size *= 2;		/* twice the old size */

      if ((p = realloc (p, size)) == NULL)
	return NULL;
    }
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                      tcob_rt_error                                     |
 |                                                                        |
\*------------------------------------------------------------------------*/
void
tcob_rt_error (char *function, int msg_num, ...)
{
  va_list ap;
  char *p;
  va_start (ap, msg_num);
  p = _format_message (msg_num, ap);
  va_end (ap);
  fprintf (stderr, "TC Runtime Error: %s: %s",function,p);
  tcob_rt_print_stack();
  tcob_rt_abort();
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                      tcob_rt_warning                                   |
 |                                                                        |
\*------------------------------------------------------------------------*/

void
tcob_rt_warning (char *function, int msg_num, ...)
{
  va_list ap;
  char *p;
  va_start (ap, msg_num);
  p = _format_message (msg_num, ap);
  va_end (ap);
  fprintf (stderr, "TC Runtime Warning: %s: %s",function,p);
  tcob_rt_print_stack();
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                      tcob_rt_debug                                     |
 |                                                                        |
\*------------------------------------------------------------------------*/

void
tcob_rt_debug (char * function,char *msg,...)
{
#ifdef DEBUG_RTS
  unsigned int size = 100;
  int n;
  char *p;
  va_list ap;

  if ((p = malloc (size)) == NULL)
    return ;
  while (1)
    {
      /* Try to print in the allocated space. */
#ifndef __MINGW32__	    
      n = vsnprintf (p, size, msg, ap);
#else      
      n = _vsnprintf (p, size, msg, ap);
#endif      
      /* If that worked, return the string. */
      if (n > -1 && n < (int)size)
	break ;
      /* Else try again with more space. */
      if (n > -1)		/* glibc 2.1 */
	size = n + 1;		/* precisely what is needed */
      else			/* glibc 2.0 */
	size *= 2;		/* twice the old size */

      if ((p = realloc (p, size)) == NULL)
	return ;
    }
  fprintf (stderr, "TC Debug: %s: %s",function,p);
#endif /* DEBUG_RTS */
}
