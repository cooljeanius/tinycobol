/* 
 * Copyright (C) 2001, 2000, 1999,  Rildo Pragana 
 *               
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
 * TinyCOBOL Run Time Library -- Strings Module
 * 

*/

#include "htcoblib.h"

// #if defined(__MINGW32__)
// #include <windows.h>
// #endif

#if defined(SunOS)
va_list __builtin_va_alist;
#endif

static unsigned int offset_substr( char *s1, char *s2,
	unsigned int n1, unsigned int n2 );
void tcob_put_integer( struct fld_desc *fdesc, char *sbuf, int value );
static struct comparand * alloc_comparand( int opt, struct comparand **list );
static void free_comparands( struct comparand *cmps );

extern struct fld_desc _generic_4binary;

/*
 * auxiliary comparands list to walk several times through comparands
 * in cob_inspect_replacing function.
 */
struct comparand {
	struct comparand *next;
	int opt;
	struct fld_desc *ffor,*fby,*fcnt;
	char            *sfor,*sby,*scnt;
	unsigned int before, after;
	unsigned int cnt;
	int state; /* -1 -> not yet (only if "after" found), 
	          0 -> go, 1 -> stop */
};
#define COMP_STATE_WAIT  -1
#define COMP_STATE_GO     0
#define COMP_STATE_STOP   1


/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          alloc_comparand                               |
 |                                                                        |
\*------------------------------------------------------------------------*/

static struct comparand * alloc_comparand( int opt, struct comparand **list ) {
	struct comparand *anew, *tmp;
	anew = (struct comparand *)malloc(sizeof(struct comparand));
	memset(anew, 0, sizeof(*anew));
	anew->opt = opt;
	if ((tmp=*list)) {
		for (; tmp->next; tmp=tmp->next) ;
		tmp->next = anew;
	} else 
		*list = anew;
	return anew;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          free_comparands                               |
 |                                                                        |
\*------------------------------------------------------------------------*/

static void free_comparands( struct comparand *cmps ) {
	struct comparand *tmp;
	while (cmps) {
		tmp = cmps;
		cmps = cmps->next;
		free(tmp);
	}
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_inspect_converting                       |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_inspect_converting( struct fld_desc *fvar, char *svar, 
	struct fld_desc *ffrom, char *sfrom, 
	struct fld_desc *fto, char *sto, ...) {

	struct fld_desc *fbef, *faft;
	char *sbef, *saft;
	va_list args;

	unsigned int len=fvar->len, blen=0, alen=0;
	unsigned int idxBef, idxAft, i, j;
	
	/* receive optional before/after variables */
	va_start(args,sto);
	if ((fbef = va_arg(args,struct fld_desc *))) {
		sbef = va_arg(args,char *);
		blen = fbef->len;
	}
	if ((faft = va_arg(args,struct fld_desc *))) {
		saft = va_arg(args,char *);
		alen = faft->len;
	}
	va_end(args);

	/* the next two calls expect offset_substr to *
	 *   return length 1 if string 2 not found.   */
	/* find BEFORE */
	idxBef = offset_substr(svar, sbef, len, blen);
	/* find AFTER */
	idxAft = offset_substr(svar, saft, len, alen);

        /* perform CONVERTING */
	for (i=((faft)?(idxAft+alen):0); i<idxBef; i++) {
		for (j=0; j<ffrom->len; j++) {
			if (svar[i] == sfrom[j]) {
				svar[i] = sto[j];
				break;
			}
		}
	}
	
	return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_inspect_tallying                         |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_inspect_tallying( struct fld_desc *fvar, char *svar, ... ) {
	struct fld_desc *fcnt;
	struct comparand *cmp, *comparands;
	char *scnt=NULL;
	int opt; 
	unsigned int len, rsize, offset;
	va_list args;

	va_start(args,svar);
	comparands = NULL;
	while ((fcnt = va_arg(args,struct fld_desc *))) {
		scnt = va_arg(args,char *);
		while ((opt = va_arg(args,int))) {
			struct fld_desc *fbefore, *fafter;
			char *sbefore, *safter;

			cmp = alloc_comparand( opt,&comparands );
			cmp->fcnt = fcnt;  /* Associate the tally identifier */
			cmp->scnt = scnt;
			cmp->cnt = 0;
			if (opt != INSPECT_CHARACTERS) {
				if ((cmp->ffor = va_arg(args,struct fld_desc *))) {
					cmp->sfor = va_arg(args,char *);
				}
			}
			if ((fbefore = va_arg(args,struct fld_desc *))) {
				sbefore = va_arg(args,char *);
				cmp->before = offset_substr(svar, sbefore,
					fvar->len, fbefore->len);
			} else {
				cmp->before = fvar->len;
			}
			if ((fafter = va_arg(args,struct fld_desc *))) {
				safter = va_arg(args,char *);
				cmp->after = offset_substr(svar, safter,
					fvar->len, fafter->len) + fafter->len;
				cmp->state = COMP_STATE_WAIT;
			}
		}
	}	
	va_end(args);

	len = fvar->len;
	/* do the actual processing */
	for (offset=0; offset<len; offset+=rsize) {
		rsize = 1;
		for (cmp=comparands; cmp; cmp=cmp->next) {
			if (cmp->state == COMP_STATE_STOP)
				continue;
			if (cmp->state == COMP_STATE_WAIT) {
				if (offset >= cmp->after)
					cmp->state = COMP_STATE_GO;
				else
					continue;
			}
			if (cmp->opt == INSPECT_CHARACTERS) {
				if (offset < cmp->before) {
					cmp->cnt ++;
					break;
				} else {
					cmp->state = COMP_STATE_STOP;
					continue;
				}
			}
			if (offset + cmp->ffor->len > cmp->before) {
				cmp->state = COMP_STATE_STOP;
				continue;
			}
			if (memcmp(svar+offset, cmp->sfor,
			           cmp->ffor->len) == 0) {
				cmp->cnt ++;
				rsize = cmp->ffor->len;
				if (cmp->opt == INSPECT_FIRST)
					cmp->state = COMP_STATE_STOP;
				break;
			}
		       	if (cmp->opt == INSPECT_LEADING) {
				cmp->state = COMP_STATE_STOP;
				continue;
			}
		}
	}

	/* Add the counters to their associated identifiers */
	for (cmp=comparands; cmp; cmp=cmp->next) {
		if (cmp->cnt > 0) {
			tcob_put_integer( cmp->fcnt, cmp->scnt,
				tcob_get_index( cmp->fcnt, cmp->scnt ) + cmp->cnt );
		}
	}

	free_comparands (comparands);
	return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_inspect_replacing                        |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_inspect_replacing( struct fld_desc *fvar, char *svar, ... ) {
	struct comparand *cmp, *comparands;
	int opt;
	unsigned int exist_trailing=0, exist_leading=0; 
	unsigned int rsize, offset;
	va_list args;

	/* Set up comparand list */
	va_start(args,svar);
	comparands = NULL;
	while ((opt = va_arg(args,int))) {
		struct fld_desc *fbefore, *fafter;
		char *sbefore, *safter;

		cmp = alloc_comparand( opt,&comparands );
		if (opt != INSPECT_CHARACTERS) {
			if ((cmp->ffor = va_arg(args,struct fld_desc *))) {
				cmp->sfor = va_arg(args,char *);
			}
		}
		if ((cmp->fby = va_arg(args,struct fld_desc *))) {
			cmp->sby = va_arg(args,char *);
		}
		if ((fbefore = va_arg(args,struct fld_desc *))) {
			sbefore = va_arg(args,char *);
			cmp->before = offset_substr(svar, sbefore,
				fvar->len, fbefore->len);
		} else {
			cmp->before = fvar->len;
		}
		if ((fafter = va_arg(args,struct fld_desc *))) {
			safter = va_arg(args,char *);
			cmp->after = offset_substr(svar, safter,
				fvar->len, fafter->len) + fafter->len;
			cmp->state = COMP_STATE_WAIT;
		}

		if (cmp->opt == INSPECT_TRAILING){
                    exist_trailing = 1;
		} else {
	            exist_leading = 1;
		}
	}
	va_end(args);

	/* Process forward from 0 to fvar->len */
	if (exist_leading) {
		for (offset=0; offset<fvar->len; offset+=rsize) {
			rsize = 1;
			for (cmp=comparands; cmp; cmp=cmp->next) {
				/* We take care of later in the code */
				if (cmp->opt == INSPECT_TRAILING)
					continue;
				/* The comparand is no longer being matched */
				if (cmp->state == COMP_STATE_STOP)
					continue;
				/* See if we can use the comparand yet */
				if (cmp->state == COMP_STATE_WAIT) {
					if (offset >= cmp->after)
						cmp->state = COMP_STATE_GO;
					else
						continue;
				}
				/* REPLACING CHARACTERS BY ... */
				if (cmp->opt == INSPECT_CHARACTERS) {
				    	if (offset < cmp->before) {
						svar[offset] = *(cmp->sby);
						break;
					} else {
						cmp->state = COMP_STATE_STOP;
						continue;
					}
				}
				/* See if we can no longer use the comparand */
				if (offset + cmp->ffor->len > cmp->before) {
					cmp->state = COMP_STATE_STOP;
					continue;
				}
				/* See if we have a match */
				if (memcmp(svar+offset, cmp->sfor,
				           cmp->ffor->len) == 0) {
					memcpy(svar+offset, cmp->sby,
					       cmp->ffor->len);
					rsize = cmp->ffor->len;
					/* If REPLACING FIRST, do not match
					 * the comparand again */
					if (cmp->opt == INSPECT_FIRST)
						cmp->state = COMP_STATE_STOP;
					break;
				}
				/* REPLACING LEADING cannot match after a
				 * non-match is encountered */
				if (cmp->opt == INSPECT_LEADING) {
					cmp->state = COMP_STATE_STOP;
					continue;
				}
			} /* for comparands */
		} /* for offset */
	} /* of exist_leading */

	/* Process backwards from fvar->len to 0
	 * no support for AFTER or BEFORE in this case */
	if (exist_trailing) {
		for (offset=fvar->len; ; offset-=rsize) {
			rsize = 1;
			for (cmp=comparands; cmp; cmp=cmp->next) {
				if (cmp->opt != INSPECT_TRAILING)
					continue;
				if (cmp->state == COMP_STATE_GO) {
					unsigned int len = cmp->ffor->len;
					if ((offset >= len) && (memcmp(svar + offset - len,
							cmp->sfor, len) == 0)) {
						memcpy(svar + offset - len, cmp->sby, len);
						rsize = len;
					} else {
						cmp->state = COMP_STATE_STOP;
					}
				}
			} /* for comparands */
			if (rsize >= offset)
				break;
		} /* for offset */
	}
	free_comparands (comparands);
	return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_unstring                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_unstring( struct fld_desc *fvar, char *svar, ... ) {
	unsigned int picLen;
	struct fld_desc fsrc = {0,DTYPE_ALPHANUMERIC,0,0,0,0,0,0,0,0,NULL};
	struct fld_desc *fptr, *ftally;
	char *sptr=NULL, *stally=NULL;
	struct fld_desc **p;
	struct fld_desc *fdest, *fdltr, *fcnt;
	char *sdelim, *sdest, *sdltr=NULL, *scnt=NULL;
	char *delimbuf;
	int partlen, delimall, nfields;
	unsigned int i, n, n1, len, delimlen;
	va_list args;

	/* receive POINTER and TALLYING arguments */
	va_start(args,svar);
	if ((fptr = va_arg(args,struct fld_desc *))) {
		sptr = va_arg(args,char *);
	}
	if ((ftally = va_arg(args,struct fld_desc *))) {
		stally = va_arg(args,char *);
	}

	/* setup indirect pointer to the start of delimiters array */
	len = 16;
	p = malloc (sizeof (struct fld_desc) * len);
	p[0] = va_arg (args, struct fld_desc *);
	for (i=0; p[i]; ) {
		if (i + 3 >= len) {
			len *= 2;
			p = realloc (p, sizeof (struct fld_desc) * len);
		}
		p[i+1] = va_arg (args, struct fld_desc *);
		p[i+2] = va_arg (args, struct fld_desc *);
		if (p[i]->len != 0) /* Remove zero-length delimiters */
			i+=3;
		p[i] = va_arg (args, struct fld_desc *);
	}

	/* now execute the actual unstring command */
	len = fvar->len;
	if (fptr) { /* if there is a pointer, skip some length at svar */
		int tempn = tcob_get_index(fptr,sptr)-1; /* get value of pointer */
		if ((tempn >= (int)len) || (tempn < 0)) {
        		free (p);
        		va_end (args);
        		return 1;
		}
		n = (unsigned int)tempn;
	} else
		n = 0;
	nfields = 0;
	for (fdest = va_arg(args, struct fld_desc *); (fdest) && (n<len);
	     fdest = va_arg(args, struct fld_desc *)) {
		sdest = va_arg(args, char *);
		if ((fdltr = va_arg(args, struct fld_desc *)))
			sdltr = va_arg(args, char *);
		if ((fcnt = va_arg(args, struct fld_desc *)))
			scnt = va_arg(args, char *);

		/* find the nearest delimiter */
		delimall = 0;
		delimlen = 0;
		delimbuf = NULL;
		partlen = len-n;
		if ((!p[0]) && (partlen>(int)(fdest->len)))
			partlen = fdest->len;
		for (i=0; (p[i]) && (partlen>0); i+=3) {
			sdelim = (char *)(p[i+1]);
			n1 = offset_substr(svar+n,sdelim,len-n,p[i]->len);
			if ((int)n1 < partlen) {
				partlen	= n1;
				delimlen = p[i]->len;
				delimbuf = sdelim;
				delimall = (int)(p[i+2]);
			}
		}

		/* move sub-string INTO dest */
		fsrc.len = partlen;
		picLen = tcob_picReqLen(1);
		fsrc.pic = (char *)malloc(picLen);
		tcob_picCreate (fsrc.pic, picLen, 'X', fsrc.len, NULL);
		tcob_move (&fsrc, svar+n, fdest, sdest);
		free(fsrc.pic);
		n += partlen;  /* adjust for the partial string processed */
		if (delimbuf)  /* adjust for delimiter too */
			n += delimlen;
		/* set DELIMITER IN if storage requested */
		if (fdltr) {
			fsrc.len = delimlen;
			picLen = tcob_picReqLen(1);
			fsrc.pic = (char *)malloc(picLen);
			tcob_picCreate (fsrc.pic, picLen, 'X', fsrc.len, NULL);
			tcob_move(&fsrc, delimbuf, fdltr, sdltr);
			free(fsrc.pic);
		}
		/* set COUNT IN if count requested */
		if (fcnt)
			tcob_put_integer(fcnt,scnt,partlen);
		/* remove all copies of delimiter */	
		if (delimall) { 
			while ((n<len) && !offset_substr(svar+n,delimbuf,
							len-n,delimlen))
				n += delimlen;
		}
		nfields++;
	}
	va_end (args);
	free (p);

	if (ftally) {
		tcob_put_integer( ftally, stally, nfields + 
			tcob_get_index( ftally, stally ) );
	}
	if (fptr)
		tcob_put_integer( fptr, sptr, n+1 );
	/* check if overflow found */
	if (n<len) {
		return 1;
	}

	return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_stringcmd                                |
 |  COBOL STRING statement.                                               |
 |  The variables, in order, are:                                         |
 |     receiving var (INTO),                                              |
 |     pointer (WITH POINTER clause) or NULL,                             |
 |     1st sending var, 1st delimiter or NULL,                            |
 |     2nd sending var, 2nd delimiter or NULL, ...                        |
 |  Each variable has its field descriptor (struct fld_desc) and its      |
 |  buffer, except if it's non-existent. In such case, only a NULL is     |
 |  passed as argument and must be skipped. (never 2 stack positions)     |
 |  The last sending variable is a NULL.                                  |
 |                                                                        | 
 |  This function returns 1 in case of overflow found, or 0 if ok.       |
 |                                                                        |
\*------------------------------------------------------------------------*/

int tcob_stringcmd( struct fld_desc *fdst, char *sdst,... ) {
	struct fld_desc *fptr, *fsrc, *fdelim;
	char *sptr, *ssrc, *sdelim=NULL;
	unsigned int srclen, dstlen, n;
	va_list args;

	dstlen = fdst->len;
	va_start(args,sdst);
	fptr = va_arg(args,struct fld_desc *);
	if (fptr) {
		sptr = va_arg(args,char *);
		n = tcob_get_index(fptr,sptr)-1; /* get index value */
	} else
		n = 0;
	if (n >= dstlen) { /* Instant OVERFLOW */
		va_end(args);
		return 1;
	}

	for (fsrc = va_arg(args,struct fld_desc *); (fsrc) && (n<dstlen);
	     fsrc = va_arg(args,struct fld_desc *)) {
		ssrc = va_arg(args,char *);
		srclen = fsrc->len;
		if ((fdelim = va_arg(args,struct fld_desc *))) { /* get delimiter's buffer */
			sdelim = va_arg(args,char *);
			srclen = offset_substr(ssrc,sdelim,srclen,fdelim->len);
		}
		memmove(sdst+n, ssrc, (n+srclen>dstlen)?dstlen-n:srclen);
		n += srclen;
	}
	va_end(args);
	if (fptr)
		tcob_put_integer( fptr, sptr, tc_min(n,dstlen)+1 );
	if ((n>dstlen) || (fsrc)) /* OVERFLOW */
		return 1;
	return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          offset_substr                                 |
 |  return number of characters before found s2 in s1                     |
 |  Note that C string functions are not useful here, because             |
 |    the strings are _not_ NULL-terminated.                              |
 |  I would like to see a better algorithm here, but this                 |
 |    "brute-force" method is easier to code now.                         |
 |  return n1 on string s2 not found                                      |
 |                                                                        |
\*------------------------------------------------------------------------*/

static unsigned int offset_substr( char *s1, char *s2,
		unsigned int n1, unsigned int n2 ) {
	unsigned int i,j;
	if ((n2>n1) || (n2==0))
		return n1;
	for (i=0;i<=n1-n2;i++) {
		for (j=0;j<n2;j++) {
			if (s1[i+j]!=s2[j]) break; 	
		}
		if (j==n2) break; /* found! */
	}
	if (i>n1-n2)
		return n1;
	return i;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_put_integer                              |
 |                                                                        |
\*------------------------------------------------------------------------*/
 
void tcob_put_integer( struct fld_desc *fdesc, char *sbuf, int value) {

	tcob_move(&_generic_4binary,(char *)&value,fdesc,sbuf);
}

/* end of strings.c */

