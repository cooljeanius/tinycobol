/* 
 * Copyright (C) 2001, 2000, 1999,  Rildo Pragana, Jim Noeth, 
 *               Andrew Cameron, David Essex.
 * Copyright (C) 1993, 1991  Rildo Pragana.
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

#ifndef RTERRORS_H
#define RTERRORS_H
enum {
    	TCB_RTERR_EMPTY,
	TCB_RTERR_RESOLVE_STUB,
	TCB_RTERR_NO_MEM,
	TCB_RTERR_NOT_IMPLEMENTED,
	TCB_RTERR_INTRINSIC_BAD_ARG,
	TCB_RTERR_GEN_NOPIPE,
	TCB_RTERR_GEN_BADDATA,
	TCB_RTERR_GEN_NOEXEC,
	TCB_RTERR_GEN_BAD_ARG,
	TCB_RTERR_GEN_SIZE_ERR,
	TCB_RTERR_GEN_BAD_PIPE,
	TCB_RTERR_GEN_RUNELEMENT
};

#define tcob_malloc(x)	 tcob_rt_malloc(__FILE__,x)

void tcob_rt_abort();
void *tcob_rt_malloc(char *fucntion,size_t size);
void tcob_rt_error (char *function, int msg_num, ...);
void tcob_rt_warning (char *function, int msg_num, ...);
void tcob_rt_debug (char *function,char *msg,...);
#endif /* RTERRORS_H */
