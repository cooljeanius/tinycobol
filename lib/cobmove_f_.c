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
 * TinyCOBOL Run Time Library -- Float numeric move functions
 *

*/

#include "htcoblib.h"

//extern int bDecimalComma;

//#define DEBUG_MOVE_RTS 1                   

/*--------------------------------------------------------------------------*\
 |                                                                          |
 |         Move routines where the source field is DTYPE_BINARY             |
 |                                                                          |
\*--------------------------------------------------------------------------*/

void tcob_move_f_9(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	char			caWork[MAX_INTEGERS + MAX_DECIMALS + 2];
	unsigned int		picLen;
	char			caFormat[20];
	struct fld_desc		fldWork;
	double			dWork=0;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_f_9 (%d)\n", _iMoveLevel_++);
	}
#endif
	fldWork.type = DTYPE_ALPHANUMERIC;
	fldWork.decimals = 0;
	fldWork.pscale = 0;
	fldWork.all = pfldDesc1->all;
	fldWork.just_r = 0;
	fldWork.separate_sign = 0;
	fldWork.leading_sign = 0;

	switch(pfldDesc1->len) {
		case 4:
			dWork = (double)(*(float *)caData1);
			break;
		case 8:
			dWork = *(double *)caData1;
			break;
	}
//	The following statements are wrong: the first one because it doesn't
//	allow more than 6 decimal places, the second because it rounds before
//	formatting. We have to design our own sprintf in the spirit of what is
//	done in dtofld.
	sprintf(caFormat, "%%%df", MAX_DIGITS);
//	sprintf(caFormat, "%%%d.%df", MAX_DIGITS, pfldDesc2->decimals+1);
	sprintf(caWork, caFormat, dWork);
// 	If decimal point is comma, replace point by comma.
	fldWork.len = strlen(caWork);
	if (bDecimalComma){
		unsigned int i;
		for(i=0;i<fldWork.len;i++){
			if (caWork[i] == '.')
			       caWork[i]=',';
		}
	}
	
	
	picLen = tcob_picReqLen(1);
	fldWork.pic = (char *)malloc(picLen);
	tcob_picCreate (fldWork.pic, picLen, 'X', fldWork.len, NULL);
	tcob_move_x_9(&fldWork, caWork, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_f_9 (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
		fprintf(stderr, "dWork:%e, fmt:%s\n", dWork, caFormat);
	}
#endif
	free(fldWork.pic);
	return;
}


void tcob_move_f_b(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	char					caWork[MAX_INTEGERS + MAX_DECIMALS + 2];
	unsigned int				picLen;
	char					caFormat[20];
	struct fld_desc			fldWork;
	double					dWork=0;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_f_b (%d)\n", _iMoveLevel_++);
	}
#endif
	fldWork.type = DTYPE_ALPHANUMERIC;
	fldWork.decimals = 0;
	fldWork.pscale = 0;
	fldWork.all = pfldDesc1->all;
	fldWork.just_r = 0;
	fldWork.separate_sign = 0;
	fldWork.leading_sign = 0;

	switch(pfldDesc1->len) {
		case 4:
			dWork = (double)(*(float *)caData1);
			break;
		case 8:
			dWork = *(double *)caData1;
			break;
	}
	sprintf(caFormat, "%%%df", MAX_DIGITS);
	sprintf(caWork, caFormat, dWork);
	fldWork.len = strlen(caWork);
	picLen = tcob_picReqLen(1);
	fldWork.pic = (char *)malloc(picLen);
	tcob_picCreate (fldWork.pic, picLen, 'X', fldWork.len, NULL);
	tcob_move_x_b(&fldWork, caWork, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_f_b (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	free(fldWork.pic);
	return;
}




void tcob_move_f_c(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	char					caWork[MAX_INTEGERS + MAX_DECIMALS + 2];
	unsigned int				picLen;
	char					caFormat[20];
	struct fld_desc			fldWork;
	double					dWork=0;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_f_c (%d)\n", _iMoveLevel_++);
	}
#endif
	fldWork.type = DTYPE_ALPHANUMERIC;
	fldWork.decimals = 0;
	fldWork.pscale = 0;
	fldWork.all = pfldDesc1->all;
	fldWork.just_r = 0;
	fldWork.separate_sign = 0;
	fldWork.leading_sign = 0;

	switch(pfldDesc1->len) {
		case 4:
			dWork = (double)(*(float *)caData1);
			break;
		case 8:
			dWork = *(double *)caData1;
			break;
	}
	sprintf(caFormat, "%%%df", MAX_DIGITS);
	sprintf(caWork, caFormat, dWork);
	fldWork.len = strlen(caWork);
	picLen = tcob_picReqLen(1);
	fldWork.pic = (char *)malloc(picLen);
	tcob_picCreate (fldWork.pic, picLen, 'X', fldWork.len, NULL);
	tcob_move_x_c(&fldWork, caWork, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_f_c (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	free(fldWork.pic);
	return;
}



void tcob_move_f_e(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_f_e (%d)\n", _iMoveLevel_++);
	}
#endif
	tcob_move_edited(pfldDesc1, caData1, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_f_e (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	return;
}



void tcob_move_f_f(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	double		dWork=0;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_f_f (%d)\n", _iMoveLevel_++);
	}
#endif
	switch(pfldDesc1->len) {
		case 4:
			dWork = (double)(*(float *)caData1);
			break;
		case 8:
			dWork = *(double *)caData1;
			break;
	}
	switch(pfldDesc2->len) {
		case 4:
			*(float *)caData2 = (float)dWork;
			break;
		case 8:
			*(double *)caData2 = dWork;
	}
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_f_f (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	return;
}
		


void tcob_move_f_x(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	char			caWork[MAX_INTEGERS + MAX_DECIMALS + 2];
	unsigned int		picLen;
	char			caFormat[20];
	struct fld_desc		fldWork;
	double			dWork=0;
	unsigned int		i, j;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_f_x (%d)\n", _iMoveLevel_++);
	}
#endif
	fldWork.type = DTYPE_ALPHANUMERIC;
	fldWork.decimals = 0;
	fldWork.pscale = 0;
	fldWork.all = pfldDesc1->all;
	fldWork.just_r = 0;
	fldWork.separate_sign = 0;
	fldWork.leading_sign = 0;

	switch(pfldDesc1->len) {
		case 4:
			dWork = (double)(*(float *)caData1);
			break;
		case 8:
			dWork = *(double *)caData1;
			break;
	}

	sprintf(caFormat, "%%%df", MAX_DIGITS);
	sprintf(caWork, caFormat, dWork);

#ifdef DEBUG_MOVE_RTS
	fprintf(stderr, "Debug tcob_move_f_x 0 : caWork=%s:\n", caWork);
#endif

	// Remove sign and decimal point 
	fldWork.len = strlen(caWork);
	for (i=0, j=0; i<fldWork.len; i++) {
	   if ((caWork[i] != '-') && (caWork[i] != '.') && (caWork[i] != ' ')){
	      caWork[j] = caWork[i];

#ifdef DEBUG_MOVE_RTS
	   fprintf(stderr, "Debug tcob_move_f_x 1 :caWork[i=%d]=%c: :caWork[j=%d]=%c:\n", 
	                   i, caWork[i], j, caWork[j]);
#endif

	      j++;
	   }

#ifdef DEBUG_MOVE_RTS
	   fprintf(stderr, "Debug tcob_move_f_x 2 :caWork[i=%d]=%c: :caWork[j=%d]=%c:\n", 
	                   i, caWork[i], j, caWork[j]);
#endif

	}
	caWork[j] = '\0';
	
	fldWork.len = strlen(caWork);
	picLen = tcob_picReqLen(1);
	fldWork.pic = (char *)malloc(picLen);
	tcob_picCreate (fldWork.pic, picLen, 'X', fldWork.len, NULL);
	tcob_move_x_x(&fldWork, caWork, pfldDesc2, caData2);

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug tcob_move_f_x 3 : caWork=%s:\n", caWork);
		fprintf(stderr, "Debug:  Leaving tcob_move_f_x (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	free(fldWork.pic);
	return;
}


