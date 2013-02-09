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
 * TinyCOBOL Run Time Library -- Packed numeric move functions
 *

*/

#include "htcoblib.h"

/*
#define DEBUG_RTS 1
#define DEBUG_MOVE_RTS 1 
#define DEBUG_MOVERT_C_LEVEL   1 
*/

/*--------------------------------------------------------------------------*\
 |                                                                          |
 |         Move routines where the source field is DTYPE_PACKED             |
 |                                                                          |
\*--------------------------------------------------------------------------*/

void tcob_move_c_9(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	unsigned int		i;
	int			j, k, SrcWork_len;
	unsigned int		bIsNegative;
	int			iSrcDecimals;
	int			iDstDecimals;
	int			iSrcOffset;
	unsigned char		iDigit;
	char			caWork[MAX_INTEGERS + MAX_DECIMALS];
	unsigned char		*caSrcData;
	unsigned char		*caDstData;
	struct fld_desc		fSrcWork;
	struct fld_desc		fDstWork;

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_c_9 (%d)\n", _iMoveLevel_++);
    }
#endif                              
	memcpy(&fSrcWork, pfldDesc1, sizeof(struct fld_desc));
	memcpy(&fDstWork, pfldDesc2, sizeof(struct fld_desc));
	caSrcData = (unsigned char *)caData1;
	caDstData = (unsigned char *)caData2;
	iSrcDecimals = (char)fSrcWork.decimals;		/* do not remove (char) */
	iDstDecimals = (char)fDstWork.decimals;		/* do not remove (char) */
	
	/* Proper COMP-3's with even length have a leading half-byte */
	/* iSrcOffset = ((fSrcWork.len & 1) == 0) ? 1 : 0; */
        SrcWork_len = tcob_picCompLength(pfldDesc1); 
	iSrcOffset = ((SrcWork_len & 1) == 0) ? 1 : 0; 

	/* Determine if source value is negative */
	bIsNegative = 0;
	if(tcob_picElemVal(fSrcWork.pic,0) == 'S') {
		iDigit = caSrcData[fSrcWork.len/2] & 0x0F;
		if((iDigit == 0x0D) || (iDigit == 0x0B))
			bIsNegative = 1;
	}

	if(fDstWork.separate_sign) {
		if(fDstWork.leading_sign) 
			++caDstData;		/* point past the sign area */
		fDstWork.len --;		/* subtract length of the sign */
	}

	if(fSrcWork.all) {			/* this is a 'move all' */
		i = 0;
		j = 0;
		k = fSrcWork.len;
		while(i < fDstWork.len) {
			iDigit = caSrcData[(j + iSrcOffset) / 2];
			if((j + iSrcOffset) & 1) 
				iDigit = iDigit & 0x0F;
			else
				iDigit = iDigit >> 4;
			++j;
			caDstData[i++] = iDigit + '0';
			if(j == k)
				j = 0;
		}
		if(tcob_picElemVal(fDstWork.pic,0) == 'S') {
			if(fDstWork.separate_sign) {
				int iLoc = (fDstWork.leading_sign) ? 0 : fDstWork.len;
				caData2[iLoc] = (bIsNegative) ? '-' : '+';
			} else
				tcob_put_sign(&fDstWork, (char *)caDstData, bIsNegative);
		}
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_c_9 (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                                        
		return;
	}						/* END OF MOVE ALL CODE */


	memset(caWork, '0', sizeof(caWork)); /* move src to 9(18)V9(18) */
	if(iSrcDecimals < 0)		/* integer scaling */
		j = MAX_DIGITS - SrcWork_len - (iSrcDecimals * -1);
	else if(iSrcDecimals > SrcWork_len)	/* fractional scaling */
		j = MAX_DIGITS + iSrcDecimals - SrcWork_len;
	else
		j = MAX_DIGITS - (SrcWork_len - fSrcWork.decimals);

#ifdef DEBUG_MOVERT_C_LEVEL
        fprintf(stderr, "debug: tcob_move_c_9 030.140 : SrcWork_len=%d, j=%d, iSrcOffset=%d\n", SrcWork_len, j, iSrcOffset);
#endif
	for(i = 0; i < SrcWork_len; ++i) {
		iDigit = caSrcData[(i + iSrcOffset) / 2];
#ifdef DEBUG_MOVERT_C_LEVEL
                fprintf(stderr, "debug: tcob_move_c_9 030.160 : i=%d, iDigit=%02x, caSrcData[%d]=%02x\n", i, iDigit, (i + iSrcOffset) / 2, caSrcData[(i + iSrcOffset) / 2]);
#endif
		if((i + iSrcOffset) & 1)
			iDigit = iDigit & 0x0F;
		else
			iDigit = iDigit >> 4;
		caWork[j + i] = iDigit + '0';
#ifdef DEBUG_MOVERT_C_LEVEL
                fprintf(stderr, "debug: tcob_move_c_9 030.180 : i=%d, iDigit=%02x, caWork[%d]=%02x\n", i, iDigit, j + i, caWork[j + i]);
#endif
	}

	if(iDstDecimals < 0)		/* integer scaling */
		j = MAX_DIGITS - fDstWork.len - (iDstDecimals * -1);
	else if(iDstDecimals > (int)fDstWork.len)	/* fractional scaling */
		j = MAX_DIGITS + iDstDecimals - fDstWork.len;
	else
		j = MAX_DIGITS - (fDstWork.len - iDstDecimals);
	
	memmove(caDstData, &caWork[j], fDstWork.len);
	if(tcob_picElemVal(fDstWork.pic,0) == 'S') {
		if(fDstWork.separate_sign) {
			int iLoc = (fDstWork.leading_sign) ? 0 : fDstWork.len;
			caData2[iLoc] = bIsNegative ? '-' : '+';
		} else
			tcob_put_sign(&fDstWork, (char *)caDstData, bIsNegative);
	}
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_c_9 (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                                        
	return;
}


void tcob_move_c_b(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	unsigned int			i;
	int				j, k, SrcWork_len;
	unsigned int			bIsNegative;
	int				iSrcDecimals;
	int				iSrcOffset;
	unsigned int			iDestLen;
	char				caWork[MAX_INTEGERS + MAX_DECIMALS + 1];
	unsigned char			*caSrcData;
	unsigned char			iDigit;
	struct fld_desc			fSrcWork;

	long long			iLongField;
	extern long long		_iIntValues_[MAX_INTEGERS];

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_c_b (%d)\n", _iMoveLevel_++);
    }
#endif                              
	memcpy(&fSrcWork, pfldDesc1, sizeof(struct fld_desc));
        SrcWork_len = tcob_picCompLength(pfldDesc1); 

	iSrcDecimals = (char)fSrcWork.decimals;
	if(iSrcDecimals >= SrcWork_len) {	/* all fraction */
		switch(pfldDesc2->len) {
			case 1:
				*(char *)caData2 = 0;
				break;
			case 2:
				*(short int *)caData2 = 0;
				break;
			case 4:
				*(int *)caData2 = 0;
				break;
			case 8:
				*(long long *)caData2 = 0;
				break;
		}
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_c_b (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                                        
		return;
	}

	if(_iIntValues_[0] == (long long)-1)	/* first time called */
		initIntValues();
	memcpy(&fSrcWork, pfldDesc1, sizeof(struct fld_desc));
	caSrcData = (unsigned char *)caData1;
	
	/* Proper COMP-3's with even length have a leading half-byte */
	/* iSrcOffset = ((fSrcWork.len & 1) == 0) ? 0 : 1; */
	iSrcOffset = ((SrcWork_len & 1) == 0) ? 1 : 0;

	/* Determine if source value is negative */
	bIsNegative = 0;
	if(tcob_picElemVal(fSrcWork.pic,0) == 'S') {
		iDigit = caSrcData[fSrcWork.len/2] & 0x0F;
		if((iDigit == 0x0D) || (iDigit == 0x0B))
			bIsNegative = 1;
	}

	memset(caWork, '0', sizeof(caWork)); /* move src to 9(18)V9(18) */
	if(fSrcWork.all) {		     /* this is a 'move all' */
		i = 0;
		j = 0;
		k = fSrcWork.len;
		while(i < MAX_INTEGERS) {
			iDigit = caSrcData[(j + iSrcOffset) / 2];
			if((j + iSrcOffset) & 1) 
				iDigit = iDigit & 0x0F;
			else
				iDigit = iDigit >> 4;
			++j;
			caWork[i++] = iDigit + '0';
			if(j == k)
				j = 0;
		}
		fSrcWork.len = MAX_INTEGERS;
	}						/* END OF MOVE ALL CODE */
	else {
		if(iSrcDecimals < 0)		/* integer scaling */
			j = MAX_DIGITS - SrcWork_len - (iSrcDecimals * -1);
		else if(iSrcDecimals > (int)SrcWork_len)	/* fractional scaling */
			j = MAX_DIGITS + iSrcDecimals - SrcWork_len;
		else
			j = MAX_DIGITS - (SrcWork_len - iSrcDecimals);
#ifdef DEBUG_MOVERT_C_LEVEL
                fprintf(stderr, "debug: tcob_move_c_b 230.140 : SrcWork_len=%d, j=%d, iSrcOffset=%d\n", SrcWork_len, j, iSrcOffset);
#endif

		for(i = 0; i < SrcWork_len; ++i) {
			iDigit = caSrcData[(i + iSrcOffset) / 2];
#ifdef DEBUG_MOVERT_C_LEVEL
                        fprintf(stderr, "debug: tcob_move_c_b 230.160 : i=%d, iDigit=%02x, caSrcData[%d]=%02x\n", i, iDigit, (i + iSrcOffset) / 2, caSrcData[(i + iSrcOffset) / 2]);
#endif
			if((i + iSrcOffset) & 1)
				iDigit = iDigit & 0x0F;
			else
				iDigit = iDigit >> 4;
			caWork[j + i] = iDigit + '0';
#ifdef DEBUG_MOVERT_C_LEVEL
                       fprintf(stderr, "debug: tcob_move_c_b 230.180 : i=%d, iDigit=%02x, caWork[%d]=%02x\n", i, iDigit, j + i, caWork[j + i]);
#endif
		}
	}

	iDestLen = 0;
	for(i=0; tcob_picElemVal(pfldDesc2->pic,i); i++) {
		if(tcob_picElemVal(pfldDesc2->pic,i) == '9')
			iDestLen += tcob_picElemLen(pfldDesc2->pic,i);
	}

	iLongField = 0;
	k = 0;
	if(iSrcDecimals > 0)
		SrcWork_len -= iSrcDecimals;
	else
		k = iSrcDecimals * -1;
	j = MAX_INTEGERS - 1;
	if(SrcWork_len < iDestLen)
		iDestLen = SrcWork_len;
	for(i = 0; i < iDestLen; ++i) {
		iLongField += (_iIntValues_[j] * (long long)(caWork[j - k] - '0'));
		--j;
	}

	if(bIsNegative)
		iLongField *= (long long)-1;
	switch(pfldDesc2->len) {
		case 1:
			*(char *)caData2 = iLongField;
			break;
		case 2:
			*(short int *)caData2 = iLongField;;
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
        fprintf(stderr, "Debug:  Leaving tcob_move_c_b (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                                        
	return;
}




void tcob_move_c_c(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	unsigned int			i;
	int				j, k, SrcWork_len, DstWork_len;
	unsigned int			bIsNegative;
	int				iSrcDecimals;
	int				iDstDecimals;
	int				iSrcOffset;
	char				caWork[MAX_INTEGERS + MAX_DECIMALS];
	unsigned char			*caSrcData;
	unsigned char			*caDstData;
	unsigned char			iDigit;
	struct fld_desc			fSrcWork;
	struct fld_desc			fDstWork;

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_c_c (%d)\n", _iMoveLevel_++);
    }
#endif                              
	memcpy(&fSrcWork, pfldDesc1, sizeof(struct fld_desc));
	memcpy(&fDstWork, pfldDesc2, sizeof(struct fld_desc));
	caSrcData = (unsigned char *)caData1;
	caDstData = (unsigned char *)caData2;
	iSrcDecimals = (char)fSrcWork.decimals;		/* do not remove (char) */
	iDstDecimals = (char)fDstWork.decimals;		/* do not remove (char) */
        
        SrcWork_len = tcob_picCompLength(pfldDesc1); 
        DstWork_len = tcob_picCompLength(pfldDesc2); 

	/* Proper COMP-3's with even length have a leading half-byte */
	/* iSrcOffset = ((fSrcWork.len & 1) == 0) ? 1 : 0; */
	/* iSrcOffset = ((fSrcWork.len & 1) == 0) ? 0 : 1; */
	iSrcOffset = ((SrcWork_len & 1) == 0) ? 1 : 0;

	/* Determine if source value is negative */
	bIsNegative = 0;
	if(tcob_picElemVal(fSrcWork.pic,0) == 'S') {
		iDigit = caSrcData[fSrcWork.len/2] & 0x0F;
		if((iDigit == 0x0D) || (iDigit == 0x0B))
			bIsNegative = 1;
	}

	if(fSrcWork.all) {			/* this is a 'move all' */
		i = 0;
		j = 0;
		k = fSrcWork.len;
		while(i < (MAX_DIGITS * 2)) { 
			caWork[i++] = caSrcData[j++];
			if(j == k)
				j = 0;
		}
	} else {
		memset(caWork, '0', sizeof(caWork)); /* move src to 9(18)V9(18) */
		if(iSrcDecimals < 0)		/* integer scaling */
			j = MAX_DIGITS - SrcWork_len - (iSrcDecimals * -1);
		else if(iSrcDecimals > (int)SrcWork_len)	/* fractional scaling */
			j = MAX_DIGITS + iSrcDecimals - SrcWork_len;
		else
			j = MAX_DIGITS - (SrcWork_len - iSrcDecimals);

#ifdef DEBUG_MOVERT_C_LEVEL
        fprintf(stderr, "debug: tcob_move_c_c 330.080 : SrcWork_len=%d, j=%d, iSrcOffset=%d\n", SrcWork_len, j, iSrcOffset);
#endif
		for(i = 0; i < SrcWork_len; ++i) {
			iDigit = caSrcData[(i + iSrcOffset) / 2];
#ifdef DEBUG_MOVERT_C_LEVEL
                        fprintf(stderr, "debug: tcob_move_c_c 330.090 : i=%d, iDigit=%02x, caSrcData[%d]=%02x\n", i, iDigit, (i + iSrcOffset) / 2, caSrcData[(i + iSrcOffset) / 2]);
#endif
			if((i + iSrcOffset) & 1)
				iDigit = iDigit & 0x0F;
			else
				iDigit = iDigit >> 4;
			caWork[j + i] = iDigit + '0';
#ifdef DEBUG_MOVERT_C_LEVEL
                fprintf(stderr, "debug: tcob_move_c_c 330.095 : i=%d, iDigit=%02x, caWork[%d]=%02x\n", i, iDigit, j + i, caWork[j + i]);
#endif
		}
	}

#ifdef DEBUG_MOVE_RTS
    {
        int idx;
        
        fprintf(stderr, "\nDebug:  Enter C->9 tcob_move_c_c, Data Dump\n");
        for (idx=0; idx<36; idx++) 
           fprintf(stderr, " %2d", idx);
        fprintf(stderr, "\n");
        for (idx=0; idx<36; idx++) 
           fprintf(stderr, " %02x", caWork[idx]);
        fprintf(stderr, "\n");
        for (idx=0; idx<36; idx++) 
           fprintf(stderr, "  %c", caWork[idx]);
        fprintf(stderr, "\n");
        fprintf(stderr, "Debug:  Enter C->9 tcob_move_c_c, Data Dump\n\n");
        
    }
#endif                                        

	if(iDstDecimals < 0)		/* integer scaling */
		j = MAX_DIGITS - DstWork_len - (iDstDecimals * -1);
	else if(iDstDecimals > DstWork_len)	/* fractional scaling */
		j = MAX_DIGITS + iDstDecimals - DstWork_len;
	else
		j = MAX_DIGITS - (DstWork_len - iDstDecimals);

	memset (caDstData, 0, fDstWork.len);
	/* k = ((DstWork_len & 1) == 0) ? 0 : 1; */
	k = ((DstWork_len & 1) == 0) ? 1 : 0;
#ifdef DEBUG_MOVERT_C_LEVEL
        fprintf(stderr, "debug: tcob_move_c_c 330.190 : fDstWork.len=%d, k=%d, j=%d\n", fDstWork.len, k, j);
#endif
	for(i = 0; i < DstWork_len; ++i) {
		iDigit = caWork[j + i] - '0';
		caDstData[k / 2] |= ((k & 1) ? (iDigit) : (iDigit << 4));
#ifdef DEBUG_MOVERT_C_LEVEL
                fprintf(stderr, "debug: tcob_move_c_c 330.195 : i=%02d, k=%02d, caWork[%02d]=%02x, iDigit=%02x, caDstData[%02d]=%02x\n", i, k, i+j, caWork[j+i], iDigit, k/2, caDstData[k / 2]);
#endif
		++k;
	}

	if(tcob_picElemVal(fDstWork.pic,0) == 'S')
		iDigit = bIsNegative ? 0x0D : 0x0C;
	else
		iDigit = 0x0F;
	caDstData[fDstWork.len - 1] |= iDigit;
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_c_c (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                                        
	return;
}



void tcob_move_c_e(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_c_e (%d)\n", _iMoveLevel_++);
    }
#endif                              
	tcob_move_edited(pfldDesc1, caData1, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_c_e (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                                        
	return;
}





void tcob_move_c_f(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	unsigned int			i;
	int				j, k, SrcWork_len;
	unsigned int			bIsNegative;
	int				iSrcDecimals;
	int				iSrcOffset;
	char				caWork[MAX_INTEGERS + MAX_DECIMALS + 2];
	unsigned char			*caSrcData;
	unsigned char			iDigit;
	struct fld_desc			fSrcWork;
	double				dWork;

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_c_f (%d)\n", _iMoveLevel_++);
    }
#endif                              
	memcpy(&fSrcWork, pfldDesc1, sizeof(struct fld_desc));
	caSrcData = (unsigned char *)caData1;
	iSrcDecimals = (char)fSrcWork.decimals;		/* do not remove (char) */
	
	/* Proper COMP-3's with even length have a leading half-byte */
	/* iSrcOffset = ((fSrcWork.len & 1) == 0) ? 1 : 0; */
	iSrcOffset = ((fSrcWork.len & 1) == 0) ? 0 : 1;
        SrcWork_len = tcob_picCompLength(pfldDesc1); 

	/* Determine if source value is negative */
	bIsNegative = 0;
	if(tcob_picElemVal(fSrcWork.pic,0) == 'S') {
		iDigit = caSrcData[fSrcWork.len/2] & 0x0F;
		if((iDigit == 0x0D) || (iDigit == 0x0B))
			bIsNegative = 1;
	} 

	if(fSrcWork.all) {			/* this is a 'move all' */
		i = 0;
		j = 0;
		k = fSrcWork.len;
		while(i < (MAX_DIGITS * 2)) { 
			iDigit = caSrcData[(j + iSrcOffset) / 2];
			if((j + iSrcOffset) & 1)
				iDigit = iDigit & 0x0F;
			else
				iDigit = iDigit >> 4;
			++j;
			caWork[i++] = iDigit + '0';
			if(j == k)
				j = 0;
		}
	} else {
		memset(caWork, '0', sizeof(caWork)); /* move src to 9(18)V9(18) */
		if(iSrcDecimals < 0)		/* integer scaling */
			j = MAX_DIGITS - SrcWork_len - (iSrcDecimals * -1);
		else if(iSrcDecimals > SrcWork_len)	/* fractional scaling */
			j = MAX_DIGITS + iSrcDecimals - SrcWork_len;
		else
			j = MAX_DIGITS - (SrcWork_len - fSrcWork.decimals);

		for(i = 0; i < SrcWork_len; ++i) {
			iDigit = caSrcData[(i + iSrcOffset) / 2];
			if((i + iSrcOffset) & 1)
				iDigit = iDigit & 0x0F;
			else
				iDigit = iDigit >> 4;
			caWork[j + i] = iDigit + '0';
		}
	}
	/* re-form to create a null-terminated string with a decimal point */
	memmove(caWork + MAX_INTEGERS + 1, caWork + MAX_INTEGERS, MAX_DECIMALS);
	caWork[MAX_INTEGERS] = '.';
	caWork[MAX_INTEGERS + MAX_DECIMALS + 1] = '\0';

	dWork = atof(caWork);
	if(bIsNegative)
		dWork *= (double)-1.0;
	if(pfldDesc2->len == 4)
		*(float *)caData2 = (float)dWork;
	else
		*(double *)caData2 = dWork;
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_c_f (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                                        
	return;
}
		


void tcob_move_c_x(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	unsigned int		i, j, k;
	unsigned int		bIsNegative;
	int			iSrcDecimals;
	int			iSrcOffset;
	int			iDstOffset;
	unsigned char		iDigit;
	unsigned char		*caSrcData;
	struct fld_desc		fSrcWork;

#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Enter tcob_move_c_x (%d)\n", _iMoveLevel_++);
    }
#endif                              
	memcpy(&fSrcWork, pfldDesc1, sizeof(struct fld_desc));
	caSrcData = (unsigned char *)caData1;
	iSrcDecimals = (char)fSrcWork.decimals;		/* do not remove (char) */
	
	/* Proper COMP-3's with even length have a leading half-byte */
	iSrcOffset = ((fSrcWork.len & 1) == 0) ? 1 : 0;

	/* Determine if source value is negative */
	bIsNegative = 0;
	if(tcob_picElemVal(fSrcWork.pic,0) == 'S') {
		iDigit = caSrcData[fSrcWork.len/2] & 0x0F;
		if((iDigit == 0x0D) || (iDigit == 0x0B))
			bIsNegative = 1;
	}

	if(fSrcWork.all) {			/* this is a 'move all' */
		i = 0;
		j = 0;
		k = fSrcWork.len;
		while(i < pfldDesc2->len) {
			iDigit = caSrcData[(j + iSrcOffset) / 2];
			if((j + iSrcOffset) & 1) 
				iDigit = iDigit & 0x0F;
			else
				iDigit = iDigit >> 4;
			++j;
			caData2[i++] = iDigit + '0';
			if(j == k)
				j = 0;
		}
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_c_x (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                                        
		return;
	}	
	/* END OF MOVE ALL CODE */

	memset(caData2, ' ', pfldDesc2->len); 
	if(fSrcWork.len > pfldDesc2->len) {
		k = pfldDesc2->len;
		iDstOffset = 0;
	} else {
		if(pfldDesc2->just_r)
			iDstOffset = pfldDesc2->len - fSrcWork.len;
		else
			iDstOffset = 0;
		k = fSrcWork.len;
	}
	for(i = 0; i < k; ++i) {
		iDigit = caSrcData[(i + iSrcOffset) / 2];
		if((i + iSrcOffset) & 1)
			iDigit = iDigit & 0x0F;
		else
			iDigit = iDigit >> 4;
		caData2[i + iDstOffset] = iDigit + '0';
	}
#ifdef DEBUG_MOVE_RTS
    {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_c_x (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif                                        
	return;
}
