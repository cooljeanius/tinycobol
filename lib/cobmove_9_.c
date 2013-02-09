/* 
 * Copyright (C) 2003  Jeff Smith
 * Copyright (C) 2001, 2000, 1999  Rildo Pragana, Jim Noeth, 
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
 * TinyCOBOL Run Time Library -- Numeric move functions
 *

 */

#include "htcoblib.h"

/* To turn RTS MOVE debugging on, change 'if 0' to 'if 1'.
 * Note that RTS MOVE debugging must also be turned on in cobmove.c .
 * Or do both with the configuration option --enable-debug-rts-move .
 */

/*
#define DEBUG_RTS 1
#define DEBUG_MOVE_RTS 1
#define DEBUG_MOVERT_9_LEVEL   1 
*/

/*--------------------------------------------------------------------------*\
 |                                                                          |
 |         Move routines where the source field is DTYPE_DISPLAY            |
 |                                                                          |
\*--------------------------------------------------------------------------*/
/* FIXME:
  This routine changes what should be READ-ONLY data, as generated 
  in the assembler code. (caSrcData = caData1;)
*/
void tcob_move_9_9(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	int				bIsNegative;
	int				iSrcDecimals, iSrcPscale;
	int				iDstDecimals, iDstPscale;
	unsigned char			*caSrcData;
	unsigned char			*caDstData;
	struct fld_desc			fSrcWork;
	struct fld_desc			fDstWork;
	unsigned int			bSrcSigned;
	unsigned int			bDstSigned;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_9_9 (%d)\n", _iMoveLevel_++);
	}
#endif

	memcpy(&fSrcWork, pfldDesc1, sizeof(fSrcWork));
	memcpy(&fDstWork, pfldDesc2, sizeof(fDstWork));

	caSrcData = (unsigned char *)caData1; 
        /* caSrcData = (unsigned char *)tcob_dup_data(pfldDesc1, caData1);
        if (caSrcData == NULL) 
            return;  */        
        
	caDstData = (unsigned char *)caData2;
	iSrcDecimals = (char)fSrcWork.decimals;	/* do not remove (char) */
	iDstDecimals = (char)fDstWork.decimals;	/* do not remove (char) */
	iSrcPscale = (char)fSrcWork.pscale;	/* do not remove (char) */
	iDstPscale = (char)fDstWork.pscale;	/* do not remove (char) */
	bSrcSigned = (tcob_picElemVal(fSrcWork.pic,0) == 'S') ? 1 : 0;
	bDstSigned = (tcob_picElemVal(fDstWork.pic,0) == 'S') ? 1 : 0;

	/* Determine source's sign and temporarily remove */
	if(bSrcSigned) {
		if(fSrcWork.separate_sign) {
			char cSign;
			if(fSrcWork.leading_sign) {
				cSign = caSrcData[0];
				++caSrcData;		/* point past the sign */
			} else
				cSign = caSrcData[fSrcWork.len - 1];
			fSrcWork.len --;		/* subtract length of sign */
			bIsNegative = (cSign == '-') ? 1 : 0;
		} else					/* Sign is non-separate */
			bIsNegative = tcob_extract_sign(&fSrcWork, (char *)caSrcData);
	} else				/* Variable is unsigned */
		bIsNegative = 0;
	
	if(bDstSigned && fDstWork.separate_sign) {
		if(fDstWork.leading_sign) 
			++caDstData;		/* point past the sign area */
		fDstWork.len --;		/* subtract length for sign */
	}

	if(fSrcWork.all && (fSrcWork.len == 1)) {
		/* Numeric ALL literal must have a length of 1 */
		memset(caDstData, *caSrcData, fDstWork.len);
	} else {
		int off_src, off_dst, len;
		unsigned int off1, off2;

		off_src = ((iSrcDecimals)?iSrcDecimals:iSrcPscale) - fSrcWork.len;
		off_dst = ((iDstDecimals)?iDstDecimals:iDstPscale) - fDstWork.len;
	
		if (off_src < off_dst) {
			off1 = 0;
			off2 = off_dst - off_src;
			len = (int)fSrcWork.len - off2;
			if (len > (int)fDstWork.len)
				len = fDstWork.len;
		} else {
			off1 = off_src - off_dst;
			off2 = 0;
			len = (int)fDstWork.len - off1;
			if (len > (int)fSrcWork.len)
				len = fSrcWork.len;
		}
		memset(caDstData, '0', fDstWork.len); 
		if (len > 0)
			memcpy(caDstData+off1, caSrcData+off2, len);
	}
	
	/* Restore signs */
	if(bSrcSigned && (!fSrcWork.separate_sign)) 
		tcob_put_sign(&fSrcWork, (char *)caSrcData, bIsNegative);
	if(bDstSigned) {
		if(fDstWork.separate_sign) {
			int iLoc = (fDstWork.leading_sign) ? 0 : fDstWork.len;
			caData2[iLoc] = (bIsNegative) ? '-' : '+';
		} else
			tcob_put_sign(&fDstWork, (char *)caDstData, bIsNegative);
	}
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_9_9 (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif         
        /*if (caSrcData != NULL)
           free(caSrcData);  */      
	
        return;
}


void tcob_move_9_b(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	unsigned int	bIsNegative;
	unsigned int	bIsZero;
	int		iSrcLen;
	unsigned int	iDstLen;
	char		*caSrcData;
	unsigned int	bSrcSigned;
	unsigned int	bDstSigned;
	long long	iLongField;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_9_b (%d)\n", _iMoveLevel_++);
	}
#endif
	caSrcData = caData1;
        /* caSrcData = tcob_dup_data(pfldDesc1, caData1);
        if (caSrcData == NULL) 
            return;     */     

	bSrcSigned = (tcob_picElemVal(pfldDesc1->pic,0) == 'S') ? 1 : 0;
	bDstSigned = (tcob_picElemVal(pfldDesc2->pic,0) == 'S') ? 1 : 0;
	iSrcLen = pfldDesc1->len;
	iDstLen = tcob_picCompLength(pfldDesc2);

	/* Determine source's sign and temporarily remove */
	if(bSrcSigned) {
		if(pfldDesc1->separate_sign) {
			char cSign;
			if(pfldDesc1->leading_sign) {
				cSign = caSrcData[0];
				++caSrcData;		/* point past the sign */
			} else
				cSign = caSrcData[pfldDesc1->len - 1];
			iSrcLen --;
			bIsNegative = (cSign == '-') ? 1 : 0;
		} else					/* Sign is non-separate */
			bIsNegative = tcob_extract_sign(pfldDesc1, caSrcData);
	} else				/* Variable is unsigned */
		bIsNegative = 0;

	bIsZero = ((pfldDesc1->len == 1) && (*caSrcData == '0')) ? 1 : 0;

	iLongField = 0;
	if (!bIsZero) {
		int i;
		int off, scale, len;
		char caWork[MAX_DIGITS];
		extern long long _iIntValues_[MAX_INTEGERS];

		/* do not remove (char) on these four assignments */
		int iSrcDecimals = (char)pfldDesc1->decimals;
		int iDstDecimals = (char)pfldDesc2->decimals;
		int iSrcPscale = (char)pfldDesc1->pscale;
		int iDstPscale = (char)pfldDesc2->pscale;

		if(pfldDesc1->all && (iSrcLen == 1)) {
			/* Numeric ALL literal must have a length of 1 */
			memset(caWork, *caSrcData, MAX_DIGITS);
			iSrcLen = MAX_DIGITS;
			iSrcDecimals = 0;
			iSrcPscale = 0;
			caSrcData = (char *)caWork;
		}
		scale = ((iDstDecimals)?iDstDecimals:iDstPscale) -
			((iSrcDecimals)?iSrcDecimals:iSrcPscale);
		off =  scale - iDstLen + iSrcLen;

		if (off > 0) {
			len = iSrcLen - off;
			if (len > (int)iDstLen)
				len = iDstLen;
		} else {
			len = iDstLen + off;
			if (len > (int)iSrcLen)
				len = iSrcLen;
			off = 0;
		}
	
		if(_iIntValues_[0] == (long long)-1)	/* first time called */
			initIntValues();
		for(i=0; i<len; i++) {
			iLongField += (_iIntValues_[MAX_INTEGERS-(len-i)-scale]
			       * (long long)(caSrcData[off+i] - '0'));
#ifdef DEBUG_MOVE_RTS
	       fprintf(stderr, "Debug: tcob_move_9_b 4: iLongField=%lld\n", 
	                       iLongField);
#endif
		}

		/* Set destination's sign */
		if(bDstSigned && bIsNegative)
			iLongField *= (long long)-1;
	}
	/* Restore source's sign */
	if(bSrcSigned && (!pfldDesc1->separate_sign))
		tcob_put_sign(pfldDesc1, caSrcData, bIsNegative);

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
		fprintf(stderr, "Debug:  Leaving tcob_move_9_b (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif

        /* if (caSrcData != NULL)
           free(caSrcData);   */     

	return;
}




void tcob_move_9_c(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	unsigned int			i;
	int				j, k, DstWork_len;
	int				bIsNegative;
	int				iSrcDecimals, iSrcPscale;
	int				iDstDecimals, iDstPscale;
	unsigned int			bSrcSigned;
	char				caWork[MAX_INTEGERS + MAX_DECIMALS];
	unsigned char			*caSrcData;
	unsigned char			*caDstData;
	unsigned char			iDigit;
	struct fld_desc			fSrcWork;
	struct fld_desc			fDstWork;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_9_c (%d)\n", _iMoveLevel_++);
	}
#endif
	memcpy(&fSrcWork, pfldDesc1, sizeof(struct fld_desc));
	memcpy(&fDstWork, pfldDesc2, sizeof(struct fld_desc));

	caSrcData = (unsigned char *)caData1;
        /* caSrcData = tcob_dup_data(pfldDesc1, caData1);
        if (caSrcData == NULL) 
            return;     */      

	caDstData = (unsigned char *)caData2;
	iSrcDecimals = (char)fSrcWork.decimals;	/* do not remove (char) */
	iDstDecimals = (char)fDstWork.decimals;	/* do not remove (char) */
	iSrcPscale = (char)fSrcWork.pscale;	/* do not remove (char) */
	iDstPscale = (char)fDstWork.pscale;	/* do not remove (char) */
	bSrcSigned = (tcob_picElemVal(fSrcWork.pic,0) == 'S') ? 1 : 0;
	
        fDstWork.len = pfldDesc2->len; 

	if(bSrcSigned) {
		if(fSrcWork.separate_sign) {
			char cSign;
			if(fSrcWork.leading_sign) {
				cSign = caSrcData[0];
				++caSrcData;		/* point past the sign */
			} else
				cSign = caSrcData[fSrcWork.len - 1];
			fSrcWork.len --;		/* subtract length of sign */
			bIsNegative = (cSign == '-') ? 1 : 0;
		} else					/* Sign is non-separate */
			bIsNegative = tcob_extract_sign(&fSrcWork, (char *)caSrcData);
	} else				/* Variable is unsigned */
		bIsNegative = 0;

	if(fSrcWork.all && (fSrcWork.len == 1)) {    /* this is a 'move all' */
		memset(caWork, *caSrcData, sizeof(caWork));
	} else {
		memset(caWork, '0', sizeof(caWork)); /* move src to 9(18)V9(18) */
		if(iSrcPscale < 0)		     /* integer scaling */
			j = MAX_DIGITS - fSrcWork.len + (iSrcPscale * -1);
		else if(iSrcDecimals > (int)fSrcWork.len)  /* fractional scaling */
			j = MAX_DIGITS + iSrcDecimals - fSrcWork.len;
		else
			j = MAX_DIGITS - (fSrcWork.len - fSrcWork.decimals);
		
		memmove(&caWork[j], caSrcData, fSrcWork.len);
		if(bSrcSigned && (!fSrcWork.separate_sign)) 
			tcob_put_sign(&fSrcWork, (char *)caSrcData, (char)bIsNegative);
	}
#ifdef DEBUG_MOVERT_9_LEVEL
        fprintf(stderr, "debug: tcob_move_9_c 300.060 : fSrcWork.len=%d, j=%d\n", fSrcWork.len, j);
#endif

        DstWork_len = tcob_picCompLength(pfldDesc2);
	if(iDstPscale < 0)		/* integer scaling */
		j = MAX_DIGITS - DstWork_len - (iDstPscale * -1);
	else if(iDstDecimals > DstWork_len)	/* fractional scaling */
		j = MAX_DIGITS + iDstDecimals - DstWork_len;
	else
		j = MAX_DIGITS - (DstWork_len - fDstWork.decimals);

	memset (caDstData, 0, fDstWork.len);
	k = ((DstWork_len & 1) == 0) ? 1 : 0;
#ifdef DEBUG_MOVERT_9_LEVEL
        fprintf(stderr, "debug: tcob_move_9_c 300.080 : fDstWork.len=%d, k=%d, j=%d\n", fDstWork.len, k, j);
#endif
	for(i = 0; i < DstWork_len; ++i) {
		iDigit = caWork[j + i] - '0';
		caDstData[k / 2] |= ((k & 1) ? (iDigit) : (iDigit << 4));
#ifdef DEBUG_MOVERT_9_LEVEL
                fprintf(stderr, "debug: tcob_move_9_c 300.090 : i=%d, k=%d, caWork[%d]=%02x, iDigit=%02x, caDstData[%d]=%02x\n", i, k, i+j, caWork[j+i], iDigit, k/2, caDstData[k / 2]);
#endif
		++k;
	}
	if(tcob_picElemVal(fDstWork.pic,0) == 'S')
		iDigit = (bIsNegative) ? 0x0D : 0x0C;
	else
		iDigit = 0x0F;
#ifdef DEBUG_MOVERT_9_LEVEL
        fprintf(stderr, "debug: tcob_move_9_c 300.120 : fDstWork.len=%d, iDigit=%02x, caDstData[%d]=%02x\n", fDstWork.len, iDigit, fDstWork.len - 1, caDstData[fDstWork.len - 1]);
#endif
	caDstData[fDstWork.len - 1] |= iDigit;
#ifdef DEBUG_MOVERT_9_LEVEL
        fprintf(stderr, "debug: tcob_move_9_c 300.140 : fDstWork.len=%d, iDigit=%02x, caDstData[%d]=%02x\n", fDstWork.len, iDigit, fDstWork.len - 1, caDstData[fDstWork.len - 1]);
#endif
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_9_c (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
        /* if (caSrcData != NULL)
           free(caSrcData);   */      

	return;
}



void tcob_move_9_e(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_9_e (%d)\n", _iMoveLevel_++);
	}
#endif
	tcob_move_edited(pfldDesc1, caData1, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_9_e (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
	return;
}



void tcob_move_9_f(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	int				i, j, k;
	int				bIsNegative;
	int				iSrcDecimals, iSrcPscale;
	char				caWork[MAX_INTEGERS + MAX_DECIMALS + 2];
	unsigned char			*caSrcData;
	struct fld_desc			fSrcWork;
	double				dWork;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_9_f (%d)\n", _iMoveLevel_++);
	}
#endif
	memcpy(&fSrcWork, pfldDesc1, sizeof(struct fld_desc));

	caSrcData = (unsigned char *)caData1;
        /* caSrcData = tcob_dup_data(pfldDesc1, caData1);
        if (caSrcData == NULL) 
            return;      */     

	iSrcDecimals = (char)fSrcWork.decimals;		/* do not remove (char) */
	iSrcPscale = (char)fSrcWork.pscale;		/* do not remove (char) */
	
	if(tcob_picElemVal(fSrcWork.pic,0) == 'S') {	/* Variable is signed */
		if(fSrcWork.separate_sign) {
			char cSign;
			if(fSrcWork.leading_sign) {
				cSign = caSrcData[0];
				++caSrcData;		/* point past the sign */
			} else
				cSign = caSrcData[fSrcWork.len - 1];
			fSrcWork.len --;		/* subtract length of sign */
			bIsNegative = (cSign == '-') ? 1 : 0;
		} else					/* Sign is non-separate */
			bIsNegative = tcob_extract_sign(&fSrcWork, (char *)caSrcData);
	} else				/* Variable is unsigned */
		bIsNegative = 0;

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
		if(iSrcPscale < 0)		/* integer scaling */
			j = MAX_DIGITS - fSrcWork.len - (iSrcPscale * -1);
		else if(iSrcDecimals > (int)fSrcWork.len)	/* fractional scaling */
			j = MAX_DIGITS + iSrcDecimals - fSrcWork.len;
		else
			j = MAX_DIGITS - (fSrcWork.len - fSrcWork.decimals);

		memmove(&caWork[j], caSrcData, fSrcWork.len);
		if((tcob_picElemVal(fSrcWork.pic,0) == 'S') && (!fSrcWork.separate_sign)) 
			tcob_put_sign(&fSrcWork, (char *)caSrcData, bIsNegative);
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
		fprintf(stderr, "Debug:  Leaving tcob_move_9_f (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
        /* if (caSrcData != NULL)
           free(caSrcData);    */    

	return;
}
		


void tcob_move_9_x(struct fld_desc *pfldDesc1, char *caData1, 
			  struct fld_desc *pfldDesc2, char *caData2) {
	unsigned int		i;
	unsigned int		bIsNegative;
	unsigned int		bSrcSigned;
	unsigned int		iSrcLen;
	int			iSrcPscale;	
	char			*caSrcData;

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Enter tcob_move_9_x (%d)\n", _iMoveLevel_++);
	}
#endif

	caSrcData = caData1;
        /* caSrcData = tcob_dup_data(pfldDesc1, caData1);
        if (caSrcData == NULL) 
            return;   */       

	iSrcLen = pfldDesc1->len;
	iSrcPscale = -(char)pfldDesc1->pscale;
	bSrcSigned = (tcob_picElemVal(pfldDesc1->pic,0) == 'S') ? 1 : 0;

	/* Remove sign, as in numeric to alphanumeric transfers, it is not
	 * transferred to the destination */
	if(bSrcSigned) {
		if(pfldDesc1->separate_sign) {
			iSrcLen --;
			if (pfldDesc1->leading_sign)
			       caSrcData ++;
		} else
			bIsNegative = tcob_extract_sign(pfldDesc1, caSrcData);
	}
        
	if(pfldDesc1->all) {	/* this is a 'move all' */
		if(iSrcLen == 1) {
			memset(caData2, *caSrcData, pfldDesc2->len);
		} else {
			unsigned int rem = pfldDesc2->len % iSrcLen;
			for(i = 0; i < pfldDesc2->len - rem; i += iSrcLen)
				memcpy(caData2+i, caSrcData, iSrcLen);
			memcpy(caData2+i, caSrcData, rem);
		}
	} else {
		/* start is the offset into the destination where the source
		 * value is placed, and off1-1 is where it ends.  off1 is where
		 * the pscale zeros begin, and off2-1 is where they end.
		 * srcoff is the number of initial digits not transferred from
		 * the source. */
		int start, end1, end2, srcoff;

		srcoff = 0;
		if(pfldDesc2->just_r) {
			start = pfldDesc2->len-(iSrcPscale+iSrcLen);
			end1  = pfldDesc2->len-iSrcPscale;
			end2  = pfldDesc2->len;
			if (start < 0) {
				srcoff = -start;
				start = 0;
			}
			if (end1 < 0)
				end1 = 0;
		} else {
			start = 0;
			end1  = iSrcLen;
			end2  = iSrcLen+iSrcPscale;
			if (end1 > pfldDesc2->len)
				end1 = pfldDesc2->len;
			if (end2 > pfldDesc2->len)
				end2 = pfldDesc2->len;
		}
		memset(caData2, ' ', pfldDesc2->len); 
	        memcpy(caData2+start, caSrcData+srcoff, end1-start);
		memset(caData2+end1, '0', end2-end1);
	}

	/* Restore sign to the source */
	if (bSrcSigned && (!pfldDesc1->separate_sign))
		tcob_put_sign(pfldDesc1, caSrcData, bIsNegative);

#ifdef DEBUG_MOVE_RTS
	{
		extern int _iMoveLevel_;
		fprintf(stderr, "Debug:  Leaving tcob_move_9_x (%d)\n", --_iMoveLevel_);
		_FLDDUMP_(pfldDesc1, caData1, "Source");
		_FLDDUMP_(pfldDesc2, caData2, "Dest");
	}
#endif
        /* if (caSrcData != NULL)
           free(caSrcData);  */       

	return;
}


