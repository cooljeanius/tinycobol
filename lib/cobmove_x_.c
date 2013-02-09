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
 * TinyCOBOL Run Time Library -- Alpha-numeric move functions
 *

*/

#include "htcoblib.h"

//#define DEBUG_MOVE_RTS 1

/*--------------------------------------------------------------------------*\
 |                                                                          |
 |       Move routines where the source field is DTYPE_ALPHANUMERIC         |
 |                                                                          |
\*--------------------------------------------------------------------------*/

void tcob_move_x_9(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	unsigned int			i;
	unsigned int			bInDecPortion;
	unsigned int			bLeadingWhite;
	unsigned int			bTrailingWhite;
	unsigned int			iDigitCount;
	unsigned int			iDecCount;
//	extern int			bDecimalComma;
	char				*caWork;
	char				caAll[MAX_DIGITS + 1];
	unsigned int			picLen;
	char				cDecimalPoint;
	char				cChar;
	char				cSign;
	struct fld_desc			fldWork;
	struct fld_desc			SrcFld;

	iDigitCount = 0;
	iDecCount = 0;
	bInDecPortion = 0;
	bLeadingWhite = 1;
	bTrailingWhite = 0;
	cSign = 0;
	cDecimalPoint = (bDecimalComma) ? ',' : '.';

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_x_9 (%d)\n", _iMoveLevel_++);
	}
#endif
	if(pfldDesc1->all) {				/* move all */
		memcpy(&SrcFld, pfldDesc2, sizeof(SrcFld));
		if(caData1[0] == 0x00) {
			memset(caAll, '0', SrcFld.len);
		} else if(caData1[0] == (char)0xFF) {
			memset(caAll, '9', SrcFld.len);
		} else if((pfldDesc1->len == 1) && (caData1[0] == ' ')) {
			/* This is a temporary hack due to the parser
			 * attempting to initialize numeric edited fields
			 * to SPACES. */
			memset(caAll, '0', SrcFld.len);
		} else {
			unsigned int rem = SrcFld.len % pfldDesc1->len;
			for(i = 0; i < (SrcFld.len - rem); i += pfldDesc1->len)
				memcpy(caAll+i, caData1, pfldDesc1->len);
			memcpy(caAll+i, caData1, rem);
		}
		if(tcob_picElemVal(SrcFld.pic,0) == 'S') {
			SrcFld.separate_sign = 1;
			SrcFld.leading_sign = 0;
			caAll[SrcFld.len++] = '+';
		}
		pfldDesc1 = &SrcFld;
		caData1 = caAll;
	}
		
	caWork = (char *)malloc(pfldDesc1->len);

	for(i = 0; i < pfldDesc1->len; ++i) {
		cChar = caData1[i];
		switch(cChar) {
			case '+':
			case '-':
				if(cSign) {
#ifdef DEBUG_MOVE_RTS
					runtime_error(RTERR_INVALID_DATA, pfldDesc1, (void *)caData1);
#endif
					memset(caData2, '0', pfldDesc2->len);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_9 (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
					free(caWork);
					return;
				}
				cSign = (cChar == '+') ? 1 : 2;
				bLeadingWhite = 0;
				if(bTrailingWhite) {
#ifdef DEBUG_MOVE_RTS
					runtime_error(RTERR_INVALID_DATA, pfldDesc1, (void *)caData1);
#endif
					memset(caData2, '0', pfldDesc2->len);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_9 (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
					free(caWork);
					return;
				}
				break;
			case '.':
			case ',':
				bLeadingWhite = 0;
				if(bTrailingWhite) {
#ifdef DEBUG_MOVE_RTS
					runtime_error(RTERR_INVALID_DATA, pfldDesc1, (void *)caData1);
#endif
					memset(caData2, '0', pfldDesc2->len);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_9 (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
					free(caWork);
					return;
				}
				if(cChar == cDecimalPoint) {
					bInDecPortion = 1;
				}
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				bLeadingWhite = 0;
				if(bTrailingWhite) {
#ifdef DEBUG_MOVE_RTS
					runtime_error(RTERR_INVALID_DATA, pfldDesc1, (void *)caData1);
#endif
					memset(caData2, '0', pfldDesc2->len);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_9 (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
					free(caWork);
					return;
				}
				caWork[iDigitCount++] = cChar;
				if(bInDecPortion)
					iDecCount++;
				break;
			case ' ':
			case '\t':
				if(!bLeadingWhite)
					bTrailingWhite = 1;
				break;
			default:
#ifdef DEBUG_MOVE_RTS
				runtime_error(RTERR_INVALID_DATA, pfldDesc1, (void *)caData1);
#endif
				memset(caData2, '0', pfldDesc2->len);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_9 (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
				free(caWork);
				return;
		}
	}
	memset (&fldWork, 0, sizeof(fldWork));
	fldWork.len = iDigitCount;
	fldWork.decimals = iDecCount;
	fldWork.type = DTYPE_DISPLAY;
	picLen = tcob_picReqLen(4);
	fldWork.pic = (char *)malloc(picLen);
	tcob_picCreate(fldWork.pic, picLen, NULL);
	if(cSign)
		tcob_picAppend(fldWork.pic, picLen, 'S', 1, NULL);
	if(iDigitCount > iDecCount)
		tcob_picAppend(fldWork.pic, picLen,
		               '9', iDigitCount - iDecCount, NULL);
	if(iDecCount)
		tcob_picAppend(fldWork.pic, picLen, 'V', 1, '9', iDecCount, NULL);
	if(cSign == 1)
		tcob_put_sign(&fldWork, caWork, 0);
	if(cSign == 2)
		tcob_put_sign(&fldWork, caWork, 1);
	tcob_move_9_9(&fldWork, caWork, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_9 (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	free(fldWork.pic);
	free(caWork);
	return;
}


void tcob_move_x_b(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	char				caWork[MAX_INTEGERS + MAX_DECIMALS];
	struct fld_desc			fldWork;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_x_b (%d)\n", _iMoveLevel_++);
	}
#endif
	memcpy(&fldWork, pfldDesc2, sizeof(struct fld_desc));
	fldWork.type = DTYPE_DISPLAY;
	fldWork.len = MAX_DIGITS;
	tcob_move_x_9(pfldDesc1, caData1, &fldWork, caWork);
	tcob_move_9_b(&fldWork, caWork, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_b (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	return;
}




void tcob_move_x_c(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	char				caWork[MAX_INTEGERS + MAX_DECIMALS];
	struct fld_desc			fldWork;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_x_c (%d)\n", _iMoveLevel_++);
	}
#endif
	memcpy(&fldWork, pfldDesc2, sizeof(struct fld_desc));
	fldWork.type = DTYPE_DISPLAY;
	tcob_move_x_9(pfldDesc1, caData1, &fldWork, caWork);
	tcob_move_9_c(&fldWork, caWork, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_c (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	return;
}



void tcob_move_x_e(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_x_e (%d)\n", _iMoveLevel_++);
	}
#endif
	tcob_move_edited(pfldDesc1, caData1, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_e (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	return;
}





void tcob_move_x_f(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	char				caWork[MAX_INTEGERS + MAX_DECIMALS];
	struct fld_desc			fldWork;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_x_f (%d)\n", _iMoveLevel_++);
	}
#endif
	memcpy(&fldWork, pfldDesc2, sizeof(struct fld_desc));
	fldWork.type = DTYPE_DISPLAY;
	fldWork.len = MAX_DIGITS;
	tcob_move_x_9(pfldDesc1, caData1, &fldWork, caWork);
	tcob_move_9_f(&fldWork, caWork, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_f (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	return;
}
		


void tcob_move_x_x(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	unsigned int			i, j, k;
	char *p;
	int spaces;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_x_x (%d)\n", _iMoveLevel_++);
	}
#endif
	if(pfldDesc1->all) {			/* this is a 'move all' */
		i = 0;
		j = 0;
		k = pfldDesc1->len;
		while(i < pfldDesc2->len) {
			caData2[i++] = caData1[j++];
			if(j == k)
				j = 0;
		}
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_x (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
		return;
	}						/* END OF MOVE ALL CODE */



	memset(caData2, ' ', pfldDesc2->len); 
	if(pfldDesc1->len > pfldDesc2->len) {
		if(pfldDesc2->just_r)
			k = pfldDesc1->len - pfldDesc2->len;
		else
			k = 0;
		j = 0;
		i = pfldDesc2->len;
	}
	else {
		if(pfldDesc2->just_r)
			j = pfldDesc2->len - pfldDesc1->len;
		else
			j = 0;
		k = 0;
		i = pfldDesc1->len;
	}
	if(!pfldDesc2->just_r){
		j = 0;
	} else {
		spaces = 0;
		p = caData1 + pfldDesc1->len - 1;
		while((*p == ' ')&&(p >= caData1)){
			spaces ++;
			p--;
		}
		i = i - spaces;
		j = j + spaces;
	}
	//memmove(&caData2 [j], &caData1 [k], i);
	memmove(caData2 + j, caData1 + k, i);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_x_x (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	return;
}


