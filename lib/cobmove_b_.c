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
 * TinyCOBOL Run Time Library -- Binary numeric move functions
 *

*/

#include "htcoblib.h"

/*
#define DEBUG_MOVE_RTS 1                    
*/

/*--------------------------------------------------------------------------*\
 |                                                                          |
 |         Move routines where the source field is DTYPE_BINARY             |
 |                                                                          |
\*--------------------------------------------------------------------------*/

void tcob_move_b_9(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	int			i;
	int			bIsNegative;
	char			caWork[MAX_INTEGERS];
	unsigned int		picLen;
	char			*pData=NULL;
	struct fld_desc		fldWork;
	long long		iLongField=0;
	long long		iLongWork;
	extern long long	_iIntValues_[MAX_INTEGERS];
	char			caWork1[MAX_INTEGERS+1];
	unsigned int		iLen;

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        caWork1[MAX_INTEGERS] = '\0';
        fprintf(stderr, "Debug:  Enter tcob_move_b_9 (%d)\n", _iMoveLevel_++);
    }
#endif                                       
	if(_iIntValues_[0] == (long long)-1)	/* first time called */
		initIntValues();

	fldWork.type = DTYPE_DISPLAY;
	fldWork.decimals = pfldDesc1->decimals;
	fldWork.pscale = 0;
	fldWork.all = pfldDesc1->all;
	fldWork.just_r = 0;
	fldWork.separate_sign = 0;
	fldWork.leading_sign = 0;
	if (tcob_picElemVal(pfldDesc1->pic,0) == 'S') {
		switch(pfldDesc1->len) {
			case 1:
				iLongField = *(char *)caData1;
				iLen = 3;
				break;
			case 2:
				iLongField = *(short int *)caData1;
				iLen = 5;
				break;
			case 4:
				iLongField = *(int *)caData1;
				iLen = 10;
				break;
			case 8:
				iLongField = *(long long *)caData1;
				iLen = 18;
				break;
		}
	}
	else {
		switch(pfldDesc1->len) {
			case 1:
				iLongField = *(unsigned char *)caData1;
				iLen = 3;
				break;
			case 2:
				iLongField = *(unsigned short int *)caData1;
				iLen = 5;
				break;
			case 4:
				iLongField = *(unsigned int *)caData1;
				iLen = 10;
				break;
			case 8:
				iLongField = *(unsigned long long *)caData1;
				iLen = 18;
				break;
		}
	}
	fldWork.len = iLen;
	picLen = tcob_picReqLen(2);
	fldWork.pic = (char *)malloc(picLen);
	tcob_picCreate (fldWork.pic, picLen, 'S', 1, '9', iLen, NULL);
	pData = &caWork[MAX_INTEGERS - iLen];

	if(iLongField < 0) {
		bIsNegative = 1;
		iLongField = iLongField * (long long)-1;
	} else
		bIsNegative = 0;

	for(i = 0; i < MAX_INTEGERS; ++i) {
		iLongWork = iLongField / _iIntValues_[i];
		caWork[i] = (unsigned char)iLongWork + '0';
		iLongField = iLongField - (_iIntValues_[i] * iLongWork);
		caWork1[i] = '=';
	}
	tcob_put_sign(&fldWork, pData, bIsNegative);
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  before tcob_move_9_9 call (%d)\n", _iMoveLevel_);
        strncpy(caWork1, caWork, MAX_INTEGERS);
        fprintf(stderr, "Debug tcob_move_b_9:  caWork1=%s, len=%d, bIsNegative=%d;\n", 
                caWork1, strlen(caWork1), bIsNegative);
        _FLDDUMP_(&fldWork, pData, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                       
	tcob_move_9_9(&fldWork, pData, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  after tcob_move_9_9 call (%d)\n", _iMoveLevel_);
        _FLDDUMP_(&fldWork, pData, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                       
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_b_9 (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                       
	free(fldWork.pic);
	return;
}


void tcob_move_b_b(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {

	unsigned int				i;
	long long				iLongField=0;
	int					iSrcDecimals, iSrcPscale;
	int					iDstDecimals, iDstPscale;
	int					scale;

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_b_b (%d)\n", _iMoveLevel_++);
    }
#endif                                       
	if (tcob_picElemVal(pfldDesc1->pic,0) == 'S') {
		switch(pfldDesc1->len) {
			case 1:
				iLongField = *(char *)caData1;
				break;
			case 2:
				iLongField = *(short int *)caData1;
				break;
			case 4:
				iLongField = *(int *)caData1;
				break;
			case 8:
				iLongField = *(long long *)caData1;
				break;
		}
	}
	else {
		switch(pfldDesc1->len) {
			case 1:
				iLongField = *(unsigned char *)caData1;
				break;
			case 2:
				iLongField = *(unsigned short int *)caData1;
				break;
			case 4:
				iLongField = *(unsigned int *)caData1;
				break;
			case 8:
				iLongField = *(unsigned long long *)caData1;
				break;
		}
	}
	if ((tcob_picElemVal(pfldDesc2->pic,0) != 'S') && (iLongField < 0)) {
		iLongField = - iLongField;	
	}
	
	/* Scaling */
	iSrcDecimals = (char)pfldDesc1->decimals;
	iDstDecimals = (char)pfldDesc2->decimals;
	iSrcPscale   = (char)pfldDesc1->pscale;
	iDstPscale   = (char)pfldDesc2->pscale;
	scale = (iDstDecimals?iDstDecimals:iDstPscale) -
		(iSrcDecimals?iSrcDecimals:iSrcPscale);
	if (scale > 0) {
		for (i=0; i<scale; i++)
			iLongField *= 10;
	} else if (scale < 0) {
		for (i=0; i<-scale; i++)
			iLongField /= 10;
	}
	
	switch(pfldDesc2->len) {
		case 1:
			*(char *)caData2 = iLongField;
			break;
		case 2:
			*(short int *)caData2 = iLongField;
			break;
		case 4:
			*(int *)caData2 = iLongField;
			break;
		case 8:
			*(long long *)caData2 = iLongField;
			break;
	}
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_b_b (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                       
	return;
}




void tcob_move_b_c(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	int				i;
	int				bIsNegative;
	char				caWork[MAX_INTEGERS];
	unsigned int			picLen;
	char				*pData=NULL;
	struct fld_desc			fldWork;
	long long			iLongField=0;
	long long			iLongWork;
	extern long long		_iIntValues_[MAX_INTEGERS];
	unsigned int			iLen;

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_b_c (%d)\n", _iMoveLevel_++);
    }
#endif                                       
	if(_iIntValues_[0] == (long long)-1)	/* first time called */
		initIntValues();

	fldWork.type = DTYPE_DISPLAY;
	fldWork.decimals = 0;
	fldWork.pscale = 0;
	fldWork.all = pfldDesc1->all;
	fldWork.just_r = 0;
	fldWork.separate_sign = 0;
	fldWork.leading_sign = 0;
	switch(pfldDesc1->len) {
		case 1:
			iLongField = *(char *)caData1;
			iLen = 3;
			break;
		case 2:
			iLongField = *(short int *)caData1;
			iLen = 5;
			break;
		case 4:
			iLongField = *(int *)caData1;
			iLen = 10;
			break;
		case 8:
			iLongField = *(long long *)caData1;
			iLen = 18;
			break;
	}
	fldWork.len = iLen;
	picLen = tcob_picReqLen(2);
	fldWork.pic = (char *)malloc(picLen);
	tcob_picCreate (fldWork.pic, picLen, 'S', 1, '9', iLen, NULL);
	pData = &caWork[MAX_INTEGERS - iLen];

	if(iLongField < 0) {
		bIsNegative = 1;
		iLongField = iLongField * (long long)-1;
	} else
		bIsNegative = 0;

	for(i = 0; i < MAX_INTEGERS; ++i) {
		iLongWork = iLongField / _iIntValues_[i];
		caWork[i] = (unsigned char)iLongWork + '0';
		iLongField = iLongField - (_iIntValues_[i] * iLongWork);
	}
	tcob_put_sign(&fldWork, pData, bIsNegative);
	tcob_move_9_c(&fldWork, pData, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_b_c (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                       
	free(fldWork.pic);
	return;
}



void tcob_move_b_e(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_b_e (%d)\n", _iMoveLevel_++);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                                       
	tcob_move_edited(pfldDesc1, caData1, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_b_e (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                       
	return;
}





void tcob_move_b_f(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	long long				iLongField=0;

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_b_f (%d)\n", _iMoveLevel_++);
    }
#endif                                       
	switch(pfldDesc1->len) {
		case 1:
			iLongField = *(char *)caData1;
			break;
		case 2:
			iLongField = *(short int *)caData1;
			break;
		case 4:
			iLongField = *(int *)caData1;
			break;
		case 8:
			iLongField = *(long long *)caData1;
			break;
	}
	switch(pfldDesc2->len) {
		case 4:
			*(float *)caData2 = (float)iLongField;
			break;
		case 8:
			*(double *)caData2 = (double)iLongField;
			break;
	}
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_b_f (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                       
	return;
}
		


void tcob_move_b_x(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	int			i;
	int			bIsNegative;
	char			caWork[MAX_INTEGERS];
	unsigned int		picLen;
	char			*pData=NULL;
	struct fld_desc		fldWork;
	long long		iLongField=0;
	long long		iLongWork;
	extern long long	_iIntValues_[MAX_INTEGERS];
	unsigned int		iLen;

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_b_x (%d)\n", _iMoveLevel_++);
    }
#endif                                       
	if(_iIntValues_[0] == (long long)-1)	/* first time called */
		initIntValues();

	fldWork.type = DTYPE_DISPLAY;
	fldWork.decimals = 0;
	fldWork.pscale = 0;
	fldWork.all = pfldDesc1->all;
	fldWork.just_r = 0;
	fldWork.separate_sign = 0;
	fldWork.leading_sign = 0;
	switch(pfldDesc1->len) {
		case 1:
			iLongField = *(char *)caData1;
			iLen = 3;
			break;
		case 2:
			iLongField = *(short int *)caData1;
			iLen = 5;
			break;
		case 4:
			iLongField = *(int *)caData1;
			iLen = 10;
			break;
		case 8:
			iLongField = *(long long *)caData1;
			iLen = 18;
			break;
	}
	fldWork.len = (pfldDesc2->len > iLen ? iLen: pfldDesc2->len);	 
	picLen = tcob_picReqLen(2);
	fldWork.pic = (char *)malloc(picLen);
	tcob_picCreate (fldWork.pic, picLen, 'S', 1, '9', iLen, NULL);
	pData = &caWork[MAX_INTEGERS - iLen];

	if(iLongField < 0) {
		bIsNegative = 1;
		iLongField = iLongField * (long long)-1;
	} else
		bIsNegative = 0;

	for(i = 0; i < MAX_INTEGERS; ++i) {
		iLongWork = iLongField / _iIntValues_[i];
		caWork[i] = (unsigned char)iLongWork + '0';
		iLongField = iLongField - (_iIntValues_[i] * iLongWork);
	}
	tcob_put_sign(&fldWork, pData, bIsNegative);
	tcob_move_9_x(&fldWork, pData, pfldDesc2, caData2);

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_b_x (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                       
	free(fldWork.pic);
	return;
}


