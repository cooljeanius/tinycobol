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

#include	<ctype.h>
#include	<float.h>
#include	<math.h>
#include	<errno.h>
#include	<string.h>
#include	<assert.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/types.h>

#include	"fixnumeric.h"

/* ----------
 * Uncomment the following to enable compilation of dump_numeric()
 * and dump_var() and to get a dump of any result produced by make_result().
 * ----------
#define NUMERIC_DEBUG
 */

#ifndef MIN
#define MIN(a,b) (((a)<(b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b)) ? (a) : (b))
#endif

#ifndef NAN
#define NAN		(0.0/0.0)
#endif

#ifndef	xmalloc
#define	xmalloc(s)	malloc(s)
#endif
#ifndef	xfree
#define	xfree(p)	free(p)
#endif

/* ----------
 * Local data types
 *
 * Note: the first digit of a NumericVar's value is assumed to be multiplied
 * by 10 ** weight.  Another way to say it is that there are weight+1 digits
 * before the decimal point.  It is possible to have weight < 0.
 *
 * The value represented by a NumericVar is determined by the sign, weight,
 * ndigits, and digits[] array.  The rscale and dscale are carried along,
 * but they are just auxiliary information until rounding is done before
 * final storage or display.  (Scales are the number of digits wanted
 * *after* the decimal point.  Scales are always >= 0.)
 *
 * buf points at the physical start of the palloc'd digit buffer for the
 * NumericVar.	digits points at the first digit in actual use (the one
 * with the specified weight).	We normally leave an unused byte or two
 * (preset to zeroes) between buf and digits, so that there is room to store
 * a carry out of the top digit without special pushups.  We just need to
 * decrement digits (and increment weight) to make room for the carry digit.
 *
 * If buf is NULL then the digit buffer isn't actually palloc'd and should
 * not be freed --- see the constants below for an example.
 *
 * NB: All the variable-level functions are written in a style that makes it
 * possible to give one and the same variable as argument and destination.
 * This is feasible because the digit buffer is separate from the variable.
 * ----------
 */
typedef unsigned char NumericDigit;

typedef	struct	NumericVar	{
	int	ndigits;	/* number of digits in digits[] - can be
								 * 0! */
	int	weight;		/* weight of first digit */
	int	rscale;		/* result scale */
	int	dscale;		/* display scale */
	int	sign;		/* NUMERIC_POS, NUMERIC_NEG, or
								 * NUMERIC_NAN */
	NumericDigit *buf;	/* start of palloc'd space for digits[] */
	NumericDigit *digits;	/* decimal digits */
} NumericVar;


/* ----------
 * Local data
 * ----------
 */
static int	global_rscale = NUMERIC_MIN_RESULT_SCALE;

/* ----------
 * Some preinitialized variables we need often
 * ----------
 */
static NumericDigit const_zero_data[1] = {0};
static NumericVar const_zero =
{0, 0, 0, 0, NUMERIC_POS, NULL, const_zero_data};

static NumericDigit const_one_data[1] = {1};
static NumericVar const_one =
{1, 0, 0, 0, NUMERIC_POS, NULL, const_one_data};

static NumericDigit const_two_data[1] = {2};
static NumericVar const_two =
{1, 0, 0, 0, NUMERIC_POS, NULL, const_two_data};

static NumericVar const_nan =
{0, 0, 0, 0, NUMERIC_NAN, NULL, NULL};



/* ----------
 * Local functions
 * ----------
 */

#ifdef NUMERIC_DEBUG
static void dump_numeric(char *str, Numeric num);
static void dump_var(char *str, NumericVar *var);

#else
#define dump_numeric(s,n)
#define dump_var(s,v)
#endif

#define digitbuf_alloc(size)  ((NumericDigit *) xmalloc(size))
#define digitbuf_free(buf)	\
	do { \
		 if ((buf) != NULL) \
			 xfree(buf); \
	} while (0)

#define	InitVar(v)		memset(v,0,sizeof(NumericVar))
static	void	AllocateVar(NumericVar *var, int ndigits);
static	void	FreeVar(NumericVar *var);
static	void	ZeroVar(NumericVar *var);

static	void	SetVarFromChar(char c, NumericVar *dest);
static	void	SetVarFromStr(char *str, NumericVar *dest);
static	void	SetVarFromNum(Numeric value, NumericVar *dest);
static	void	SetVarFromVar(NumericVar *value, NumericVar *dest);
static	char	*GetStrFromVar(NumericVar *var, int dscale);

static	Numeric	MakeResult(NumericVar *var);

static	void	ApplyPrecision(NumericVar *var, int precision, int scale);
static	int		CmpVar(NumericVar *var1, NumericVar *var2);
static	void	AddVar(NumericVar *var1, NumericVar *var2, NumericVar *result);
static	void	SubVar(NumericVar *var1, NumericVar *var2, NumericVar *result);
static	void	MulVar(NumericVar *var1, NumericVar *var2, NumericVar *result);
static	void	DivVar(NumericVar *var1, NumericVar *var2, NumericVar *result);
static	void	ModVar(NumericVar *var1, NumericVar *var2, NumericVar *result);
static	void	CeilVar(NumericVar *var, NumericVar *result);
static	void	FloorVar(NumericVar *var, NumericVar *result);
static	void	SqrtVar(NumericVar *arg, NumericVar *result);
static	void	ExpVar(NumericVar *arg, NumericVar *result);
static	void	LnVar(NumericVar *arg, NumericVar *result);
static	void	LogVar(NumericVar *base, NumericVar *num, NumericVar *result);
static	void	PowerVar(NumericVar *base, NumericVar *exp, NumericVar *result);
static	int		CmpAbs(NumericVar *var1, NumericVar *var2);
static	void	AddAbs(NumericVar *var1, NumericVar *var2, NumericVar *result);
static	void	SubAbs(NumericVar *var1, NumericVar *var2, NumericVar *result);

extern	Numeric
NumericInput(
	char	*str,
	int		precision,
	int		scale)
{
	NumericVar	value;
	Numeric		res;

	if (str == NULL)
		return NULL;

	if (strcmp(str, "NULL") == 0)
		return NULL;

	if (strcmp(str, "NaN") == 0)
		return MakeResult(&const_nan);

	InitVar(&value);
	SetVarFromStr(str, &value);

	ApplyPrecision(&value, precision, scale);

	res = MakeResult(&value);
	FreeVar(&value);

	return res;
}

extern	Numeric
NumericInputChar(
	char	c,
	int		precision,
	int		scale)
{
	NumericVar	value;
	Numeric		res;

	InitVar(&value);
	SetVarFromChar(c, &value);

	ApplyPrecision(&value, precision, scale);

	res = MakeResult(&value);
	FreeVar(&value);

	return res;
}

extern	void
NumericFree(
	Numeric	num)
{
	if		(  num  !=  NULL  ) {
		xfree(num);
	}
}

extern	char *
NumericOutput(
	Numeric	num)
{
	NumericVar	x;
	char		*str;

	if (num == NULL)
		return strdup("NULL");

	if (NUMERIC_IS_NAN(num))
		return strdup("NaN");

	InitVar(&x);
	SetVarFromNum(num, &x);

	str = GetStrFromVar(&x, x.dscale);

	FreeVar(&x);

	return str;
}

extern	Numeric
NumericShift(
	Numeric	num,
	int		digit)
{
	Numeric		res;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	res = (Numeric) xmalloc(num->varlen);
	memcpy(res, num, num->varlen);

	res->n_weight += digit;

	return res;
}

extern	Numeric
NumericDup(
	Numeric	num)
{
	Numeric		res;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	res = (Numeric) xmalloc(num->varlen);
	memcpy(res, num, num->varlen);

	return res;
}

extern	Numeric
NumericRescale(
	Numeric	num,
	int		precision,
	int		scale)
{
	Numeric		new;
	int			maxweight;
	NumericVar	var;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	maxweight = precision - scale;

	/* ----------
	 * If the number is in bounds and due to the present result scale
	 * no rounding could be necessary, just make a copy of the input
	 * and modify its scale fields.
	 * ----------
	 */
	if		(num->n_weight < maxweight && scale >= num->n_rscale)	{
		new = (Numeric) xmalloc(num->varlen);
		memcpy(new, num, num->varlen);
		new->n_rscale = scale;
		new->n_sign_dscale = NUMERIC_SIGN(new) |
			((int) scale & NUMERIC_DSCALE_MASK);
		return new;
	}

	/* ----------
	 * We really need to fiddle with things - unpack the number into
	 * a variable and let ApplyPrecision() do it.
	 * ----------
	 */
	InitVar(&var);

	SetVarFromNum(num, &var);
	ApplyPrecision(&var, precision, scale);
	new = MakeResult(&var);

	FreeVar(&var);

	return new;
}

extern	Numeric
NumericAbs(
	Numeric	num)
{
	Numeric		res;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	res = (Numeric) xmalloc(num->varlen);
	memcpy(res, num, num->varlen);

	res->n_sign_dscale = NUMERIC_POS | NUMERIC_DSCALE(num);

	return res;
}


extern	Numeric
NumericUMinus(
	Numeric	num)
{
	Numeric		res;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	res = (Numeric) xmalloc(num->varlen);
	memcpy(res, num, num->varlen);

	/* ----------
	 * The packed format is known to be totally zero digit trimmed
	 * always. So we can identify a ZERO by the fact that there
	 * are no digits at all.  Do nothing to a zero.
	 * ----------
	 */
	if		(num->varlen != NUMERIC_HDRSZ)	{
		/* Else, flip the sign */
		if (NUMERIC_SIGN(num) == NUMERIC_POS)
			res->n_sign_dscale = NUMERIC_NEG | NUMERIC_DSCALE(num);
		else
			res->n_sign_dscale = NUMERIC_POS | NUMERIC_DSCALE(num);
	}

	return res;
}


extern	Numeric
NumericSign(
	Numeric	num)
{
	Numeric		res;
	NumericVar	result;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	InitVar(&result);

	/* ----------
	 * The packed format is known to be totally zero digit trimmed
	 * always. So we can identify a ZERO by the fact that there
	 * are no digits at all.
	 * ----------
	 */
	if		(num->varlen == NUMERIC_HDRSZ) {
		SetVarFromVar(&const_zero, &result);
	} else {
		/* ----------
		 * And if there are some, we return a copy of ONE
		 * with the sign of our argument
		 * ----------
		 */
		SetVarFromVar(&const_one, &result);
		result.sign = NUMERIC_SIGN(num);
	}

	res = MakeResult(&result);
	FreeVar(&result);

	return res;
}


extern	Numeric
NumericRound(
	Numeric	num,
	int		scale)
{
	Numeric		res;
	NumericVar	arg;
	int			i;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	/* ----------
	 * Limit the scale value to avoid possible overflow in calculations below.
	 * ----------
	 */
	scale = MIN(NUMERIC_MAX_RESULT_SCALE,
				MAX(-NUMERIC_MAX_RESULT_SCALE, scale));

	/* ----------
	 * Unpack the argument and round it at the proper digit position
	 * ----------
	 */
	InitVar(&arg);
	SetVarFromNum(num, &arg);

	i = arg.weight + scale + 1;

	if		(i < arg.ndigits)	{

		/*
		 * If i = 0, the value loses all digits, but could round up if its
		 * first digit is more than 4.	If i < 0 the result must be 0.
		 */
		if		(i < 0) {
			arg.ndigits = 0;
		} else {
			int			carry = (arg.digits[i] > 4) ? 1 : 0;

			arg.ndigits = i;
			while	(carry)	{
				carry += arg.digits[--i];
				arg.digits[i] = carry % 10;
				carry /= 10;
			}

			if	(i < 0)	{
				assert(i == -1);/* better not have added more than 1 digit */
				assert(arg.digits > arg.buf);
				arg.digits--;
				arg.ndigits++;
				arg.weight++;
			}
		}
	}

	scale = MIN(NUMERIC_MAX_DISPLAY_SCALE, MAX(0, scale));
	arg.rscale = scale;
	arg.dscale = scale;

	res = MakeResult(&arg);

	FreeVar(&arg);
	return res;
}


extern	Numeric
NumericTrunc(
	Numeric	num,
	int		scale)
{
	Numeric		res;
	NumericVar	arg;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	/* ----------
	 * Limit the scale value to avoid possible overflow in calculations below.
	 * ----------
	 */
	scale = MIN(NUMERIC_MAX_RESULT_SCALE,
				MAX(-NUMERIC_MAX_RESULT_SCALE, scale));

	/* ----------
	 * Unpack the argument and truncate it at the proper digit position
	 * ----------
	 */
	InitVar(&arg);
	SetVarFromNum(num, &arg);

	arg.ndigits = MIN(arg.ndigits, MAX(0, arg.weight + scale + 1));

	scale = MIN(NUMERIC_MAX_DISPLAY_SCALE, MAX(0, scale));
	arg.rscale = scale;
	arg.dscale = scale;

	res = MakeResult(&arg);

	FreeVar(&arg);
	return res;
}


extern	Numeric
NumericCeil(
	Numeric	num)
{
	Numeric		res;
	NumericVar	result;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	InitVar(&result);

	SetVarFromNum(num, &result);
	CeilVar(&result, &result);

	result.dscale = 0;

	res = MakeResult(&result);
	FreeVar(&result);

	return res;
}


extern	Numeric
NumericFloor(
	Numeric	num)
{
	Numeric		res;
	NumericVar	result;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	InitVar(&result);

	SetVarFromNum(num, &result);
	FloorVar(&result, &result);

	result.dscale = 0;

	res = MakeResult(&result);
	FreeVar(&result);

	return res;
}


extern	int
NumericCmp(
	Numeric	num1,
	Numeric	num2)
{
	int			result;
	NumericVar	arg1;
	NumericVar	arg2;

	if (num1 == NULL || num2 == NULL)
		return (int) 0;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return (int) 0;

	InitVar(&arg1);
	InitVar(&arg2);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	result = CmpVar(&arg1, &arg2);

	FreeVar(&arg1);
	FreeVar(&arg2);

	return (int) ((result == 0) ? 0 : ((result < 0) ? -1 : 1));
}


extern	Bool
NumericEQ(
	Numeric	num1,
	Numeric	num2)
{
	int			result;
	NumericVar	arg1;
	NumericVar	arg2;

	if (num1 == NULL || num2 == NULL)
		return FALSE;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return FALSE;

	InitVar(&arg1);
	InitVar(&arg2);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	result = CmpVar(&arg1, &arg2);

	FreeVar(&arg1);
	FreeVar(&arg2);

	return (result == 0);
}


extern	Bool
NumericNE(
	Numeric	num1,
	Numeric	num2)
{
	int			result;
	NumericVar	arg1;
	NumericVar	arg2;

	if (num1 == NULL || num2 == NULL)
		return FALSE;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return FALSE;

	InitVar(&arg1);
	InitVar(&arg2);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	result = CmpVar(&arg1, &arg2);

	FreeVar(&arg1);
	FreeVar(&arg2);

	return (result != 0);
}


extern	Bool
NumericGT(
	Numeric	num1,
	Numeric	num2)
{
	int			result;
	NumericVar	arg1;
	NumericVar	arg2;

	if (num1 == NULL || num2 == NULL)
		return FALSE;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return FALSE;

	InitVar(&arg1);
	InitVar(&arg2);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	result = CmpVar(&arg1, &arg2);

	FreeVar(&arg1);
	FreeVar(&arg2);

	return (result > 0);
}


extern	Bool
NumericGE(
	Numeric	num1,
	Numeric	num2)
{
	int			result;
	NumericVar	arg1;
	NumericVar	arg2;

	if (num1 == NULL || num2 == NULL)
		return FALSE;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return FALSE;

	InitVar(&arg1);
	InitVar(&arg2);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	result = CmpVar(&arg1, &arg2);

	FreeVar(&arg1);
	FreeVar(&arg2);

	return (result >= 0);
}


extern	Bool
NumericLT(
	Numeric	num1,
	Numeric	num2)
{
	int			result;
	NumericVar	arg1;
	NumericVar	arg2;

	if (num1 == NULL || num2 == NULL)
		return FALSE;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return FALSE;

	InitVar(&arg1);
	InitVar(&arg2);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	result = CmpVar(&arg1, &arg2);

	FreeVar(&arg1);
	FreeVar(&arg2);

	return (result < 0);
}


extern	Bool
NumericLE(
	Numeric	num1,
	Numeric	num2)
{
	int			result;
	NumericVar	arg1;
	NumericVar	arg2;

	if (num1 == NULL || num2 == NULL)
		return FALSE;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return FALSE;

	InitVar(&arg1);
	InitVar(&arg2);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	result = CmpVar(&arg1, &arg2);

	FreeVar(&arg1);
	FreeVar(&arg2);

	return (result <= 0);
}


extern	Numeric
NumericADD(
	Numeric	num1,
	Numeric	num2)
{
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;
	Numeric		res;

	if (num1 == NULL || num2 == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return MakeResult(&const_nan);

	InitVar(&arg1);
	InitVar(&arg2);
	InitVar(&result);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	AddVar(&arg1, &arg2, &result);
	res = MakeResult(&result);

	FreeVar(&arg1);
	FreeVar(&arg2);
	FreeVar(&result);

	return res;
}


extern	Numeric
NumericSUB(
	Numeric	num1,
	Numeric	num2)
{
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;
	Numeric		res;

	if (num1 == NULL || num2 == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return MakeResult(&const_nan);

	InitVar(&arg1);
	InitVar(&arg2);
	InitVar(&result);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	SubVar(&arg1, &arg2, &result);
	res = MakeResult(&result);

	FreeVar(&arg1);
	FreeVar(&arg2);
	FreeVar(&result);

	return res;
}

extern	Numeric
NumericMUL(
	Numeric	num1,
	Numeric	num2)
{
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;
	Numeric		res;

	if (num1 == NULL || num2 == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return MakeResult(&const_nan);

	InitVar(&arg1);
	InitVar(&arg2);
	InitVar(&result);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	global_rscale = arg1.rscale + arg2.rscale;

	MulVar(&arg1, &arg2, &result);

	result.dscale = arg1.dscale + arg2.dscale;

	res = MakeResult(&result);

	FreeVar(&arg1);
	FreeVar(&arg2);
	FreeVar(&result);

	return res;
}

extern	Numeric
NumericDIV(
	Numeric	num1,
	Numeric	num2)
{
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;
	Numeric		res;
	int			res_dscale;

	if (num1 == NULL || num2 == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return MakeResult(&const_nan);

	InitVar(&arg1);
	InitVar(&arg2);
	InitVar(&result);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	res_dscale = MAX(arg1.dscale + arg2.dscale, NUMERIC_MIN_DISPLAY_SCALE);
	res_dscale = MIN(res_dscale, NUMERIC_MAX_DISPLAY_SCALE);
	global_rscale = MAX(arg1.rscale + arg2.rscale,
						NUMERIC_MIN_RESULT_SCALE);
	global_rscale = MAX(global_rscale, res_dscale + 4);
	global_rscale = MIN(global_rscale, NUMERIC_MAX_RESULT_SCALE);

	DivVar(&arg1, &arg2, &result);

	result.dscale = res_dscale;

	res = MakeResult(&result);

	FreeVar(&arg1);
	FreeVar(&arg2);
	FreeVar(&result);

	return res;
}


extern	Numeric
NumericMOD(
	Numeric	num1,
	Numeric	num2)
{
	Numeric		res;
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;

	if (num1 == NULL || num2 == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return MakeResult(&const_nan);

	InitVar(&arg1);
	InitVar(&arg2);
	InitVar(&result);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	ModVar(&arg1, &arg2, &result);

	result.dscale = result.rscale;
	res = MakeResult(&result);

	FreeVar(&result);
	FreeVar(&arg2);
	FreeVar(&arg1);

	return res;
}


extern	Numeric
NumericINC(
	Numeric	num)
{
	NumericVar	arg;
	Numeric		res;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	InitVar(&arg);

	SetVarFromNum(num, &arg);

	AddVar(&arg, &const_one, &arg);
	res = MakeResult(&arg);

	FreeVar(&arg);

	return res;
}


extern	Numeric
NumericDEC(
	Numeric	num)
{
	NumericVar	arg;
	Numeric		res;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	InitVar(&arg);

	SetVarFromNum(num, &arg);

	SubVar(&arg, &const_one, &arg);
	res = MakeResult(&arg);

	FreeVar(&arg);

	return res;
}


extern	Numeric
NumericMIN(
	Numeric	num1,
	Numeric	num2)
{
	NumericVar	arg1;
	NumericVar	arg2;
	Numeric		res;

	if (num1 == NULL || num2 == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return MakeResult(&const_nan);

	InitVar(&arg1);
	InitVar(&arg2);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	if (CmpVar(&arg1, &arg2) <= 0)
		res = MakeResult(&arg1);
	else
		res = MakeResult(&arg2);

	FreeVar(&arg1);
	FreeVar(&arg2);

	return res;
}


extern	Numeric
NumericMAX(
	Numeric	num1,
	Numeric	num2)
{
	NumericVar	arg1;
	NumericVar	arg2;
	Numeric		res;

	if (num1 == NULL || num2 == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return MakeResult(&const_nan);

	InitVar(&arg1);
	InitVar(&arg2);

	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	if (CmpVar(&arg1, &arg2) >= 0)
		res = MakeResult(&arg1);
	else
		res = MakeResult(&arg2);

	FreeVar(&arg1);
	FreeVar(&arg2);

	return res;
}


extern	Numeric
NumericSQRT(
	Numeric	num)
{
	Numeric		res;
	NumericVar	arg;
	NumericVar	result;
	int			res_dscale;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	InitVar(&arg);
	InitVar(&result);

	SetVarFromNum(num, &arg);

	res_dscale = MAX(arg.dscale, NUMERIC_MIN_DISPLAY_SCALE);
	res_dscale = MIN(res_dscale, NUMERIC_MAX_DISPLAY_SCALE);
	global_rscale = MAX(arg.rscale, NUMERIC_MIN_RESULT_SCALE);
	global_rscale = MAX(global_rscale, res_dscale + 4);
	global_rscale = MIN(global_rscale, NUMERIC_MAX_RESULT_SCALE);

	SqrtVar(&arg, &result);

	result.dscale = res_dscale;

	res = MakeResult(&result);

	FreeVar(&result);
	FreeVar(&arg);

	return res;
}


extern	Numeric
NumericEXP(
	Numeric	num)
{
	Numeric		res;
	NumericVar	arg;
	NumericVar	result;
	int			res_dscale;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	InitVar(&arg);
	InitVar(&result);
	SetVarFromNum(num, &arg);

	res_dscale = MAX(arg.dscale, NUMERIC_MIN_DISPLAY_SCALE);
	res_dscale = MIN(res_dscale, NUMERIC_MAX_DISPLAY_SCALE);
	global_rscale = MAX(arg.rscale, NUMERIC_MIN_RESULT_SCALE);
	global_rscale = MAX(global_rscale, res_dscale + 4);
	global_rscale = MIN(global_rscale, NUMERIC_MAX_RESULT_SCALE);

	ExpVar(&arg, &result);

	result.dscale = res_dscale;

	res = MakeResult(&result);

	FreeVar(&result);
	FreeVar(&arg);

	return res;
}

extern	Numeric
NumericLN(
	Numeric	num)
{
	Numeric		res;
	NumericVar	arg;
	NumericVar	result;
	int			res_dscale;

	if (num == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num))
		return MakeResult(&const_nan);

	InitVar(&arg);
	InitVar(&result);
	SetVarFromNum(num, &arg);

	res_dscale = MAX(arg.dscale, NUMERIC_MIN_DISPLAY_SCALE);
	res_dscale = MIN(res_dscale, NUMERIC_MAX_DISPLAY_SCALE);
	global_rscale = MAX(arg.rscale, NUMERIC_MIN_RESULT_SCALE);
	global_rscale = MAX(global_rscale, res_dscale + 4);
	global_rscale = MIN(global_rscale, NUMERIC_MAX_RESULT_SCALE);

	LnVar(&arg, &result);

	result.dscale = res_dscale;

	res = MakeResult(&result);

	FreeVar(&result);
	FreeVar(&arg);

	return res;
}

extern	Numeric
NumericLOG(
	Numeric	num1,
	Numeric num2)
{
	Numeric		res;
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;
	int			res_dscale;

	if (num1 == NULL || num2 == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return MakeResult(&const_nan);

	InitVar(&arg1);
	InitVar(&arg2);
	InitVar(&result);
	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	res_dscale = MAX(arg1.dscale + arg2.dscale, NUMERIC_MIN_DISPLAY_SCALE);
	res_dscale = MIN(res_dscale, NUMERIC_MAX_DISPLAY_SCALE);
	global_rscale = MAX(arg1.rscale + arg2.rscale, NUMERIC_MIN_RESULT_SCALE);
	global_rscale = MAX(global_rscale, res_dscale + 4);
	global_rscale = MIN(global_rscale, NUMERIC_MAX_RESULT_SCALE);

	LogVar(&arg1, &arg2, &result);

	result.dscale = res_dscale;

	res = MakeResult(&result);

	FreeVar(&result);
	FreeVar(&arg2);
	FreeVar(&arg1);

	return res;
}


extern	Numeric
NumericPOWER(
	Numeric	num1,
	Numeric	num2)
{
	Numeric		res;
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;
	int			res_dscale;

	if (num1 == NULL || num2 == NULL)
		return NULL;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return MakeResult(&const_nan);

	InitVar(&arg1);
	InitVar(&arg2);
	InitVar(&result);
	SetVarFromNum(num1, &arg1);
	SetVarFromNum(num2, &arg2);

	res_dscale = MAX(arg1.dscale + arg2.dscale, NUMERIC_MIN_DISPLAY_SCALE);
	res_dscale = MIN(res_dscale, NUMERIC_MAX_DISPLAY_SCALE);
	global_rscale = MAX(arg1.rscale + arg2.rscale, NUMERIC_MIN_RESULT_SCALE);
	global_rscale = MAX(global_rscale, res_dscale + 4);
	global_rscale = MIN(global_rscale, NUMERIC_MAX_RESULT_SCALE);

	PowerVar(&arg1, &arg2, &result);

	result.dscale = res_dscale;

	res = MakeResult(&result);

	FreeVar(&result);
	FreeVar(&arg2);
	FreeVar(&arg1);

	return res;
}


extern	Numeric
IntToNumeric(
	int		val)
{
	Numeric		res;
	NumericVar	result;
	char		tmp[12];

	InitVar(&result);

	sprintf(tmp,"%d",val);
	SetVarFromStr(tmp, &result);
	res = MakeResult(&result);

	FreeVar(&result);

	return res;
}


extern	int
NumericToInt(
	Numeric	num)
{
	NumericVar x;
	char	   *str;
	int        result;

	if (num == NULL)
		return 0;


	if (NUMERIC_IS_NAN(num))
		fprintf(stderr, "Cannot convert NaN to int4");

	InitVar(&x);
	SetVarFromNum(num, &x);

	str = GetStrFromVar(&x, 0);		/* dscale = 0 produces rounding */

	FreeVar(&x);

	result = atoi(str);
	xfree(str);

	return result;
}


extern	Numeric
LongLongIntToNumeric(
	long long int   val)
{
	Numeric		res;
	NumericVar	result;
	char		tmp[24];

	InitVar(&result);

#ifdef __MINGW32__
	sprintf(tmp,"%I64d",val);
#else
	sprintf(tmp,"%lld",val);
#endif
	SetVarFromStr(tmp, &result);
	res = MakeResult(&result);

	FreeVar(&result);

	return res;
}


extern	long long int
NumericToLongLongInt(
	Numeric	num)
{
	NumericVar    x;
	char	      *str;
	long long int result;

	if (num == NULL)
		return 0;

	if (NUMERIC_IS_NAN(num))
		fprintf(stderr, "Cannot convert NaN to long long int(%d)", sizeof(long long int));

	InitVar(&x);
	SetVarFromNum(num, &x);

	str = GetStrFromVar(&x, 0); /* dscale = 0 produces rounding */

	FreeVar(&x);

/*	result = atoi(str); */
#ifdef __MINGW32__
	sscanf(str,"%I64d",&result);
#else
	sscanf(str,"%lld",&result);
#endif
	xfree(str);

	return result;
}


extern	Numeric
DoubleToNumeric(
	double	val)
{
	Numeric		res;
	NumericVar	result;
	char		buf[DBL_DIG + 100];

	if (isnan(val))
		return MakeResult(&const_nan);

	sprintf(buf, "%.*g", DBL_DIG, val);

	InitVar(&result);

	SetVarFromStr(buf, &result);
	res = MakeResult(&result);

	FreeVar(&result);

	return res;
}


extern	double
NumericToDouble(
	Numeric	num)
{
	char	   *tmp;
	double		result;

	if (NUMERIC_IS_NAN(num))	{
		return	NAN;
	}

	tmp = NumericOutput(num);
	result = atof(tmp);
	xfree(tmp);

	return result;
}

#ifdef NUMERIC_DEBUG

/* ----------
 * dump_numeric() - Dump a value in the db storage format for debugging
 * ----------
 */
static void
dump_numeric(
	char	*str,
	Numeric num)
{
	int			i;

	printf("%s: NUMERIC w=%d r=%d d=%d ", str, num->n_weight, num->n_rscale,
		   NUMERIC_DSCALE(num));
	switch	(NUMERIC_SIGN(num))	{
	  case NUMERIC_POS:
		printf("POS");
		break;
	  case NUMERIC_NEG:
		printf("NEG");
		break;
	  case NUMERIC_NAN:
		printf("NaN");
		break;
	  default:
		printf("SIGN=0x%x", NUMERIC_SIGN(num));
		break;
	}

	for (i = 0; i < num->varlen - NUMERIC_HDRSZ; i++)
		printf(" %d %d", (num->n_data[i] >> 4) & 0x0f, num->n_data[i] & 0x0f);
	printf("\n");
}


/* ----------
 * dump_var() - Dump a value in the variable format for debugging
 * ----------
 */
static void
dump_var(
	char	*str,
	NumericVar	*var)
{
	int			i;

	printf("%s: VAR w=%d r=%d d=%d ", str, var->weight, var->rscale,
		   var->dscale);
	switch	(var->sign)	{
	  case NUMERIC_POS:
		printf("POS");
		break;
	  case NUMERIC_NEG:
		printf("NEG");
		break;
	  case NUMERIC_NAN:
		printf("NaN");
		break;
	  default:
		printf("SIGN=0x%x", var->sign);
		break;
	}

	for (i = 0; i < var->ndigits; i++)
		printf(" %d", var->digits[i]);

	printf("\n");
}

#endif	 /* NUMERIC_DEBUG */


static void
AllocateVar(
	NumericVar	*var,
	int			ndigits)
{
	digitbuf_free(var->buf);
	var->buf = digitbuf_alloc(ndigits + 1);
	var->buf[0] = 0;
	var->digits = var->buf + 1;
	var->ndigits = ndigits;
}


static void
FreeVar(
	NumericVar	*var)
{
	digitbuf_free(var->buf);
	var->buf = NULL;
	var->digits = NULL;
	var->sign = NUMERIC_NAN;
}


static void
ZeroVar(
	NumericVar	*var)
{
	digitbuf_free(var->buf);
	var->buf = NULL;
	var->digits = NULL;
	var->ndigits = 0;
	var->weight = 0;			/* by convention; doesn't really matter */
	var->sign = NUMERIC_POS;	/* anything but NAN... */
}


static void
SetVarFromStr(
	char	*str,
	NumericVar *dest)
{
	char	   *cp = str;
	Bool		have_dp = FALSE;
	int			i = 0;

	while	(*cp)	{
		if (!isspace(*cp))
			break;
		cp++;
	}

	AllocateVar(dest, strlen(cp));
	dest->weight = -1;
	dest->dscale = 0;
	dest->sign = NUMERIC_POS;

	switch	(*cp)	{
		case '+':
			dest->sign = NUMERIC_POS;
			cp++;
			break;

		case '-':
			dest->sign = NUMERIC_NEG;
			cp++;
			break;
	}

	if		(*cp == '.')	{
		have_dp = TRUE;
		cp++;
	}

	while	(	(  *cp  !=  0  )
			&&	(  !isdigit(*cp)  ) )	cp ++;

	while	(*cp)	{
		if		(isdigit(*cp))	{
			dest->digits[i++] = *cp++ - '0';
			if (!have_dp)
				dest->weight++;
			else
				dest->dscale++;
		} else
		if (*cp == '.')	{
			if (have_dp)
				fprintf(stderr, "Bad numeric input format '%s'", str);
			have_dp = TRUE;
			cp++;
		} else
		if		(*cp == 'e' || *cp == 'E')
			break;
		else
			cp ++;
	}
	dest->ndigits = i;

	/* Handle exponent, if any */
	if		(*cp == 'e' || *cp == 'E')	{
		long		exponent;
		char	   *endptr;

		cp++;
		exponent = strtol(cp, &endptr, 10);
		if (endptr == cp)
			fprintf(stderr, "Bad numeric input format '%s'", str);
		cp = endptr;
		if (exponent > NUMERIC_MAX_PRECISION ||
			exponent < -NUMERIC_MAX_PRECISION)
			fprintf(stderr, "Bad numeric input format '%s'", str);
		dest->weight += (int) exponent;
		dest->dscale -= (int) exponent;
		if (dest->dscale < 0)
			dest->dscale = 0;
	}

	/* Should be nothing left but spaces */
	while	(*cp)	{
		if (!isspace(*cp))
			fprintf(stderr, "Bad numeric input format '%s'", str);
		cp++;
	}

	/* Strip any leading zeroes */
	while	(dest->ndigits > 0 && *(dest->digits) == 0)	{
		(dest->digits)++;
		(dest->weight)--;
		(dest->ndigits)--;
	}
	if (dest->ndigits == 0)
		dest->weight = 0;

	dest->rscale = dest->dscale;
}

static void
SetVarFromChar(
	char	c,
	NumericVar *dest)
{
	AllocateVar(dest, 1);
	dest->weight = 0;
	dest->sign = NUMERIC_POS;

	if		(  isdigit(c)  ) {
		dest->digits[0] = c - '0';
	} else {
		dest->digits[0] = 0;
	}
	dest->dscale = 0;
	dest->ndigits = 1;

	dest->rscale = dest->dscale;
}

static void
SetVarFromNum(
	Numeric	num,
	NumericVar	*dest)
{
	NumericDigit *digit;
	int			i;
	int			n;

	n = num->varlen - NUMERIC_HDRSZ;	/* number of digit-pairs in packed
										 * fmt */

	AllocateVar(dest, n * 2);

	dest->weight = num->n_weight;
	dest->rscale = num->n_rscale;
	dest->dscale = NUMERIC_DSCALE(num);
	dest->sign = NUMERIC_SIGN(num);

	digit = dest->digits;

	for	( i = 0; i < n ; i++ )	{
		unsigned char digitpair = num->n_data[i];

		*digit++ = (digitpair >> 4) & 0x0f;
		*digit++ = digitpair & 0x0f;
	}
}


static void
SetVarFromVar(
	NumericVar	*value,
	NumericVar	*dest)
{
	NumericDigit *newbuf;

	newbuf = digitbuf_alloc(value->ndigits + 1);
	newbuf[0] = 0;				/* spare digit for rounding */
	memcpy(newbuf + 1, value->digits, value->ndigits);

	digitbuf_free(dest->buf);

	memcpy(dest, value, sizeof(NumericVar));
	dest->buf = newbuf;
	dest->digits = newbuf + 1;
}

static char *
GetStrFromVar(
	NumericVar	*var,
	int dscale)
{
	char	   *str;
	char	   *cp;
	int			i;
	int			d;

	i = dscale + var->weight + 1;
	if		(i >= 0 && var->ndigits > i)	{
		int			carry = (var->digits[i] > 4) ? 1 : 0;

		var->ndigits = i;

		while	(carry)	{
			carry += var->digits[--i];
			var->digits[i] = carry % 10;
			carry /= 10;
		}

		if		(i < 0)	{
			assert(i == -1);	/* better not have added more than 1 digit */
			assert(var->digits > var->buf);
			var->digits--;
			var->ndigits++;
			var->weight++;
		}
	}
	else
		var->ndigits = MAX(0, MIN(i, var->ndigits));

	str = xmalloc(MAX(0, dscale) + MAX(0, var->weight) + 4);
	cp = str;

	if (var->sign == NUMERIC_NEG)
		*cp++ = '-';

	i = MAX(var->weight, 0);
	d = 0;

	while	(i >= 0)	{
		if (i <= var->weight && d < var->ndigits)
			*cp++ = var->digits[d++] + '0';
		else
			*cp++ = '0';
		i--;
	}

	if		(dscale > 0)	{
		*cp++ = '.';
		while	(i >= -dscale)	{
			if (i <= var->weight && d < var->ndigits)
				*cp++ = var->digits[d++] + '0';
			else
				*cp++ = '0';
			i--;
		}
	}

	*cp = '\0';
	return str;
}


static Numeric
MakeResult(
	NumericVar	*var)
{
	Numeric		result;
	NumericDigit *digit = var->digits;
	int			weight = var->weight;
	int			sign = var->sign;
	int			n;
	int			i,
				j;

	if	(sign == NUMERIC_NAN)	{
		result = (Numeric) xmalloc(NUMERIC_HDRSZ);
		result->varlen = NUMERIC_HDRSZ;
		result->n_weight = 0;
		result->n_rscale = 0;
		result->n_sign_dscale = NUMERIC_NAN;
		dump_numeric("MakeResult()", result);
		return result;
	}

	n = MAX(0, MIN(var->ndigits, var->weight + var->rscale + 1));

	while	(n > 0 && *digit == 0)	{
		digit++;
		weight--;
		n--;
	}
	while (n > 0 && digit[n - 1] == 0)
		n--;

	if		(n == 0)	{
		weight = 0;
		sign = NUMERIC_POS;
	}

	result = (Numeric) xmalloc(NUMERIC_HDRSZ + (n + 1) / 2);
	result->varlen = NUMERIC_HDRSZ + (n + 1) / 2;
	result->n_weight = weight;
	result->n_rscale = var->rscale;
	result->n_sign_dscale = sign |
		((int) var->dscale & NUMERIC_DSCALE_MASK);

	i = 0;
	j = 0;
	while	(j < n)	{
		unsigned char digitpair = digit[j++] << 4;

		if (j < n)
			digitpair |= digit[j++];
		result->n_data[i++] = digitpair;
	}

	dump_numeric("MakeResult()", result);
	return result;
}

static void
ApplyPrecision(
	NumericVar *var,
	int			precision,
	int			scale)
{
	int			maxweight;
	int			i;

	maxweight = precision - scale;

	i = scale + var->weight + 1;
	if		(  i >= 0 && var->ndigits > i)	{
		int		carry = (var->digits[i] > 4) ? 1 : 0;

		var->ndigits = i;
		while	(carry)	{
			carry += var->digits[--i];
			var->digits[i] = carry % 10;
			carry /= 10;
		}

		if		(  i  <  0  )	{
			assert(i == -1);	/* better not have added more than 1 digit */
			assert(var->digits > var->buf);
			var->digits--;
			var->ndigits++;
			var->weight++;
		}
	} else {
		var->ndigits = MAX(0, MIN(i, var->ndigits));
	}

	if		(  var->weight  >=  maxweight  )	{
		/* Determine true weight; and check for all-zero result */
		int		tweight = var->weight;

		for	( i = 0; i < var->ndigits; i++ )	{
			if (var->digits[i])
				break;
			tweight--;
		}

		if (tweight >= maxweight && i < var->ndigits)
			fprintf(stderr, "overflow on numeric "
			  "ABS(value) >= 10^%d for field with precision %d scale %d \n",
				 tweight, precision, scale);
	}

	var->rscale = scale;
	var->dscale = scale;
}

static int
CmpVar(
	NumericVar	*var1,
	NumericVar	*var2)
{
	if		(  var1->ndigits  ==  0  )	{
		if (var2->ndigits == 0)
			return 0;
		if (var2->sign == NUMERIC_NEG)
			return 1;
		return -1;
	}
	if		(  var2->ndigits  ==  0  )	{
		if (var1->sign == NUMERIC_POS)
			return 1;
		return -1;
	}

	if		(  var1->sign  ==  NUMERIC_POS  )	{
		if (var2->sign == NUMERIC_NEG)
			return 1;
		return CmpAbs(var1, var2);
	}

	if (var2->sign == NUMERIC_POS)
		return -1;

	return	CmpAbs(var2, var1);
}


static	void
AddVar(
	NumericVar	*var1,
	NumericVar	*var2,
	NumericVar	*result)
{
	if		(  var1->sign  ==  NUMERIC_POS  )	{
		if		(  var2->sign  ==  NUMERIC_POS  )	{
			AddAbs(var1, var2, result);
			result->sign = NUMERIC_POS;
		} else {
			switch	(CmpAbs(var1, var2))	{
			  case 0:
				ZeroVar(result);
				result->rscale = MAX(var1->rscale, var2->rscale);
				result->dscale = MAX(var1->dscale, var2->dscale);
				break;
			  case 1:
				SubAbs(var1, var2, result);
				result->sign = NUMERIC_POS;
				break;
			  case -1:
				SubAbs(var2, var1, result);
				result->sign = NUMERIC_NEG;
				break;
			}
		}
	} else {
		if		(  var2->sign  ==  NUMERIC_POS  )	{
			switch	(CmpAbs(var1, var2))	{
			  case 0:
				ZeroVar(result);
				result->rscale = MAX(var1->rscale, var2->rscale);
				result->dscale = MAX(var1->dscale, var2->dscale);
				break;
			  case 1:
				SubAbs(var1, var2, result);
				result->sign = NUMERIC_NEG;
				break;
			  case -1:
				SubAbs(var2, var1, result);
				result->sign = NUMERIC_POS;
				break;
			}
		} else {
			AddAbs(var1, var2, result);
			result->sign = NUMERIC_NEG;
		}
	}
}


static	void
SubVar(
	NumericVar	*var1,
	NumericVar	*var2,
	NumericVar	*result)
{
	if		(  var1->sign  ==  NUMERIC_POS  )	{
		if		(  var2->sign  ==  NUMERIC_NEG  )	{
			AddAbs(var1, var2, result);
			result->sign = NUMERIC_POS;
		} else {
			switch	(CmpAbs(var1, var2))	{
			  case	0:
				ZeroVar(result);
				result->rscale = MAX(var1->rscale, var2->rscale);
				result->dscale = MAX(var1->dscale, var2->dscale);
				break;
			  case 1:
				SubAbs(var1, var2, result);
				result->sign = NUMERIC_POS;
				break;
			  case -1:
				SubAbs(var2, var1, result);
				result->sign = NUMERIC_NEG;
				break;
			}
		}
	} else {
		if		(  var2->sign  ==  NUMERIC_NEG  )	{
			switch	(CmpAbs(var1, var2))	{
			  case 0:
				ZeroVar(result);
				result->rscale = MAX(var1->rscale, var2->rscale);
				result->dscale = MAX(var1->dscale, var2->dscale);
				break;
			  case 1:
				SubAbs(var1, var2, result);
				result->sign = NUMERIC_NEG;
				break;
			  case -1:
				SubAbs(var2, var1, result);
				result->sign = NUMERIC_POS;
				break;
			}
		} else {
			AddAbs(var1, var2, result);
			result->sign = NUMERIC_NEG;
		}
	}
}


static	void
MulVar(
	NumericVar	*var1,
	NumericVar	*var2,
	NumericVar *result)
{
	NumericDigit *res_buf;
	NumericDigit *res_digits;
	int			res_ndigits;
	int			res_weight;
	int			res_sign;
	int			i,
				ri,
				i1,
				i2;
	long		sum = 0;

	res_weight = var1->weight + var2->weight + 2;
	res_ndigits = var1->ndigits + var2->ndigits + 1;
	if		(  var1->sign  ==  var2->sign  ) {
		res_sign = NUMERIC_POS;
	} else {
		res_sign = NUMERIC_NEG;
	}

	res_buf = digitbuf_alloc(res_ndigits);
	res_digits = res_buf;
	memset(res_digits, 0, res_ndigits);

	ri = res_ndigits;
	for	( i1 = var1->ndigits - 1; i1 >= 0; i1-- )	{
		sum = 0;
		i = --ri;

		for	( i2 = var2->ndigits - 1; i2 >= 0; i2-- )	{
			sum = sum + res_digits[i] + var1->digits[i1] * var2->digits[i2];
			res_digits[i--] = sum % 10;
			sum /= 10;
		}
		res_digits[i] = sum;
	}

	i = res_weight + global_rscale + 2;
	if		(i >= 0 && i < res_ndigits)	{
		sum = (res_digits[i] > 4) ? 1 : 0;
		res_ndigits = i;
		i--;
		while	(sum)	{
			sum += res_digits[i];
			res_digits[i--] = sum % 10;
			sum /= 10;
		}
	}

	while	(res_ndigits > 0 && *res_digits == 0)		{
		res_digits++;
		res_weight--;
		res_ndigits--;
	}
	while (res_ndigits > 0 && res_digits[res_ndigits - 1] == 0)
		res_ndigits--;

	if		(  res_ndigits  ==  0  )	{
		res_sign = NUMERIC_POS;
		res_weight = 0;
	}

	digitbuf_free(result->buf);
	result->buf = res_buf;
	result->digits = res_digits;
	result->ndigits = res_ndigits;
	result->weight = res_weight;
	result->rscale = global_rscale;
	result->sign = res_sign;
}

static	void
DivVar(
	NumericVar	*var1,
	NumericVar	*var2,
	NumericVar *result)
{
	NumericDigit *res_digits;
	int			res_ndigits;
	int			res_sign;
	int			res_weight;
	NumericVar	dividend;
	NumericVar	divisor[10];
	int			ndigits_tmp;
	int			weight_tmp;
	int			rscale_tmp;
	int			ri;
	int			i;
	long		guess;
	long		first_have;
	long		first_div;
	int			first_nextdigit;
	int			stat = 0;

	ndigits_tmp = var2->ndigits + 1;
	if (ndigits_tmp == 1)
		fprintf(stderr, "division by zero on numeric");

	if		(  var1->sign  ==  var2->sign  ) {
		res_sign = NUMERIC_POS;
	} else {
		res_sign = NUMERIC_NEG;
	}
	res_weight = var1->weight - var2->weight + 1;
	res_ndigits = global_rscale + res_weight;
	if (res_ndigits <= 0)
		res_ndigits = 1;

	if		(  var1->ndigits  ==  0  )	{
		ZeroVar(result);
		result->rscale = global_rscale;
		return;
	}

	InitVar(&dividend);
	for (i = 1; i < 10; i++)
		InitVar(&divisor[i]);

	divisor[1].ndigits = ndigits_tmp;
	divisor[1].rscale = var2->ndigits;
	divisor[1].sign = NUMERIC_POS;
	divisor[1].buf = digitbuf_alloc(ndigits_tmp);
	divisor[1].digits = divisor[1].buf;
	divisor[1].digits[0] = 0;
	memcpy(&(divisor[1].digits[1]), var2->digits, ndigits_tmp - 1);

	dividend.ndigits = var1->ndigits;
	dividend.weight = 0;
	dividend.rscale = var1->ndigits;
	dividend.sign = NUMERIC_POS;
	dividend.buf = digitbuf_alloc(var1->ndigits);
	dividend.digits = dividend.buf;
	memcpy(dividend.digits, var1->digits, var1->ndigits);

	digitbuf_free(result->buf);
	result->buf = digitbuf_alloc(res_ndigits + 2);
	res_digits = result->buf;
	result->digits = res_digits;
	result->ndigits = res_ndigits;
	result->weight = res_weight;
	result->rscale = global_rscale;
	result->sign = res_sign;
	res_digits[0] = 0;

	first_div = divisor[1].digits[1] * 10;
	if (ndigits_tmp > 2)
		first_div += divisor[1].digits[2];

	first_have = 0;
	first_nextdigit = 0;

	weight_tmp = 1;
	rscale_tmp = divisor[1].rscale;

	for	( ri = 0; ri <= res_ndigits; ri++ )	{
		first_have = first_have * 10;
		if (first_nextdigit >= 0 && first_nextdigit < dividend.ndigits)
			first_have += dividend.digits[first_nextdigit];
		first_nextdigit++;

		guess = (first_have * 10) / first_div + 1;
		if (guess > 9)
			guess = 9;

		while	(  guess  >  0  )	{
			if		(  divisor[guess].buf  ==  NULL  )	{
				int			i;
				long		sum = 0;

				memcpy(&divisor[guess], &divisor[1], sizeof(NumericVar));
				divisor[guess].buf = digitbuf_alloc(divisor[guess].ndigits);
				divisor[guess].digits = divisor[guess].buf;
				for	( i = divisor[1].ndigits - 1; i >= 0; i-- )	{
					sum += divisor[1].digits[i] * guess;
					divisor[guess].digits[i] = sum % 10;
					sum /= 10;
				}
			}

			divisor[guess].weight = weight_tmp;
			divisor[guess].rscale = rscale_tmp;

			stat = CmpAbs(&dividend, &divisor[guess]);
			if (stat >= 0)
				break;

			guess--;
		}

		res_digits[ri + 1] = guess;
		if		(  stat  ==  0  )	{
			ri++;
			break;
		}

		weight_tmp--;
		rscale_tmp++;

		if (guess == 0)
			continue;

		SubAbs(&dividend, &divisor[guess], &dividend);

		first_nextdigit = dividend.weight - weight_tmp;
		first_have = 0;
		if (first_nextdigit >= 0 && first_nextdigit < dividend.ndigits)
			first_have = dividend.digits[first_nextdigit];
		first_nextdigit++;
	}

	result->ndigits = ri + 1;
	if		(  ri  ==  res_ndigits + 1  )	{
		int		carry = (res_digits[ri] > 4) ? 1 : 0;

		result->ndigits = ri;
		res_digits[ri] = 0;

		while	(  carry && ri > 0  )	{
			carry += res_digits[--ri];
			res_digits[ri] = carry % 10;
			carry /= 10;
		}
	}

	while	(  result->ndigits  >  0  &&  *(result->digits)  ==  0  )	{
		(result->digits)++;
		(result->weight)--;
		(result->ndigits)--;
	}
	while (result->ndigits > 0 && result->digits[result->ndigits - 1] == 0)
		(result->ndigits)--;
	if (result->ndigits == 0)
		result->sign = NUMERIC_POS;

	digitbuf_free(dividend.buf);
	for (i = 1; i < 10; i++)
		digitbuf_free(divisor[i].buf);
}


static	void
ModVar(
	NumericVar	*var1,
	NumericVar	*var2,
	NumericVar	*result)
{
	NumericVar	tmp;
	int			save_global_rscale;

	InitVar(&tmp);

	save_global_rscale = global_rscale;
	global_rscale = var2->rscale + 2;

	DivVar(var1, var2, &tmp);
	tmp.rscale = var2->rscale;
	tmp.ndigits = MAX(0, MIN(tmp.ndigits, tmp.weight + tmp.rscale + 1));

	global_rscale = var2->rscale;
	MulVar(var2, &tmp, &tmp);

	SubVar(var1, &tmp, result);

	global_rscale = save_global_rscale;
	FreeVar(&tmp);
}


static	void
CeilVar(
	NumericVar	*var,
	NumericVar	*result)
{
	NumericVar	tmp;

	InitVar(&tmp);
	SetVarFromVar(var, &tmp);

	tmp.rscale = 0;
	tmp.ndigits = MIN(tmp.ndigits, MAX(0, tmp.weight + 1));
	if (tmp.sign == NUMERIC_POS && CmpVar(var, &tmp) != 0)
		AddVar(&tmp, &const_one, &tmp);

	SetVarFromVar(&tmp, result);
	FreeVar(&tmp);
}

static	void
FloorVar(
	NumericVar	*var,
	NumericVar	*result)
{
	NumericVar	tmp;

	InitVar(&tmp);
	SetVarFromVar(var, &tmp);

	tmp.rscale = 0;
	tmp.ndigits = MIN(tmp.ndigits, MAX(0, tmp.weight + 1));
	if (tmp.sign == NUMERIC_NEG && CmpVar(var, &tmp) != 0)
		SubVar(&tmp, &const_one, &tmp);

	SetVarFromVar(&tmp, result);
	FreeVar(&tmp);
}


static	void
SqrtVar(
	NumericVar	*arg,
	NumericVar *result)
{
	NumericVar	tmp_arg;
	NumericVar	tmp_val;
	NumericVar	last_val;
	int			res_rscale;
	int			save_global_rscale;
	int			stat;

	save_global_rscale = global_rscale;
	global_rscale += 8;
	res_rscale = global_rscale;

	stat = CmpVar(arg, &const_zero);
	if		(  stat  ==  0  )	{
		SetVarFromVar(&const_zero, result);
		result->rscale = res_rscale;
		result->sign = NUMERIC_POS;
		return;
	}

	if (stat < 0)
		fprintf(stderr, "math error on numeric - cannot compute SQRT of negative value");

	InitVar(&tmp_arg);
	InitVar(&tmp_val);
	InitVar(&last_val);

	SetVarFromVar(arg, &tmp_arg);
	SetVarFromVar(result, &last_val);

	digitbuf_free(result->buf);
	result->buf = digitbuf_alloc(1);
	result->digits = result->buf;
	result->digits[0] = tmp_arg.digits[0] / 2;
	if (result->digits[0] == 0)
		result->digits[0] = 1;
	result->ndigits = 1;
	result->weight = tmp_arg.weight / 2;
	result->rscale = res_rscale;
	result->sign = NUMERIC_POS;

	while	(TRUE)	{
		DivVar(&tmp_arg, result, &tmp_val);

		AddVar(result, &tmp_val, result);
		DivVar(result, &const_two, result);

		if (CmpVar(&last_val, result) == 0)
			break;
		SetVarFromVar(result, &last_val);
	}

	FreeVar(&last_val);
	FreeVar(&tmp_val);
	FreeVar(&tmp_arg);

	global_rscale = save_global_rscale;
	DivVar(result, &const_one, result);
}


static void
ExpVar(
	NumericVar	*arg,
	NumericVar	*result)
{
	NumericVar	x;
	NumericVar	xpow;
	NumericVar	ifac;
	NumericVar	elem;
	NumericVar	ni;
	int			d;
	int			i;
	int			ndiv2 = 0;
	Bool		xneg = FALSE;
	int			save_global_rscale;

	InitVar(&x);
	InitVar(&xpow);
	InitVar(&ifac);
	InitVar(&elem);
	InitVar(&ni);

	SetVarFromVar(arg, &x);

	if		(  x.sign  ==  NUMERIC_NEG  )	{
		xneg = TRUE;
		x.sign = NUMERIC_POS;
	}

	save_global_rscale = global_rscale;
	global_rscale = 0;
	for	( i = x.weight, d = 0; i >= 0; i--, d++ )	{
		global_rscale *= 10;
		if (d < x.ndigits)
			global_rscale += x.digits[d];
		if (global_rscale >= 1000)
			fprintf(stderr, "argument for EXP() too big");
	}

	global_rscale = global_rscale / 2 + save_global_rscale + 8;

	while	(  CmpVar(&x, &const_one)  >  0  )	{
		ndiv2++;
		global_rscale++;
		DivVar(&x, &const_two, &x);
	}

	AddVar(&const_one, &x, result);
	SetVarFromVar(&x, &xpow);
	SetVarFromVar(&const_one, &ifac);
	SetVarFromVar(&const_one, &ni);

	for	( i = 2; TRUE; i++ )	{
		AddVar(&ni, &const_one, &ni);
		MulVar(&xpow, &x, &xpow);
		MulVar(&ifac, &ni, &ifac);
		DivVar(&xpow, &ifac, &elem);

		if (elem.ndigits == 0)
			break;

		AddVar(result, &elem, result);
	}

	while (ndiv2-- > 0)
		MulVar(result, result, result);

	global_rscale = save_global_rscale;
	if (xneg)
		DivVar(&const_one, result, result);
	else
		DivVar(result, &const_one, result);

	result->sign = NUMERIC_POS;

	FreeVar(&x);
	FreeVar(&xpow);
	FreeVar(&ifac);
	FreeVar(&elem);
	FreeVar(&ni);
}


static	void
LnVar(
	NumericVar	*arg,
	NumericVar *result)
{
	NumericVar	x;
	NumericVar	xx;
	NumericVar	ni;
	NumericVar	elem;
	NumericVar	fact;
	int			i;
	int			save_global_rscale;

	if (CmpVar(arg, &const_zero) <= 0)
		fprintf(stderr, "math error on numeric - cannot compute LN of value <= zero");

	save_global_rscale = global_rscale;
	global_rscale += 8;

	InitVar(&x);
	InitVar(&xx);
	InitVar(&ni);
	InitVar(&elem);
	InitVar(&fact);

	SetVarFromVar(&const_two, &fact);
	SetVarFromVar(arg, &x);

	while (CmpVar(&x, &const_two) >= 0)	{
		SqrtVar(&x, &x);
		MulVar(&fact, &const_two, &fact);
	}
	SetVarFromStr("0.5", &elem);
	while (CmpVar(&x, &elem) <= 0)	{
		SqrtVar(&x, &x);
		MulVar(&fact, &const_two, &fact);
	}

	SubVar(&x, &const_one, result);
	AddVar(&x, &const_one, &elem);
	DivVar(result, &elem, result);
	SetVarFromVar(result, &xx);
	MulVar(result, result, &x);

	SetVarFromVar(&const_one, &ni);

	for (i = 2; TRUE; i++)	{
		AddVar(&ni, &const_two, &ni);
		MulVar(&xx, &x, &xx);
		DivVar(&xx, &ni, &elem);

		if (CmpVar(&elem, &const_zero) == 0)
			break;

		AddVar(result, &elem, result);
	}

	global_rscale = save_global_rscale;
	MulVar(result, &fact, result);

	FreeVar(&x);
	FreeVar(&xx);
	FreeVar(&ni);
	FreeVar(&elem);
	FreeVar(&fact);
}

static	void
LogVar(
	NumericVar	*base,
	NumericVar	*num,
	NumericVar *result)
{
	NumericVar	ln_base;
	NumericVar	ln_num;

	global_rscale += 8;

	InitVar(&ln_base);
	InitVar(&ln_num);

	LnVar(base, &ln_base);
	LnVar(num, &ln_num);

	global_rscale -= 8;

	DivVar(&ln_num, &ln_base, result);

	FreeVar(&ln_num);
	FreeVar(&ln_base);
}

static void
PowerVar(
	NumericVar	*base,
	NumericVar	*exp,
	NumericVar *result)
{
	NumericVar	ln_base;
	NumericVar	ln_num;
	int			save_global_rscale;

	save_global_rscale = global_rscale;
	global_rscale += global_rscale / 3 + 8;

	InitVar(&ln_base);
	InitVar(&ln_num);

	LnVar(base, &ln_base);
	MulVar(&ln_base, exp, &ln_num);

	global_rscale = save_global_rscale;

	ExpVar(&ln_num, result);

	FreeVar(&ln_num);
	FreeVar(&ln_base);

}

static int
CmpAbs(
	NumericVar	*var1,
	NumericVar	*var2)
{
	int			i1 = 0;
	int			i2 = 0;
	int			w1 = var1->weight;
	int			w2 = var2->weight;
	int			stat;

	while	(w1 > w2 && i1 < var1->ndigits)	{
		if (var1->digits[i1++] != 0)
			return 1;
		w1--;
	}
	while	(w2 > w1 && i2 < var2->ndigits)	{
		if (var2->digits[i2++] != 0)
			return -1;
		w2--;
	}

	if		(  w1  ==  w2  )	{
		while	(i1 < var1->ndigits && i2 < var2->ndigits)	{
			stat = var1->digits[i1++] - var2->digits[i2++];
			if		(stat)	{
				if (stat > 0)
					return 1;
				return -1;
			}
		}
	}

	while	(  i1  <  var1->ndigits  )	{
		if (var1->digits[i1++] != 0)
			return 1;
	}
	while	(  i2  <  var2->ndigits  )	{
		if (var2->digits[i2++] != 0)
			return -1;
	}

	return 0;
}


static	void
AddAbs(
	NumericVar	*var1,
	NumericVar	*var2,
	NumericVar *result)
{
	NumericDigit *res_buf;
	NumericDigit *res_digits;
	int			res_ndigits;
	int			res_weight;
	int			res_rscale;
	int			res_dscale;
	int			i,
				i1,
				i2;
	int			carry = 0;

	res_weight = MAX(var1->weight, var2->weight) + 1;
	res_rscale = MAX(var1->rscale, var2->rscale);
	res_dscale = MAX(var1->dscale, var2->dscale);
	res_ndigits = res_rscale + res_weight + 1;
	if (res_ndigits <= 0)
		res_ndigits = 1;

	res_buf = digitbuf_alloc(res_ndigits);
	res_digits = res_buf;

	i1 = res_rscale + var1->weight + 1;
	i2 = res_rscale + var2->weight + 1;
	for	( i = res_ndigits - 1; i >= 0; i-- )	{
		i1--;
		i2--;
		if (i1 >= 0 && i1 < var1->ndigits)
			carry += var1->digits[i1];
		if (i2 >= 0 && i2 < var2->ndigits)
			carry += var2->digits[i2];

		res_digits[i] = carry % 10;
		carry /= 10;
	}

	while	(res_ndigits > 0 && *res_digits == 0)	{
		res_digits++;
		res_weight--;
		res_ndigits--;
	}
	while (res_ndigits > 0 && res_digits[res_ndigits - 1] == 0)
		res_ndigits--;

	if (res_ndigits == 0)
		res_weight = 0;

	digitbuf_free(result->buf);
	result->ndigits = res_ndigits;
	result->buf = res_buf;
	result->digits = res_digits;
	result->weight = res_weight;
	result->rscale = res_rscale;
	result->dscale = res_dscale;
}

static	void
SubAbs(
	NumericVar	*var1,
	NumericVar	*var2,
	NumericVar	*result)
{
	NumericDigit *res_buf;
	NumericDigit *res_digits;
	int			res_ndigits;
	int			res_weight;
	int			res_rscale;
	int			res_dscale;
	int			i,
				i1,
				i2;
	int			borrow = 0;

	res_weight = var1->weight;
	res_rscale = MAX(var1->rscale, var2->rscale);
	res_dscale = MAX(var1->dscale, var2->dscale);
	res_ndigits = res_rscale + res_weight + 1;
	if (res_ndigits <= 0)
		res_ndigits = 1;

	res_buf = digitbuf_alloc(res_ndigits);
	res_digits = res_buf;

	i1 = res_rscale + var1->weight + 1;
	i2 = res_rscale + var2->weight + 1;
	for	(i = res_ndigits - 1; i >= 0; i--)	{
		i1--;
		i2--;
		if (i1 >= 0 && i1 < var1->ndigits)
			borrow += var1->digits[i1];
		if (i2 >= 0 && i2 < var2->ndigits)
			borrow -= var2->digits[i2];

		if		(borrow < 0)	{
			res_digits[i] = borrow + 10;
			borrow = -1;
		} else {
			res_digits[i] = borrow;
			borrow = 0;
		}
	}

	while	(res_ndigits > 0 && *res_digits == 0)	{
		res_digits++;
		res_weight--;
		res_ndigits--;
	}
	while (res_ndigits > 0 && res_digits[res_ndigits - 1] == 0)
		res_ndigits--;

	if (res_ndigits == 0)
		res_weight = 0;

	digitbuf_free(result->buf);
	result->ndigits = res_ndigits;
	result->buf = res_buf;
	result->digits = res_digits;
	result->weight = res_weight;
	result->rscale = res_rscale;
	result->dscale = res_dscale;
}

extern	void
NumericFormat(
	char	*buf,
	char	*format,
	Numeric	num)
{
	char	*f
	,		*p
	,		sup;
	size_t	len;
	int		fPSign
	,		fNSign
	,		fMinus
	,		fMark
	,		fSup
	,		fSmall;
	char	*str
	,		*q
	,		*qq;
	Numeric	nnum;

	if		(  format  ==  NULL  ) {
		format = "ZZZZZZZZZ9";
	}
	if		(  NumericNegative(num)  )	{
		fMinus = TRUE;
		nnum = NumericUMinus(num);
		str = NumericOutput(nnum);
		NumericFree(nnum);
	} else {
		fMinus = FALSE;
		str = NumericOutput(num);
	}

	fPSign = FALSE;
	fNSign = FALSE;
	fSup = FALSE;
	fSmall = FALSE;
	sup = ' ';
	for	( f = format ; *f != '\0' ; f ++ )	{
		switch	(*f)	{
		  case	'\\':
			sup = *f;
			fSup = TRUE;
			break;
		  case	'Z':
			sup = ' ';
			fSup = TRUE;
			break;
		  case	'-':
			if		(  fNSign  )	{
				fSup = TRUE;
			}
			fNSign = TRUE;
			break;
		  case	'+':
			if		(  fPSign  )	{
				fSup = TRUE;
			}
			fPSign = TRUE;
			break;
		  case	'.':
			fSmall = TRUE;
			break;
		  default:
			break;
		}
	}

	for	( len = 0 , p = format ; *p != 0 && *p != '.' ; len ++, p ++ );		
	for	( q = str ; *q != 0 && *q != '.' ; q ++ );
	qq = q - 1;
	q ++;

	if		(  fSmall  ) {
		p = buf + len;
		f = format + len;
		while	(  *f  !=  0  ) {
			switch	(*f) {
			  case	'9':
				*p = *q;
				q ++;
				break;
			  default:
				*p = *f;
				break;
			}
			f ++;
			p ++;
		}
		*p = 0;
		len --;
	} else {
		*(p + 1) = 0;
	}

	p = buf + len;
	f = format + len;

	if		(  !fSup  )	{
		for	(  ; f >= format ; f --, p -- )	{
			switch	(*f)	{
			  case	'9':
				if		(  qq  <  str  )	{
					*p = '0';
				} else {
					*p = *qq;
					qq --;
				}
				break;
			  case	'-':
				if		(  fMinus  )	{
					*p = '-';
				} else {
					*p = ' ';
				}
				break;
			  case	'+':
				if		(  fMinus  )	{
					*p = '-';
				} else {
					*p = '+';
				}
				break;
			  default:
				*p = *f;
				break;
			}
		}
	} else {
		fMark = FALSE;
		for	( ; f >= format ; f --, p -- )	{
			if		(	(  qq  <  str  )
					||	(	(  qq  ==  str  )
						&&	(  *qq  ==  '0'  ) ) ) {
				switch	(*f)	{
				  case	'Z':
				  case	'-':
				  case	'+':
				  case	'\\':
				  case	',':
					if		(	(  fNSign  )
							 &&	(  fMinus  ) )	{
						fNSign = FALSE;
						*p = '-';
						if		(  *f  ==  '-'  )	{
							fMark = TRUE;
						}
					} else
					if		(	(  fPSign   )
							 &&	(  !fMinus  ) )	{
						fPSign = FALSE;
						*p = '+';
						if		(  *f  ==  '+'  )	{
							fMark = TRUE;
						}
					} else
					if		(  !fMark  )	{
						*p = sup;
						fMark = TRUE;
					} else {
						*p = ' ';
					}
					break;
				  case	'9':
					*p = '0';
					break;
				  default:
					*p = *f;
					break;
				}
			} else {
				switch	(*f)	{
				  case	'Z':
				  case	'\\':
				  case	'9':
				  case	'-':
				  case	'+':
					*p = *qq;
					qq --;
					break;
				  default:
					*p = *f;
					break;
				}
			}
		}
	}
	xfree(str);
}

extern	void
NumericFormatToPrecision(
	char	*format,
	int		*precision,
	int		*scale)
{
	Bool	fSmall
	,		fSign;

	if		(  format  ==  NULL  ) {
		*precision = NUMERIC_DEFAULT_PRECISION;
		*scale = NUMERIC_DEFAULT_SCALE;
	} else {
		*precision = 0;
		*scale = 0;
		fSmall = FALSE;
		fSign = FALSE;
		while	(  *format  !=  0  ) {
			switch	(*format)	{
			  case	'-':
			  case	'+':
				if		(  !fSmall  ) {
					fSign = TRUE;
				}
			  case	'Z':
			  case	'\\':
			  case	'9':
				if		(  fSmall  ) {
					(*scale) ++;
				}
				(*precision) ++;
				break;
			  case	'.':
				fSmall = TRUE;
				break;
			  default:
				break;
			}
			format ++;
		}
		if		(  fSign  ) {
			(*precision) --;
		}
	}
}

