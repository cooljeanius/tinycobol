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
 * TinyCOBOL Run Time Library -- Screen I/O functions
 *

*/

#include "htcoblib.h"
#include "mwindows.h"
#include "screenio.h"
#include "rterrors.h"

//extern char *screen_status;   // pointer to the screen status field 
//extern char *screen_cursor;   // pointer to the cursor field 

//extern int bDecimalComma;

static int  bScrIOInit = 0;
static char cDecimalChar = '.';
static struct ScrFld *_Fields_ = (struct ScrFld *)0;

#define get_first_field() (_Fields_)
#define set_first_field(f) (_Fields_=f)


static void set_cursor_yx(int,int);
void cob_scr_process(int iAttr, int iLine, int line_sign, int iColumn,
		int column_sign, int iFgColor, int iBgColor,int size,
		struct fld_desc *fldScr, char *caScr, void *pInfo, ...);

static void free_scr_fields();
void cob_init_screen();

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                     tcob_accept_curses                                  |
 |                                                                         |
 |   Similar to tcob_accept_std (basicio.c) but only called when position  |
 |   options or on exception are given or with screenio initialized.       |
 |                                                                         |
 |   Simulates an accept of an screen section item, first calls            |
 |   tcob_scr_process and the tcob_accept_screen                           |
 |                                                                         |
\*-------------------------------------------------------------------------*/
int tcob_accept_curses( char *buffer, struct fld_desc *f, int flags ) {
	int r,y;
	struct fld_desc *f_tmp=NULL;
	char *buffer_tmp=NULL;

	f_tmp = (struct fld_desc *)malloc(sizeof(struct fld_desc));
	buffer_tmp = (char *)malloc(f->len);
	
	if((!f_tmp)||(!buffer_tmp)) {
		tcob_rt_error("screenio: tcob_accept_curses",TCB_RTERR_NO_MEM);
	}
	
	memcpy(f_tmp,f,sizeof(struct fld_desc));
	
	if (flags & SCR_JUST_RIGHT) {
		f_tmp->just_r = 1;
	}
	
	if (!(flags & SCR_UPDATE)) {
         	if ((f_tmp->type == DTYPE_ALPHANUMERIC)||
   	  	    (f_tmp->type == DTYPE_ALPHA)||
       	            (f_tmp->type == DTYPE_GROUP))
			memset(buffer_tmp,' ',f_tmp->len);
		else
			memset(buffer_tmp,'0',f_tmp->len);
	} else {
		memcpy(buffer_tmp,buffer,f_tmp->len);
	}
	
	tcob_scr_process(flags, 0, 0, 0,0,-1,-1,-1,f_tmp,buffer_tmp,f_tmp,buffer_tmp,f_tmp,buffer_tmp);
	
	r = tcob_accept_screen();
	
	tcob_move(f_tmp,buffer_tmp,f,buffer);
  	
	if ( f_tmp != NULL ) { free(f_tmp); f_tmp = NULL;}
	if ( buffer_tmp != NULL ) { free(buffer_tmp); buffer_tmp = NULL ; }

	y=tcob_scr_gety();
	
	if (!(flags & SCR_NO_ADVANCING)){  // no advancing? 
		set_cursor_yx(y + 1 , 1);
	}
	
	if ( r == TCOBKEY_RETURN || r == TCOBKEY_ENTER)
		r=0;
	
	return r;
}
/*int accept_curses_old( char *buffer, struct fld_desc *f, int flags ) {
	int i, r, x, y, x0, y0, bEndLoop, first=1;
	int action;
	static char *szBuf = NULL;
	int tmp, len = f->len;
	int ib;  // szBuf offset
	unsigned int picLen;
	struct fld_desc f1 = {0,DTYPE_ALPHANUMERIC,0,0,0,0,0,0,0,0,NULL};

	cob_init_screen();
	// we alloc the line buffer only at the first time 
	if (!szBuf)
		szBuf=malloc(RLBUF_SIZE);
	// check if UPDATE was given (copy input field to szBuf and show it) 
	getyx(stdscr,y0,x0);
	if (flags & SCR_UPDATE) {
		strncpy(szBuf,buffer,len);
		getyx(stdscr,y,x);
		for (i=0; i<len; i++)
			addch(buffer[i]);
		set_cursor_yx(y,x);
	} else {
	       	if ((f->type == DTYPE_ALPHANUMERIC)||
		    (f->type == DTYPE_ALPHA)||
		    (f->type == DTYPE_GROUP))
			memset(szBuf,' ',len);
		else
			memset(szBuf,'0',len);
	}
	
	// do the accept 
	szBuf[len] = '\0';
	ib=0;
	for (bEndLoop=0; !bEndLoop; ) {
		r=getch();
		action = _get_action_for_key(r);
		switch (action) {
		  case EDIT_BACKSPACE:
			if (ib > 0) {
				ib--;
				if (ib < len)
					memmove(szBuf+ib,szBuf+ib+1,len-ib);
				szBuf[len-1]=' ';
				getyx(stdscr,y,x);
				x--;
				set_cursor_yx(y,x);
				for (tmp=ib;tmp<len;tmp++)
					addch(szBuf[tmp]);
				set_cursor_yx(y,x);
			}
			break;
		  case EDIT_RIGHT:
			if (ib < len) {
				ib++;
				getyx(stdscr,y,x);
				x++;
				set_cursor_yx(y,x);
			}
			break;
		  case EDIT_DOWN_FIELD:
		  case EDIT_NEXT_FIELD:
			if(ib < len) {
				memset(szBuf+ib, ' ', len-ib);
				addch_set(' ', len-ib);
				ib = len;
			}
			r = 0x0d; // simulate a <Return> key 
			bEndLoop++;
			break;
		  case TCOBKEY_HOMECLR:
			//getyx(stdscr,y,x);
			//x -= ib;
			ib = 0;
	       		if ((f->type == DTYPE_ALPHANUMERIC)||
		    	   (f->type == DTYPE_ALPHA)||
		    	   (f->type == DTYPE_GROUP))
				memset(szBuf,' ',len);
			else
				memset(szBuf,'0',len);
			set_cursor_yx(y0,x0);
			for (i=0; i<len; i++)
				addch(szBuf[i]);
			set_cursor_yx(y0,x0);
			break;
		  default:
			// allow accented (portuguese, french, ...) chars as well 
			if (r < ' ' || r > 0xff || r == 0x7f) {
				if (first)
					ib = len;
				bEndLoop++;
			} else {
				first=0;
				if (ib < len) {
					szBuf[ib++] = r;
					addch(r);
				}
				if ((ib >= len) && (flags & SCR_AUTO)) {
					bEndLoop++;
					r = 0x0d; // simulate a <Return> key 
				}
			}
		}
	}
	if (r == 0x0d || r == 0x0a) {
		r = 0;
	}
	if (flags & SCR_JUST_RIGHT) {
		// trim right blanks 
		for (ib=len-1; (szBuf[ib] == ' ') && (ib > 0); ib--) ;
		ib++;
		memmove(szBuf+len-ib, szBuf, ib);
	       	if ((f->type == DTYPE_ALPHANUMERIC)||
		    (f->type == DTYPE_ALPHA)||
		    (f->type == DTYPE_GROUP))
			memset(szBuf,' ',len-ib);
		else
			memset(szBuf,'0',len-ib);
		// update screen with the field justified right 
		set_cursor_yx(y0,x0);
		for (i=0; i<len; i++)
			addch(szBuf[i]);
	}
	f1.len = strlen(szBuf);
	picLen = tcob_picReqLen(1);
	f1.pic = (char *)malloc(picLen);
	tcob_picCreate (f1.pic, picLen, 'X', f1.len, NULL);
	tcob_move( &f1,szBuf,f,buffer );
	free(f1.pic);
	return r;
}*/
/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                     tcob_display_curses                                 |
 |                                                                         |
 |   Similar to tcob_display_std (basicio.c) but only called when position |
 |   options are given or with screenio initialized.                       |
 |                                                                         |
 |   Simulates an accept of an screen section item, first calls            |
 |   tcob_scr_process and the tcob_accept_screen                           |
 |                                                                         |
\*-------------------------------------------------------------------------*/

void tcob_display_curses( struct fld_desc *f, char *s, int dspflags ) {
	int y;

	tcob_scr_process(dspflags, 0, 0, 0,0,-1,-1,-1,f,s,NULL);
	tcob_display_screen();
	
	y=tcob_scr_gety();

	if (!(dspflags & SCR_NO_ADVANCING))  // no advancing? 
		set_cursor_yx(y + 1 , 1);
}
/*
void display_curses_old( struct fld_desc *f, char *s, int dspflags ) {
	char *buffer;
	unsigned int i;
	struct fld_desc ftmp;
	unsigned int picLen;
	int  domove=0;
	int  x,y;
	unsigned int len;

	cob_init_screen();
	if (dspflags & 2) {  // erase? 
		getyx(stdscr,y,x);
		erase();
		set_cursor_yx(y,x);
	}
	if (dspflags & 4) {  // erase to end of line? 
		getyx(stdscr,y,x);
		clrtoeol();
		set_cursor_yx(y,x);
	}
	if ((f->type == DTYPE_DISPLAY) 
         || (f->type == DTYPE_PACKED) 
         || (f->type == DTYPE_BININT) 
         || (f->type == DTYPE_FLOAT)) {
		domove++;
		memmove(&ftmp,f,sizeof(ftmp));
		len = tcob_picCompLength(f) + tc_abs((char)f->pscale);
		//printf("display: type=%c, len=%d, decimals=%d\n",
		//	f->type, f->len, f->decimals);
		
		picLen = tcob_picReqLen(4);
		ftmp.pic = (char *)malloc(picLen);
		tcob_picCreate (ftmp.pic, picLen, NULL);
		if(tcob_picElemVal(f->pic,0) == 'S')
			tcob_picAppend (ftmp.pic, picLen, '-', 1, NULL);
		if (ftmp.decimals <= 0) {
			tcob_picAppend (ftmp.pic, picLen, '9', len, NULL);
		} else if (tcob_picElemVal(f->pic,0) == 'P' || // unsigned scaled 
			   tcob_picElemVal(f->pic,1) == 'P') { // signed scaled 
			tcob_picAppend (ftmp.pic, picLen,
				cDecimalChar, 1,
				'9', ftmp.decimals, NULL);
		} else {
			tcob_picAppend (ftmp.pic, picLen,
				'9', len - ftmp.decimals,
				cDecimalChar, 1,
				'9', ftmp.decimals, NULL);
		}
		ftmp.type = DTYPE_EDITED;
		if(tcob_picElemVal(f->pic,0) == 'S') // account for the sign 
			len++;
		if (ftmp.decimals > 0) // account for the decimal point 
			len++;
		ftmp.len = len;
		buffer = malloc(len);
		tcob_move(f,s,&ftmp,buffer);
		free(ftmp.pic);
	} else {
		len = f->len;
		buffer = s;
	}

	for (i=0; i<len; i++)
		addch(buffer[i]);
	if ((dspflags & 1)==0)  // no advancing? 
		addch('\n');
	refresh();
	if (domove)
		free(buffer);
}*/



/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_goxy_expr                                 |
 |                                                                         |
 |   Position cursor at the screen with screen plugin.                     |
 |   Called only if DISPLAY  or ACCEPT statements generated with           |
 |   position-spec is found.                                               |
 |   Uses double coords because allow any arbitrary expressions.           |
 |                                                                         |
 |   tcob_goxy                                                             |
 |   tcob_go_y                                                             |
 |   tcob_go_x                                                             |
 |                                                                         |
 |   The same functionality but using intgers.                             |
 |                                                                         |
\*-------------------------------------------------------------------------*/
void tcob_goxy_expr ( double x, double y ) {
	tcob_init_screen();
	set_cursor_yx((int)y-1,(int)x-1);
}
void tcob_gox_expr ( double x) {
	tcob_init_screen();
	set_cursor_yx(tcob_scr_gety(),(int)x-1);
}
void tcob_goy_expr ( double y) {
	tcob_init_screen();
	set_cursor_yx((int)y-1,tcob_scr_getx());
}
void tcob_goxy ( int x, int y ) {
        tcob_init_screen();
	set_cursor_yx(y-1,x-1);
}
void tcob_goxy_variable ( char *var, int len ) {
        int x,y,pos;
    	char tmp[7];
    	tcob_init_screen();
    	/* len should be 4 or 6 */
        if ((len != 4)&&(len != 6))
	    tcob_rt_error("screenio: tcob_goxy_variable",TCB_RTERR_EMPTY,"bad arguments");
    	strncpy(tmp,var,len);
        pos=atoi(tmp);
    	if (len == 6) {
	  y = pos / 1000;
	  x = pos - (1000 * y);
	} else {
	  y = pos / 100;
	  x = pos - (100 * y);
	}
	set_cursor_yx(y-1,x-1);
}

void tcob_go_x ( int x,int sign) {
	tcob_init_screen();
       if(x==0) return;
       if (sign != 0)
	{
	  x=tcob_scr_getx() + (sign * x);
	}
	else
	{
	    x--;
	}
        
	set_cursor_yx(tcob_scr_gety(),x );
}
void tcob_go_y ( int y,int sign ) {
	tcob_init_screen();
        if(y==0) return;
        if (sign != 0)
	{
	  y=tcob_scr_gety() + (sign * y);
	}
	else
	{
	    y--;
	}
	set_cursor_yx(y,tcob_scr_getx());
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 | get_next_input_field                                                    |
 | get_prev_input_field                                                    |
 |                                                                         |
 | This are helper functions for tcob_accept_screen to help moving between |
 | fields.                                                                 |
\*-------------------------------------------------------------------------*/
struct ScrFld *get_next_input_field(struct ScrFld *p) {
	struct ScrFld *pFld;
	/* find next input field in chain */
	for (pFld=p->pNext; pFld; pFld=pFld->pNext) {
		if(pFld->fldTo)
			return pFld;
	}
	return NULL;
}
struct ScrFld *get_prev_input_field(struct ScrFld *p) {
	struct ScrFld *pFldAux, *pNext;
        /* find prev input field in chain */
        
        pFldAux = get_first_field(); 
	if (pFldAux->fldTo == NULL)
		pFldAux = get_next_input_field(pFldAux);

        for(; pFldAux; pFldAux=pNext) {
		pNext = get_next_input_field(pFldAux);
		if (p == pNext)
			return pFldAux;
	}
	return NULL;

}
/*-------------------------------------------------------------------------*\
 | prepare_field       - Prepare the string to be accepted or moved        |
 |                                                                         |
 | prepare_dest_field  - Prepare the destination field for make a move to  |
 |                       'to' field                                        | 
 | prepare_input_field - Prepare the input field to make it easy to accept |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static void prepare_field(char *ca,int len) {
	int j=0;
	int i=0;
	int spaces_after_data=0;
	int data_found=0;

	// Numeric or edited field 
	// Only accepted 0123456789+-., and spaces before and after input
	
	for(i=0;i < len;i++) { 
		if((ca[i]=='+')||
		   (ca[i]=='-')||
		   (ca[i]=='.')||
		   (ca[i]==',')||
		   ((ca[i] >= '0') && (ca[i] <='9'))) {    // accepted chars
			if (!spaces_after_data) {
				data_found++;
				ca[j]=ca[i];
				j++;
			}
		// spaces or incorrect char
		} else if((ca[i] == ' ') && (data_found)) {
			spaces_after_data++;
		}	
	} //for
	memset(ca+j, ' ', len-j);
}
void prepare_dest_field(struct ScrFld *pFld) {
	if(pFld->fldScr.type != DTYPE_ALPHANUMERIC)
	        prepare_field(pFld->caScr,pFld->fldScr.len);
	return;
}
void prepare_input_field(struct ScrFld *pFld) {
	if(pFld->fldScr.type != DTYPE_ALPHANUMERIC)
        	prepare_field(pFld->caWk,pFld->fldScr.len);
	return;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_accept_screen                             |
 |  Calls to this routine are generated by the compiler when an ACCEPT     |
 |  verb with an assocated screeen section name is encountered.  The       |
 |  routine takes no arguments, but assumes that the routine               |
 |  tcob_scr_process has been called once for each field in the referenced |
 |  screen. The tcob_scr_process builds a linked list of ScrFld structures |
 |  with one structure per field in the screen. This linked list is        |
 |  referenced to by the external variable _Fields_.  Upon exit from this  |
 |  routine, all memory associated with these structures is freed.         |
 |                                                                         |
 |  Input is accepted from any field that has a destination or "To"        |
 |  field associated with it. The routine accepts keyboard input and that  |
 |  input is edited to insure that it is valid for the type of field       |
 |  that was described in the screen section.                              |
 |                                                                         |
 |  Control stays in this routine until a carrage return is received,      |
 |  then, corresponding data is moved to all receiving fields, memory      |
 |  is freed, the screen mode is reset and the routine exits back to the   |
 |  calling mainline program.                                              |
 |                                                                         |
\*-------------------------------------------------------------------------*/
int tcob_accept_screen() {
	int 			key_status;
	struct ScrFld		*pFld;
	char tmp[5];
	
	
	tcob_init_screen();
	//
	// Accept all the fields
	//
	pFld=get_first_field();
	key_status = tcob_scr_accept(pFld);
	// 
	// If exists the SCREEN STATUS field move the value to it .
	// The SCREEN STATUS field is a PIC X(4) or 9(4) display 
	// 
	if (!(screen_status==NULL)) { 
		tmp[4]='\0';
#ifdef __MINGW32__			
			_snprintf(tmp,5,"%4.4u",key_status);
#else			
			snprintf(tmp,5,"%4.4u",key_status);
#endif			
		memcpy(screen_status,tmp,4);
	}
	// Move data to 'to' fields 	
	for(pFld=get_first_field(); pFld; pFld=pFld->pNext) {
		if(pFld->fldTo) {
			if (pFld->caWk != pFld->caScr) {
			    prepare_input_field(pFld);
			    tcob_move(&pFld->fldWk, pFld->caWk, &pFld->fldScr, pFld->caScr);
			}
			if (pFld->caScr != pFld->caTo) {
			    prepare_dest_field(pFld);
			    tcob_move(&pFld->fldScr, pFld->caScr, pFld->fldTo, pFld->caTo);
			}
		}
	}
	
	free_scr_fields();  // free Fields
	return key_status;
}


/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_display_screen                            |
 |  Calls to this routine are generated by the compiler when an DISPLAY    |
 |  verb with an assocated screeen section name is encountered.  The       |
 |  routine takes no arguments, but assumes that the routine               |
 |  tcob_scr_process has been called once for each field in the referenced |
 |  screen. The tcob_scr_process builds a linked list of ScrFld structures |
 |  with one structure per field in the screen. This linked list is        |
 |  referenced to by the external variable Fields.  Upon exit from this    |
 |  routine, all memory associated with these structures is freed.         |
 |                                                                         |
\*-------------------------------------------------------------------------*/

void tcob_display_screen() {
	tcob_init_screen();
	tcob_scr_display(get_first_field());
	free_scr_fields();
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                               tcob_scr_process                          |
 |                                                                         |
\*-------------------------------------------------------------------------*/
void tcob_scr_process(int iAttr, int iLine, int line_sign, int iColumn,
		int column_sign, int iFgColor, int iBgColor, int size,
		struct fld_desc *fldScr, char *caScr, void *pInfo, ...) {
	va_list					ap;
	unsigned int				i;
	int 					bIsAlpha;
	int 					bIsDisplay;
	int 					bIsEdited;
	int 					bDecPoint;
	unsigned int 				iCharCnt;
	unsigned int 				iDecCnt;
	struct ScrFld				*pFld;
	void					*pWk;
	char					c;
	
	tcob_init_screen();
	
	pFld = get_first_field();

	if (pFld == NULL) {
		pFld = (struct ScrFld *)malloc(sizeof(struct ScrFld));
		if(!pFld) {
			tcob_rt_error("screenio: tcob_scr_process",TCB_RTERR_NO_MEM);
			return;
		}
		set_first_field(pFld);
	} else {
		while(pFld->pNext)
			pFld = pFld->pNext;
		pFld->pNext = (struct ScrFld *)malloc(sizeof(struct ScrFld));
		if(!pFld->pNext) {
			tcob_rt_error("screenio: tcob_scr_process",TCB_RTERR_NO_MEM);
			return;
		}
		pFld = pFld->pNext;
	}
	pFld->pNext = (struct ScrFld *)0;

	va_start(ap, pInfo);
	pWk = pInfo;
	pFld->fldFrom = (struct fld_desc *)pWk;
	if(pWk) {
		pWk = va_arg(ap, void *);
		pFld->caFrom = (char *)pWk;
	} else 
		pFld->caFrom = (char *)0;
	pWk = va_arg(ap, void *);
	pFld->fldTo = (struct fld_desc *)pWk;
	if(pWk) {
		pWk = va_arg(ap, void *);
		pFld->caTo = (char *)pWk;
	} else 
		pFld->caTo = (char *)0;

	pFld->iAttributes = iAttr;

	if (iLine) 
	  switch(line_sign) { 
		case 1:
			pFld->iLine = tcob_scr_gety() + iLine;
			break;
		case -1:
			pFld->iLine = tcob_scr_gety() - iLine;
			break;
		default:
			pFld->iLine = iLine - 1;
			break;
	  } 
	else
          pFld->iLine = tcob_scr_gety();

	if (tcob_scr_gety() != pFld->iLine)
	    tcob_scr_setx(0);

	tcob_scr_sety(pFld->iLine);
 	
	if(iColumn)
	  switch(column_sign) { 
		case 1:
			pFld->iCol = tcob_scr_getx() + iColumn;
			break;
		case -1:
			pFld->iCol = tcob_scr_getx() - iColumn;
			break;
		default:
			pFld->iCol = iColumn - 1;
			break;
	  }
	else
	  pFld->iCol = tcob_scr_getx();

	tcob_scr_setx(pFld->iCol);

        pFld->iFgColor = iFgColor;
	if ((iFgColor > 0 ) && (iFgColor & 0x00000008)) {
	      pFld->iAttributes |= SCR_HIGHLIGHT ;
	}
	pFld->iBgColor = iBgColor;
	
	memcpy(&(pFld->fldScr), fldScr, sizeof(struct fld_desc));
	pFld->caScr = caScr;
	bIsAlpha = 0;
	bIsDisplay = 0;
	bIsEdited = 0;
	bDecPoint = 0;
	iCharCnt = 0;
	iDecCnt = 0;
	if ((pFld->fldScr.type==DTYPE_GROUP) || (pFld->fldScr.pic==NULL)) {
		int picLen;
		picLen = tcob_picReqLen(1);
		pFld->fldScr.pic = (char *)malloc(picLen);
		tcob_picCreate (pFld->fldScr.pic, picLen, 'X', pFld->fldScr.len, NULL);
	}
	for(i=0; (c=tcob_picElemVal(pFld->fldScr.pic,i)); i++) {
		unsigned int t = tcob_picElemLen(pFld->fldScr.pic,i);
		switch(c) {
			case 'A':
			case 'X':
				++bIsAlpha;
				iCharCnt += t;
				break;
			case '9':
				iCharCnt += t;
				if(bDecPoint)
					iDecCnt += t;
				break;
			case 'V':
				++bDecPoint;
				break;
			case '.':
			case ',':
				if(c == cDecimalChar)
					++bDecPoint;
				++bIsEdited;
				iCharCnt ++;
				break;
			case '+':
			case '-':
			case 'Z':
			case '*':
			case '$':
				++bIsEdited;
				iCharCnt += t;
				if(bDecPoint)
					iDecCnt += t;
				break;
			default:
				++bIsEdited;
				iCharCnt += 1;
		}
	}
	if(bIsEdited)	/* change field type to something appropriate */
		pFld->fldScr.type = DTYPE_EDITED;
	else if(!bIsAlpha)
		pFld->fldScr.type = DTYPE_DISPLAY;
	else
		pFld->fldScr.type = DTYPE_ALPHANUMERIC;

	//if(pFld->fldTo)	{	/* if we have a destination field */

		if ((size > 1) && ((unsigned int)size < iCharCnt)) /* size clause */
			iCharCnt = (unsigned int)size;
		pFld->fldScr.len = iCharCnt;
		pFld->fldWk.len = pFld->fldScr.len;
	/*	if(bIsEdited)
			pFld->fldWk.type = DTYPE_DISPLAY;
		else if(!bIsAlpha)
			pFld->fldWk.type = DTYPE_DISPLAY;
		else*/
			pFld->fldWk.type = DTYPE_ALPHANUMERIC;
		//pFld->fldWk.decimals = (unsigned char)iDecCnt;
		pFld->fldWk.just_r=0;
		pFld->fldWk.all = 0;
		pFld->fldWk.pic = pFld->caPicWk;

		if((pFld->fldWk.type == DTYPE_DISPLAY) 
		|| (pFld->fldWk.type == DTYPE_EDITED)) {
			tcob_picCreate (pFld->caPicWk, 20, 'S', 1,
				'9', iCharCnt-iDecCnt, NULL);
			if(iDecCnt)
				tcob_picAppend (pFld->caPicWk, 20, 'V', 1,
					'9', iDecCnt, NULL);
		} else
			tcob_picCreate (pFld->caPicWk, 20, 'X', pFld->fldScr.len,NULL);
		
		pFld->caWk = (char *)malloc(pFld->fldScr.len);
		
		if ((pFld->fldFrom) && (pFld->caFrom != pFld->caScr )) {
			tcob_move(pFld->fldFrom, pFld->caFrom, &pFld->fldScr, pFld->caScr);
		}

	tcob_move(&pFld->fldScr, pFld->caScr, &pFld->fldWk, pFld->caWk);
		
	/*} else
		pFld->caWk = (char *)0;*/
	
	pFld->iFldPos = 0;
	pFld->iScrPos = 0;
	tcob_scr_setx(tcob_scr_getx()+ pFld->fldScr.len); 

	return;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                           free_scr_fields                               |
 |   Frees memory used by the fields prepared by tcob_scr_process          |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static void free_scr_fields() {
	struct ScrFld	*pFld, *next;

	for (pFld=_Fields_; pFld; pFld=next) {
		next = pFld->pNext;
		if (pFld->caWk) free (pFld->caWk);
		if (pFld) free (pFld);
	}
	_Fields_ = (struct ScrFld *)NULL;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                            set_cursor_yx                                |
 |     Move the cursor to the X Y position. It a layer for the curses      |
 |     move function.                                                      |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static void set_cursor_yx(int y,int x) {
	
        tcob_scr_setyx(y,x);
	/* 
	 * If exists the CURSOR field move the value to it .
	 * The CURSOR field is a PIC X(6) or 9(6) display 
	 */
	if (!(screen_cursor==NULL)) { 
                char tmp[6];
		sprintf(tmp,"%3.3u%3.3u",tcob_scr_gety(),tcob_scr_getx());
		memcpy(screen_cursor,tmp,6);
	}
	
}

/*-------------------------------------------------------------------------*\
 |        tcob_accept_inkey                                                |
 |  Move 1 to field if there is a typed key in the buffer, 0 if not.       |
 |  This version uses curses.                                              |
\*-------------------------------------------------------------------------*/
int tcob_accept_inkey(struct fld_desc *f, char *buffer ) {
	struct fld_desc ftmp = {1,DTYPE_ALPHANUMERIC,0,0,0,0,0,0,0,0,NULL};
	char ctmp[1];
	if (tcob_scr_kbdstatus()) {
		ctmp[0]='1';
	} else {
		ctmp[0]='0';
	}
	tcob_move(&ftmp,ctmp,f,buffer);
	return 0;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                            do_putch_terminal                            |
 |                                                                         |
\*-------------------------------------------------------------------------*/
/*
void do_putch_terminal(char c) {
	int x,y;
	int mx, my;

	getyx(stdscr, y, x);
	getmaxyx(stdscr, my, mx);

	if(c>31)
		addch(c);
	else if(c=='\t') {
		do {
			addch(' ');
			x++;
			if(x==mx) {
				x=0;
				if(y<my)
					y++;
				set_cursor_yx(y,x);
				return;
			}
		} while(x%8);		
	} else if(c=='\n') {
		if(y<my)
			set_cursor_yx(y+1,  x);
	} else if(c=='\r') {
		set_cursor_yx(y,0);
	}
}

*/
/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                             tcob_init_screen                            |
 |                                                                         |
\*-------------------------------------------------------------------------*/

void tcob_init_screen(void) {

	if (bScrIOInit) // No need to initilize more than once 
		return;
	if (bDecimalComma)
		cDecimalChar = ',';

	tcob_scr_init();

	bScrIOInit++;
}


/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                             display_terminal                            |
 |                                                                         |
\*-------------------------------------------------------------------------*/

/*void display_terminal(char *buf, int len) {
	int i;
//	char *tbuf=buf;
	
//	while(*buf)
	for(i=0; i<len; i++)
		do_putch_terminal(buf[i]);
	refresh();
}

*/
/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                             newline_terminal                            |
 |                                                                         |
\*-------------------------------------------------------------------------*/

/*void newline_terminal(void) {
	do_putch_terminal('\n');
}

*/
/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          display_erase_terminal                         |
 |                                                                         |
\*-------------------------------------------------------------------------*/

/*void display_erase_terminal(void) {
	clear();
	refresh();
}*/


/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                             tcob_do_scrio_finish                        |
 |                                                                         |
\*-------------------------------------------------------------------------*/

void tcob_do_scrio_finish(void) {
	if (bScrIOInit) {
		tcob_scr_finish();
	}
}


/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                             outit_terminal                              |
 |                                                                         |
\*-------------------------------------------------------------------------*/

/*void outit_terminal(void) {	
	write(2, "BRK",3);
}*/


/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                             outeek_terminal                             |
 |                                                                         |
\*-------------------------------------------------------------------------*/

/*void outeek_terminal(void) {	
	write(2, "CNT",3);
}*/


/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                           ep_debug_terminal                             |
 |                                                                         |
\*-------------------------------------------------------------------------*/

/*void ep_debug_terminal(void *addr, void *low, void *high, void *ret) {
	printf("ADDR=%p LOW=%p HIGH=%p RET=%p\n", addr, low, high, ret);
	fflush(stdout);
}*/


/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                              backspace                                  |
 |                                                                         |
\*-------------------------------------------------------------------------*/

/*static void backspace(void) {
	int y,x;
	getyx(stdscr, y,x);
	if(x) x--;
	set_cursor_yx(y,x);
}*/


/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                             cob_accept                                  |
 |                                                                         |
\*-------------------------------------------------------------------------*/
/*
int cob_accept(char *buffer, struct fld_desc *f, int echo ) {
	int y,x;
	unsigned int i, ib;
	int cnt, digcnt;
	// cnt 		= how many chars need be entered
	// digcnt 	= how many already entered 
	//
	int c, sign=0;
	int decimal_flg=0;

	getyx(stdscr, y,x);
	//
	// echo & 4 --> DARK,
	// echo == 0 --> NO ECHO
	//
	if (echo & 2) {		// WITH FILLER (this isn't standard, 
			        //		I've invented it, but...) 
		addch_set('_', f->len);
		if (f->decimals) addch(cDecimalChar);
		refresh();
	}
	if (echo & 8) {		// WITH UPDATE 
		for (i=0;i<f->len;i++)
			addch(buffer[i]);
		set_cursor_yx(y,x);
		refresh();
	}
	digcnt=0;
	cnt=f->len;
	ib = 0;
	while (1) {
		c=getch();
		if (c=='\n') // curses return '\n' as the return key 
			break;
		if (c=='-' && ib==0) {
			sign=1;
			if (echo & 3) addch('-');
			else if (echo & 4) addch('*');
			continue;
		}
		if (c==KEY_BACKSPACE) {
			for (i=0; i<ib; i++) {
				backspace();
				if (echo & 2) addch('_');
				else if (echo & 8) addch(buffer[i]);
				else if (echo) addch(' ');
			}
			if (decimal_flg) {
				if (echo & 2) addch(cDecimalChar);
				else if (echo & 8) { } // nothing to be done 
				else if (echo) addch(' ');
			}
			refresh();
			decimal_flg=0;
			cnt=f->len;
			digcnt=0;
			ib=0;
			continue;
		}
		if (c==8) {
			if (ib>0) {
				ib--;
				if (echo) backspace();
				if (cnt==f->decimals) {
					decimal_flg=0;
					if (echo) backspace();
				}
				else if (digcnt==1 && sign) {
					sign=0;
					if (echo) backspace();
				}
				cnt++;
				digcnt--;
			}
			continue;
		}
		if ( ((f->type==DTYPE_ALPHA) && (isalpha(c) || c==' ')) ||
		     ((f->type==DTYPE_ALPHANUMERIC || f->type==DTYPE_GROUP)
					&& (isprint(c) || c==' ')) ||
		     ((f->type==DTYPE_DISPLAY) && isdigit(c) )) {
			buffer[ib++] = c;
			if (echo & 4) addch('*');
			else if (echo) addch(c);
			if (cnt) { 
				cnt--;
				digcnt++;
			}
			if (cnt==f->decimals && cnt) {
				if (echo & 4) addch('*');
				else if (echo) addch(cDecimalChar);
				decimal_flg++;
			}
			continue;
		}
		if (c==cDecimalChar && f->type==DTYPE_DISPLAY && !decimal_flg) {
			decimal_flg++;
			cnt=f->decimals;
			if (echo & 4) addch('*');
			else if (echo) addch(cDecimalChar);
			continue;
		}
	}

	if (f->type==DTYPE_DISPLAY) {
		if (!decimal_flg) {
			// align field (integer part) at the right 
			if (f->len-cnt)
				memmove(buffer+cnt-f->decimals,
					buffer,digcnt);
			// fill rest of field at the left with zeros 
				if (cnt>f->decimals)
					memset(buffer,'0',cnt-f->decimals);
			// fill decimal digits with zeros at the right 
			memset(buffer+f->len-f->decimals,
				'0',f->decimals);
		} else {
			memset(buffer+ib, '0', cnt);
			digcnt += cnt;
			ib += cnt;
			memmove(buffer+f->len-digcnt,buffer,digcnt);
			memset(buffer,'0',f->len-digcnt);
		}
	} else 
		memset(buffer+ib,' ',cnt);
	if (f->type==DTYPE_DISPLAY)
		put_sign(f,buffer,sign);
	printw("\n");
	return (int)ib;
}

*/
/* screenio.c */
