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
 * TinyCOBOL Run Time Library -- Picture clauses functions
 *

*/

/* #define DEBUG_RTS 0 */
/* #define DEBUG_PIC_RTS 1 */

/*---------------------------------------------------------------------------*\
 |                                                                           |
 |  COBOL Compiler Run Time Library -- Pictures                              |
 |    See each function's comments for more detail.                          |
 |  Independent of compressed PIC implementation:                            |
 |    tcob_picExpand() - Returns an expanded version of the PIC string       |
 |    tcob_picCompLength() - Numeric character count                         |
 |    tcob_picEditedCompLength() - Numeric-edited character count            |
 |    tcob_picEditedCompDecimals() - Decimal numeric-edited characters count |
 |  Dependent on compressed PIC implementation:                              |
 |    tcob_picElemVal() - Retrieve character value from a specified element  |
 |    tcob_picElemLen() - Retrieve character count from a specified element  |
 |    tcob_picReqLen() - Determine size to allocate for a new compressed PIC |
 |    tcob_picCreate() - Start a new compressed PIC string                   |
 |    tcob_picAppend() - Continue a compressed PIC string                    |
 |                                                                           |
\*---------------------------------------------------------------------------*/

#include "htcoblib.h"
#include "screenio.h"

//extern int bDecimalComma;

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_picExpand                                |
 |  expand a picture returning a malloc'ed string                         |
 |  from: "XAYBZC" (where X, Y, Z are picture characters and              |
 |                  A, B, C are binary counts for each character)         |
 |    to: "XXXXYYYZZZZZ"                                                  |
 |                                                                        |
\*------------------------------------------------------------------------*/

char * tcob_picExpand( struct fld_desc *f ) {
	char            *result, c;
	unsigned int    i, t, tot;

	for (i=0, tot=0; tcob_picElemVal(f->pic,i); i++)
		tot += tcob_picElemLen(f->pic,i);
	result = malloc(tot+1);
	for (i=0, tot=0; (c=tcob_picElemVal(f->pic,i)); i++) {
		t = tcob_picElemLen(f->pic,i);
		memset (&result[tot], c, t);
		tot += t;
	}
	result[tot] = '\0';
/*
#ifdef PICTURE_TESTING
	printf("tcob_picexpand: %s\n", result);
	free(result);
	return NULL;
#else
	return result;
#endif
*/
	return result;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_picCompLength                            |
 |  For numeric types, determine the total number of stored digits.       |
 |  Includes 9's.                                                         |
 |                                                                        |
\*------------------------------------------------------------------------*/

unsigned int tcob_picCompLength( struct fld_desc *f ) {
	unsigned int  len=0, i;
	char c;
	
	for (i=0; (c=tcob_picElemVal(f->pic,i)); i++) {
		if (c == '9')
			len += tcob_picElemLen(f->pic,i);
	}
	return len;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_picEditedCompLength                      |
 |  For the numeric-edited type, determine the total number of digits     |
 |  available.  Includes 9's, Z's,*'s, and multiples of +, -, and the     |
 |  currency sign.                                                        |
 |                                                                        |
\*------------------------------------------------------------------------*/

unsigned int tcob_picEditedCompLength( struct fld_desc *f ) {
	unsigned int  len=0, i;
	unsigned int bSeenPlus=0, bSeenMinus=0, bSeenCurrency=0;
	char c;
//	extern char cCurrencySymbol;

	for (i=0; (c=tcob_picElemVal(f->pic,i)); i++) {
		unsigned int ilen = tcob_picElemLen(f->pic,i);
		if (c == '9' || c == 'Z' || c == '*' ||
		    (bSeenPlus && (c == '+')) ||
		    (bSeenMinus && (c == '-')) ||
		    (bSeenCurrency && (c == cCurrencySymbol)) )
			len += ilen;
		
		if (!bSeenPlus && (c == '+')) {
			bSeenPlus = 1;
			len += ilen - 1;
		} else if (!bSeenMinus && (c == '-')) {
			bSeenMinus = 1;
			len += ilen - 1;
		} else if (!bSeenCurrency && (c == cCurrencySymbol)) {
			bSeenCurrency = 1;
			len += ilen - 1;
		}
	}
	return len;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                         tcob_picTotalLen                               |
 |                                                                        |
\*------------------------------------------------------------------------*/

unsigned int tcob_picTotalLen( char *pic ) {
	int  len=0;
	while (*pic) {
		len += *(pic+1);
		pic+=2;
	}
	return len;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_picSignPosition                          |
 |  For the numeric- type, determine the position of the sign             |
 |                                                                        |
\*------------------------------------------------------------------------*/

unsigned int tcob_picSignPosition( struct fld_desc *f ) {
	unsigned int  len=0, i;
	char c;
	int d = TCOB_DISPLAYFIELD(f->type);

	for (i=0; (c=tcob_picElemVal(f->pic,i)); i++) {
		unsigned int ilen = tcob_picElemLen(f->pic,i);
		len += ilen;
                		if ((c == '+' || c == '-') || (c == 'S' && d && i == 0)) {
			len -= ilen;
			return len;
		}
	}
	return -1;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_picDecimalPointPosition                  |
 |  For the numeric- type, determine the position of the decimal point    |
 |                                                                        |
\*------------------------------------------------------------------------*/

unsigned int tcob_picDecimalPointPosition( struct fld_desc *f ) {
	unsigned int  len=0, i;
//	extern int bDecimalComma;

	char c, cDecimal = (bDecimalComma) ? ',' : '.';

	for (i=0; (c=tcob_picElemVal(f->pic,i)); i++) {
		unsigned int ilen = tcob_picElemLen(f->pic,i);
			len += ilen;
		if (c == cDecimal) {
			len -= ilen;
			return len;
		}
	}
	return -1;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_picEditedCompDecimals                    |
 |  For the numeric-edited type, determine the total number of digits     |
 |  available after the decimal point.  Includes 9's, Z's,*'s, and        |
 |  multiples of +, -, and the currency sign.                             |
 |                                                                        |
\*------------------------------------------------------------------------*/

unsigned int tcob_picEditedCompDecimals( struct fld_desc *f ) {
	unsigned int  len=0, i;
	int bSeenDecimal=0, bSeenPlus=0, bSeenMinus=0, bSeenCurrency=0;
//	extern int bDecimalComma;
//	extern char cCurrencySymbol;
	char c, cDecimal = (bDecimalComma) ? ',' : '.';

	for (i=0; (c=tcob_picElemVal(f->pic,i)); i++) {
		unsigned int ilen = tcob_picElemLen(f->pic,i);
		if (bSeenDecimal &&  // Must find the decimal point first
		    (c == '9' || c == 'Z' || c == '*' ||
		    (bSeenPlus && (c == '+')) ||
		    (bSeenMinus && (c == '-')) ||
		    (bSeenCurrency && (c == cCurrencySymbol)) ) )
			len += ilen;
		if (!bSeenDecimal && (c == cDecimal)) {
			bSeenDecimal = 1;
		} else if (!bSeenPlus && (c == '+')) {
			bSeenPlus = 1;
			if (bSeenDecimal)
				len += ilen - 1;
		} else if (!bSeenMinus && (c == '-')) {
			bSeenMinus = 1;
			if (bSeenDecimal)
				len += ilen - 1;
		} else if (!bSeenCurrency && (c == cCurrencySymbol)) {
			bSeenCurrency = 1;
			if (bSeenDecimal)
				len += ilen - 1;
		}
	}
	return len;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                   tcob_picElemLen & tcob_picElemVal                    |
 |  Determine the length or value of element i in array p.                |
 |  Each element is composed of an 8-bit character and an 8-bit length.   |
 |                                                                        |
\*------------------------------------------------------------------------*/

unsigned int tcob_picElemLen(char *p, unsigned int i) {
	return ( (unsigned int)(((unsigned short *)p)[i] >> 8) );
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                         tcob_picElemVal                                |
 |                                                                        |
\*------------------------------------------------------------------------*/
char tcob_picElemVal(char *p, unsigned int i) {
	return ( ((unsigned short *)p)[i] & 0x0ff );
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                           tcob_picReqLen                               |
 |  Determine number of bytes to request for holding a compressed PIC     |
 |  string of i elements.                                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

unsigned int tcob_picReqLen(unsigned int i) {
	/* Currently using a 1-byte value and a 1-byte length for each
	 * element, plus a 1-byte NULL to indicate the end */
	return ((i*2)+1);
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                           tcob_picCreate                               |
 |  Create a new PIC string and place in p.                               |
 |                                                                        |
\*------------------------------------------------------------------------*/

char *tcob_picCreate(char *p, unsigned int len, ...) {
	char pc;
	unsigned int i=0, ilen;
	va_list args;

	va_start(args, len);
	while ((pc=va_arg(args,int))) {
		for (ilen=va_arg(args, int); ilen>255; ilen-=255) {
			if (i+1>=len)
				break;
			p[i] = pc;
			p[i+1] = 255;
			ilen -= 255;
			i += 2;
		}
		if (i+1>=len)
			break;
		p[i] = pc;
		p[i+1] = ilen;
		i += 2;
	}
	if (i<len)
		p[i] = '\0';
	  else if (i>1)
		p[i-2] = '\0';
	  else if (len==1)
		p[0] = '\0';
	va_end(args);
	return p;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                           tcob_picAppend                               |
 |  Continue the PIC string found in p.                                   |
 |                                                                        |
\*------------------------------------------------------------------------*/

char *tcob_picAppend(char *p, unsigned int len, ...) {
	char pc;
	unsigned int i, ilen;
	va_list args;
	
	for (i=0; p[i]; i+=2) ;

	va_start(args, len);
	while ((pc=va_arg(args,int))) {
		for (ilen=va_arg(args, int); ilen>255; ilen-=255) {
			if (i+1>=len)
				break;
			p[i] = pc;
			p[i+1] = 255;
			ilen -= 255;
			i += 2;
		}
		if (i+1>=len)
			break;
		p[i] = pc;
		p[i+1] = ilen;
		i += 2;
	}
	if (i<len)
		p[i] = '\0';
	  else if (i>1)
		p[i-2] = '\0';
	  else if (len==1)
		p[0] = '\0';
	va_end(args);
	return p;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                           tcob_picChangeChar                           |
 |  change the PIC string char in p.                                      |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_picChangeChar(char *p, int i, char c) {
 p[i*2]= c;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                            tcob_classifyPic                            |
 | Classify picture type - compressed pic pointer to picture type         |
 |                                                                        |
\*------------------------------------------------------------------------*/

char tcob_classifyPic( char *p ) {
	int i;
	char type=0;
	
	for (i=0; p[i]; i+=2) {
		switch (p[i]) {
		case 'A':
				if ((type != DTYPE_ALPHANUMERIC && type != DTYPE_EDITED)
					|| !type)
						type = DTYPE_ALPHA;
				break;
		case 'X':
				if (type == DTYPE_DISPLAY || !type)
					type = DTYPE_ALPHANUMERIC;
				break;
		case 'Z':
				type=DTYPE_EDITED;
				break;
		case '9':
				if (!type)
					type=DTYPE_DISPLAY;
				break;
		case 'V':
		case 'P':
		case 'S':
				break;
		case '.':
		case ',':
		case '0':
		case 'B':
		case '/':
		case '+':
		case '-':
		case '*':
		case 'C':
		case 'R':
		case 'D':
				type=DTYPE_EDITED;
				break;
		}
	}
	return type;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                           tcob_isNumEdit                               |
 | Determine if a picture is a numeric-edited field (true) or             |
 | alphanumeric-edited (false)                                            |
 |                                                                        |
 | Standard: ISO/IEC 1989:2001 (pp.323-324)                               |
 | 13.16.38.3 General Rules                                               |
 | FORMAT 1                                                               |
 | 7) To define an item as alphanumeric-edited, character-string-1        |
 |    shall include:                                                      |
 |    - at least one symbol 'A' or 'X', and                               |
 |    - at least one of the symbols from the set 'B', '0', '/'.           |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_isNumEdit(char *p) {
	char cDecimalChar = '.';
	int i,dsep=0;
	int axfound=0;
	int bzslfound=0;

	if (bDecimalComma)
           cDecimalChar = ',';
	
	for (i=0; p[i]; i+=2) {
		switch (p[i]) {
		/* the standard says we must find one of those below, at least,
		   but for dates (pic 99/99/999) which is visibly not
		   numeric-edited, there is none 'A' or 'X'. So let's not 
		   require this until someone explains me what to do here. */
		case 'A':
		case 'X':
			axfound=1;
			break;
		/* don't count a 'B' after 'D' (DB) */
		case 'D':
			if (p[i+1]==1 && p[i+2]=='B' && p[i+3]==1) {
                           i+=2;
                           continue;
			}
		case '.':
		case ',':
			if (p[i] == cDecimalChar) {
			   /* if (dsep++) { // This code does NOT work properly */
			   if (dsep > 0) {
                               return 0;
                           }
                           /* This code does NOT work properly 
                           // make sure there are no repetitions here 
                           //if (tcob_picElemLen(p, i) > 1) { */
#ifdef DEBUG_PIC_RTS
                           fprintf(stderr, "Debug: tcob_isNumEdit p[%d]=%c, p[i+1]=%d\n", i, p[i], p[i+1]);
                           //fprintf(stderr, "Debug: tcob_isNumEdit p[%d]=%c(%d)\n", i, tcob_picElemVal(p, i), tcob_picElemLen(p, i));
#endif
                           if (p[i+1] > 1) {
                              return 0;
			   } 
			   dsep++;
			}
			continue;
		case 'B':
		case '0':
		case '/':
			bzslfound=1;
			break;
		}
	}
	if (bzslfound && axfound)
		return 0;
	else
		return 1;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_isNumeric                                |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_isNumeric(char *p) {
	int i;

	for (i=0; p[i]; i+=2) {
		switch (p[i]) {
		case '9': 
			continue;
		case 'V': 
			continue;
		default:
			return 0;
		}
	}
	return 1;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                           tcob_isZNum                                  |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_isZNum(char *p) {
	int i;

	for (i=0; p[i]; i+=2) {
		switch (p[i]) {
		case '-':
		case ',':
		case '.':
		case '9': 
		case 'Z': 
			continue;
		default:
			return 0;
		}
	}
	return 1;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                           tcob_isAlpha                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_isAlpha(char *p) {
	int i;

	for (i=0; p[i]; i+=2) {
		switch (p[i]) {
		case 'A': 
		case 'X': 
			return 1;
		}
	}
	return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                           tcob_hasZ                                    |
 |  Check if the picture has any pic Z string                             |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_hasZ(char *p) {
	int i;
	for (i=0; p[i]; i+=2) {
		switch (p[i]) {
		case 'Z':
			return 1;
		}
	}
	return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                         tcob_picCharLen                                |
 |  Determine number of significative characters (Z,X,A,9,*) there        |
 |  are in the picture                                                    |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_picCharLen( unsigned char *pic ) {
	int n=0;
	while (*pic) {
		if (strchr("9ZXA*",*pic)) {
			n+=*(pic+1);
		}
		pic += 2;
	}
	return n;
}
