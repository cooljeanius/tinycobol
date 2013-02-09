/*
 * Copyright (C) 2006, 2001, 2000, 1999,  Rildo Pragana, Jim Noeth, 
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
 */

#ifndef _IMATH_H_
#define _IMATH_H_

#include "htcoblib.h"
#include "fixnumeric.h"

void tcob_fld2num(struct fld_desc *f, char *s, Numeric *pn); 
void tcob_push_num(struct fld_desc *f, char *s, Numeric n0); 
int  tcob_assign_num(struct fld_desc *f, char *s1, int opts, Numeric n0); 
int  tcob_num2fld(struct fld_desc *f, char *s1, int round, Numeric n1); 
void tcob_add_num(Numeric *pn, Numeric n1);
void tcob_subtract_num(Numeric *pn, Numeric n1);
void tcob_multiply_num(Numeric *pn, Numeric n1);
void tcob_divide_num(Numeric *pn, Numeric n1);
void tcob_pow_num(Numeric *pn, Numeric n1);
int  tcob_iadd_num(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, int round);
int  tcob_isubtract_num(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, int round); 
int  tcob_imultiply_num(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, struct fld_desc *f3, char *s3, int round); 
int  tcob_idivide_num(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, struct fld_desc *f3, char *s3, int round ); 
int  tcob_idivide1_num(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, struct fld_desc *f3, char *s3, struct fld_desc *f4, char *s4, int round); 
int  tcob_check_size_overflow_num(struct fld_desc *f, Numeric n0); 

/* Defined in htcoblib.h */
/* int tcob_check_condition_num(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, struct fld_desc *f3, char *s3); */
/* int tcob_compare_num(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2); */


#endif	 /* _IMATH_H_ */
