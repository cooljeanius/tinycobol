/* 
 * A library for BCD calculation
 *
 * Copyright (C) 1998 Jan Wieck 
 * Copyright (C) 2001 Masami Ogoshi <ogochan@linux.or.jp>
 * Copyright (C) 2006 David Essex
 *
 * This code originated from PostgreSQL.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA  02111-1307, USA.
 */

#ifndef _NUMERIC_H_
#define _NUMERIC_H_

#include	<stdlib.h>

#ifndef	Bool
#define	Bool		int
#endif
#ifndef	FALSE
#define	FALSE		0
#endif
#ifndef	TRUE
#define	TRUE		(!FALSE)
#endif

/* ----------
 * The hardcoded limits and defaults of the numeric data type
 * ----------
 */
#define NUMERIC_MAX_PRECISION		1000
#define NUMERIC_DEFAULT_PRECISION	30
#define NUMERIC_DEFAULT_SCALE		6


/* ----------
 * Internal limits on the scales chosen for calculation results
 * ----------
 */
#define NUMERIC_MAX_DISPLAY_SCALE	NUMERIC_MAX_PRECISION
#define NUMERIC_MIN_DISPLAY_SCALE	(NUMERIC_DEFAULT_SCALE + 4)

#define NUMERIC_MAX_RESULT_SCALE	(NUMERIC_MAX_PRECISION * 2)
#define NUMERIC_MIN_RESULT_SCALE	(NUMERIC_DEFAULT_PRECISION + 4)


/* ----------
 * Sign values and macros to deal with packing/unpacking n_sign_dscale
 * ----------
 */
#define NUMERIC_SIGN_MASK	0xC000
#define NUMERIC_POS			0x0000
#define NUMERIC_NEG			0x4000
#define NUMERIC_NAN			0xC000
#define NUMERIC_DSCALE_MASK 0x3FFF
#define NUMERIC_SIGN(n)		((n)->n_sign_dscale & NUMERIC_SIGN_MASK)
#define NUMERIC_DSCALE(n)	((n)->n_sign_dscale & NUMERIC_DSCALE_MASK)
#define NUMERIC_IS_NAN(n)	(NUMERIC_SIGN(n) != NUMERIC_POS &&			\
								NUMERIC_SIGN(n) != NUMERIC_NEG)


/* ----------
 * The Numeric data type stored in the database
 *
 * NOTE: by convention, values in the packed form have been stripped of
 * all leading and trailing zeroes (except there will be a trailing zero
 * in the last byte, if the number of digits is odd).  In particular,
 * if the value is zero, there will be no digits at all!  The weight is
 * arbitrary in this case, but we normally set it to zero.
 * ----------
 */
typedef	struct	NumericData	{
	size_t		varlen;			/* Variable size		*/
	int		n_weight;		/* Weight of 1st digit	*/
	int		n_rscale;		/* Result scale			*/
	int		n_sign_dscale;	/* Sign + display scale */
	unsigned char n_data[1];	/* Digit data (2 decimal digits/byte) */
}	NumericData;
typedef NumericData *Numeric;

#define NUMERIC_HDRSZ	(sizeof(size_t) + sizeof(int) * 3)

/* ----------
 * external functions
 * ----------
 */

extern	Numeric	NumericInput(char *str, int precision, int scale);
extern	char	*NumericOutput(Numeric num);
extern	Numeric	NumericRescale(Numeric num, int precision, int scale);
extern	Numeric	NumericShift(Numeric num, int digit);
extern	Numeric	NumericDup(Numeric num);
extern	void	NumericFormat(char *buf, char *format, Numeric num);
extern	void	NumericFormatToPrecision(char *format, int *precision, int *scale);
extern	Numeric	NumericInputChar(char c, int precision, int scale);
extern	void	NumericFree(Numeric num);

extern	Numeric	NumericAbs(Numeric num);
extern	Numeric	NumericUMinus(Numeric num);
extern	Numeric	NumericSign(Numeric num);
extern	Numeric	NumericRound(Numeric num, int scale);
extern	Numeric	NumericTrunc(Numeric num, int scale);
extern	Numeric	NumericCeil(Numeric num);
extern	Numeric	NumericFloor(Numeric num);

extern	int	NumericCmp(Numeric num1, Numeric num2);
extern	Bool	NumericEQ(Numeric num1, Numeric num2);
extern	Bool	NumericNE(Numeric num1, Numeric num2);
extern	Bool	NumericGT(Numeric num1, Numeric num2);
extern	Bool	NumericGE(Numeric num1, Numeric num2);
extern	Bool	NumericLT(Numeric num1, Numeric num2);
extern	Bool	NumericLE(Numeric num1, Numeric num2);

extern	Numeric	NumericADD(Numeric num1, Numeric num2);
extern	Numeric	NumericSUB(Numeric num1, Numeric num2);
extern	Numeric	NumericMUL(Numeric num1, Numeric num2);
extern	Numeric	NumericDIV(Numeric num1, Numeric num2);
extern	Numeric	NumericMOD(Numeric num1, Numeric num2);
extern	Numeric	NumericINC(Numeric num);
extern	Numeric	NumericDEC(Numeric num);

extern	Numeric	NumericMIN(Numeric num1, Numeric num2);
extern	Numeric	NumericMAX(Numeric num1, Numeric num2);

extern	Numeric	NumericSQRT(Numeric num);
extern	Numeric	NumericEXP(Numeric num);
extern	Numeric	NumericLN(Numeric num);
extern	Numeric	NumericLOG(Numeric num1, Numeric num2);
extern	Numeric	NumericPOWER(Numeric num1, Numeric num2);

#define	NumericPositive(n)	(((n)->n_sign_dscale & NUMERIC_POS) == NUMERIC_POS)
#define	NumericNegative(n)	(((n)->n_sign_dscale & NUMERIC_NEG) == NUMERIC_NEG)

extern	Numeric	IntToNumeric(int val);
extern	int	NumericToInt(Numeric num);

extern	Numeric	LongLongIntToNumeric(long long int val);
extern	long long int NumericToLongLongInt(Numeric num);

extern	Numeric	DoubleToNumeric(double val);
extern	double	NumericToDouble(Numeric num);

#endif	 /* _NUMERIC_H_ */
