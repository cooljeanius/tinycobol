/* 
 * Copyright (C) 2002,2001, 2000, 1999,  Rildo Pragana, Jim Noeth, 
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
 * TinyCOBOL Run Time Library -- Curses Screen I/O functions
 *

   Colour numbers:
   NUMBER    STANDARD        CURSES 
   ----------------------------------------
   0         black           COLOR_BLACK
   1         blue            COLOR_RED
   2         green           COLOR_GREEN
   3         cyan            COLOR_YELLOW
   4         red             COLOR_BLUE
   5         magenta         COLOR_MAGENTA
   6         brown/yellow    COLOR_CYAN
   7         white           COLOR_WHITE

   Color numbers from COBOL standard:
   0 black           
   1 blue            
   2 green           
   3 cyan            
   4 red             
   5 magenta         
   6 brown/yellow    
   7 white           
  
   Color numbers from Curses library:
   COLOR_BLACK      0
   COLOR_RED        1
   COLOR_GREEN      2
   COLOR_YELLOW     3
   COLOR_BLUE       4
   COLOR_MAGENTA    5
   COLOR_CYAN       6
   COLOR_WHITE      7

*/

#include "htcoblib.h"
#include "mwindows.h"

#if defined(__CYGWIN__)
#include <ncurses/ncurses.h>
#else
#if defined(__MINGW32__)
#include <pdcurses.h>
#else
#include <curses.h>
#endif
#endif

#include "screenio.h"
#include "rterrors.h"
#include "config.h"
/* PDcurses 2.4 does not have the following defenetion */
#ifndef KEY_CODE_YES
#define KEY_CODE_YES        0x100        /* A wchar_t contains a key code */
#endif

static short fore_color;      /*  Actual fore and back colors */      
static short back_color;

static int cursor_x = 0;      /* Actual screen position for dinamically */
static int cursor_y = 0;      /* calculate +/- line/col  */
static struct KeyBinding *keyBindings;

extern int catch_cntrlc;
extern void tcob_catch_cntrlc(int sig_num);


/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                  tcob_scr_init                                          |
 |  Initialize curses                                                      |
 |                                                                         |
\*-------------------------------------------------------------------------*/
int tcob_scr_init(void)
{

#ifdef  __PDCURSES__
        int i;
#endif

        initscr();
        noecho();
        cbreak();
        keypad(stdscr,TRUE);
        scrollok(stdscr,TRUE);
        nonl();
        /* raw(); */
        noecho();
                             
        keyBindings = tcob_get_keybindings();

        if (has_colors()) {
            start_color();
            pair_content(0,&fore_color,&back_color);
        }

#ifdef  __PDCURSES__
        /*
         *  This is needed for pdcurses, that has all the pairs to 0-7
         */
        for(i=0;i<COLOR_PAIRS;i++)
           init_pair(i,0,0);
#endif

       attrset(A_NORMAL);

       /* set the INT (Ctrl-C) signal handler */
       signal(SIGINT, tcob_catch_cntrlc);

       return TRUE;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                      tcob_scr_finish                                    |
 |     Close curses                                                        |
 |                                                                         |
\*-------------------------------------------------------------------------*/
void tcob_scr_finish(void)
{
        if(!isendwin())
             endwin();
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                  tcob_scr_setchar                                       |
 |    Set len positions to c                                               |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static void tcob_scr_setchar(char c, unsigned int len)
{
        unsigned int i;
        for (i=0; i<len; i++)
            addch(c);
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                  tcob_scr_getx                                          |
 |  Get actual cursos position on the screen                               |
 |                                                                         |
\*-------------------------------------------------------------------------*/
int tcob_scr_getx(void)
{
        return cursor_x;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                     tcob_scr_gety                                       |
 |                                                                         |
\*-------------------------------------------------------------------------*/
int tcob_scr_gety(void)
{
        return cursor_y;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                        tcob_scr_setyx                                   |
 |   Set cursos position on the screen                                     |
\*-------------------------------------------------------------------------*/
void tcob_scr_setyx(int y, int x)
{
        move(y,x);
        getyx(stdscr,cursor_y,cursor_x);
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                      tcob_scr_setx                                      |
 |                                                                         |
\*-------------------------------------------------------------------------*/
void tcob_scr_setx(int x)
{
        tcob_scr_setyx(tcob_scr_gety(),x);
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                  tcob_scr_sety                                          |
 |                                                                         |
\*-------------------------------------------------------------------------*/
void tcob_scr_sety(int y)
{
        tcob_scr_setyx(y,tcob_scr_getx());
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                    tcob_scr_kbdstatus                                   |
 |    Get the status of keyboard                                           |
 |    TRUE if there is a char in the buffer and FALSE if not               |
 |                                                                         |
\*-------------------------------------------------------------------------*/
int tcob_scr_kbdstatus(void)
{
        int c;
        nodelay(stdscr,TRUE);
        c=getch();
        nodelay(stdscr,FALSE);
        if (c==ERR) {
                return 0;
        }
        ungetch(c);
        return 1;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_scr_action_for_key                        |
 |  Looks in the table which is the action to return for the key passed.   |
 |  If exists the SCREEN STATUS field moves the value in the table to it.  |
 |                                                                         |
\*-------------------------------------------------------------------------*/
int tcob_scr_action_for_key(int key,int *status) 
{
        struct KeyBinding *binding=NULL;
        struct KeyBinding *pbindings;
    
        
        for(pbindings=keyBindings; pbindings->keyCode!=0; pbindings++) {
                if (pbindings->keyCode == key) {
                        binding=pbindings;
                        break;
                }
        }
        if (binding==NULL) {
                return EDIT_NOP;
        }
        *status = binding->screenStatus;
        return binding->action;

}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                        get_curses_color                                 |
 |  Returns the curses color code from the cobol color number              |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static int get_curses_color(int cobol_color) 
{

  unsigned int colour = COLOR_BLACK;
        
/*        switch(cobol_color % 8)   */   
        switch(cobol_color % COLORS)     {
                case TC_BLUE:
                  colour = COLOR_BLUE;
                  break;
               case TC_GREEN:
                  colour = COLOR_GREEN;
                  break;
                case TC_CYAN:
                  colour = COLOR_CYAN;
                  break;
                case TC_RED:
                  colour = COLOR_RED;
                  break;
                case TC_MAGENTA:
                  colour = COLOR_MAGENTA;
                  break;
                case TC_YELLOW:
                  colour = COLOR_YELLOW;
                  break;
                case TC_WHITE:
                  colour = COLOR_WHITE;
                  break;
                case TC_BLACK:
                default:
                  break;
        }        
        return colour;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                           set_colors                                    |
 |   sets the color for the next display                                   |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static void set_colors(void)
{
        int i;
        short fore, back;
        for(i = 0; i < COLOR_PAIRS; ++i) {
                pair_content(i,&fore,&back);
                if ((fore == fore_color) && (back == back_color)) {
                        break;
                }
                if ((fore == 0) && (back == 0)) {
                        init_pair(i,fore_color,back_color);
                        break;
                }
        }
        if (i != COLOR_PAIRS) 
        {
#ifdef CURSES_HAS_COLOR_SET
                color_set(i,NULL);
#else
                attrset(COLOR_PAIR(i));
#endif
                bkgdset(COLOR_PAIR(i));
               
        } 
        else {
#ifdef CURSES_HAS_COLOR_SET
               color_set(0,NULL);
#endif
               attrset(A_NORMAL);
        }
        
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                            set_attributes                               |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static void set_atributes(struct ScrFld *pFld) 
{
        attr_t        iAttr=0;

        attrset(A_NORMAL);

        if (pFld->iAttributes != -1)
        {
           if ((pFld->iAttributes & SCR_HIGHLIGHT) == SCR_HIGHLIGHT)
              iAttr |= A_BOLD;
                        
           if ((pFld->iAttributes & SCR_LOWLIGHT) == SCR_LOWLIGHT)
              iAttr |= A_DIM;

           if ((pFld->iAttributes & SCR_UNDERLINE) == SCR_UNDERLINE)
              iAttr |= A_UNDERLINE;
 
           if ((pFld->iAttributes & SCR_REVERSE_VIDEO) == SCR_REVERSE_VIDEO)
              iAttr |= A_REVERSE;
                        
           if ((pFld->iAttributes & SCR_BLINK) == SCR_BLINK) {
              iAttr |= A_BLINK;
            }
                        
           if ((pFld->iAttributes & SCR_BELL) == SCR_BELL)
              beep();

           if ((pFld->iAttributes & SCR_BLANK_SCREEN) == SCR_BLANK_SCREEN) {
              clear();
              tcob_scr_setyx(tcob_scr_gety(),tcob_scr_getx());
           }
           attron(iAttr);
        }

        if (has_colors() == TRUE) {
           fore_color=COLOR_WHITE;
           back_color=COLOR_BLACK;
           if (pFld->iFgColor != -1){
              fore_color=get_curses_color(pFld->iFgColor);
           }
           if (pFld->iBgColor != -1){
                back_color=get_curses_color(pFld->iBgColor);
           }
           set_colors();
        }

}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                            _DisplayField                                |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static void _DisplayField(struct ScrFld *pFld) 
{
        set_atributes(pFld);
        tcob_scr_setyx(pFld->iLine, pFld->iCol);
        
        if(pFld->iAttributes & SCR_BLANK_LINE) { /* erase all the current line */
                move(tcob_scr_gety(),0);
                clrtoeol();                
                tcob_scr_setyx(tcob_scr_gety(),tcob_scr_getx());
        }
        if(pFld->iAttributes & SCR_ERASE_EOL) /* erase to end of line */
                clrtoeol();                
        if(pFld->iAttributes & SCR_ERASE_EOS) /* erase to end of screen */
                clrtobot();                
        if(pFld->iAttributes & SCR_BELL)
                beep();
        if(pFld->iAttributes & SCR_BLANK_SCREEN){
                clear();
                tcob_scr_setyx(tcob_scr_gety(),tcob_scr_getx());
        }

        if(pFld->iAttributes & SCR_SECURE) {
                tcob_scr_setchar('*', pFld->fldScr.len);
        } else {
                if((pFld->iAttributes & SCR_BLANK_WHEN_ZERO) != SCR_BLANK_WHEN_ZERO) {
                        addnstr(pFld->caScr, pFld->fldScr.len);
                } else {
                        unsigned int i, sign;
                        tcob_scr_setyx(pFld->iLine, pFld->iCol);
                        sign = tcob_extract_sign(&pFld->fldWk, pFld->caWk);
                        for(i = 0; i < pFld->fldWk.len; ++i) {
                                if(pFld->caWk[i] != '0')
                                        break;
                        }
                        tcob_put_sign(&pFld->fldWk, pFld->caWk, sign);
                        if(i == pFld->fldWk.len)
                                tcob_scr_setchar(' ', pFld->fldScr.len);
                        else
                                addnstr(pFld->caScr, pFld->fldScr.len);
                }
        }
        refresh();
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                     _DisplayForAccept                                   |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static void _DisplayForAccept(struct ScrFld *pFld) 
{

        set_atributes(pFld);
        tcob_scr_setyx(pFld->iLine, pFld->iCol);

        if(pFld->iAttributes & SCR_BLANK_LINE)
                clrtoeol();                

        if(pFld->iAttributes & SCR_SECURE)
                tcob_scr_setchar('*', pFld->fldScr.len);
        else if(pFld->iAttributes & SCR_NOECHO)
                tcob_scr_setchar(' ', pFld->fldScr.len);
        else        
                addnstr(pFld->caWk, pFld->fldScr.len);

}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                    tcob_scr_display_field                               |
 |                                                                         |
\*-------------------------------------------------------------------------*/
void tcob_scr_display_field(struct ScrFld *pFld)
{
        _DisplayField(pFld);
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                    tcob_scr_display_for_input                           |
 |                                                                         |
\*-------------------------------------------------------------------------*/
void tcob_scr_display_for_input(struct ScrFld *pFld)
{
        _DisplayForAccept(pFld);
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                         tcob_scr_display                                |
 |                                                                         |
\*-------------------------------------------------------------------------*/
void tcob_scr_display(struct ScrFld *fields) 
{
        struct ScrFld *pFld;
                
        for(pFld=fields; pFld; pFld=pFld->pNext) {
        /*   if we have a from field */
        /*        if(pFld->fldFrom) { 
         *          tcob_move(pFld->fldFrom, pFld->caFrom, &(pFld->fldScr), pFld->caScr);
         *        }
        */
                tcob_scr_display_field(pFld);
                tcob_scr_setx(tcob_scr_getx() + pFld->fldScr.len);
        }
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                         move_cursor_first                               |
 | This are helper functions for cob_accept_screen to help moving inside a |
 | field.                                                                  |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static void move_cursor_first(struct ScrFld *pFld) 
{
        pFld->iScrPos = 0;
        pFld->iFldPos = 0;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                         move_cursor_last                                |
 | This are helper functions for cob_accept_screen to help moving inside a |
 | field.                                                                  |
 |                                                                         |
\*------------------------------------------------------------------------*/
static void move_cursor_last(struct ScrFld *pFld) 
{
        pFld->iScrPos = pFld->fldScr.len - 1;
        pFld->iFldPos = pFld->fldWk.len - 1;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                     move_cursor_left                                    |
 | This are helper functions for cob_accept_screen to help moving inside   |
 | a field.                                                                |
 |                                                                         |
\*------------------------------------------------------------------------*/
static int move_cursor_left(struct ScrFld *pFld) 
{
        char cWk;
        if(pFld->iFldPos) {
                --pFld->iFldPos;
                --pFld->iScrPos;
                if((pFld->iScrPos) && (pFld->fldScr.type == DTYPE_EDITED)) {
                        cWk = pFld->caScr[pFld->iScrPos];
                        while(pFld->iScrPos) {
                                if((cWk != '.')
                                && (cWk != ','))
                                        break;
                                --pFld->iScrPos;
                                cWk = pFld->caScr[pFld->iScrPos];
                        }
                }
                return 1;
        }
        return 0;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                    move_cursor_right                                    |
 |                                                                         |
\*-------------------------------------------------------------------------*/
static int move_cursor_right(struct ScrFld *pFld) 
{
        char cWk;
        if(pFld->iFldPos < (int)(pFld->fldWk.len - 1)) {
                ++pFld->iScrPos;
                ++pFld->iFldPos;
                if(pFld->fldScr.type == DTYPE_EDITED) {
                        cWk = pFld->caScr[pFld->iScrPos];
                        while(pFld->iScrPos < (int)(pFld->fldScr.len - 1)) {
                                if((cWk != '.')
                                && (cWk != ','))
                                        break;
                                ++pFld->iScrPos;
                                cWk = pFld->caScr[pFld->iScrPos];
                        }
                }
                return 1;
        }
        return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                         tcob_scr_accept_field                          |
 |    Accept one field                                                    |
 |                                                                        |
\*------------------------------------------------------------------------*/
int tcob_scr_accept_field(struct ScrFld *pFld,int *status)
{
        int j, k, iKey,bAtEnd,action;
        move_cursor_first(pFld);
        set_atributes(pFld);
        while(1) {        
                tcob_scr_setyx(pFld->iLine, pFld->iCol + pFld->iScrPos);
                refresh();
                iKey = getch();
                *status=0;
                if(!(iKey & KEY_CODE_YES) && !(iKey < ' ')) {  /* data key pressed */ 
                        bAtEnd = 0;
                        if(pFld->fldScr.type != DTYPE_ALPHANUMERIC) { /* numeric input */
                                if(((iKey < '0') || (iKey > '9')) && 
                                    (iKey != '-') &&
                                    (iKey != '+') &&
                                    (iKey != '.') &&
                                    (iKey != ',')) {
                                        beep();
                                        iKey = 0;
                                }
                        }
                        if ( iKey ) {
                                /* upper & loower */
                                if (pFld->iAttributes & SCR_UPPER) 
                                    iKey=toupper(iKey);
                                if (pFld->iAttributes & SCR_LOWER) 
                                    iKey=tolower(iKey);
                                pFld->caWk[pFld->iFldPos] = (char)iKey;
                                _DisplayForAccept(pFld);
                                if(pFld->iFldPos < (int)(pFld->fldScr.len - 1)) {
                                        ++pFld->iFldPos;
                                        ++pFld->iScrPos;
                                } else
                                        bAtEnd = 1;
                        }
                        if((bAtEnd) && (pFld->iAttributes & SCR_AUTO)) {
                                return EDIT_DOWN_FIELD;
                        }
                } else {  /* non data key pressed */
                        action = tcob_scr_action_for_key(iKey,status);
                        switch(action) {                
                                case EDIT_LEFT:                        /* move cursor to left */
                                        if (!(move_cursor_left(pFld))) {
                                                if (pFld->iAttributes & SCR_AUTO) {
                                                        return EDIT_UP_FIELD;
                                                } else {
                                                        beep();
                                                }                
                                        }
                                        break;
                                case EDIT_RIGHT:                        /* move cursor to right */
                                        if (!(move_cursor_right(pFld))) {
                                                if (pFld->iAttributes & SCR_AUTO) {
                                                        return EDIT_DOWN_FIELD;
                                                } else        {
                                                        beep();
                                                }
                                        }
                                        break;
                                case EDIT_FIRST:
                                        move_cursor_first(pFld);
                                        break;
                                case EDIT_LAST:        
                                        move_cursor_last(pFld);
                                        break;
                                case EDIT_BACKSPACE:
                                        if(pFld->iFldPos) {
                                                --pFld->iFldPos;
                                                --pFld->iScrPos;
                                        } else {
                                                beep();
                                        }
                                case EDIT_DELETE:                        /* delete character under cursor */
                                        j = pFld->fldWk.len - pFld->iFldPos - 1;
                                        k = pFld->iFldPos;
                                        memmove(pFld->caWk+k, pFld->caWk+k+1, j);
                                        pFld->caWk[k + j] = ' ';
                                        _DisplayForAccept(pFld);
                                        break;
                                case EDIT_INSERT:                /* insert a character before cursor */
                                        j = pFld->fldWk.len - pFld->iFldPos - 1;
                                        k = pFld->iFldPos;
                                        memmove(pFld->caWk+k+1, pFld->caWk+k, j);
                                        pFld->caWk[k] = ' ';
                                        _DisplayForAccept(pFld);
                                        break;
                                case EDIT_CLEAR:         /* clear the current field */
                                        memset(pFld->caWk,' ',pFld->fldWk.len);
                                        _DisplayForAccept(pFld);
                                        break;
                                case EDIT_CLEAR_TOEND:    /* Clear to the end of field */
                                        j = pFld->fldWk.len - pFld->iFldPos - 1;
                                        k = pFld->iFldPos;
                                        memset(pFld->caWk + k,' ',j);
                                        _DisplayForAccept(pFld);
                                        break;
                                default:                  /* replace character under cursor */ 
                                        return action;
                        }
                }
        }
        return EDIT_TERMINATE;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                         tcob_scr_accept                                |
 |  Accept all the fields until finish of function key pressed            |
 |  Return the value for the screen_status                                |
 |                                                                        |
\*------------------------------------------------------------------------*/
int tcob_scr_accept(struct ScrFld *fields) 
{
        int                         key_status,action;
        struct ScrFld                *pFld;
        struct ScrFld                *pFirst=NULL;
        struct ScrFld                *pLast=NULL;
        struct ScrFld                *pPrev=NULL;
        
        for (pFld=fields; pFld; pFld=pFld->pNext) {
                prepare_input_field(pFld);                
                if(pFld->fldTo)        {  /* cursor stop */ 
                        if(!pFirst)
                                pFirst = pFld;
                        pLast = pFld;
                }
        }

        if(!pFirst)
                return 0;

        for(pFld=pFirst;pFld;) {  /* main accept loop */
                 if(pFld->fldTo) {
                        prepare_input_field(pFld);
                        tcob_move(&pFld->fldWk, pFld->caWk, &pFld->fldScr, pFld->caScr);
                }

                tcob_scr_display_for_input(pFld);                
                
                if (pFld != pPrev) { /* if new field, put the cursor on position */
                                     /* and display the last accepted */
                        if (pPrev)
                           tcob_scr_display_field(pPrev);
                        
                }
        
                pPrev = pFld;
                action = tcob_scr_accept_field(pFld,&key_status);
                tcob_move(&pFld->fldWk, pFld->caWk, &pFld->fldScr, pFld->caScr);

                switch(action) {
                  case EDIT_FIRST_FIELD:   /* move to first input field */
                        pFld = pFirst;
                        break;  
                  case EDIT_LAST_FIELD:    /* move to last input field */
                        pFld = pLast;
                        break;  
                  case EDIT_DOWN_FIELD:    /* move cursor to next input field */
                                           /* find next input field in chain */
                        pFld = get_next_input_field(pFld);
                        break;
                  case EDIT_UP_FIELD:      /* move cursor to prev input field */
                                           /* find prev input field in chain */
                        pFld = get_prev_input_field(pFld);
                        break;
                  case EDIT_NEXT_FIELD:    /* move cursor to next input field */
                        pFld = get_next_input_field(pFld);
                        if(!pFld)          /* if last field rotate */
                                pFld = pFirst;
                        break;
                  case EDIT_PREV_FIELD:    /* move cursor to prev input field */
                                           /* find prev input field in chain */
                        pFld = get_prev_input_field(pFld);
                        if(!pFld)          /* if last field rotate */
                                pFld = pLast;
                        break;
                  case EDIT_TERMINATE:     /* we're done */
                        pFld = NULL;
                        break;
                } /* switch  */
        } /* main loop*/
        if(pPrev)
                tcob_scr_display_field(pPrev); /* Display last accepted field */
        refresh();
        return key_status;
}

/* scr_curses.c */
