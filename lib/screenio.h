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

#ifndef SCREENIO_H
#define SCREENIO_H


#define TCOB_STR_DECIMAL_IS_POINT       '.'
#define TCOB_STR_DECIMAL_IS_COMMA       ','

#define TCOB_DISPLAYFIELD(TYPE) ((TYPE) == DTYPE_DISPLAY)
#define TCOB_EDITEDFIELD(TYPE) ((TYPE) == DTYPE_EDITED)
#define TCOB_NUMERICFIELD(TYPE) (DISPLAYFIELD(TYPE) || EDITEDFIELD(TYPE))

/* COBOL standard color nums */

#define TC_BLACK   0
#define TC_BLUE    1
#define TC_GREEN   2
#define TC_CYAN    3
#define TC_RED     4
#define TC_MAGENTA 5
#define TC_YELLOW  6
#define TC_WHITE   7


/* control keys */
#define TCOBKEY_TAB 		9
#define TCOBKEY_FORWARD 	12
#define TCOBKEY_HOMECLR 	24
#define TCOBKEY_RETURN		13
#define TCOBKEY_ENTER		0527
#define TCOBKEY_ESCAPE 		27

/* 
 "pseudo-key" to indicate auto-clean must be enabled for all fields 
 We use KEY_MAX-1 to avoid conflicting with curses definitions 
*/
#define TCOBKEY_AUTOCLEANALL	0776

/* Actions binded to keys pressed */

#define EDIT_FIRST_FIELD	1	/* Go to the first field */
#define EDIT_LAST_FIELD		2	/* Go to the last field */

#define EDIT_UP_FIELD		3	/* Go to the next field at last field
					   terminate edit mode */
#define EDIT_DOWN_FIELD		4	/* Go to the prev. field at first field
					   terminate edit mode */
#define EDIT_NEXT_FIELD		5	/* Go to the next field at last field
					   begin on the first field again */
#define EDIT_PREV_FIELD		6	/* Go to the prev. field at first 
					   go to last filed */

#define EDIT_LEFT		7	/* move cursor left */
#define EDIT_RIGHT		8	/* move cursor right */
#define EDIT_FIRST  		9	/* move cursor to the begining of field */
#define EDIT_LAST		10	/* move cursor to the end of field */

#define EDIT_INSERT		11	/* Insert a space */
#define EDIT_BACKSPACE		12	/* delete the char prev. to cursor */
#define EDIT_DELETE		13	/* delete the char on the cursor */

#define EDIT_TERMINATE		14	/* Terminate the edition, move value to SCREEN STATUS */

#define EDIT_CLEAR		15	/* Clear the current field */
#define EDIT_CLEAR_TOEND        16      /* Clear from the current position to the end of field */
#define EDIT_DECIMALPT          17      /* decimal point key */

#define EDIT_NOP		0	/* Do Nothing, the value is a normal char 
					   or there isn no bindig for this code.
					   This is also the value of SCREEN STATUS
                                 	   of SCREEN STATUS for auto fields, correct 
					   input screen status = 0, (COBOL 2001 draft)*/
					   
/* Struct to bind the key pressed and the action to do */
struct KeyBinding {
  int keyCode;		/* Key code returned by getch */
  short action;		/* Action to perform */
  int screenStatus;	/* Value to move to the SCREEN STATUS */
};



struct ScrFld {
	struct ScrFld	*pNext;				/* pointer to next field in list */
	int				iAttributes;		/* field attributs */
	int				iFldPos;			/* horizontal position in field */
	int				iScrPos;			/* horizontal position on screen */
	short int		iLine;				/* Line number of start of field */
	short int		iCol;				/* column number of start of field */
	short int		iFgColor;			/* foreground color */
	short int		iBgColor;			/* background color */
	struct fld_desc	*fldFrom;			/* field description of source field */
	char			*caFrom;			/* data area of source field */
	struct fld_desc	*fldTo;				/* field description of dest. field */
	char			*caTo;				/* data are of destination field */
	struct fld_desc	fldScr;				/* field description of screen field */
	char			*caScr;				/* data are of screen field */
	struct fld_desc fldWk;				/* work field desc for input fields */
	char			*caWk;				/* work data area for input fields */
	char			caPicWk[20];		/* area for picture definition */
};


//
// Usefull functions for use from the screen frontends
//
struct ScrFld *get_next_input_field(struct ScrFld *p);
struct ScrFld *get_prev_input_field(struct ScrFld *p);
void prepare_dest_field(struct ScrFld *pFld);
void prepare_input_field(struct ScrFld *pFld);
//
// functions that should be implemented by screen frontends
//
int tcob_scr_init();
void tcob_scr_finish();

int tcob_scr_accept(struct ScrFld *);
void tcob_scr_display(struct ScrFld *);
void tcob_scr_setyx(int y,int x);
void tcob_scr_sety(int y);
void tcob_scr_setx(int x);
int tcob_scr_gety();
int tcob_scr_getx();
int tcob_scr_kbdstatus();

#endif /* SCREENIO_H */
