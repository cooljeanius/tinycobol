/* 
 * Copyright (C) 2007-2010  Rildo Pragana, David Essex.
 * Copyright (C) 1999-2006  Rildo Pragana, Ferran Pegueroles, Jim Noeth,
 *                          Bernard Giroud, David Essex, Andrew Cameron. 
 * Copyright (C) 1993, 1991 Rildo Pragana.
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
 * TinyCOBOL Run Time Library -- Header files
 *

 */
 

#ifndef HTCOBLIB_H
#define HTCOBLIB_H

#include "htconfig.h"
#include "mwindows.h"

#ifndef __MINGW32__
#include <sys/param.h>
#endif

#include <sys/stat.h>
#include <ctype.h>
#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <stdarg.h>
#include <sys/types.h>

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif

#include <signal.h>    

#define tc_min(x,y) ((x)<(y) ? (x) : (y))
#define tc_abs(x) ((x)<0 ? -(x) : (x))

#define HTCOB_LD_PATH    "TCOB_LD_LIBRARY_PATH"

#ifndef LT_DIRSEP_CHAR
#define LT_DIRSEP_CHAR          '/'
#endif
#ifndef LT_DIRSEP_STR
#define LT_DIRSEP_STR           "/"
#endif

#ifdef WITH_LIBREADLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#define RETURN_STATUS(x)        do { save_status (f, x); return(x); } while (0)

#define RTL_FILE_VERSION        5

#define KEY_RETURN              10
#define CHR_POSITIVE            '+'
#define CHR_NEGATIVE            '-'
#define CHR_BLANK               ' '
#define CHR_ZERO                '0'
#define CHR_DASH                '-'
#define CHR_UNDERSCORE          '_'
#define CHR_DOLLARD_SIGN        '$'
#define CHR_PERIOD              '.'
#define CHR_EOS                 '\0'

#define STR_DASH                "-"
#define STR_UNDERSCORE          "_"
#define STR_PERIOD              "."


#define DTYPE_DISPLAY           '9'
#define DTYPE_ALPHA             'A'
#define DTYPE_BININT            'B'
#define DTYPE_PACKED            'C'
#define DTYPE_ACCEPT_DISPLAY    'D'
#define DTYPE_EDITED            'E'
#define DTYPE_GROUP             'G'
#define DTYPE_POINTER           'H'
#define DTYPE_FLOAT             'U'
#define DTYPE_ALPHANUMERIC      'X'
#define DTYPE_ALPHANUMERICL     'x'

#define DTYPE_COUNT             7
#define MAX_DIGITS              18                          
#define MAX_INTEGERS            18                          
#define MAX_DECIMALS            18                          

#define RLBUF_SIZE              8192

/* File organization */
enum tcb_file_organization {
  TCB_FILE_ORGANIZATION_NONE,  
  TCB_FILE_ORGANIZATION_INDEXED,  
  TCB_FILE_ORGANIZATION_SEQUENTIAL,  
  TCB_FILE_ORGANIZATION_RELATIVE,  
  TCB_FILE_ORGANIZATION_LINESEQUENTIAL, 
  TCB_FILE_ORGANIZATION_SORT  
};

/* File access mode */
enum tcb_file_access_mode {
  TCB_FILE_ACCESS_MODE_NONE,  
  TCB_FILE_ACCESS_MODE_SEQUENTIAL,  
  TCB_FILE_ACCESS_MODE_DYNAMIC,  
  TCB_FILE_ACCESS_MODE_RANDOM   
};

/* 
 The following are used by file open IO routine.
 They indicate that the filename is EXTERNAL.
 The stored filename string is then used as an environment 
 variable name. It is used to determined the actual filename.
 If no environment variable is defined, then the filename
 defaults to the stored name.

#define ACCEV_ENVAR             5
#define ACCEV_SEQUENTIAL        6
#define ACCEV_DYNAMIC           7
#define ACCEV_RANDOM            8
*/

enum tcb_file_read_rec_mode {
  TCB_FILE_READ_REC_NONE,  
  TCB_FILE_READ_REC_NEXT,  
  TCB_FILE_READ_REC_PREVIOUS,  
  TCB_FILE_READ_REC_CURRENT  
};

enum tcb_file_write_advancing {
  TCB_FILE_WRITE_ADVANCING_PAGE_AFTER    = -2, /* after advancing page */
  TCB_FILE_WRITE_ADVANCING_PAGE_BEFORE   = -1, /* before advancing page */
  TCB_FILE_WRITE_ADVANCING_NONE          = 0,  
  TCB_FILE_WRITE_ADVANCING_NLINES_BEFORE = 1,  /* write before advancing N lines */  
  TCB_FILE_WRITE_ADVANCING_NLINES_AFTER  = 2   /* write after advancing N lines */ 
};

enum tcb_file_open_mode {
  TCB_FILE_OPEN_MODE_NONE,  
  TCB_FILE_OPEN_MODE_INPUT,  
  TCB_FILE_OPEN_MODE_IO,  
  TCB_FILE_OPEN_MODE_OUTPUT,  
  TCB_FILE_OPEN_MODE_EXTEND  
};

enum tcb_file_std_flag {
  TCB_FILE_STD_FLAG_NONE,  
  TCB_FILE_STD_FLAG_INPUT,  
  TCB_FILE_STD_FLAG_OUTPUT,  
  TCB_FILE_STD_FLAG_ERROR  
};

/* File key flags */
enum tcb_file_key_flags {
 TCB_FILE_KEY_FLAG_INDEXED_UNIQUE,
 TCB_FILE_KEY_FLAG_INDEXED_DUPLICATES,
 TCB_FILE_KEY_FLAG_RELATIVE, 
 TCB_FILE_KEY_FLAG_SORT_ASCENDING, 
 TCB_FILE_KEY_FLAG_SORT_DESCENDING 
};

/* inspect options */
#define INSPECT_CHARACTERS      1
#define INSPECT_ALL             2
#define INSPECT_LEADING         3
#define INSPECT_FIRST           4
#define INSPECT_TRAILING        5

/* screen attributes */
#define SCR_BLANK_WHEN_ZERO  0x00000001
#define SCR_HIGHLIGHT        0x00000002
#define SCR_LOWLIGHT         0x00000004
#define SCR_UNDERLINE        0x00000008
#define SCR_REVERSE_VIDEO    0x00000010
#define SCR_BLINK            0x00000020
#define SCR_JUST_LEFT        0x00000040
#define SCR_JUST_RIGHT       0x00000080
#define SCR_AUTO             0x00000100
#define SCR_SECURE           0x00000200
#define SCR_REQUIRED         0x00000400
#define SCR_FULL             0x00000800
#define SCR_SIGN_LEADING     0x00001000                   
#define SCR_SIGN_SEPARATE    0x00002000
/* #define SCR_SIGN_PRESENT     0x00004000 */
#define SCR_BELL             0x00008000
#define SCR_BLANK_SCREEN     0x00010000
#define SCR_BLANK_LINE       0x00020000
#define SCR_DISPLAY          0x00040000  /* if set display, else accept */     
#define SCR_NOECHO           0x00080000
#define SCR_UPDATE           0x00100000
#define SCR_ERASE_EOL        0x00200000
#define SCR_ERASE_EOS        0x00400000
#define SCR_NO_ADVANCING     0x00800000
#define SCR_UPPER            0x01000000
#define SCR_LOWER            0x02000000
#define SCR_IS_REFMOD        0x04000000 /* accept into a refmod field */

#define RTERR_INVALID_DATA      1
#define RTERR_INVALID_PIC       2       
#define RTERR_NO_MEM            3       
#define RTERR_DBG_TRACE         4      

/* CONDITIONAL */
enum tcb_conditional {
  TCB_CONDITIONAL_NONE,  
  TCB_CONDITIONAL_EQUAL,  
  TCB_CONDITIONAL_LT,  
  TCB_CONDITIONAL_LTEQ,  
  TCB_CONDITIONAL_GT,  
  TCB_CONDITIONAL_GTEQ,  
  TCB_CONDITIONAL_NOTEQ,  
  TCB_CONDITIONAL_NOTLT  
};

/* NOTE: This code was originally copied from OpenCOBOL */
/* File I-O status */
enum tcb_file_status {
  TCB_STATUS_00_SUCCESS                 = 00,
  TCB_STATUS_02_SUCCESS_DUPLICATE       = 02,
  TCB_STATUS_04_SUCCESS_INCOMPLETE      = 04,
  TCB_STATUS_05_SUCCESS_OPTIONAL        = 05,
  TCB_STATUS_07_SUCCESS_NO_UNIT         = 07,
  TCB_STATUS_10_END_OF_FILE             = 10,
  TCB_STATUS_14_OUT_OF_KEY_RANGE        = 14,
  TCB_STATUS_21_KEY_INVALID             = 21,
  TCB_STATUS_22_KEY_EXISTS              = 22,
  TCB_STATUS_23_KEY_NOT_EXISTS          = 23,
  TCB_STATUS_30_PERMANENT_ERROR         = 30,
  TCB_STATUS_31_INCONSISTENT_FILENAME   = 31,
  TCB_STATUS_34_BOUNDARY_VIOLATION      = 34,
  TCB_STATUS_35_NOT_EXISTS              = 35,
  TCB_STATUS_37_PERMISSION_DENIED       = 37,
  TCB_STATUS_38_CLOSED_WITH_LOCK        = 38,
  TCB_STATUS_39_CONFLICT_ATTRIBUTE      = 39,
  TCB_STATUS_41_ALREADY_OPEN            = 41,
  TCB_STATUS_42_NOT_OPEN                = 42,
  TCB_STATUS_43_READ_NOT_DONE           = 43,
  TCB_STATUS_44_RECORD_OVERFLOW         = 44,
  TCB_STATUS_46_READ_ERROR              = 46,
  TCB_STATUS_47_INPUT_DENIED            = 47,
  TCB_STATUS_48_OUTPUT_DENIED           = 48,
  TCB_STATUS_49_I_O_DENIED              = 49,
  TCB_STATUS_51_RECORD_LOCKED           = 51,
  TCB_STATUS_52_EOP                     = 52,
  TCB_STATUS_57_I_O_LINAGE              = 57,
  TCB_STATUS_61_FILE_SHARING            = 61,
  TCB_STATUS_91_NOT_AVAILABLE           = 91,
  TCB_STATUS_99_UNKNOWN                 = 99
};

#define NO_OF_FILES           100
#define TCOB_MAX_PATHLN       255

/* 2 ways to enter a run element, 
 * entering a program directly or via a call (increasing the process stack
 * or
 * returning from a called program
 */
enum {
  TCB_RUN_ELEMENT_ENTER,
  TCB_RUN_ELEMENT_RETURN
};

#pragma pack(1)

struct file_flags {
  unsigned int optional:1;
  unsigned int file_missing:1;
  unsigned int with_advancing:1;
  unsigned int adv_before:1;
  unsigned int init_done:1;
  unsigned int eof_hit:1;
  unsigned int read_done:1;
  unsigned int read_next_done:1;
  unsigned int start_record:1;
  unsigned int file_external:1;
  unsigned int file_printer:1;
  unsigned int file_isvariable:1;
  unsigned int reserved:4;
};


struct fld_desc {
        unsigned long int len;
        char type;
        unsigned char decimals;
        char pscale;
        unsigned int all:1;
        unsigned int just_r:1;
        unsigned int separate_sign:1;
        unsigned int leading_sign:1;
        unsigned int blank:1;
        unsigned int reserved:3;
        char *pic;
};

typedef struct _tcob_file_key {
  struct fld_desc *key_desc;        /* key field */
  int flag;                         /* UNIQUE=0, WITH DUPLICATES=1 keys (RELATIVE/INDEXED files) */
                                    /* ASCENDING=3, DESCENDING=4 (SORT file order) */
  unsigned int offset;              /* Record offset */
} tcob_file_key;

struct file_desc {
  unsigned char vers_id;
  struct fld_desc *fname_desc;
  int reclen;                     /* record length - max */
  int reclen_min;                 /* record length - min */

  unsigned char organization;     /* File organization */
                                  /* 1=INDEXED, 2=SEQUENTIAL, 3=RELATIVE 4=LINE-SEQUENTIAL */
  unsigned char access_mode;      /* File access mode */
                                  /* 1=SEQUENTIAL, 2=DYNAMIC, 3=RANDOM */
  unsigned char open_mode;        /* File open mode */
                                  /* 1=INPUT, 2=I-O, 3=OUTPUT, 4=EXTEND */

  char file_status[2];            /* internally saved file_status */
  /* char file_status_ext[2];     // extention - file status - unused feature */

  char *filename;                 /* Resolved file name  */

  void *dbp;                      /* File handle (FILE/fileid-int/handle) */

  char *record;                   /* Pointer to file data storage */

  struct file_flags flags;        /* File flags */

  unsigned char file_std_flag;    /* Standard-in/out/error indicator */
                                  /* NONE=0, INPUT=1, OUTPUT=2, ERROR=3 */

  /* Used for RELATIVE/INDEXED/SORT file types */
  unsigned short int  nkeys;      /* Number of keys */
  /* short int ckey;              // Current key  */
  tcob_file_key *keys;            /* Pointer to RELATIVE/INDEXED key descriptions */
};


struct scr_desc {
        int attr;
        int line;
        int column;
        short int foreground;
        short int background;
        void (*process_scr)();
};

/*
// Structure for keeping info for each run element
*/
struct runelement_info {
        char *name;                    /* the name of the run element */
        char *screen_status;           /* pointer to the screen_status 
                                          field for this run element */
        char *screen_cursor;           /* pointer to the screen_cursor
                                          field for this run element */
        int   decimal_comma;           /* value of the decimal comma symbol
                                          for this run element */
        int   currency_symbol;         /* value of the currency symbol
                                          for this run element */
        void *handler;                 /* pointer for dynamic loaded routines
                                          for calling cancel */
        struct file_list *files;       /* pointer to file open by run element. */
};

struct runelement_list {
        struct runelement_info *element;      
        struct runelement_list *next;
        struct runelement_list *prev;
};

struct file_list {
        struct file_desc *file;
        struct file_list *next;
};
#pragma pack()

DLL_EXPIMP extern int bDecimalComma;
DLL_EXPIMP extern char cCurrencySymbol;
/* DLL_EXPIMP extern int tcob_var_argc; */
/* DLL_EXPIMP extern char **tcob_var_argv; */
DLL_EXPIMP extern char* screen_status;
DLL_EXPIMP extern char* screen_cursor;

/* cobmove.c */
void  tcob_move(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2);
void  _DUMP_(unsigned char *caData, char *szCount, char *caOut);
void  _FLDDUMP_(struct fld_desc *f, char *c, char *szMsg);
void  float2all(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2);
void  initIntValues();
/* cobmove_9_.c */
void  tcob_move_9_9(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_9_b(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_9_c(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_9_e(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_9_f(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_9_x(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
/* cobmove_b_.c */
void  tcob_move_b_9(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_b_b(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_b_c(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_b_e(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_b_f(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_b_x(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
/* cobmove_c_.c */
void  tcob_move_c_9(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_c_b(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_c_c(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_c_e(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_c_f(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_c_x(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
/* cobmove_f_.c */
void  tcob_move_f_9(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_f_b(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_f_c(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_f_e(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_f_f(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_f_x(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
/* cobmove_x_.c */
void  tcob_move_x_9(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_x_b(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_x_c(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_x_e(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_x_f(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_x_x(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
/* cobmove_e_.c */
void  tcob_move_edited(struct fld_desc *f1, char *s1, 
                       struct fld_desc *f2, char *s2);
void  tcob_move_e_9(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_e_b(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_e_c(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_e_e(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_e_f(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);
void  tcob_move_e_x(struct fld_desc *f1, char *s1, 
                    struct fld_desc *f2, char *s2);

/* mcmath.c */
char  tcob_sign_to_char(int  digit );
int   tcob_char_to_sign(char  ch );
char  tcob_extract_sign(struct fld_desc *f, char *s);
void  tcob_put_sign(struct fld_desc *f, char *s, char sign);
int   tcob_get_index(struct fld_desc *f, char *s);
void  tcob_fldtod(struct fld_desc *f, char *sdata, double *fp);
void  tcob_push_double(struct fld_desc *f, char *s, double d);
int   tcob_assign_double(struct fld_desc *f, char *s1, int opts, double d1);
int   tcob_dtofld(struct fld_desc *f, char *s1, int round, double d1);
void  tcob_add_double(double *d2, double d1);
void  tcob_subtract_double(double *d2, double d1); 
void  tcob_multiply_double(double *d2, double d1); 
void  tcob_divide_double(double *d2, double d1); 
int   tcob_add(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, int round);
int   tcob_subtract(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, int round);
int   tcob_multiply(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, struct fld_desc *f3, char *s3, int round);
int   tcob_divide(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, struct fld_desc *f3, char *s3, int round);
int   tcob_divide1(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2, struct fld_desc *f3, char *s3, struct fld_desc *f4, char *s4, int round);
int   tcob_check_size_overflow(struct fld_desc *f, double d);
int   tcob_check_condition(struct fld_desc *f1, char *s1, ...);
int   tcob_compare(struct fld_desc *f1, char *s1, struct fld_desc *f2, char *s2);

/* general.c */
void tcob_stop_run(void); 
unsigned int tcob_fldLength(struct fld_desc *f);
char * tcob_dup_data(struct fld_desc *pfldDesc1, char *caData1);

void tcob_add_file_list(struct file_desc *f);
void tcob_remove_file_list(struct file_desc *f);

void tcob_cancel_all();
struct runelement_info *tcob_get_current_runelement();
void tcob_unload_runelement(struct runelement_info *i);

/* pictures.c */
char*        tcob_picExpand(struct fld_desc *f); 
unsigned int tcob_picCompLength(struct fld_desc *f); 
unsigned int tcob_picEditedCompLength(struct fld_desc *f); 
unsigned int tcob_picEditedCompDecimals(struct fld_desc *f); 
unsigned int tcob_picElemLen(char *p, unsigned int i);
char         tcob_picElemVal(char *p, unsigned int i);
unsigned int tcob_picReqLen(unsigned int i);
char*        tcob_picCreate(char *p, unsigned int len, ...);
char*        tcob_picAppend(char *p, unsigned int len, ...);
int          tcob_isFloatPic(char *p);
int          tcob_isNumEdit(char *p);

/* basicio.c */
void  tcob_newline(int dupon); 
void  tcob_display(struct fld_desc *f, char *s, int dupon);
void  tcob_vdisplay(struct fld_desc *f, char *s, ...);
void  tcob_display_erase(int dupon); 
int   tcob_accept_chron(struct fld_desc *f, char *buffer, int date_fmt, int is_yyyy);
int   tcob_accept_std(char *buffer, struct fld_desc *f, int echo);
int   tcob_accept_cmd_line(struct fld_desc *f, char *buffer);
int   tcob_accept_env_var(struct fld_desc *f, char *buffer, struct fld_desc *ev, char *evname);
int   tcob_init(int ac, char **av);

/* fileio.c : File IO public functions */

int tcob_open(struct file_desc *f, char *fname, int mode);
int tcob_close(struct file_desc *f); 

int tcob_read_lseq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_lseq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_write_adv_lseq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                        int opt, struct fld_desc *cnt_desc, char *cnt_buf, 
                        struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_read_seq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf); 

int tcob_read_next_seq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_seq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_adv_seq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, int opt, struct fld_desc *cnt_desc, char *cnt_buf, 
                       struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_rewrite_seq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf);

/* filerel.c : Relative file IO public functions */
int tcob_read_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_read_next_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, int nflag, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_rewrite_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_delete_rel(struct file_desc *f, struct fld_desc *cnt_desc, char *cnt_buf);
int tcob_start_rel(struct file_desc *f, int cond, struct fld_desc *cnt_desc, char *cnt_buf); 

int tcob_file_exception_code(struct file_desc *f, int imode, int option);

/* Private functions
int   tcob_close_real(struct file_desc *f, char *record); 
int   tcob_save_status(char *status, int rt);
*/

/* Indexed file IO public functions */
int tcob_open_idx(struct file_desc *f, int mode);
int tcob_close_idx(struct file_desc *f);
int tcob_read_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                  struct fld_desc *reclen_desc, char *reclen_buf, 
                  int ikey, struct fld_desc *fkey, char *keybuf);
int tcob_read_next_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                  int nflag, 
                  struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                   struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_rewrite_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf,
                     struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_start_idx(struct file_desc *f, 
                   int cond, int ikey, struct fld_desc *recfdesc, char *key_ptr);
int tcob_delete_idx(struct file_desc *f);


/*  For Indexed file IO Private functions see fileisam.h */

/* screenio.c */
int   tcob_accept_screen();
void  tcob_display_screen();
void  tcob_scr_process(int iAttr, int iLine, int line_sign,int iColumn,
                      int column_sign, int iFgColor, int iBgColor, int size,
                                struct fld_desc *fldScr, char *caScr, void *pInfo, ...);
void  tcob_init_screen(void);
void  tcob_do_scrio_finish();   

/* dyncall.c */                
/* void *tcob_resolve_subr(struct fld_desc*, char *); */
void *tcob_resolve_subr(struct fld_desc*, char *, int);
void tcob_resolve_subr_error(void);
void tcob_cancel_subr(char *);
int tcob_call_loadlib(struct fld_desc*, char *);
void *tcob_resolve(char *);

/* Run Time Error Routines */
void runtime_error(int iErrorNbr, struct fld_desc *pFld, void *pData);    

/* EOF htcoblib.h */
#endif /* HTCOBLIB_H */
