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
 * TinyCOBOL Run Time Library -- Math functions 
 *

*/

#include "htcoblib.h"

/* undef DEBUG_RTS */
/* #define DEBUG_RTS 1 */
/* define DEBUG_MOVE_RTS 1 */
#if defined DEBUG_RTS
/* #define DEBUG_RTN(fmt, p1, p2, p3, p4, p5, p6)
      {fprintf(stderr, fmt, p1, p2, p3, p4, p5, p6);} */
#else
/* #define DEBUG_RTN(fmt, p1, p2, p3, p4, p5, p6) */
#endif

/* global data */
static double exp10[]={1e0,1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9,1e10,1e11,
        1e12,1e13,1e14,1e15,1e16,1e17,1e18,1e19,1e20,1e21,1e22,1e23,1e24,
        1e25,1e26,1e27,1e28,1e29,1e30,1e31,1e32,1e33,1e34,1e35,1e36,1e37,
        1e38,1e39,1e40,1e41,1e42,1e43,1e44,1e45,1e46,1e47,1e48,1e49,1e50};
struct fld_desc _generic_4binary = { 4,DTYPE_BININT,0,0,0,0,0,0,0,0,"S\19\x09" };
struct fld_desc _generic_8float = { 8,DTYPE_FLOAT,15,0,0,0,0,0,0,0,"S\19\x0fV\19\x0f" };

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          fp_runtime_error                              |
 |                                                                        |
\*------------------------------------------------------------------------*/

#if 0
static void fp_runtime_error( struct fld_desc *f ) {
        char *pic;
        fprintf(stderr,"math runtime error: *** invalid contents of numeric field ***\n"); 
        pic = tcob_picExpand(f);
        fprintf(stderr,"field len: %ld, type: %c, decimals: %d, pic: %s\n",
                f->len,f->type,f->decimals,pic);
        free(pic);
/*      getchar();*/
}
#endif

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          dump_double                                   |
 |                                                                        |
\*------------------------------------------------------------------------*/

#if 0
static void dump_double( char *msg, unsigned char *ptr ) {
        int i;
        printf(msg);
        for (i=7;i>=0;i--)
                printf("%02.2x",ptr[i]);
        getchar();
}
#endif

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_sign_to_char                             |
 |  input: digit (-9..-1,0,1..9, or 0x80 for -0)                          |
 |  return: character  +0...+9:"{ABCDEFGHI"  -0...-9:"}JKLMNOPQR"         |
 |                                                                        |
\*------------------------------------------------------------------------*/

char tcob_sign_to_char( int digit ) {
        if (!digit) return '{';
        if (digit==0x80) return '}';
        if (digit>0) return 'A'+(char)(digit-1);
        digit= -digit;
        return 'J'+(char)(digit-1);
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_char_to_sign                             |
 |  input and return are reverse those of tcob_sign_to_char               |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_char_to_sign( char ch ) {
        if (ch=='{') return 0;
        if (ch=='}') return 0x80;
        if (ch<'J') return (int)(ch-'A'+1);
        return (-(int)(ch-'J'+1));
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_extract_sign                             |
 |  return: sign (0 is +, 1 is -)                                         |
 |  modified: s[f->len-1] (if type is not PACKED and is signed)           |
 |                                                                        |
\*------------------------------------------------------------------------*/
char tcob_extract_sign( struct fld_desc *f, char *s ) {
        char *tmp;
        int digit;

        if (tcob_picElemVal(f->pic,0) != 'S')
                return 0;
        if (f->type==DTYPE_PACKED) {
                digit = s[f->len/2] & 0x0F;
                return (((digit == 0x0D) || (digit == 0x0B)) ? 1 : 0) ;
        }
        tmp = (f->leading_sign) ? s : s+f->len-1;
        digit = tcob_char_to_sign(*tmp);
        if (digit==0x80) {
           *tmp='0';
        }
        else { 
           if (digit<0) {
              *tmp='0'-digit;
           }
           else {
                *tmp='0'+digit;
                return 0;
           }
        }
        return 1;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_put_sign                                 |
 |  modified: possibly s[f->len/2] or s[f->len-1]                         |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_put_sign( struct fld_desc *f, char *s, char sign ) {
        char *tmp;
        int digit;

        if (f->type==DTYPE_PACKED) {
                if (tcob_picElemVal(f->pic,0) == 'S')
                        digit = (sign) ? 0x0D : 0x0C;
                else
                        digit = 0x0F;
                s[f->len/2] = (s[f->len/2] & 0xF0) | digit;
                return;
        }
        if (tcob_picElemVal(f->pic,0) != 'S') return;
        tmp = (f->leading_sign) ? s : s+f->len-1;
        digit = *tmp - '0';
/*      fprintf(stderr, "tcob_put_sign: t=%c,d=%d,s=%d\n",*tmp,digit,sign); */
        if (sign) digit = -digit;
        *tmp = tcob_sign_to_char ((sign && digit==0) ? 0x80 : digit);
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_adjust_length                            |
 |                                                                        |
\*------------------------------------------------------------------------*/

struct fld_desc *
tcob_adjust_length( struct fld_desc *dep_desc, char *dep_val, 
        int min, int max, struct fld_desc *var_desc, struct fld_desc *item,
        struct fld_desc *copy) {
                int itocc;
                tcob_move( dep_desc, dep_val, &_generic_4binary, (char *)&itocc);
                if (itocc < min || itocc > max) {
                        /* should generate exception, for now just a warning */
                        fprintf(stderr,"*** Warning: table size out of bounds ");
                        fprintf(stderr,"(requested = %d, min = %d, max = %d)\n",
                                itocc,min,max);
                        itocc = max;
                }
                
                memmove(copy,var_desc,sizeof(struct fld_desc));
                copy->len -= (max - itocc) * item->len;
                return copy;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_get_index & al.                          |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_get_index(struct fld_desc *f, char *s) 
{
  int index=0;
  
  if (f != NULL) 
     tcob_move(f, s, &_generic_4binary, (char *)&index);
   
  return index;
}

int tcob_cnv_ll2i( long long idx ) {
        /* If a run-time truncation check should occur, it should be here */
        return (int)idx;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_fldtod                                   |
 |  Convert from a string to a double based on the fld_desc               |
 |  modified: *fp                                                         |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_fldtod(struct fld_desc *f, char *sdata, double *fp) {
        unsigned int i;
        unsigned char sign=0;
        unsigned char fpdig;
        int scale;
        double fpp=0.;
        char *s;
        
#ifdef DEBUG_MOVE_RTS
        fprintf(stderr, "debug: tcob_fldtod 1: f: type=%c, len=%ld, dec=%d, sdata=%s\n", 
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
                        case 1: fpp = (double) *((char *)s); break;
                        case 2: fpp = (double) *((short int *)s); break;
                        case 4: fpp = (double) *((int *)s); break;
                        case 8: fpp = (double) *((long long *)s); break;
                }       
/*                fprintf(stderr, "debug: tcob_fldtod 3: f->len=%d, fpp=%f, s=%d\n",
                        f->len,
                        fpp,
                        *((int *)s)); */
                break;
          case DTYPE_PACKED:
                for (i=0; ; i++) {
                        fpdig = ((i&1) ? s[i/2] : s[i/2]>>4) & 0x0F;
                        if (fpdig > 9)
                                break;
                        fpp *= 10.;
                        fpp += (double)fpdig;
                }
                sign = ((fpdig==0x0D) || (fpdig==0x0B)) ? 1 : 0;
                break;
          case DTYPE_FLOAT:
                switch (f->len) {
                   case 4: 
                        fpp = (double) *((float *)s); 
/*                             fprintf(stderr, "debug: tcob_fldtod 3a: fpp=%f, s=%f\n", 
                                                 fpp, *((float *)s)); */
                        break;
                   case 8: 
                        fpp = (double) *((double *)s); 
/*                              fprintf(stderr, "debug: tcob_fldtod 3b: fpp=%f, s=%f\n", 
                                                 fpp, *((double *)s)); */
                        break;
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
                  for (i=0;i<f->len;i++) {
                      fpdig = (s[i]==' ') ? 0 : s[i]-'0';
                      fpp *= 10.;
                      fpp += (double)fpdig;
                  }
                  if (f->separate_sign) {
                      f->len ++;
                      if (f->leading_sign)
                          s --;
                  } else
                      tcob_put_sign(f,s,sign);
                  break;
        }

        /* scale the number with it's (fld_desc *)->decimals */
        /* No decimal scaling required for floating types */
        if (f->type != DTYPE_FLOAT) {
            scale = f->decimals;
            if (scale == 0 && f->pscale < 0)
                    scale = f->pscale;
/*            fprintf(stderr, "debug: tcob_fldtod 8a: scale=%d\n",  scale); */
            if (scale > 0 && scale <= 50)
                    fpp /= exp10[scale];
            else if (scale > 50) /* because our table don't have everything */
                    fpp /= pow(10.,(double)scale);
            else if (scale < 0) /* because our table don't have everything */
                    fpp /= pow(10.,(double)scale);
            if (sign) 
                    fpp = -fpp;
            /*dump_double( "\fRes:",&fpp );*/

        }

        *fp = fpp;

#ifdef DEBUG_MOVE_RTS
        fprintf(stderr, "debug: tcob_fldtod 9: f: type=%c, len=%d, dec=%d; fpp=%g\n", 
                f->type, (int)f->len, f->decimals, fpp);
#endif

        if (s != NULL) 
            free(s);          

        return;          
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_push_double                              |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_push_double( struct fld_desc *f, char *s, double d ) {
        tcob_fldtod( f,s,&d );
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          do_rounding                                   |
 |                                                                        |
\*------------------------------------------------------------------------*/

static void do_rounding( struct fld_desc *f, double *d1 ) {
        double fp = *d1;
        double rounding_incr = .5;
        
/*      fp *= exp10[f->decimals]; */
        if (fp < 0) {
           rounding_incr = - rounding_incr;
        }
        if (f->pscale < 0)
                rounding_incr *= exp10[-(f->pscale)];
        else
                rounding_incr /= exp10[f->decimals];
/*       fprintf(stderr, "debug: do_rounding 1: d1=%f, dec=%d, ri=%f\n",
                  fp, f->decimals, rounding_incr); */
        fp += rounding_incr;
/*       fprintf(stderr, "debug: do_rounding 2: d1=%f\n", fp); */
         *d1 = fp;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_assign_double                            |
 |  opts: bit 0 = ROUNDED                                                 |
 |        bit 1 = ON SIZE ERROR                                           |
 |                                                                        |
\*------------------------------------------------------------------------*/

int  tcob_assign_double( struct fld_desc *f, char *s1, int opts, double d1 ) {
        int rc=0;
        double tempd = d1; /* do not change d1, as it only exists on the stack */

/*         fprintf(stderr, "debug: tcob_assign_double 1: d1=%f\n", d1); */
        if (f->type == DTYPE_EDITED)
                f->decimals = tcob_picEditedCompDecimals(f);

        if (opts & 1)
                do_rounding(f, &tempd);
        if (opts & 2)
                rc = tcob_check_size_overflow(f, tempd);

#ifdef DEBUG_MOVE_RTS
        fprintf(stderr, "debug: tcob_assign_double 2: d1=%g, rc=%d\n", tempd, rc);
#endif
        if (rc == 0)
                rc = tcob_dtofld(f,s1,0,tempd); /* no rounding, already done */
/*         tcob_move( &_generic_8float, (char *)&tempd, f, s1 ); */

/*        fprintf(stderr, "debug: tcob_assign_double 3: d1=%f, s1=%s, rc=%d\n", 
                            d1, s1, rc); */

        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_dtofld                                   |
 |  Convert from a double to a string based on the fld_desc,              |
 |  rounding if indicated by round                                        |
 |                                                                        |
\*------------------------------------------------------------------------*/

int  tcob_dtofld( struct fld_desc *f, char *s1, int round, double d1 ) {
        int ndec;
        unsigned int i, len;
        unsigned int sign, rc=0;
        double remainder;
        double fpa;

#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_dtofld 0: d1=%f, rc=%d\n", d1, rc);
#endif

        switch (f->type) {
          case DTYPE_BININT:
                d1 *= exp10[f->decimals];

/*                 fprintf(stderr, "debug: tcob_dtofld 2a: d1=%f, rc=%d\n", d1, rc); */

                if (round != 0)
                        d1 += (d1 > 0.) ? .5 : -.5;

/*                fprintf(stderr, "debug: tcob_dtofld 2b: d1=%f, rc=%d\n", d1, rc); */

                switch (f->len) {
                        case 1: 
                          *((char *)s1) = (int) d1; 
/*                          fprintf(stderr, "debug: tcob_dtofld 2-1: d1=%f, s1=%d\n",
                                    d1, *((char *)s1)); */
                          break;
                        case 2: 
                          *((short int *)s1) = (int) d1; 
/*                          fprintf(stderr, "debug: tcob_dtofld 2-2: d1=%f, s1=%d\n",
                                    d1, *((short int *)s1)); */
                          break;
                        case 4: 
                          *((int *)s1) = (int) d1; 
/*                          fprintf(stderr, "debug: tcob_dtofld 2-4: d1=%f, s1=%d, fi=%d\n",
                                   d1, *((int *)s1), fi); */
                          break;
                        case 8: 
                          *((long long *)s1) = (long long) d1; 
/*                          fprintf(stderr, "debug: tcob_dtofld 2-8: d1=%f, s1=%d\n",
                                    d1, *((long long *)s1)); */
                          break;
                }
                return rc;
          case DTYPE_PACKED:
                len = f->len;
                break;
          case DTYPE_FLOAT:
                switch (f->len) {
                   case 4: 
                     *((float *)s1) = (float) d1; 
/*                      fprintf(stderr, "debug: tcob_dtofld 3: d1=%f, s1=%f\n",
                                        d1, *((float *)s1)); */
                     break;
                   case 8: 
                       *((double *)s1) = d1;
/*                     fprintf(stderr, "debug: tcob_dtofld 4: d1=%f, s1=%f\n",
                                        d1, *((double *)s1)); */
                     break;
                   default:
                     rc = 1; 
                     break;
                }       
/*                fprintf(stderr, "debug: tcob_dtofld 5: d1=%f, rc=%d\n",
                          d1, rc); */
                return rc;
          case DTYPE_EDITED:
                len = tcob_picEditedCompLength(f);
                break;
          default:
                len = f->len;
                break;
        }
/*dump_double("\fAssign: ",&d1);*/
        fpa = d1;
        if (f->type == DTYPE_EDITED)
                ndec = tcob_picEditedCompDecimals(f);
        else
                ndec = (int)f->decimals;
/*        fprintf(stderr, "debug: tcob_dtofld 7a: fpa=%f,dec=%d\n", fpa, ndec); */
        if (fpa<0.) {
                sign = 1;
                fpa = -fpa;
        } else
                sign = 0;

/*         fprintf(stderr, "debug: tcob_dtofld 6: len=%d, ndec=%d, exp10[len-ndec]=%f, fpa=%f\n",
                           len, ndec, exp10[len-ndec], fpa); */

#if 0
           /* Do not remove this code */
           if (fpa>exp10[len-ndec]) {
                   fp_runtime_error(f);
                   rc = 1;
                   return rc;
           }
#endif

        fpa *= exp10[ndec];
        remainder = fpa - (unsigned long) fpa;
        if (f->pscale < 0) {
                fpa /= exp10[abs(f->pscale)];
                remainder /= exp10[abs(f->pscale)];
        }

/* the following line is to fix a truncation error caused by rounding
 * in converting from long to double to long (i.e. 4.5 to 4.49999...).
 */
/*      fprintf(stderr, "debug: tcob_dtofld 6: fpa=%f, round=%d\n", fpa,round); */
        if (remainder >= 0.9999999) fpa += 0.0000001;
/*      if ( (round != 0) || ((unsigned long)(fpa * 10) % 10 > 8) )
                fpa += (fpa > 0.) ? .5 : -.5; */
/*                fprintf(stderr, "debug: tcob_dtofld 7: fpa=%f\n", fpa); */
/*      if (fpa>pow(2.,32.)) {
                printf("\fFP overflow!"); getchar();
                return;
        }
*/

        if (f->type != DTYPE_PACKED) {
           unsigned int mini;
           unsigned long fint;
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
 
           memset (s, '0', len);
           /* digits 10 and up */
           if (fpa>=exp10[9]) {  /* fpa >= 1,000,000,000 */
              fint = (unsigned long) ( fpa/exp10[9] );
              /* subtrai parte alta do numero */
              fpa -= fint * exp10[9];
              /* converte parte alta para string */
              for (i=len-9; (i>0) && (fint!=0); i--) {
                   s[i-1] = (char)(fint % 10) + '0';
                   fint /= 10;
              }
           }
           /* digits 9 and below */
           fint = (unsigned long) fpa;
           mini = (len>9) ? len-9 : 0; 
           for (i=len; (i>mini) && (fint!=0); i--) {
                   s[i-1] = (char)(fint % 10) + '0';
                   fint /= 10;
           }
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
                   tcob_put_sign( f,s1,sign );
        }
/*      fprintf(stderr, "\nString: %20.20s\n", s); */ /* getchar(); */
        if (f->type==DTYPE_PACKED) {
                unsigned long long fpahold = (unsigned long long)fpa;
                unsigned char cDigit, cSign;

                memset (s1, 0, (len/2)+1); /* Initialize s1 array */
                if ((len&1)==0) /* Make sure length is odd */
                        len++;
                /* convert scaled number in fpa to our result */
                for (i=len; (i>0) && (fpahold!=0); i--) {
                        cDigit = fpahold % 10;
                        if ((i%2) == 1)
                                cDigit <<= 4;
                        fpahold /= 10;
                        s1[(i-1)/2] |= cDigit;
                }
                /* attach the sign */
                if (tcob_picElemVal(f->pic,0) == 'S')
                        cSign = (sign) ? 0x0D : 0x0C;
                else
                        cSign = 0x0F;
                s1[len/2] |= cSign;
        }
        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_add_double                               |
 |                          tcob_subtract_double                          |
 |                          tcob_multiply_double                          |
 |                          tcob_divide_double                            |
 |                          tcob_pow_double                               |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_add_double( double *d2, double d1 ) {
        *d2 += d1;
}
void tcob_subtract_double( double *d2, double d1 ) {
        *d2 -= d1;
}
void tcob_multiply_double( double *d2, double d1 ) {
        *d2 *= d1;
}
void tcob_divide_double( double *d2, double d1 ) {
#if 0
        /* check for divide by zero */
        if (d1==0) {
                fprintf(stderr,"*** RUNTIME ERROR: divide by zero\n");
                exit(1);
        }
#endif

        *d2 /= d1;
}
void tcob_pow_double( double *d2, double d1 ) {
        *d2 = pow(*d2,d1);
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_add                                      |
 |                                                                        |
\*------------------------------------------------------------------------*/

int  tcob_add( struct fld_desc *f1, char *s1,
          struct fld_desc *f2, char *s2, int round ) {
        int rc=0;
        double fp1, fp2;

        tcob_fldtod(f1,s1,&fp1);
        tcob_fldtod(f2,s2,&fp2);
        fp1+=fp2;
        rc = tcob_check_size_overflow(f2, fp1);
        if (rc == 0)
                tcob_dtofld(f2,s2,round,fp1);
        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_subtract                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

int  tcob_subtract( struct fld_desc *f1, char *s1,
               struct fld_desc *f2, char *s2, int round ) {
        int rc=0;
        double fp1, fp2;

        tcob_fldtod(f1,s1,&fp1);
        tcob_fldtod(f2,s2,&fp2);
        fp2 -= fp1; 
        rc = tcob_check_size_overflow(f2, fp2);
        if (rc == 0) 
                tcob_dtofld(f2,s2,round,fp2);
        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_multiply                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

int  tcob_multiply( struct fld_desc *f1, char *s1,
               struct fld_desc *f2, char *s2,
               struct fld_desc *f3, char *s3, int round ) {
        int rc=0;
        double fp1, fp2, fp3;

        tcob_fldtod(f1,s1,&fp1);
        tcob_fldtod(f2,s2,&fp2);
        fp3 = fp1*fp2;
        rc = tcob_check_size_overflow(f3, fp3);
        if (rc == 0)
                tcob_dtofld(f3,s3,round,fp3);
        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_divide                                   |
 |                                                                        |
\*------------------------------------------------------------------------*/

int  tcob_divide( struct fld_desc *f1, char *s1,
             struct fld_desc *f2, char *s2,
             struct fld_desc *f3, char *s3, int round ) {
        int rc=0;
        double fp1, fp2, fp3;

        tcob_fldtod(f1,s1,&fp1);
        tcob_fldtod(f2,s2,&fp2);
        if (fp2 == 0)
                rc = 1;
        else {
                fp3=fp1/fp2;
                rc = tcob_check_size_overflow(f3, fp3);
                if (rc == 0)
                        tcob_dtofld(f3,s3,round,fp3);
        }

        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_divide1                                  |
 |  Divide with remainder option                                          |
 |                                                                        |
\*------------------------------------------------------------------------*/

int  tcob_divide1( struct fld_desc *f1, char *s1,
              struct fld_desc *f2, char *s2,
              struct fld_desc *f3, char *s3,
              struct fld_desc *f4, char *s4, int round ) {
        int rc=0;
        double fp1, fp2, fp3, fp4, tfp3;

        tcob_fldtod(f1,s1,&fp1);
        tcob_fldtod(f2,s2,&fp2);
/*      fprintf(stderr, "debug mcmath 1: fp1=%05.5f fp2=%05.5f\n", fp1, fp2); */
        if (fp2 == 0)  { /* divide by zero error */
            rc = 1;
            return rc;
        }
        
        /*  
         * Calculate GIVING  
         */
        fp3 = fp1 / fp2;
/*      fprintf(stderr, "debug mcmath 2: fp3=%05.5f\n", fp3); */
        rc = tcob_check_size_overflow(f3, fp3);
        if (rc != 0)
            return rc;

        tcob_dtofld(f3,s3,round,fp3);

        /* 
         *  Calculate REMAINDER.
         */

        tcob_fldtod(f3,s3,&tfp3);

        fp4 = (fp1 - (tfp3*fp2));
/*      fprintf(stderr, "debug mcmath 3: fp4=%05.5f, tfp3=%05.5f\n", fp4, tfp3); */
        rc = tcob_check_size_overflow(f4, fp4);
        if (rc != 0) {
/*              fprintf(stderr, "debug mcmath 4: check_size_overflow : "
                                "a overflow has occured on fp4=%05.5f\n",
                       fp4); */
                return rc;
        }

/*      fprintf(stderr, "debug mcmath 4: fp1=%05.5f, fp2=%05.5f, fp3=%05.5f, tfp3=%05.5f, fp4=%05.5f, fp4=%05.5f\n", fp1, fp2, fp3, tfp3, fp4, fp4); */
        tcob_dtofld(f4,s4,0,fp4);

        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_check_size_overflow                      |
 |  Check if size will fit in destination field.  0 if yes, 1 if false.   |
 |                                                                        |
\*------------------------------------------------------------------------*/

int  tcob_check_size_overflow( struct fld_desc *f, double d ) {
        unsigned int rc, len;

        if (f->type == DTYPE_EDITED)
                len = tcob_picEditedCompLength(f);
        else
                len = tcob_picCompLength(f) + tc_abs((char)f->pscale); 

#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_check_size_overflow 1: piclen=%d, f->len=%d, f->decimals=%d\n", 
                         len, (int)f->len, f->decimals);
#endif
        if (len < f->decimals) {
           rc = 1;
        } else if ( ((d<0.0)?-d:d) >= exp10[len - f->decimals]) {
           rc = 1;
        } else {
           rc = 0;
        }

#ifdef DEBUG_RTS
        fprintf(stderr, "debug: tcob_check_size_overflow 2: d=%g, rc=%d\n", 
                         d, rc);
#endif
        return rc;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_check_numeric                            |
 |  test if all data in variable conforms to its class (type)             |
 |  0 if true, 1 if false.                                                |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_check_numeric ( struct fld_desc *f, char *s ) {
        unsigned int i, dig=0;
        char c;

        if ((f->type == DTYPE_BININT)
         || (f->type == DTYPE_PACKED)
         || (f->type == DTYPE_FLOAT))
                return 0; /* these types are assumed to always be valid */
        for (i=0;i<f->len;i++) {
                c = s[i];
                /* must have at least one digit */
                if (!dig && (c >= '0') && (c <= '9'))
                        dig++;
                if (i==0 && ((c==' ')||(c=='+')||(c=='-')))
                        continue;
                /* look for a number followed by several spaces (is this valid?) */
                if (c==' ') {
                        for (; i<f->len; i++) {
                                if (s[i]!=' ')
                                        return 1;
                        }
                        break;
                }
        /*
          Omit: NULL picture (bug in refmod's) 
                No picture in group items 
        */
                if ((f->pic != NULL) && (f->type != DTYPE_GROUP)) {
                        /* take care of signed numbers (non separate sign) */
                        if ((i==f->len-1) && (tcob_picElemVal(f->pic,0) == 'S')) {
                                if (strchr("}ABCDEFGHI{JKLMNOPQR",c)!=NULL) {
                                        dig++;
                                        break;
                                }
                        }
                }
                if ((c>'9') || (c<'0'))
                        return 1;
        }
        if (!dig)
                return 1;
        return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_check_alphabetic                         |
 |  Is the string alphabetic?  0 if yes, 1 if no.                         |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_check_alphabetic ( struct fld_desc *f, char *s ) {
        unsigned int i;
        char c;

        for (i=0;i<f->len;i++) {
                c = s[i];
                if (!((c==' ') || ((c>='a') && (c<='z')) || ((c>='A') && (c<='Z'))))
                        return 1;
        }
        return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_check_upper                              |
 |  Is the string in upper case?  0 if yes, 1 if no.                      |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_check_upper ( struct fld_desc *f, char *s ) {
        unsigned int i;
        char c;

        for (i=0;i<f->len;i++) {
                c = s[i];
                if (!((c==' ') || ((c>='A') && (c<='Z'))))
                        return 1;
        }
        return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_check_lower                              |
 |  Is the string in lower case?  0 if yes, 1 if no.                      |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_check_lower ( struct fld_desc *f, char *s ) {
        unsigned int i;
        char c;

        for (i=0;i<f->len;i++) {
                c = s[i];
                if (!((c==' ') || ((c>='a') && (c<='z'))))
                        return 1;
        }
        return 0;
}


/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_check_condition                          |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_check_condition( struct fld_desc *f1, char *s1,... ) {
        struct fld_desc *f2, *f3;
        char *s2, *s3;
        int ret=1;  /* assume wrong */
        va_list args;
        double fp1, fp2, fp3;

        va_start(args,s1);
        f2 = va_arg(args,struct fld_desc *);
        while (f2) {
                s2 = va_arg(args,char *);
                f3 = va_arg(args,struct fld_desc *);
                s3 = va_arg(args,char *);
                
                if (f1->type == DTYPE_DISPLAY || f1->type == DTYPE_BININT) {
                        tcob_fldtod(f1,s1,&fp1);
                        tcob_fldtod(f2,s2,&fp2);
                        tcob_fldtod(f3,s3,&fp3);
                        if ((fp1>=fp2 && fp1<=fp3)) {
                                ret = 0;
                                break;
                        }
                } else {
                        if (tcob_compare(f1, s1, f2, s2) > -1 &&
                            tcob_compare(f1, s1, f3, s3) < 1) {
                            ret = 0;
                            break;
                        }
                }
                f2 = va_arg(args,struct fld_desc *);
        }
        va_end(args);
        return ret;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_compare_doubles                          |
 |  retorna 1 se d1>d2; 0 se d1==d2; -1 se d1<d2                          |
 |  return  1 if d1>d2; 0 if d1==d2; -1 if d1<d2                          |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_compare_doubles (double d1, double d2) {
        if (d1>d2) return 1;
        if (d2>d1) return -1;
        return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          compare_all                                   |
 |  retorna 1 se s1>d2; 0 se s1==s2; -1 se s1<s2                          |
 |  return  1 if s1>s2; 0 if s1==s2; -1 if s1<s2                          |
 |  s1 and s2 must be compared unsigned otherwise High-value compares     |
 |            less than Low-value.                                        |
 |                                                                        |
\*------------------------------------------------------------------------*/

static int compare_all( struct fld_desc *f1, char *s1,
                        struct fld_desc *f2, char *s2 ) {
        unsigned int i, j, k, maxi;
        unsigned char *us1 = (unsigned char *)s1,
                      *us2 = (unsigned char *)s2;
        
        maxi=(f1->len<f2->len)?f1->len:f2->len;  /* min (f1->len, f2->len) */
        j=0; k=0;
        for (i=0;i<maxi;i++) {
                if (us1[j] == us2[k]) continue;
                if (us1[j] >  us2[k]) return 1;
                if (us1[j] <  us2[k]) return -1;
                j++; k++;
                if (f1->all && j >= f1->len) j=0;
                if (f2->all && k >= f2->len) k=0;
        }
        
        if (f1->len>f2->len)
                while (j<f1->len) {
                        if (us1[j++]!=us2[k++]) return 1;
                        if (k >= f2->len) k=0;
                }
        else
                while (k<f2->len) {
                        if (us2[k++]!=us1[j++]) return -1;
                        if (j >= f1->len) j=0;
                }
        return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_compare                                  |
 |  retorna 1 se s1>s2; 0 se s1==s2; -1 se s1<s2                          |
 |  return  1 if s1>s2; 0 if s1==s2; -1 if s1<s2                          |
 |  s1 and s2 must be declared unsigned otherwise High-value compares     |
 |            less than Low-value.                                        |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_compare( struct fld_desc *f1, char *s1,
                  struct fld_desc *f2, char *s2 ) {
        unsigned int i, maxi;
        double fp1, fp2;
        char c1, c2;
        unsigned char *us1 = (unsigned char *)s1,
                      *us2 = (unsigned char *)s2;

   if ((f1->type==DTYPE_ALPHANUMERIC || f1->type==DTYPE_GROUP) &&
       (f2->type==DTYPE_ALPHANUMERIC || f2->type==DTYPE_GROUP)) {  /* compare strings */
        if (f1->all || f2->all)
                return (compare_all(f1,s1,f2,s2));
        maxi=(f1->len<f2->len)?f1->len:f2->len;  /* min (f1->len, f2->len) */
        for (i=0;i<maxi;i++) {
                if (us1[i] == us2[i]) continue;
                if (us1[i] >  us2[i]) return 1;
                if (us1[i] <  us2[i]) return -1;
        }
        if (f1->len>f2->len)
                for (; i<f1->len; i++) {
                        if (us1[i]!=' ') return 1;
                }
        else
                for (; i<f2->len; i++) {
                        if (us2[i]!=' ') return -1;
                }
   } else if ((f1->type!=DTYPE_DISPLAY
            && f1->type!=DTYPE_PACKED
            && f1->type!=DTYPE_BININT)
           || (f2->type!=DTYPE_DISPLAY
            && f2->type!=DTYPE_PACKED
            && f2->type!=DTYPE_BININT)) {  /* compare strings */
        if (f1->all || f2->all)
                return (compare_all(f1,s1,f2,s2));
        maxi=(f1->len<f2->len)?f1->len:f2->len;  /* min (f1->len, f2->len) */
        for (i=0;i<maxi;i++) {
                if (us1[i] == us2[i]) continue;
                c1 = s1[i]; c2 = s2[i];
                /* ignore the signs if any */
                if (f1->type == DTYPE_DISPLAY && tcob_picElemVal(f1->pic,0) == 'S') {
                        c1 = (char)tcob_char_to_sign(c1);
                        c1 = c1 < 0 ? (c1 * -1) + '0': c1 + '0';
                }
                if (f2->type == DTYPE_DISPLAY && tcob_picElemVal(f2->pic,0) == 'S') {
                        c2 = (char)tcob_char_to_sign(c2);
                        c2 = c2 < 0 ? (c2 * -1) + '0': c2 + '0';
                }
                if (c1 == c2) continue;
                if (c1 > c2) return 1;
                if (c1 < c2) return -1;
        }
        if (f1->len>f2->len)
                for (; i<f1->len; i++) {
                        if (us1[i]!=' ') return 1;
                }
        else
                for (; i<f2->len; i++) {
                        if (us2[i]!=' ') return -1;
                }
    } else {
        tcob_fldtod(f1,s1,&fp1);
        tcob_fldtod(f2,s2,&fp2);
        if (fp1>fp2) return 1;
        if (fp2>fp1) return -1;
    }
    return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_assign_int                               |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_assign_int( struct fld_desc *desc, char *val, int value ) {
        tcob_move( &_generic_4binary, (char *)&value, desc, val );
}

/* end of MCMATH.C */

