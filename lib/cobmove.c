/* 
 * Copyright (C) 1999 - 2003, Rildo Pragana, Jim Noeth, 
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

 *
 * TinyCOBOL Run Time Library -- Main move Module
 *
 
*/

#include "htcoblib.h"

/*
#define DEBUG_RTS 1
#define DEBUG_MOVE_RTS 1
*/

#define COBMV_9_	0
#define COBMV_B_	6
#define COBMV_C_	12
#define COBMV_E_        30
#define COBMV_F_	18
#define COBMV_X_	24
#define COBMV__9	0
#define COBMV__B	1
#define COBMV__C	2
#define COBMV__E	3
#define COBMV__F	4
#define COBMV__X	5
#define COBMV_MAX	255

#ifdef DEBUG_MOVE_RTS
char *StrMovRtn[] = {
  "tcob_move_9_9", "tcob_move_9_b", "tcob_move_9_c", 
  "tcob_move_9_e", "tcob_move_9_f", "tcob_move_9_x",
  "tcob_move_b_9", "tcob_move_b_b", "tcob_move_b_c", 
  "tcob_move_b_e", "tcob_move_b_f", "tcob_move_b_x",
  "tcob_move_c_9", "tcob_move_c_b", "tcob_move_c_c", 
  "tcob_move_c_e", "tcob_move_c_f", "tcob_move_c_x",
  "tcob_move_f_9", "tcob_move_f_b", "tcob_move_f_c", 
  "tcob_move_f_e", "tcob_move_f_f", "tcob_move_f_x",
  "tcob_move_x_9", "tcob_move_x_b", "tcob_move_x_c", 
  "tcob_move_x_e", "tcob_move_x_f", "tcob_move_x_x",
  "tcob_move_e_9", "tcob_move_e_b", "tcob_move_e_c",
  "tcob_move_e_e", "tcob_move_e_f", "tcob_move_e_x"
};
#endif

/*--------------------------------------------------------------------------*\
 |                                                                          |
 |       void tcob_move( struct fld_desc *FieldDescSrc,                     |
 |                      char            *caSrcBuffer,                       |
 |                      struct fld_desc *FieldDescDest,                     |
 |                      char            *caDestBuffer)                      |
 |                                                                          |
 |   Copy the contents of the field described by FieldDescSrc (data is      |
 |   pointed to by caSrcBuffer) to the field described by FieldDescDest     |
 |   (data will be stored in memory pointed to by caDescBuffer).            |
 |                                                                          |
 |   This routine will appropriately convert data (or format it) as it      |
 |   potentially moves from one data type to another. Truncation and        |
 |   padding will also be done in this routine if field sizes differ.       |
 |   Data types that this routine will handle are:                          |
 |                                                                          |
 |   Type  Source Type            Destination Type       Defined As         |
 |    '9'  Numeric Display    Numeric Display    DTYPE_DISPLAY              |
 |    'D'  Accept Display     Accept Display     DTYPE_ACCEP_DISPLAY        |
 |    'C'  Numeric Packed Decimal Numeric Packed Decimal DTYPE_PACKED       |
 |    'A'  Alpha          Alpha          DTYPE_ALPHA                        |
 |    'X'  AlphaNumeric       AlphaNumeric       DTYPE_ALPHANUMERIC         |
 |    'E'  AlphaNumeric       Numeric Edited     DTYPE_EDITED               |
 |    'G'  AlphaNumeric       AlphaNumeric       DTYPE_GROUP                |
 |    'B'  Numeric Bin Int    Numeric Bin Int    DTYPE_BININT               |
 |    'U'  Floating Point     Floating Point     DTYPE_FLOAT                |
 |                                                                          |
 |   The main entry point is tcob_move, which looks at the data types of    |
 |   the source and destinations, then calls a specific routine to handle   |
 |   those specific data types. The routines are listed below, their name   |
 |   is composed of tcob_move_?_?, where the first question mark is the     |
 |   source data type, and the second question mark is the destination      |
 |   data type. Certain data types are grouped together, such as ALPHA,     |
 |   ALPHANUMERIC, GROUP and EDITED (when it is the source). This reduces   |
 |   the number of routines needed to handle the various data types (the    |
 |   list below is without the prefix tcob_move, i.e. _x_x means:           |
 |   tcob_move_x_x).                                                        |
 |                                                                          |
 |   _x_x  _9_x  _b_x  _f_x  _c_x                                           |
 |   _x_9  _9_9  _b_9  _f_9  _c_9                                           |
 |   _x_c  _9_c  _b_b  _f_b  _c_b                                           |
 |   _x_e  _9_b  _b_c  _f_c  _c_c                                           |
 |   _x_f  _9_e  _b_e  _f_e  _c_e                                           |
 |   _x_b  _9_f  _b_f  _f_f  _c_f                                           |
 |                                                                          |
\*-------------------------------------------------------------------------*/

void tcob_move( struct fld_desc *pfldDesc1, char *caData1,
                struct fld_desc *pfldDesc2, char *caData2 ) {
	int	i;
	extern void (*pMovRtn[])(struct fld_desc *, char *,
			struct fld_desc *, char *);

	switch(pfldDesc1->type) {
		case DTYPE_DISPLAY:
			i = COBMV_9_;
			break;
		case DTYPE_ALPHA:
			i = COBMV_X_;
			break;
		case DTYPE_BININT:
			i = COBMV_B_;
			break;
		case DTYPE_PACKED:
			i = COBMV_C_;
			break;
		case DTYPE_ACCEPT_DISPLAY:
			i = COBMV_X_;
			break;
		case DTYPE_EDITED:
//			i = COBMV_X_;
			i = COBMV_E_;
			break;
		case DTYPE_GROUP:
			i = COBMV_X_;
			break;
		case DTYPE_FLOAT:
			i = COBMV_F_;
			break;
		case DTYPE_ALPHANUMERIC:
		case DTYPE_ALPHANUMERICL:
			i = COBMV_X_;
			break;
		default:
			runtime_error(RTERR_INVALID_PIC, pfldDesc1, (void *)caData1);
			return;
	}
	switch(pfldDesc2->type) {
		case DTYPE_DISPLAY:
			i += COBMV__9;
			break;
		case DTYPE_ALPHA:
			i += COBMV__X;
			break;
		case DTYPE_BININT:
			i += COBMV__B;
			break;
		case DTYPE_PACKED:
			i += COBMV__C;
			break;
		case DTYPE_ACCEPT_DISPLAY:
			i += COBMV__X;
			break;
		case DTYPE_EDITED:
			i += COBMV__E;
			break;
		case DTYPE_GROUP:
			i += COBMV__X;
			break;
		case DTYPE_FLOAT:
			i += COBMV__F;
			break;
		case DTYPE_ALPHANUMERIC:
		case DTYPE_ALPHANUMERICL:
			i += COBMV__X;
			break;
		default:
			runtime_error(RTERR_INVALID_PIC, pfldDesc2, (void *)caData2);
			return;
	}

	/* Override for non-elementary moves */
	if ((pfldDesc1->type == DTYPE_GROUP)
	 || (pfldDesc2->type == DTYPE_GROUP)) {
		i = COBMV_X_ + COBMV__X;
	}
	
#ifdef DEBUG_MOVE_RTS
//	fprintf(stderr, "Debug:  tcob_move type = %d\n", i);
	fprintf(stderr, "Debug:  tcob_move type = %d, %s\n", i, StrMovRtn[i]);
#endif
	pMovRtn[i](pfldDesc1, caData1, pfldDesc2, caData2);
}



/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          runtime_error                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

void runtime_error(int iErrorNum, struct fld_desc *pField, void *pData) {
	unsigned int		i, j, k;
	extern int		_iRtErrorNbr[];
	extern char		*_szRtErrorDesc[];

	for(i = 0; _iRtErrorNbr[i] != -1; ++i)
		if(iErrorNum == _iRtErrorNbr[i])
			break;

	fprintf(stderr, "\n\nRun Time Error - ");
	if(_iRtErrorNbr[i] != -1)
		fprintf(stderr, "%s\n", _szRtErrorDesc[i]);
	else
		fprintf(stderr, "Unknown Error\n");

	if(pField) {
		fprintf(stderr, "Field Description: ");
		fprintf(stderr, "len = %ld, type = %c, dec/pscale = %d/%d, all = %d, just_r = %d, signs = %d/%d\n",
			pField->len, pField->type, (char)pField->decimals,
			(char)pField->pscale, pField->all, pField->just_r,
			pField->separate_sign, pField->leading_sign);
	}
	if(!pData) {
		fprintf(stderr, "No data pointer provided\n");
		return;
	}
	
	fprintf(stderr, "Data Dump, Address = %08lX", (unsigned long)pData);
	k = tcob_fldLength(pField);
        if (k > 240) 
           k = 240;
	for(j=0; j<k; j+=24) {
		fprintf(stderr, "\n%04d: ", (unsigned)j);
		for(i = 0; i < 24; ++i) {
			if((i + j) == tcob_fldLength(pField))
				break;
			fprintf(stderr, "%02X ", ((unsigned char *)pData)[j+i]);
		}
		fprintf(stderr, "\n      ");
		for(i = 0; i < 24; ++i) {
			if((i + j) == pField->len)
			if((i + j) == tcob_fldLength(pField))
				break;
			if((((unsigned char *)pData)[i] >= ' ') 
			&& (((unsigned char *)pData)[i] < 0x7f))
				fprintf(stderr, " %c ", ((unsigned char *)pData)[j+i]);
			else
				fprintf(stderr, "   ");
		}
	}
	fprintf(stderr, "\n\n");
}

int _iRtErrorNbr[] = {
	RTERR_INVALID_DATA,
	RTERR_INVALID_PIC,
	-1
};

char *_szRtErrorDesc[] = {
	"Invalid Data Content",
	"Invalid Picture Structure",
	(char *)0
};


/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          _DUMP_                                        |
 |                                                                        |
\*------------------------------------------------------------------------*/

void _DUMP_(unsigned char *caData, char *szCount, char *caOut) {
	unsigned int    i, k;
	unsigned char   c;

	k = 0;
	for(i = 0; i < 4; ++i) {
		if(szCount[i] == '\0')
			break;
		k = (k * 10) + (szCount[i] - '0');
	}

	for(i = 0; i < k; ++i) {
		c = (caData[i] >> 4) + '0';
		if (c > '9') c += 7;
		caOut[i * 2] = c;

		c = (caData[i] & 0xf) + '0';
		if (c > '9') c += 7;
		caOut[(i * 2) + 1] = c;
	}
}


/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          _FLDDUMP_                                     |
 |                                                                        |
\*------------------------------------------------------------------------*/

void _FLDDUMP_(struct fld_desc *pField, char *pData, char *szDesc) {
	unsigned int    i, j;

	if(szDesc)
		fprintf(stderr, "\n_FLDDUMP_\n%s: ", szDesc);
	if(pField) {
		fprintf(stderr, "len=%ld, type=%c, dec/pscale=%d/%d, ",
			pField->len, pField->type, (char)pField->decimals, (char)pField->pscale);
		fprintf(stderr, "all=%d, jr/bz=%d/%d, signs (l/s)= %d/%d\n",
			pField->all, pField->just_r, pField->blank, pField->leading_sign, pField->separate_sign);
	}
        if (pField->type != DTYPE_GROUP && pField->type != DTYPE_ALPHANUMERICL) {
		fprintf(stderr, "picture:");
		for(i=0; tcob_picElemVal(pField->pic,i); i++) {
			fprintf(stderr, "%c(%d)", tcob_picElemVal(pField->pic,i),
			tcob_picElemLen(pField->pic,i));
		}
		fprintf(stderr, "\n");
	}
	if(!pData) {
		fprintf(stderr, "No data pointer provided\n");
		return;
	}
	
	fprintf(stderr, "Data Dump, Address = %08lX", (unsigned long)pData);
	for(j=0; j<tcob_fldLength(pField); j+=24) {
		fprintf(stderr, "\n%04d: ", (unsigned)j);
		for(i = 0; i < 24; ++i) {
			if((i + j) == tcob_fldLength(pField))
				break;
			fprintf(stderr, "%02X ", ((unsigned char *)pData)[j+i]);
		}
		fprintf(stderr, "\n      ");
		for(i = 0; i < 24; ++i) {
			if((i + j) == tcob_fldLength(pField))
				break;
			if((((unsigned char *)pData)[i] >= ' ') 
			&& (((unsigned char *)pData)[i] < 0x7f))
				fprintf(stderr, " %c ", ((unsigned char *)pData)[j+i]);
			else
				fprintf(stderr, "   ");
		}
	}
	fprintf(stderr, "\n\n");
}


/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          initIntValues                                 |
 |  Initialize the values in the _iIntValues_ array.                      |
 |                                                                        |
\*------------------------------------------------------------------------*/

void initIntValues () {
	unsigned int		i;
	extern long long	_iIntValues_[MAX_INTEGERS];

	_iIntValues_[MAX_INTEGERS - 1] = (long long)1;
	for(i = MAX_INTEGERS -1; i > 0; --i) 
		_iIntValues_[i - 1] = _iIntValues_[i] * (long long)10;
}


/*------------------------------------------------------------------------*\
 |                                                                        |
 |                     Static Storage Definitions                         |
 |                                                                        |
\*------------------------------------------------------------------------*/

int bDecimalComma = 0;
char cCurrencySymbol = '$';
long long _iIntValues_[MAX_INTEGERS] = {
    (long long)-1, (long long)-1, (long long)-1,
    (long long)-1, (long long)-1, (long long)-1,
    (long long)-1, (long long)-1, (long long)-1,
    (long long)-1, (long long)-1, (long long)-1,
    (long long)-1, (long long)-1, (long long)-1,
    (long long)-1, (long long)-1, (long long)-1
};

void (*pMovRtn[])(struct fld_desc *, char *, 
			struct fld_desc *, char *) = {
		tcob_move_9_9, tcob_move_9_b, tcob_move_9_c, 
		tcob_move_9_e, tcob_move_9_f, tcob_move_9_x,
		tcob_move_b_9, tcob_move_b_b, tcob_move_b_c, 
		tcob_move_b_e, tcob_move_b_f, tcob_move_b_x,
		tcob_move_c_9, tcob_move_c_b, tcob_move_c_c, 
		tcob_move_c_e, tcob_move_c_f, tcob_move_c_x,
		tcob_move_f_9, tcob_move_f_b, tcob_move_f_c, 
		tcob_move_f_e, tcob_move_f_f, tcob_move_f_x,
		tcob_move_x_9, tcob_move_x_b, tcob_move_x_c, 
		tcob_move_x_e, tcob_move_x_f, tcob_move_x_x,
		tcob_move_e_9, tcob_move_e_b, tcob_move_e_c,
		tcob_move_e_e, tcob_move_e_f, tcob_move_e_x
		};


#ifdef DEBUG_MOVE_RTS
int	_iMoveLevel_ = 0;
#endif

