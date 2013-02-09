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

/* 
 * 
 *   COBOL Compiler Run Time Library -- Math Module
 * 
 */

/*
 IMPORTANT NOTE: <<<----
 Numeric type is a pointer (4 bytes) to a data structure.
 The structure is created dynamically when assigned (=) to a Numeric type.
 The Numeric type pointer is stored on the stack generated from the COBOL code.
 To avoid memory leaks (eek!), care must be taken to free the allocated memory
 when no longer required.
*/

#include "imath.h"

/* undef DEBUG_RTS */
/* #define DEBUG_RTS 1  */
/* #define DEBUG_MOVE_RTS 1  */
//#define DEBUG_MOVE_RTS 1  
//#define DEBUG_RTS 1  

static char *exp10s[]={ "1", "10", "100",
                      "1000", "10000", "100000",
                      "1000000", "10000000", "100000000",
                      "1000000000", "10000000000", "100000000000",
                      "1000000000000", "10000000000000", "100000000000000",
                      "1000000000000000", "10000000000000000",
                      "100000000000000000", "1000000000000000000",
                      NULL}; 

/* intermidiate bcd variables */
/* static Numeric nv1; */


/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_dump_num                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

#if 0

static void tcob_dump_num(char *name, Numeric v)
{
        printf("TC RTL BCD[%s] : varlen=%d, n_weight=%d, n_rscale=%d, n_sign_dscale = %d\n",
                name, 
                v->varlen,
                v->n_weight, 
                v->n_rscale
                v->n_sign_dscale);
}
#endif

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_fld2num                                  |
 |  Convert from a string to a 'BCD Numeric' based on the fld_desc        |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_fld2num(struct fld_desc *f, char *sdata, Numeric *pn) 
{
        unsigned int i, j;
        unsigned char sign=0;
        unsigned char fpdig;
        int ndec = f->decimals;
        long long int lli1=0;
        double dbl1;
        char ibuf[64];
        Numeric n0 = *pn;
        char *s;
       
#ifdef DEBUG_MOVE_RTS
        fprintf(stderr, "debug: tcob_fld2num 1: f: type=%c, len=%ld, dec=%d, sdata=%s\n", 
                f->type, 
                f->len, 
                f->decimals,
                sdata);
#endif

        s = tcob_dup_data(f, sdata);
        if (s == NULL) 
           return;          

        switch (f->type) {
          case DTYPE_BININT:
                switch (f->len) {
                        case 1: 
                          lli1 = (long long int) *((char *)s); 
                          break;
                        case 2: 
                          lli1 = (long long int) *((short int *)s); 
                          break;
                        case 4: 
                          lli1 = (long long int) *((int *)s); 
                          break;
                        case 8: 
                          lli1 = (long long int) *((long long *)s); 
                          break;
                }       
#ifdef DEBUG_MOVE_RTS
                fprintf(stderr, "debug: tcob_fld2num 3: f->len=%d, lli1=%lld, s=%d\n",
                        f->len, lli1, *((int *)s)); 
#endif
                n0 = LongLongIntToNumeric(lli1);
                if (f->decimals != 0) {
	           n0 = NumericRescale(n0, 31, ndec);
	           n0 = NumericShift(n0, -ndec);
                }
                break;

          case DTYPE_PACKED:
                for (i=0; ; i++) {
                        fpdig = ((i&1) ? s[i/2] : s[i/2]>>4) & 0x0F;
                        if (fpdig > 9)
                                break;
                        lli1 *= 10;
                        lli1 += (long long int)fpdig;
                }
                sign = ((fpdig==0x0D) || (fpdig==0x0B)) ? 1 : 0;
                if (sign) 
                    lli1 = -lli1;

                n0 = LongLongIntToNumeric(lli1);
                if (f->decimals != 0) {
	           n0 = NumericRescale(n0, 31, ndec);
	           n0 = NumericShift(n0, -ndec);
                }
                break;

          case DTYPE_FLOAT:
                {
                switch (f->len) {
                   case 4: 
//                        sprintf(ibuf, "%f", *((float *)s);
                        dbl1 = (double) *((float *)s);
                        break;
                   case 8: 
//                        sprintf(ibuf, "%d", *((double *)s);
                        dbl1 = *((double *)s);
                        break;
                   }
                n0 = DoubleToNumeric(dbl1);
                }
                break;

          default:
                if (f->separate_sign) {
                    f->len --;
                    if (f->leading_sign) {
                        sign=(s[0] == '-') ? 1 : 0;
                        s ++;
                    } else
                        sign=(s[f->len] == '-') ? 1 : 0;
                } else
                    sign=tcob_extract_sign(f,s);

#ifdef DEBUG_MOVE_RTS
        fprintf(stderr, "debug: tcob_fld2num 6: f: type=%c, len=%ld, dec=%d, s=%s\n", 
                f->type, 
                f->len, 
                f->decimals,
                s);
#endif
                i = 0;
                j = 0;
                ibuf[j] = '\0';
                if (sign) {
                   ibuf[j] = '-';
                   j = 1;
                   ibuf[j] = '\0';
                }

                fpdig = 0;
                if (f->decimals > 0) {
                  fpdig = f->len - f->decimals;
                }
                
//                for (i; i<f->len; i++) {
                while (i < f->len) {
                    if ((fpdig > 0) && (i == fpdig)) {
                       ibuf[j] = '.';
                       j++;                      
                    }
                    if (s[i] != '-') {
                       ibuf[j] = (s[i]==' ') ? 0 : s[i];
                    }
                    j++;
                    i++;
                }
                ibuf[j] = '\0';

                n0 = NumericInput(ibuf, f->len, f->decimals);

                if (f->separate_sign) {
                    f->len ++;
                    if (f->leading_sign)
                        s --;
                } else
                    tcob_put_sign(f,s,sign);
                break;
        }

 #ifdef DEBUG_MOVE_RTS
       fprintf(stderr, "debug: tcob_fld2mun 7: f: type=%c, len=%d, dec=%d; n0=%s\n", 
                f->type, (int)f->len, f->decimals, NumericOutput(n0));
#endif
       *pn = n0;
        
#ifdef DEBUG_MOVE_RTS
       fprintf(stderr, "debug: tcob_fld2mun 9: f: type=%c, len=%d, dec=%d; n0=%s\n", 
                f->type, (int)f->len, f->decimals, NumericOutput(*pn));
#endif

        if (s != NULL) 
            free(s);          

        return;          
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_push_num                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_push_num(struct fld_desc *f, char *s, Numeric n0) 
{
#ifdef DEBUG_MOVE_RTS
        fprintf(stderr, "debug: tcob_push_num 1: f: type=%c, len=%d, dec=%d;\n", 
                f->type, (int)f->len, f->decimals);
#endif

        tcob_fld2num(f, s, &n0);


#ifdef DEBUG_MOVE_RTS
        fprintf(stderr, "debug: tcob_push_num 2: f: type=%c, len=%d, dec=%d, n0=%s;\n", 
                f->type, (int)f->len, f->decimals, NumericOutput(n0));
#endif
}


/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_assign_num                               |
 |  opts: bit 0 = ROUNDED                                                 |
 |        bit 1 = ON SIZE ERROR                                           |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_assign_num(struct fld_desc *f, char *s1, int opts, Numeric n0) 
{
        int rc=0;
        /* do not change n0 (pointer), as it only exists on the stack */
        Numeric n1;

#ifdef DEBUG_MOVE_RTS
        fprintf(stderr, "debug: tcob_assign_num 0: n0=%s\n", NumericOutput(n0));
#endif
        n1 = NumericDup(n0);
        if (f->type == DTYPE_EDITED)
                f->decimals = tcob_picEditedCompDecimals(f);

        if (opts & 1)
           /* tcob_do_rounding_num(f, n1); */
           n1 = NumericRound(n1, f->decimals);
#ifdef DEBUG_MOVE_RTS
       fprintf(stderr, "debug: tcob_assign_num 1: n1=%s, opts=%d\n", NumericOutput(n1), opts);
#endif
       if (opts & 2)
          rc = tcob_check_size_overflow_num(f, n1);

#ifdef DEBUG_MOVE_RTS
       fprintf(stderr, "debug: tcob_assign_num 2: n1=%s, rc=%d\n", NumericOutput(n1), rc);
#endif
       /* no rounding, already done */
       if (rc == 0)
          rc = tcob_num2fld(f, s1, 0, n1); 

/*       fprintf(stderr, "debug: tcob_assign_num  3: n1=%s, s1=%s, rc=%d\n", 
                          NumericOutput(n1), s1, rc); */

       NumericFree(n1);
       /*
       Numeric 'n0' is a pointer stored on the TC generated stack, so 
       if this is the last assignment (conversion), then delete Numeric.
       Failure to do so will create lost pointer(s) and memory leaks !!!
       This code causes seg faults ????
       */
       /*
       if (opts & 4) {
          NumericFree(n0);
          n0 = NULL;
       }
       */
       
       return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_num2fld                                  |
 |  Convert from a BCD to a string based on the fld_desc,                 |
 |  rounding if indicated by round                                        |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_num2fld(struct fld_desc *f, char *s1, int round, Numeric n1) 
{
        int ndec, i, j, len;
        unsigned int sign, rc=0;
        Numeric n2;
        char s2[64]; 

#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_num2fld 0: n1=%s, rc=%d\n", NumericOutput(n1), rc);
#endif


        /* Round or truncate decimals */
        if (n1->n_rscale > 0) {
           if (round != 0) {
              n1 = NumericRound(n1, f->decimals);
           }
           else {
              n1 = NumericTrunc(n1, f->decimals);
           }
        }

#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_num2fld 1: n1=%s, round=%d\n", NumericOutput(n1), round);
#endif

        switch (f->type) {

          case DTYPE_BININT:
                n2 = NumericShift(n1, n1->n_rscale);
#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_num2fld 2: n1=%s\n", NumericOutput(n2));
#endif
                switch (f->len) {
                        case 1:
                          *((char *)s1) = (char) NumericToInt(n2);
/*                          fprintf(stderr, "debug: tcob_num2fld 2-1: n1=%s, s1=%d\n",
                                    NumericOutput(n2), *((char *)s1)); */
                          break;
                        case 2: 
                          *((short int *)s1) = (short) NumericToInt(n2); 
/*                          fprintf(stderr, "debug: tcob_num2fld 2-2: n1=%s, s1=%d\n",
                                    NumericOutput(n2), *((short int *)s1)); */
                          break;
                        case 4: 
                          *((int *)s1) = NumericToInt(n2);  
/*                          fprintf(stderr, "debug: tcob_num2fld 2-4: n1=%s, s1=%d\n",
                                   NumericOutput(n2), *((int *)s1)); */
                          break;
                        case 8: 
                          *((long long *)s1) = NumericToLongLongInt(n2);; 
/*                          fprintf(stderr, "debug: tcob_num2fld 2-8: n1=%s, s1=%d\n",
                                    NumericOutput(n2), *((long long *)s1)); */
                          break;
                }
                return rc;

          case DTYPE_FLOAT:
                switch (f->len) {
                   case 4: 
                     *((float *)s1) = (float) NumericToDouble(n1); 
/*                      fprintf(stderr, "debug: tcob_num2fld 3f: n1=%s, s1=%f\n",
                                        NumericOutput(n1), *((float *)s1)); */
                     break;
                   case 8: 
                       *((double *)s1) = NumericToDouble(n1);
/*                     fprintf(stderr, "debug: tcob_num2fld 3d: n1=%s, s1=%f\n",
                                        NumericOutput(n1), *((double *)s1)); */
                     break;
                   default:
                     rc = 1; 
                     break;
                }       
/*                fprintf(stderr, "debug: tcob_num2fld 5: n1=%s, rc=%d\n",
                          NumericOutput(n1), rc); */
                return rc;

          case DTYPE_EDITED:
                len = tcob_picEditedCompLength(f);
                break;

          case DTYPE_PACKED:
          default:
                len = f->len;
                break;
        }

        if (f->type == DTYPE_EDITED)
                ndec = tcob_picEditedCompDecimals(f);
        else
                ndec = (int)f->decimals;

        if (NumericNegative(n1)) {
           sign = 1;
        }
        else {
           sign = 0;
        }

        n2 = NumericShift(n1, n1->n_rscale);
        if (NumericNegative(n2))
           n2 = NumericUMinus(n2);
        n2 = NumericRescale(n2, 31, 0);
        sprintf(s2, "%s", NumericOutput(n2));

#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_num2fld 6: n2=%s, s2=%s, len=%d, dec=%d, sign=%d\n", 
                           NumericOutput(n2), s2, len, ndec, sign); 
#endif

/*
#if 0
        // Do not remove this code 
        // Check for overflow ??? 
        // if (fpa>exp10[len-ndec]) 
        i = strlen(s2);
        if (i > len) {
           NumericFree(n2);
           fp_runtime_error(f);
           rc = 1;
           return rc;
        }
#endif
*/
/*
        fpa *= exp10d[ndec];
        remainder = fpa - (unsigned long) fpa;
        if (f->pscale < 0) {
                fpa /= exp10d[abs(f->pscale)];
                remainder /= exp10d[abs(f->pscale)];
        }
*/
        if (f->type != DTYPE_PACKED) {
           /* unsigned int mini; */
           /* unsigned long fint; */
           char *s;
           if (f->type == DTYPE_EDITED)
                   s = (char *)malloc(len);
           else
                   s = s1;
           
           /* if seperate sign, tack on and hide */
           if (f->separate_sign) {
              char cSign = (sign) ? '-' : '+';
              if (f->leading_sign) {
                 s[0] = cSign;
                 s ++;
              } else
                 s[len-1] = cSign;
              len --;
           }
 
           /* Initialize s array */
           memset (s, '0', len);
           /* 
            if len(s2) > len(s) then move and truncate s2
            if len(s2) =< len(s) then move data
           */
           i = strlen(s2) - 1;
           j = len - 1;
#ifdef DEBUG_RTS
           fprintf(stderr, "debug: tcob_num2fld 7a: s[%d]=%c, s2[%d]=%c\n", j, s[j], i, s2[i]); 
#endif
//           for (i, j; ((i >= 0) || (j >= 0)); i--, j--) {
           while((i >= 0) && (j >= 0)) {
                s[j] = s2[i];
#ifdef DEBUG_RTS
                fprintf(stderr, "debug: tcob_num2fld 7b: s[%d]=%c, s2[%d]=%c\n", j, s[j], i, s2[i]); 
#endif
                i--;
                j--;
           }
           
#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_num2fld 8: n2=%s, len=%d, dec=%d, sign=%d\n", 
                           NumericOutput(n2), len, ndec, sign); 
#endif
/*
           // digits 10 and up 
           if (fpa>=exp10d[9]) {  // fpa >= 1,000,000,000 
              fint = (unsigned long) ( fpa/exp10d[9] );
              // subtrai parte alta do numero 
              fpa -= fint * exp10d[9];
              // converte parte alta para string 
              for (i=len-9; (i>0) && (fint!=0); i--) {
                   s[i-1] = (char)(fint % 10) + '0';
                   fint /= 10;
              }
           }
           // digits 9 and below 
           fint = (unsigned long) fpa;
           mini = (len>9) ? len-9 : 0; 
           for (i=len; (i>mini) && (fint!=0); i--) {
                   s[i-1] = (char)(fint % 10) + '0';
                   fint /= 10;
           }
*/
           /* for numeric edited, move value and clean up */
           if (f->type == DTYPE_EDITED) {
                   struct fld_desc fcopy;
                   unsigned int picLen = tcob_picReqLen(4);
                   memcpy (&fcopy, f, sizeof(struct fld_desc));
                   fcopy.pic = (char *)malloc(picLen);
                   tcob_picCreate (fcopy.pic, picLen, 'S', 1, '9', len-ndec, NULL);
                   if (ndec > 0)
                           tcob_picAppend (fcopy.pic, picLen, 'V', 1, '9', ndec, NULL);
                   fcopy.type = DTYPE_DISPLAY;
                   fcopy.len = len;
                   fcopy.decimals = ndec;
                   tcob_put_sign (&fcopy, s, sign);
                   tcob_move (&fcopy, s, f, s1);
                   free (fcopy.pic);
                   free (s);
           }
           /* tack on the sign */
           if (!(f->separate_sign))
                   tcob_put_sign(f, s1, sign);
#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_num2fld 10: n2=%s, len=%d, dec=%d, sign=%d\n", 
                           NumericOutput(n2), len, ndec, sign); 
#endif
        }

        if (f->type==DTYPE_PACKED) {
                /* unsigned long long fpahold = (unsigned long long)fpa; */
                unsigned char cDigit, cSign;

                /* Initialize s1 array */
                memset (s1, 0, (len/2)+1);  
                /* Make sure length is odd */
                if ((len&1) == 0) 
                    len++;

/*                
                // Set the last digit in s1 which includes the sign 
                cDigit = s2[i];
                cDigit <<= 4;
                s1[j] = cDigit;
                i--;
                j--;
*/
                /* Deternine length */
                j = len;
                i = strlen(s2) - 1;
                /* convert scaled number in s2 into s1 */
/*
//                while ((i >= 0) && (j > 0)) {
//                     i--;
//                     j--;
*/
                for (i, j; ((i >= 0) && (j > 0)); i--, j--) {
                     cDigit = s2[i];
                     if ((j%2) == 1)
                        cDigit <<= 4;
                     s1[(j-1)/2] |= cDigit;
                }

/*
                for (i=len; (i>0) && (fpahold!=0); i--) {
                        cDigit = fpahold % 10;
                        if ((i%2) == 1)
                                cDigit <<= 4;
                        fpahold /= 10;
                        s1[(i-1)/2] |= cDigit;
                }
*/
                /* attach the sign */
                if (tcob_picElemVal(f->pic,0) == 'S')
                        cSign = (sign) ? 0x0D : 0x0C;
                else
                        cSign = 0x0F;
                s1[len/2] |= cSign;
        }
        
#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_num2fld 16: n2=%s, len=%d, dec=%d, sign=%d\n", 
                           NumericOutput(n2), len, ndec, sign); 
#endif
        NumericFree(n2);

        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_add_num                                  |
 |                          tcob_subtract_num                             |
 |                          tcob_multiply_num                             |
 |                          tcob_divide_num                               |
 |                          tcob_pow_num                                  |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_add_num(Numeric *pn, Numeric n1) 
{
        Numeric n2 = *pn;

#ifdef DEBUG_MOVE_RTS
        fprintf(stderr, "debug: tcob_add_num 1: n2=%s; n1=%s\n", NumericOutput(n2), NumericOutput(n1));
#endif

        n2 = NumericADD(n2, n1);

#ifdef DEBUG_MOVE_RTS
        fprintf(stderr, "debug: tcob_add_num 2: n2=%s; n1=%s\n", NumericOutput(n2), NumericOutput(n1));
#endif
        *pn = n2;
        NumericFree(n1);
}

void tcob_subtract_num(Numeric *pn, Numeric n1) 
{
        Numeric n2 = *pn;

        n2 = NumericSUB(n2, n1);
        *pn = n2;
        
        NumericFree(n1);
}

void tcob_multiply_num(Numeric *pn, Numeric n1) 
{
        Numeric n2 = *pn;

        n2 = NumericMUL(n2, n1);
        *pn = n2;
        
        NumericFree(n1);
}

void tcob_divide_num(Numeric *pn, Numeric n1) 
{
/*
   Divide by zero should not be neccessary, check is done in libfix
*/
        Numeric n2 = *pn;
        Numeric n0;
	
        n0 = NumericInput("0.0",1,1);
        /* check for divide by zero */
        //if (n1 == 0) {
        if (NumericEQ(n1, n0) == FALSE) {
//           fprintf(stderr,"*** RUNTIME ERROR: divide by zero\n");
//           exit(1);
        // *n2 /= n1;
           n2 = NumericDIV(n2, n1);
        }        

        *pn = n2;
        NumericFree(n0);
        NumericFree(n1);
}

void tcob_pow_num(Numeric *pn, Numeric n1) 
{ 
        Numeric n2 = *pn;

        n2 = NumericPOWER(n2, n1);

        *pn = n2;
        NumericFree(n1);
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_iadd_num                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_iadd_num(struct fld_desc *f1, char *s1,
                  struct fld_desc *f2, char *s2, int round) 
{
        int rc=0;
        Numeric n1, n2;

        tcob_fld2num(f1, s1, &n1);
        tcob_fld2num(f2, s2, &n2);
        // n1+=n2;
        n1 = NumericADD(n2, n1);
        rc = tcob_check_size_overflow_num(f2, n1);
        if (rc == 0)
            tcob_num2fld(f2, s2, round, n1);

        NumericFree(n1);
        NumericFree(n2);
        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_isubtract_num                            |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_isubtract_num(struct fld_desc *f1, char *s1,
                       struct fld_desc *f2, char *s2, int round) 
{
        int rc=0;
        Numeric n1, n2;

        tcob_fld2num(f1, s1, &n1);
        tcob_fld2num(f2, s2, &n2);
        // n2 -= n1; 
        n2 = NumericSUB(n2, n1);
        rc = tcob_check_size_overflow_num(f2, n2);
        if (rc == 0) 
                tcob_num2fld(f2,s2,round,n2);

        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_imultiply_num                            |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_imultiply_num(struct fld_desc *f1, char *s1,
                       struct fld_desc *f2, char *s2,
                       struct fld_desc *f3, char *s3, int round) 
{
        int rc=0;
        Numeric n1, n2, n3;

        tcob_fld2num(f1, s1, &n1);
        tcob_fld2num(f2, s2, &n2);
//        n3 = n1 * n2;
        n3 = NumericMUL(n1, n2);
        rc = tcob_check_size_overflow_num(f3, n3);
        if (rc == 0)
                tcob_num2fld(f3, s3, round,n3);
        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_idivide_num                              |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_idivide_num(struct fld_desc *f1, char *s1,
                     struct fld_desc *f2, char *s2,
                     struct fld_desc *f3, char *s3, int round) 
{
        int rc=0;
        Numeric n0, n1, n2, n3;

        tcob_fld2num(f2, s2, &n2);

        n0 = NumericInput("0.0",1,1);
        /* check for divide by zero */
        if (NumericEQ(n2, n0) == TRUE) {
           rc = 1;
        }
        else {
           tcob_fld2num(f1, s1, &n1);
           n3 = NumericDIV(n1, n2);
           rc = tcob_check_size_overflow_num(f3, n3);
           if (rc == 0)
              tcob_num2fld(f3, s3, round, n3);
        }

        NumericFree(n0);
        NumericFree(n1);
        NumericFree(n2);
        NumericFree(n3);

        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_idivide1_num                             |
 |  Divide with remainder option                                          |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_idivide1_num(struct fld_desc *f1, char *s1,
                      struct fld_desc *f2, char *s2,
                      struct fld_desc *f3, char *s3,
                      struct fld_desc *f4, char *s4, int round) 
{
        int rc=0;
        Numeric d0, n1, n2, n3, n4;

        tcob_fld2num(f2, s2, &n2);
//      fprintf(stderr, "debug mcmath 1: n1=%s n2=%s\n", NumericOutput(n1), NumericOutput(n2)); 

//        if (n2 == 0)  { /* divide by zero error */
        d0 = NumericInput("0.0",1,1);
        /* check for divide by zero */
        if (NumericEQ(n2, d0) == TRUE) {
            rc = 1;
            return rc;
        }
        
        /*  
         * Calculate GIVING  
         */
        tcob_fld2num(f1, s1, &n1);
//        n3 = n1 / n2;
        n3 = NumericDIV(n1, n2);
/*      fprintf(stderr, "debug imath 2 : n3=%s\n", NumericOutput(n3)); */

        rc = tcob_check_size_overflow_num(f3, n3);
        if (rc != 0)
            return rc;

        tcob_num2fld(f3, s3, round, n3);

        /* 
         *  Calculate REMAINDER.
         */

//        tcob_fld2num(f3, s3, &tfp3);

//        n4 = (n1 - (tfp3 * n2));
        d0 = NumericMUL(n3, n2);
        n4 = NumericSUB(n1, d0);
//      fprintf(stderr, "debug imath 3 : n1=%s, n2=%s, n3=%s, n4=%s\n", 
//                         NumericOutput(n1), 
//                         NumericOutput(n2), 
//                         NumericOutput(n3), 
//                         NumericOutput(n4)); 

        rc = tcob_check_size_overflow_num(f4, n4);
        if (rc != 0) {
/*              fprintf(stderr, "debug mcmath 4: check_size_overflow : "
                                "a overflow has occured on n4=%s\n",
                       NumericOutput(n4)); */
                return rc;
        }

//      fprintf(stderr, "debug imath 4 : n1=%s, n2=%s, n3=%s, n4=%s\n", 
//                         NumericOutput(n1), 
//                         NumericOutput(n2), 
//                         NumericOutput(n3), 
//                         NumericOutput(n4)); 

        tcob_num2fld(f4, s4, 0, n4);

        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_check_size_overflow_num                  |
 |  Check if size will fit in destination field.  0 if yes, 1 if false.   |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_check_size_overflow_num(struct fld_desc *f, Numeric n0) 
{
        unsigned int rc, len;
        Numeric n1;

        if (f->type == DTYPE_EDITED)
                len = tcob_picEditedCompLength(f);
        else
                len = tcob_picCompLength(f) + tc_abs((char)f->pscale); 

#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_check_size_overflow_num 1: n0=%s, piclen=%d, f->len=%d, f->decimals=%d\n", 
                         NumericOutput(n0), len, (int)f->len, f->decimals);
#endif
        if (len < f->decimals) {
           rc = 1;
        } 
        else {
//          if ( ((d<0)?-d:d) >= exp10[len - f->decimals]) {
           n1 = NumericInput(exp10s[len - f->decimals], 31, 0);
           if (NumericGE(n0, n1) == TRUE) {
              rc = 1;
          } 
          else {
             rc = 0;
          }
        }

#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_check_size_overflow_num 2: n0=%s, n1=%s, rc=%d\n", 
                         NumericOutput(n0), NumericOutput(n1), rc); 
#endif
        NumericFree(n1);

        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_check_condition_num                      |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_check_condition_num(struct fld_desc *f1, char *s1,
                             struct fld_desc *f2, char *s2, 
                             struct fld_desc *f3, char *s3) 
{
        int rc=1;  /* assume false */
        Numeric n1, n2, n3;

        tcob_fld2num(f1, s1, &n1);
        tcob_fld2num(f2, s2, &n2);
        tcob_fld2num(f3, s3, &n3);

        if ((NumericGE(n1, n2) == TRUE) && 
            (NumericLE(n1, n3) == TRUE)) 
           rc = 0;

        NumericFree(n1);
        NumericFree(n2);
        NumericFree(n3);

        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_compare_num                              |
 |  return  1 if s1>s2; 0 if s1==s2; -1 if s1<s2                          |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_compare_num(struct fld_desc *f1, char *s1,
                 struct fld_desc *f2, char *s2) 
{
    int rc = 0;
    Numeric n1, n2;

    tcob_fld2num(f1, s1, &n1);
    tcob_fld2num(f2, s2, &n2);

    rc = NumericCmp(n1, n2); 

    NumericFree(n1);
    NumericFree(n2);

    return rc;
}

/* end of IMATH.C */

