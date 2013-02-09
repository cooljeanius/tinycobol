/* 
 * Copyright (C) 1999 - 2010,  Rildo Pragana, 
 *               Jim Noeth, Andrew Cameron, David Essex.
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
 * TinyCOBOL Run Time Library -- Accept/Display basic I/O functions
 *

*/

/* 
// #define DEBUG_BASIC_RTS 1
// #define HTCOB_LD_PATH    "TCOB_LD_LIBRARY_PATH" 
// #define DEBUG_BASIC_RTS 1 
*/

#include "basicio.h"
#include "rterrors.h"
#include "mwindows.h"

#ifndef __MINGW32__
#include <termios.h>
#endif

#ifndef __MINGW32__
/* Needed for gettimeofday */
#include <sys/time.h>
#else
/* Needed for GetSystemTime */
#include <windows.h>
#endif


#ifdef  USE_MF_COMPATABILITY
#define TCOB_COMMANDLINE_MFCOMP  1
#endif


//extern int bDecimalComma;
static int tcob_var_argc = 0;
static char **tcob_var_argv = NULL;


#ifdef WITH_LIBREADLINE
#define _readline readline
#define _add_history add_history
#endif

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_newline                                   |
 |                                                                         |
\*-------------------------------------------------------------------------*/

void tcob_newline(int dupon) { 
        putc('\n', ((dupon==1) ? stdout : stderr));
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_vdisplay                                  |
 |                                                                         |
\*-------------------------------------------------------------------------*/

void tcob_vdisplay(struct fld_desc *f, char *s, ...) 
{
        struct fld_desc *f1;
        char *s1;
        FILE *fp = stdout;
        char buffer[128], *buf;
        unsigned int i=0, len=0, nl=0, dupon=1;
        va_list args;

        va_start(args, s);

        /* 
         Set the STDOUT/STDERR and newline(CRLF/LF) options 
         which are found in the first 2 paramaters
        */
        nl = (int)f;
        dupon = (int)s;

        if (dupon == 2)
           fp = stderr;

        /* Convert (if required) and display the next N fields */
        f1 = va_arg(args, struct fld_desc *);
        while (f1 != NULL) {
            s1 = va_arg(args, char *);
#ifdef DEBUG_BASIC_RTS
         {
         fprintf(stderr, "debug : tcob_vdisplay 0080.010 : f1->type=%c, f1->len=%d, f1->decimals=%d\n",
                 f1->type, f1->len, f1->decimals);                
         if (f1->type == 'C') {
            unsigned int j;
            unsigned char *s2=s1;
            fprintf(stderr, "debug : tcob_vdisplay 0080.015 : hexDump=");
            for (j=0; j<f1->len; j++, s2++) 
                //fprintf(stderr, "%c", *(s1+j));
                fprintf(stderr, "%x", *s2);
            fprintf(stderr, ";\n");
         }
         }
#endif                                       
            if ( (f1->type == DTYPE_DISPLAY)
               || (f1->type == DTYPE_PACKED)
               || (f1->type == DTYPE_BININT)
               || (f1->type == DTYPE_FLOAT)) {
                  len = tcob_display_expand(f1, s1, buffer); 
                  buf = buffer;
             }
             else {
                  len = f1->len;
                  buf = s1;
             }
#ifdef DEBUG_BASIC_RTS
         {
            fprintf(stderr, "debug : tcob_vdisplay 0080.060 : len=%d\n", len);
            unsigned int j;
            fprintf(stderr, "debug : tcob_vdisplay 0080.065 : charDump=");
            for (j=0; j<len; j++) 
                fprintf(stderr, "%c", *(buf+j));
            fprintf(stderr, ";\n");
         }
#endif                                       
             for (i=0; i<len; i++)
                  putc(buf[i], fp);
             f1 = va_arg(args, struct fld_desc *);
        }
        va_end(args);

        if (nl == 2)
           putc('\n', fp);
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_display                                   |
 |                                                                         |
\*-------------------------------------------------------------------------*/

void tcob_display(struct fld_desc *f, char *s, int dupon) 
{
        FILE *fp;
        char buffer[128], *buf;
        unsigned int i, len=0;

        if ( (f->type == DTYPE_DISPLAY)
          || (f->type == DTYPE_PACKED)
          || (f->type == DTYPE_BININT)
          || (f->type == DTYPE_FLOAT)) {
             len = tcob_display_expand(f, s, buffer); 
             buf = buffer;
        }
        else {
             len = f->len;
             buf = s;
        }

        if (dupon == 1) {
           fp = stdout;
        } 
        else {
           fp = stderr;
        }
        for (i=0; i<len; i++)
            putc(buf[i], fp);

}

int tcob_display_expand(struct fld_desc *f, char *s, char *buf) 
{
        char *buffer;
        struct fld_desc ftmp;
        unsigned int picLen;
        unsigned int len;
        char cDecimalChar;

        cDecimalChar = (bDecimalComma) ? ',' : '.';
        len = tcob_picCompLength(f) + tc_abs((char)f->pscale);

#ifdef DEBUG_BASIC_RTS
        {
         fprintf(stderr, "debug : tcob_display_expand 0170.040 : f->type=%c, f->len=%d, len=%d, f->decimals=%d\n",
                 f->type, f->len, len, f->decimals);                
         if (f->type != DTYPE_GROUP) {
            unsigned char c;
            unsigned int i;
            fprintf(stderr, "debug : tcob_display_expand 0170.045 : pic=");
            for(i=0; (c=tcob_picElemVal(f->pic,i)); i++) {
              fprintf(stderr, "%c(%d)", c, tcob_picElemLen(f->pic,i));
            }
            fprintf(stderr, "\n");
         }
        }
#endif                                       
        memmove(&ftmp,f,sizeof(ftmp));
        ftmp.type = DTYPE_EDITED;

        picLen = tcob_picReqLen(4);
        ftmp.pic = (char *)malloc(picLen);
        tcob_picCreate(ftmp.pic, picLen, NULL);
        if(tcob_picElemVal(f->pic,0) == 'S')
                tcob_picAppend (ftmp.pic, picLen, '-', 1, NULL);
        if (ftmp.decimals <= 0) {
                tcob_picAppend (ftmp.pic, picLen, '9', len, NULL);
        } else if (tcob_picElemVal(f->pic,0) == 'P' || /* unsigned scaled */
                   tcob_picElemVal(f->pic,1) == 'P') { /* signed scaled */
                tcob_picAppend (ftmp.pic, picLen,
                        cDecimalChar, 1,
                        '9', ftmp.decimals, NULL);
        } else {
                tcob_picAppend (ftmp.pic, picLen,
                        '9', len - ftmp.decimals,
                        cDecimalChar, 1,
                        '9', ftmp.decimals, NULL);
        }

        if (ftmp.decimals > 0) /* account for the decimal point */
                len++;
        if(tcob_picElemVal(f->pic,0) == 'S') /* account for the sign */
                len++;
        buffer = buf;        
        ftmp.len = len;

#ifdef DEBUG_BASIC_RTS
        {
         fprintf(stderr, "debug : tcob_display_expand 0170.120 : type=%c, len=%d, decimals=%d;\n",
                ftmp.type, ftmp.len, ftmp.decimals);                
         if (ftmp.type != DTYPE_GROUP) {
           unsigned char c;
           unsigned int i;
           fprintf(stderr, "debug : tcob_display_expand 0170.125: pic=");
           for(i=0; (c=tcob_picElemVal(ftmp.pic,i)); i++)
              fprintf(stderr, "%c(%d)", c, tcob_picElemLen(ftmp.pic,i));
           fprintf(stderr, "\n");
         }
        }
#endif                                       

#ifdef DEBUG_BASIC_RTS
        {
        fprintf(stderr, "debug : tcob_display_expand 0170.160 : f->len=%d\n", f->len);
        unsigned int j;
        unsigned char *s2=s;
        fprintf(stderr, "debug : tcob_display_expand 0170.165 : hexDump=");
        for (j=0; j<f->len; j++, s2++) 
            fprintf(stderr, "%x", *s2);
//            fprintf(stderr, "%x", *(s+j));
        fprintf(stderr, ";\n");
        }
#endif                                       
        tcob_move(f, s, &ftmp, buffer);
#ifdef DEBUG_BASIC_RTS
        {
        fprintf(stderr, "debug : tcob_display_expand 0170.180 : ftmp.len=%d\n", ftmp.len);
        unsigned int j;
        fprintf(stderr, "debug : tcob_display_expand 0170.185 : charDump=");
        for (j=0; j<ftmp.len; j++) 
            fprintf(stderr, "%02x", *(buffer+j));
        fprintf(stderr, ";\n");
        }
#endif                                       

        free(ftmp.pic);

        return (len);
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_display_erase                             |
 |                                                                         |
\*-------------------------------------------------------------------------*/

void tcob_display_erase(int dupon) { 
        putc('\f', ((dupon == 1) ? stdout : stderr));
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_accept_chron                              |
 |  Accepts a variable using the current local time/date.                  |
 |                                                                         |
\*-------------------------------------------------------------------------*/

/* DATE-TIME */
#define DATE                 0
#define TIME                 1
#define DAY                 2
#define DAY_OF_WEEK         3

int tcob_accept_chron( struct fld_desc *f, char *buffer,
                       int date_fmt, int is_yyyy ) {
        time_t tnow;
        struct tm *timep;
        unsigned int ctime;
        unsigned int year;
        unsigned int digits;
        unsigned int hsec;  /* hundredths of a second */

        time(&tnow);
        timep = localtime(&tnow);
        year = (is_yyyy) ? (timep->tm_year)+1900 : (timep->tm_year)%100;

        /* Determine hundredths of a second */
        if (date_fmt == TIME) {
#ifndef __MINGW32__
                struct timeval tv;
                gettimeofday (&tv, NULL);
                hsec = tv.tv_usec / 10000;
#else
                SYSTEMTIME st;
                GetSystemTime (&st);
                hsec = st.wMilliseconds / 10;
#endif
        }

        switch (date_fmt) {
         case TIME:
         /*  Accepts the current time in the form 'HHMMSScc'.
          *    HH is the hour (0-23), MM is the minute, SS is the second,
          *    cc is hundredths of a second.
          */
                ctime = timep->tm_hour * 1000000 +
                        timep->tm_min * 10000 +
                        timep->tm_sec * 100 +
                        hsec;
                digits = 8;
                break;
         case DATE:
         /*  Accepts the current date in the form 'YYMMDD'/'YYYYMMDD'.
          *    YY is the year, MM is the month (January=1), DD is the day.
          */
                ctime = year * 10000 +
                        ((timep->tm_mon)+1) * 100 +
                        timep->tm_mday;
                digits = (is_yyyy) ? 8 : 6;
                break;
         case DAY:
         /*  Accepts the current day of the year in the form 'YYDDD'/'YYYYDDD'.
          *    YY is the year, DDD is the day of the year.
          */
                ctime = year * 1000 +
                        ((timep->tm_yday)+1);
                digits = (is_yyyy) ? 7 : 5;
                break;
         case DAY_OF_WEEK:
         /*  Accepts the current day of the week into a single character.
          *  The reason for the calculation is that C's representation of
          *    Sunday is 0, while in COBOL it is 7.  The rest of the week is
          *    the same in both languages (Monday=1 ... Saturday=6).
          */
                ctime = (((timep->tm_wday)+6)%7)+1;
                digits = 1;
                break;
         default:
                return 1;
        }

        {
          struct fld_desc tmpfld;
          int piclen;
          char edited[9];  /* length is max value of 'digits' plus one */

          memset (&tmpfld, 0, sizeof(tmpfld));
          tmpfld.len = digits;
          tmpfld.type = DTYPE_DISPLAY;
          piclen = tcob_picReqLen(1);
          tmpfld.pic = tcob_picCreate (malloc(piclen), piclen, '9', digits);
          sprintf(edited, "%0*d", digits, ctime);
          tcob_move(&tmpfld, (char *)&edited, f, buffer);
          free (tmpfld.pic);
        }

        return 0;
}



/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_accept_std                                |
 |                                                                         |
\*-------------------------------------------------------------------------*/

int tcob_accept_std(char *buffer, struct fld_desc *f, int flags) 
{

#ifndef __MINGW32__
        struct termios attr;
#endif
        int r;
        static char *szBuf = NULL;
        unsigned int picLen;        
        struct fld_desc f1 = {0,DTYPE_ALPHANUMERIC,0,0,0,0,0,0,0,0,NULL};

#ifndef __MINGW32__
        if ((flags&SCR_NOECHO)!=0) {
                // Get terminal attributes
                if( tcgetattr(STDIN_FILENO, &attr) != 0) 
                        return (-1);

                // Turn off echo flag 
                attr.c_lflag &= ~(ECHO); 

                // Set terminal attributes 
                // Discard any typed but un-read characters
                if( tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr) != 0) 
                        return (-1);
        }
#endif

#ifdef WITH_LIBREADLINE
        if (isatty(fileno(stdin))) {
                szBuf = _readline("");
        } else {
                fgets(szBuf,RLBUF_SIZE,stdin);
                szBuf[strlen(szBuf)-1]=0;
        }
        r = strlen(szBuf) ? 0 : -1; /* it's not really "on escape", but... */
#else
        /* we alloc the line buffer only at the first time */
        if (szBuf == NULL)
           szBuf = (char *)malloc(RLBUF_SIZE);
        /* check for EOF or error condition */
        if(fgets(szBuf,RLBUF_SIZE,stdin) != NULL) {
           szBuf[strlen(szBuf)-1]=0;
           r = 0;
        }
        else {
           szBuf[0]='\0';
           r = -1;
        }
#endif        

        f1.len = strlen(szBuf);
        picLen = tcob_picReqLen(1);
        f1.pic = (char *)malloc(picLen);
        tcob_picCreate(f1.pic, picLen, 'X', f1.len, NULL);

#ifdef WITH_LIBREADLINE
        if (f1.len)
           _add_history(szBuf);
#endif

        tcob_move(&f1, szBuf, f, buffer);
        free (f1.pic);

#ifdef WITH_LIBREADLINE
        /* free the buffer only if it came from a readline call */
        if (isatty(fileno(stdin))) {
           free(szBuf);        
           szBuf = NULL;        
        }
#else
        free(szBuf);        
        szBuf = NULL;        
#endif

#ifndef __MINGW32__
        if ((flags&SCR_NOECHO)!=0) {
           // Turn on echo flag 
           attr.c_lflag |= ECHO; 

           // Set terminal attributes 
           if( tcsetattr(STDIN_FILENO, TCSANOW, &attr) != 0) 
              return (-1);
        }
#endif

    return r;                

}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_accept_cmd_line                           |
 |  Accepts the set of command-line variables as a single string.          |
 |  Return value - 0: Success                                              |
 |                 1: Insufficient space in buffer                         |
 |                                                                         |
\*-------------------------------------------------------------------------*/

int tcob_accept_cmd_line(struct fld_desc *f, char *buffer ) {
        int             i, r=0;
        unsigned int    len, totlen;

#ifdef DEBUG_BASIC_RTS
        fprintf(stderr, "debug: accept_cmd_line : f.type=%c, f.len=%d\n", f->type, f->len);
#endif

        /* Padd variable with blanks */
        memset(buffer, ' ', f->len);

        /* Process input parms */ 
        totlen = 0;
        /* Command line index */
/*
//#ifdef DEBUG_BASIC_RTS
//        fprintf(stderr, "debug: accept_cmd_line 1: tcob_var_argc=%d\n", ac);
//#endif
*/

#ifdef TCOB_COMMANDLINE_MFCOMP
        for (i=1; i<tcob_var_argc; i++) {
#else
        for (i=0; i<tcob_var_argc; i++) {
#endif

#ifdef DEBUG_BASIC_RTS
        fprintf(stderr, "debug: accept_cmd_line 2: av[%d]=%s;\n", i, tcob_var_argv[i]);
#endif

                len = strlen(tcob_var_argv[i]);

//#ifdef DEBUG_BASIC_RTS
//        fprintf(stderr, "debug: accept_cmd_line 3: len=%d; j=%d;\n", len, j);
//#endif

                if (f->len >= totlen + len) {
                        memmove(&buffer[totlen], tcob_var_argv[i], len);
                        totlen += (len + 1);
                        if ((i+1 != tcob_var_argc) && (f->len < totlen)) {
                                i = tcob_var_argc;
                                r = 1;
                        }
                } 
                else {

//#ifdef DEBUG_BASIC_RTS
//        fprintf(stderr, "debug: accept_cmd_line 4: len=%d; j=%d;\n", len, j);
//#endif

                        i = tcob_var_argc;
                        r = 1;
                }
        }

        return r;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_accept_env_var                            |
 |  Accepts an environment variable.                                       |
 |  Return value - 0: Success                                              |
 |                 1: Environment variable was not found                   |
 |                 2: Insufficient space in buffer                         |
 |                 3: Other error                                          |
 |                                                                         |
\*-------------------------------------------------------------------------*/

int tcob_accept_env_var(struct fld_desc *f, char *buffer, struct fld_desc *ev, char *ptevname) {
        int             r=0, i;
        unsigned int    len;
        char            *pt1, *strevn;

#ifdef DEBUG_BASIC_RTS
        fprintf(stderr, "debug: accept_env_var 510100: f.type=%c, f.len=%d, f.type=%c, ev.len=%d;\n", 
                f->type, f->len, ev->type, ev->len);
#endif

        /* Padd variable with blanks */
        memset(buffer, ' ', f->len);

        len = ev->len;
#ifdef DEBUG_BASIC_RTS
           fprintf(stderr, "debug: accept_env_var 510120: f.len=%d, evlen=%d;\n", f->len, len);
#endif
        for (i = len - 1; i >= 0; i--) {
           if (*(ptevname+i) != ' ') 
              break;
        }        
        len = i + 1;
#ifdef DEBUG_BASIC_RTS
           fprintf(stderr, "debug: accept_env_var 510140: f.len=%d, evlen=%d;\n", f->len, len);
#endif
        
        strevn = malloc(len + 1);
        if (strevn == NULL) {
           r = 3;
           return r;          
        }
        memcpy(strevn, ptevname, len);
        *(strevn+len) = '\0'; 
#ifdef DEBUG_BASIC_RTS
        fprintf(stderr, "debug: accept_env_var 510160: len=%d, strevn=%s;\n", len, strevn);
#endif
                
        /* Get environment variable, if it exists */
        if ((pt1 = getenv(strevn)) == NULL) {
           r = 1;
#ifdef DEBUG_BASIC_RTS
           fprintf(stderr, "debug: accept_env_var 510200: f.len=%d, evlen=%d;\n", f->len, len);
#endif
        }
        else {
           len = strlen(pt1);
#ifdef DEBUG_BASIC_RTS
           fprintf(stderr, "debug: accept_env_var 510300: f.len=%d, evlen=%d;\n", f->len, len);
#endif
           if (f->len < len) {
              len = f->len;
              r = 2;
           }
#ifdef DEBUG_BASIC_RTS
           fprintf(stderr, "debug: accept_env_var 510400: f.len=%d, evlen=%d;\n", f->len, len);
#endif
           memmove(buffer, pt1, len);
        }

        free(strevn);
        return r;
}

/*-------------------------------------------------------------------------*\
 |                                                                         |
 |                          tcob_init                                      |
 |  Initialize the command line variables.                                 |
 |  Return value - 0: Success                                              |
 |                                                                         |
\*-------------------------------------------------------------------------*/

int tcob_init(int ac, char **av) {

  int r=0;

  tcob_var_argc = ac;
  tcob_var_argv = av;

  return r;
}

/* end of basicio.c */
