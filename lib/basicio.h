/*
 * Copyright (C) 2006, 2001, 2000, 1999,  Rildo Pragana, 
 *               Jim Noeth, Andrew Cameron, David Essex.
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
 * TinyCOBOL Run Time Library -- Accept/Display basic I/O functions
 *
 
*/

#ifndef _BASICIO_H_
#define _BASICIO_H_

#include "htcoblib.h"

/* Function only called by other Run-Time functions */

int tcob_display_expand(struct fld_desc*, char *, char *);

#endif	 /* _BASICIO_H_ */
