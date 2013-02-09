/* 
 * Copyright (C) 1999 - 2003, Rildo Pragana, Jim Noeth, 
 *                            David Essex.
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
 * TinyCOBOL Run Time Library -- Edited move functions
 *

*/

#include "htcoblib.h"

/*
#define DEBUG_RTS 1 
#define DEBUG_MOVE_RTS 1 
#define DEBUG_MOVE_RTS1 1 
*/

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_move_edited                              |
 |                                                                        |
\*------------------------------------------------------------------------*/

enum suppress_state {SUPPRESS_NOT_YET,
                     SUPPRESS_YES,
                     SUPPRESS_DONE};

void tcob_move_edited( struct fld_desc *pSrcFld, char *pSrcData,
                       struct fld_desc *pDstFld, char *pDstData ) {
        unsigned int                        i, k;
        unsigned int                        iSrcPtr;
        int                                 iDstPtr;
        int                                 iDecimalPos;
        enum suppress_state                 iSuppress;
        unsigned int                        bIsNegative;
        unsigned int                        bInFraction;
        unsigned int                        bIsAlphaEdited;
        unsigned int                        bBlanking;
//        extern int                        bDecimalComma;

        char                                *caWorkData;
        char                                *pPic;
        unsigned int                        picLen;
        char                                cChar;
        char                                cFloatChar;
        char                                cFillChar;
        char                                cInsertion;
        char                                cDecimalPoint;
        char                                cComma;
//        extern char                        cCurrencySymbol;

        struct fld_desc                     FldWrk;

#ifdef DEBUG_MOVE_RTS
        {
         extern int _iMoveLevel_;
         fprintf(stderr, "Debug:  Enter tcob_move_edited (%d)\n", _iMoveLevel_++);
        }
#endif

        memset(&FldWrk, 0, sizeof(struct fld_desc)); /* All values to 0 */
        picLen = tcob_picReqLen(1);
        FldWrk.pic = (char *)malloc(picLen);
        tcob_picCreate (FldWrk.pic, picLen, 'S', 1, NULL);
        FldWrk.just_r = pDstFld->just_r;
        pPic = pDstFld->pic;
        bIsNegative = 0;
        bInFraction = 0;
        bIsAlphaEdited = 0;        /* Assume Numeric-Edited */
        bBlanking = 1;
        cInsertion = '\0';
        if(bDecimalComma) {
                cComma = '.';
                cDecimalPoint = ',';
        } else {
                cComma = ',';
                cDecimalPoint = '.';
        }

        for(i=0; (cChar=tcob_picElemVal(pPic,i)); i++) {
                k = tcob_picElemLen(pPic,i);
                if((cChar == 'X')
                || (cChar == '9')
                || (cChar == 'A')) {
                        if(cChar != '9')
                                bIsAlphaEdited = 1;
                        bBlanking = 0;
                        FldWrk.len += k;
                        if(bInFraction)
                                FldWrk.decimals += k;
                } else if((cChar == 'Z')
                       || (cChar == '*')) {
                        cInsertion = cChar;
                        FldWrk.len += k;
                        if(bInFraction)
                                FldWrk.decimals += k;
                } else if((cChar == '+')
                       || (cChar == '-')
                       || (cChar == cCurrencySymbol)) {
                        if(cInsertion) {
                                if(cInsertion == cChar) {
                                        FldWrk.len += k;
                                        if(bInFraction)
                                                FldWrk.decimals += k;
                                }
                        } else if(k > 1) {
                                cInsertion = cChar;
                                FldWrk.len += (k - 1);
                                if(bInFraction)
                                        FldWrk.decimals += (k - 1);
                        } else {
                                unsigned int ii;
                                unsigned char c;
                                for(ii=i+1; (c=tcob_picElemVal(pPic, ii)); ii++) {
                                        if (c == cChar) {
                                                cInsertion = cChar;
                                                break;
                                        } else if((c != cDecimalPoint)
                                               && (c != cComma)
                                               && (c != '0')
                                               && (c != '/')
                                               && (c != 'B')){
                                                break;
                                        }
                                }
                        }
                } else if((cChar == cDecimalPoint)
                       || (cChar == 'V')) {
                        bInFraction = 1;
                }
        }
        if(FldWrk.len == 0) {
                free(FldWrk.pic);
                return;
        }
        caWorkData = (char *)malloc(FldWrk.len);
        if(!caWorkData) {
                free(FldWrk.pic);
                return;
        }
        FldWrk.type = (bIsAlphaEdited) ? DTYPE_ALPHANUMERIC : DTYPE_DISPLAY;
        
        tcob_move(pSrcFld, pSrcData, &FldWrk, caWorkData);

        if(!bIsAlphaEdited)
                bIsNegative = tcob_extract_sign(&FldWrk, caWorkData);
        if(bBlanking) { /* Zero suppression with replacement insertion */
                for(i = 0; i < FldWrk.len; ++i)
                        if(caWorkData[i] != '0')
                                break;
                if(i == FldWrk.len) {        /* it is zero, so blank it out */
                        if (cInsertion == '*') {
                                unsigned int j, dp = 0;
                                memset(pDstData, '*', pDstFld->len);
                                /* reset the decimal point */
                                for(j=0; (cChar=tcob_picElemVal(pPic, j)); j++) {
                                        if (cChar==cDecimalPoint) {
                                                pDstData[dp] = cChar;
                                                break;
                                        }
                                        dp += tcob_picElemLen(pPic, j);
                                        if (dp >= pDstFld->len)
                                                break;
                                }
                        } else {
                                memset(pDstData, ' ', pDstFld->len);
                        }
                        free(FldWrk.pic);
                        return;
                }
        }
        free(FldWrk.pic);

        iSuppress = SUPPRESS_NOT_YET;
        bInFraction = 0;
        cFloatChar = '\0';
        cFillChar = ' ';

        iSrcPtr = 0;
        iDstPtr = 0;
        iDecimalPos = 0;

        /* pPic now becomes an expanded version of the PIC string */
        pPic = tcob_picExpand(pDstFld);
        if(!pPic) {
                free(caWorkData);
                return;
        }
        for(i=0; (cChar=pPic[i]); i++, iDstPtr++) {
                if((cChar == 'X')
                || (cChar == '9')
                || (cChar == 'A')) {
                        if((iSuppress == SUPPRESS_YES) /* floating insertion so far */
                        && (cFloatChar)) {
                                pDstData[iDstPtr - 1] = cFloatChar;
                        }
                        pDstData[iDstPtr] = caWorkData[iSrcPtr];
                        iSuppress = SUPPRESS_DONE;
                        iSrcPtr++;
                } else if((cChar == 'Z')
                       || (cChar == '*')) {
                        if (iSuppress == SUPPRESS_DONE) {
                                pDstData[iDstPtr] = caWorkData[iSrcPtr];
                        } else if (caWorkData[iSrcPtr] != '0') {
                                pDstData[iDstPtr] = caWorkData[iSrcPtr];
                                iSuppress = SUPPRESS_DONE;
                        } else {
                                if (cChar == '*')
                                        cFillChar = '*';
                                pDstData[iDstPtr] = cFillChar;
                                iSuppress = SUPPRESS_YES;
                        }
                        iSrcPtr++;
                } else if((cChar == cCurrencySymbol)
                       || (cChar == '+')
                       || (cChar == '-')) {
                        char c;
                        if     (cChar == '+') c = (bIsNegative) ? '-' : cChar;
                        else if(cChar == '-') c = (bIsNegative) ? cChar : ' ';
                        else                  c = cChar;

                        if((!cInsertion)
                          ||(cInsertion == 'Z')
                          ||(cInsertion == '*')) {
                                pDstData[iDstPtr] = c;
                        } else { /* floating insertion */
                                if (iSuppress == SUPPRESS_YES) {
                                        if (caWorkData[iSrcPtr] != '0') {
                                                pDstData[iDstPtr-1] = c;
                                                iSuppress = SUPPRESS_DONE;
                                        } else {
                                                pDstData[iDstPtr] = ' ';
                                                 iSrcPtr++;
                                        }
                                }

                                if (cChar != cInsertion) {
                                        pDstData[iDstPtr] = c;
                                } else if (iSuppress == SUPPRESS_DONE) {
                                        pDstData[iDstPtr] = caWorkData[iSrcPtr];
                                        iSrcPtr++;
                                } else if (iSuppress == SUPPRESS_NOT_YET) {
                                        pDstData[iDstPtr] = ' ';
                                        cFloatChar = c;
                                        iSuppress = SUPPRESS_YES;
                                }                                        
                        }

                } else if((cChar == cComma) /* simple insertion */
                       || (cChar == '0')
                       || (cChar == '/')
                       || (cChar == 'B')) {
                        pDstData[iDstPtr] = (iSuppress == SUPPRESS_YES)
                                ? cFillChar
                                : ((cChar == 'B') ? ' ' : cChar);

                } else if(cChar == cDecimalPoint) { /* special insertion */
                        pDstData[iDstPtr] = cChar;
                        if ((iSuppress == SUPPRESS_YES) && (cFloatChar))
                                pDstData[iDstPtr-1] = cFloatChar;
                        iSuppress = SUPPRESS_DONE;
                } else if(cChar == 'V') {
                        iDstPtr--; /* iDstPtr not incremented */
                        iDecimalPos = iDstPtr+1;

                } else if((cChar == 'C')
                       && (pPic[i + 1] == 'R')) {
                        if(bIsNegative) {
                                pDstData[iDstPtr]   = 'C';
                                pDstData[iDstPtr+1] = 'R';
                        } else {
                                pDstData[iDstPtr]   = ' ';
                                pDstData[iDstPtr+1] = ' ';
                        }
                        i++;
                        iDstPtr++;
                } else if((cChar == 'D')
                       && (pPic[i + 1] == 'B')) {
                        if(bIsNegative) {
                                pDstData[iDstPtr]   = 'D';
                                pDstData[iDstPtr+1] = 'B';
                        } else {
                                pDstData[iDstPtr]   = ' ';
                                pDstData[iDstPtr+1] = ' ';
                        }
                        i++;
                        iDstPtr++;
                } else {
                        pDstData[iDstPtr] = cChar;
                        iSuppress = SUPPRESS_DONE;
                }
        }
        if((iDecimalPos)
        && (iSuppress == SUPPRESS_DONE)) {
                for(i=iDecimalPos; i < pDstFld->len; i++) {
                        if((pDstData[i] >= '0')
                        && (pDstData[i] <= '9'))
                                break;
                        pDstData[i] = '0';
                }
        }
        free(pPic);
        free(caWorkData);
#ifdef DEBUG_MOVE_RTS
        {
         extern int _iMoveLevel_;
         fprintf(stderr, "Debug:  Leaving tcob_move_edited (%d)\n", --_iMoveLevel_);
         _FLDDUMP_(pSrcFld, pSrcData, "Source");
         _FLDDUMP_(pDstFld, pDstData, "Dest");
        }
#endif
        return;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_move_e_9                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_move_e_9( struct fld_desc *pfldDesc1, char *caData1,
                    struct fld_desc *pfldDesc2, char *caData2 ) {

        unsigned int                        i;
        unsigned int                        bInDecPortion;
        unsigned int                        bLeadingWhite;
        unsigned int                        bTrailingWhite;
        unsigned int                        iDigitCount;
        unsigned int                        iDecCount;
//        extern int                        bDecimalComma;
        char                                *caWork;
        unsigned int                        picLen;
        char                                cDecimalPoint;
        char                                cChar;
        char                                cSign;
        struct fld_desc                     fldWork;

        iDigitCount = 0;
        iDecCount = 0;
        bInDecPortion = 0;
        bLeadingWhite = 0;
        bTrailingWhite = 0;
        cSign = 0;
        cDecimalPoint = (bDecimalComma) ? ',' : '.';

#ifdef DEBUG_MOVE_RTS
        {
                extern int _iMoveLevel_;
                fprintf(stderr, "Debug:  Enter tcob_move_e_9 (%d)\n", _iMoveLevel_++);
        }
#endif
                
        caWork = (char *)malloc(pfldDesc1->len);

        /* de-edit */
        /* Check for CR or DB at end to indicate a minus sign */
        i = pfldDesc1->len - 2;
        if (i >= 0) {
           if (((caData1[i] == 'C') && (caData1[i+1] == 'R')) || 
               ((caData1[i] == 'D') && (caData1[i+1] == 'B'))) { 
               cSign = 2;
           }
        }
        
        for(i = 0; i < pfldDesc1->len; ++i) {
                cChar = caData1[i];
                switch(cChar) {
                        case '+':
                        case '-':
                                if(cSign) {
                                        runtime_error(RTERR_INVALID_DATA, pfldDesc1, 
                                                (void *)caData1);
                                        memset(caData2, '0', pfldDesc2->len);
#ifdef DEBUG_MOVE_RTS
        {
                extern int _iMoveLevel_;
                fprintf(stderr, "Debug:  Leaving tcob_move_e_9 (%d)\n", --_iMoveLevel_);
                _FLDDUMP_(pfldDesc1, caData1, "Source");
                _FLDDUMP_(pfldDesc2, caData2, "Dest");
        }
#endif
                                        free(caWork);
                                        return;
                                }
                                cSign = (cChar == '+') ? 1 : 2;
                                break;
                        case '.':
                        case ',':
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
                                caWork[iDigitCount++] = cChar;
                                if(bInDecPortion)
                                        iDecCount++;
                                break;
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

#ifdef DEBUG_MOVE_RTS
        {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  before tcob_move_9_9 call (%d)\n", _iMoveLevel_);
        _FLDDUMP_(&fldWork, caWork, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
        }
#endif
        tcob_move_9_9(&fldWork, caWork, pfldDesc2, caData2);

#ifdef DEBUG_MOVE_RTS
        {
                extern int _iMoveLevel_;
                fprintf(stderr, "Debug:  Leaving tcob_move_e_9 (%d)\n", --_iMoveLevel_);
                _FLDDUMP_(pfldDesc1, caData1, "Source");
                _FLDDUMP_(pfldDesc2, caData2, "Dest");
        }
#endif
        free(fldWork.pic);
        free(caWork);
        return;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_move_e_b                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_move_e_b( struct fld_desc *pfldDesc1, char *caData1,
                    struct fld_desc *pfldDesc2, char *caData2 )
{

        unsigned int                        picLen, iLen;
        char                                *caWork;
        struct fld_desc                     fldWork;

#ifdef DEBUG_MOVE_RTS
        {
                extern int _iMoveLevel_;
                fprintf(stderr, "Debug:  Enter tcob_move_e_b (%d)\n", _iMoveLevel_++);
        }
#endif

        memset (&fldWork, 0, sizeof(fldWork));

        fldWork.decimals = pfldDesc2->decimals;
        fldWork.type = DTYPE_DISPLAY;
        fldWork.pscale = pfldDesc2->pscale;
        fldWork.all = pfldDesc2->all;
        fldWork.just_r = pfldDesc2->just_r;
        fldWork.separate_sign = pfldDesc2->separate_sign;
        fldWork.leading_sign = pfldDesc2->leading_sign ;
        fldWork.len = tcob_picCompLength(pfldDesc2);

        picLen = (2 * pfldDesc2->len ) + 1;
        fldWork.pic = (char *)malloc(picLen);
        memcpy(fldWork.pic, pfldDesc2->pic, picLen);

        iLen = tcob_picCompLength(pfldDesc2);
        caWork = (char *)malloc(iLen);
        memset (caWork, 0, iLen);

#ifdef DEBUG_MOVE_RTS
        {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  before tcob_move_e_9 call (%d)\n", _iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(&fldWork, caWork, "Dest");
        }
#endif

        tcob_move_e_9(pfldDesc1, caData1, &fldWork, caWork);

#ifdef DEBUG_MOVE_RTS
        {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  before tcob_move_9_b call (%d)\n", _iMoveLevel_);
        _FLDDUMP_(&fldWork, caWork, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
        }
#endif

        tcob_move_9_b(&fldWork, caWork, pfldDesc2, caData2);

#ifdef DEBUG_MOVE_RTS
        {
                extern int _iMoveLevel_;
                fprintf(stderr, "Debug:  Leaving tcob_move_e_b (%d)\n", --_iMoveLevel_);
                _FLDDUMP_(pfldDesc1, caData1, "Source");
                _FLDDUMP_(pfldDesc2, caData2, "Dest");
        }
#endif
        free(fldWork.pic);
        free(caWork);
        return;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_move_e_f                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_move_e_f( struct fld_desc *pfldDesc1, char *caData1,
                    struct fld_desc *pfldDesc2, char *caData2 )
{

        unsigned int                        picLen, iLen;
        char                                *caWork;
        struct fld_desc                     fldWork;

#ifdef DEBUG_MOVE_RTS
        {
                extern int _iMoveLevel_;
                fprintf(stderr, "Debug:  Enter tcob_move_e_f (%d)\n", _iMoveLevel_++);
        }
#endif

        memset (&fldWork, 0, sizeof(fldWork));

        fldWork.decimals = pfldDesc2->decimals;
        fldWork.type = DTYPE_DISPLAY;
        fldWork.pscale = pfldDesc2->pscale;
        fldWork.all = pfldDesc2->all;
        fldWork.just_r = pfldDesc2->just_r;
        fldWork.separate_sign = pfldDesc2->separate_sign;
        fldWork.leading_sign = pfldDesc2->leading_sign ;
        fldWork.len = tcob_picCompLength(pfldDesc2);

        picLen = (2 * pfldDesc2->len ) + 1;
        fldWork.pic = (char *)malloc(picLen);
        memcpy(fldWork.pic, pfldDesc2->pic, picLen);

        iLen = tcob_picCompLength(pfldDesc2);
        caWork = (char *)malloc(iLen);
        memset (caWork, 0, iLen);

#ifdef DEBUG_MOVE_RTS
        {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  before tcob_move_e_9 call (%d)\n", _iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(&fldWork, caWork, "Dest");
        }
#endif

        tcob_move_e_9(pfldDesc1, caData1, &fldWork, caWork);

#ifdef DEBUG_MOVE_RTS
        {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  before tcob_move_9_f call (%d)\n", _iMoveLevel_);
        _FLDDUMP_(&fldWork, caWork, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
        }
#endif

        tcob_move_9_f(&fldWork, caWork, pfldDesc2, caData2);

#ifdef DEBUG_MOVE_RTS
        {
                extern int _iMoveLevel_;
                fprintf(stderr, "Debug:  Leaving tcob_move_e_f (%d)\n", --_iMoveLevel_);
                _FLDDUMP_(pfldDesc1, caData1, "Source");
                _FLDDUMP_(pfldDesc2, caData2, "Dest");
        }
#endif
        free(fldWork.pic);
        free(caWork);
        return;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_move_e_c                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_move_e_c( struct fld_desc *pfldDesc1, char *caData1,
                    struct fld_desc *pfldDesc2, char *caData2 )
{

        unsigned int                        picLen, iLen;
        char                                *caWork;
        struct fld_desc                     fldWork;

#ifdef DEBUG_MOVE_RTS
        {
                extern int _iMoveLevel_;
                fprintf(stderr, "Debug:  Enter tcob_move_e_c (%d)\n", _iMoveLevel_++);
        }
#endif

        memset (&fldWork, 0, sizeof(fldWork));

        fldWork.decimals = pfldDesc2->decimals;
        fldWork.type = DTYPE_DISPLAY;
        fldWork.pscale = pfldDesc2->pscale;
        fldWork.all = pfldDesc2->all;
        fldWork.just_r = pfldDesc2->just_r;
        fldWork.separate_sign = pfldDesc2->separate_sign;
        fldWork.leading_sign = pfldDesc2->leading_sign ;
        fldWork.len = tcob_picCompLength(pfldDesc2);

        picLen = (2 * pfldDesc2->len ) + 1;
        fldWork.pic = (char *)malloc(picLen);
        memcpy(fldWork.pic, pfldDesc2->pic, picLen);

        iLen = tcob_picCompLength(pfldDesc2);
        caWork = (char *)malloc(iLen);
        memset (caWork, 0, iLen);

#ifdef DEBUG_MOVE_RTS
        {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  before tcob_move_e_9 call (%d)\n", _iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(&fldWork, caWork, "Dest");
        }
#endif

        tcob_move_e_9(pfldDesc1, caData1, &fldWork, caWork);

#ifdef DEBUG_MOVE_RTS
        {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  before tcob_move_9_c call (%d)\n", _iMoveLevel_);
        _FLDDUMP_(&fldWork, caWork, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
        }
#endif

        tcob_move_9_c(&fldWork, caWork, pfldDesc2, caData2);

#ifdef DEBUG_MOVE_RTS
        {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Leaving tcob_move_e_c (%d)\n", --_iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(pfldDesc2, caData2, "Dest");
        }
#endif
        free(fldWork.pic);
        free(caWork);
        return;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_move_e_e                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_move_e_e( struct fld_desc *pfldDesc1, char *caData1,
                    struct fld_desc *pfldDesc2, char *caData2 )
{
 unsigned int i, j, k=0;
 char *caWork, cChar, eChar, *pData, caWork1[MAX_INTEGERS];
 struct fld_desc fldWork;

#ifdef DEBUG_MOVE_RTS1
 {
  extern int _iMoveLevel_;
  fprintf(stderr, "Debug:  Enter tcob_move_e_e (%d)\n", _iMoveLevel_++);
 }
#endif

 caWork = tcob_picExpand(pfldDesc1);

 /* Check for numeric-edited picture format */
 /* if (tcob_isNumEdit(caWork) == 1) { This does NOT work properly */
 if (tcob_isNumEdit(pfldDesc1->pic) == 1) {

#ifdef DEBUG_MOVE_RTS1
    {
    extern int _iMoveLevel_;
    fprintf(stderr, "Debug:  Leaving tcob_move_e_e-z (%d)\n", _iMoveLevel_++);
    _FLDDUMP_(pfldDesc1, caData1, "Source");
    _FLDDUMP_(pfldDesc2, caData2, "Dest");
    }
#endif

    /* Build temporary work */
    fldWork.len = tcob_picEditedCompLength(pfldDesc1) + 2;
    fldWork.type = DTYPE_DISPLAY;
    fldWork.decimals = tcob_picEditedCompDecimals(pfldDesc1);
    fldWork.pscale = 0;
    fldWork.all = pfldDesc1->all;
    fldWork.just_r = 0;
    fldWork.separate_sign = 0;
    fldWork.leading_sign = 0;
    i = tcob_picReqLen(fldWork.len);
    fldWork.pic = (char *)malloc(i);
    pData = &caWork1[MAX_INTEGERS - i];

#ifdef DEBUG_MOVE_RTS1
    fprintf(stderr, "Debug:  Leaving tcob_move_e_e-z0 len=%d, decimals=%d, i=%d\n", fldWork.len, fldWork.decimals, i);
#endif

    if (fldWork.decimals > 0) {
       k = fldWork.len - fldWork.decimals;
       if (k > 0) 
          tcob_picCreate(fldWork.pic, fldWork.len, 'S', 1, '9', k, 'V', 1, '9', j, NULL);
       else 
          tcob_picCreate(fldWork.pic, fldWork.len, 'S', 1, 'V', 1, '9', j, NULL);
    }
    else {
       tcob_picCreate(fldWork.pic, fldWork.len, 'S', 1, '9', i, NULL);
    }

    tcob_move_e_9(pfldDesc1, caData1, &fldWork, caWork1);
#ifdef DEBUG_MOVE_RTS1
    {
    extern int _iMoveLevel_;
    fprintf(stderr, "Debug:  Leaving tcob_move_e_e-z1 (%d)\n", _iMoveLevel_);
    _FLDDUMP_(pfldDesc1, caData1, "Source");
    _FLDDUMP_(&fldWork, caWork1, "Dest");
    }
#endif

    tcob_move_9_e(&fldWork, caWork1, pfldDesc2, caData2);
#ifdef DEBUG_MOVE_RTS1
    {
    extern int _iMoveLevel_;
    fprintf(stderr, "Debug:  Leaving tcob_move_e_e-z2 (%d)\n", _iMoveLevel_);
    _FLDDUMP_(&fldWork, caWork1, "Source");
    _FLDDUMP_(pfldDesc1, caData1, "Dest");
    }
#endif

    free(fldWork.pic);
 }
 else {
    caWork = tcob_picExpand(pfldDesc2);

    for(i=0, j=0; i < pfldDesc2->len; ++i) {
       cChar = caWork[i];               

#ifdef DEBUG_MOVE_RTS
       {
       extern int _iMoveLevel_;
       fprintf(stderr, "Debug:  Loop dump: tcob_move_e_e: j=%d, caData1[i=%d]=%c, caData2[i=%d]=%c, caWork[i=%d]=%c, eChar=%c, cChar=%c, (%d)\n", j, i, caData1[j], i, caData2[i], i, caWork[i], eChar, cChar, _iMoveLevel_);
       }
#endif

       if (pfldDesc1->len > j) {
          eChar = caData1[j];               
       }
       else {
          eChar = ' ';               
       }
       switch(cChar) {
       case '9':
          if ((eChar > 47) && (eChar < 58)) {
             caData2[i] = eChar;               
          }
          else {
             caData2[i] = cChar;               
          }
          j++;
          break;
       case 'B':
          caData2[i] = ' ';               
          break;
       case 'Z':
          if (eChar == 48) {
             caData2[i] = ' ';               
          }
          else {
             caData2[i] = eChar;               
          }
          j++;
          break;
       case 'X':
          caData2[i] = eChar;               
          j++;
          break;
       default:
          caData2[i] = cChar;               
          j++;
          break;
       }

#ifdef DEBUG_MOVE_RTS
       {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  Loop dump: tcob_move_e_e: j=%d, caData1[i=%d]=%c, caData2[i=%d]=%c, caWork[i=%d]=%c, eChar=%c, cChar=%c, (%d)\n", j, i, caData1[j], i, caData2[i], i, caWork[i], eChar, cChar, _iMoveLevel_);
/*
        if (j == 0) {
          fprintf(stderr, "Debug:  Loop dump: tcob_move_e_e: caData1[j=%d]=%c, caData2[i=%d]=%c, caWork[i=%d]=%c, eChar=%c, cChar=%c, (%d)\n", (j), caData1[j], i, caData2[i], i, caWork[i], eChar, cChar, _iMoveLevel_);
        }
        else {
//          fprintf(stderr, "Debug:  Loop dump: tcob_move_e_e: caData1[j=%d]=%c, caData2[i=%d]=%c, caWork[i=%d]=%c, eChar=%c, cChar=%c, (%d)\n", (j-1), caData1[j-1], i, caData2[i], i, caWork[i], eChar, cChar, _iMoveLevel_);
          fprintf(stderr, "Debug:  Loop dump: tcob_move_e_e: caData1[j=%d]=%c, caData2[i=%d]=%c, caWork[i=%d]=%c, eChar=%c, cChar=%c, (%d)\n", j, caData1[j], i, caData2[i], i, caWork[i], eChar, cChar, _iMoveLevel_);
        }
*/
       }
#endif

    }
 }

#ifdef DEBUG_MOVE_RTS
 {
  extern int _iMoveLevel_;
  fprintf(stderr, "Debug:  Leaving tcob_move_e_e (%d)\n", --_iMoveLevel_);
  _FLDDUMP_(pfldDesc1, caData1, "Source");
  _FLDDUMP_(pfldDesc2, caData2, "Dest");
 }
#endif
 
 free(caWork);
 return;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_move_e_x                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_move_e_x( struct fld_desc *pfldDesc1, char *caData1,
                    struct fld_desc *pfldDesc2, char *caData2 )
{

        unsigned int                        picLen, iLen;
        char                                *caWork;
        struct fld_desc                     fldWork;

#ifdef DEBUG_MOVE_RTS
        {
                extern int _iMoveLevel_;
                fprintf(stderr, "Debug:  Enter tcob_move_e_x (%d)\n", _iMoveLevel_++);
        }
#endif

        memset (&fldWork, 0, sizeof(fldWork));

        fldWork.decimals = pfldDesc1->decimals;
        fldWork.type = DTYPE_ALPHANUMERIC;
        fldWork.pscale = pfldDesc1->pscale;
        fldWork.all = pfldDesc1->all;
        fldWork.just_r = pfldDesc1->just_r;
        fldWork.separate_sign = pfldDesc1->separate_sign;
        fldWork.leading_sign = pfldDesc1->leading_sign ;
        fldWork.len = pfldDesc1->len;

        picLen = tcob_picReqLen(1);
        fldWork.pic = (char *)malloc(picLen);
        tcob_picCreate (fldWork.pic, picLen, 'X', pfldDesc1->len, NULL);

        iLen = pfldDesc1->len;
        caWork = (char *)malloc(iLen);
        memcpy (caWork, caData1, iLen);

#ifdef DEBUG_MOVE_RTS
        {
        extern int _iMoveLevel_;
        fprintf(stderr, "Debug:  before tcob_move_x_x call (%d)\n", _iMoveLevel_);
        _FLDDUMP_(pfldDesc1, caData1, "Source");
        _FLDDUMP_(&fldWork, caWork, "Dest");
        }
#endif

        tcob_move_x_x(&fldWork, caWork, pfldDesc2, caData2);

#ifdef DEBUG_MOVE_RTS
        {
                extern int _iMoveLevel_;
                fprintf(stderr, "Debug:  Leaving tcob_move_e_x (%d)\n", --_iMoveLevel_);
                _FLDDUMP_(pfldDesc1, caData1, "Source");
                _FLDDUMP_(pfldDesc2, caData2, "Dest");
        }
#endif
        free(fldWork.pic);
        free(caWork);
        return;
}


