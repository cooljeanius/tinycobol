/*
 * Copyright (C) 2007-2010  Rildo Pragana, David Essex.
 * Copyright (C) 1999-2004  Rildo Pragana, Ferran Pegueroles, Jim Noeth,
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
 * TinyCOBOL Run Time Library -- File Handling functions
 * 

*/

/* Permissible statements -- table from CD-1.2 (cobol draft) pp. 450
 *   ----------------------------------------------------------------- 
 *   organization    | statement  | -------- open mode ------
 *   (access mode)   |            | input output  i-o  extend
 *   ----------------+------------+--------------------------
 *   line sequential |  read      |   X            
 *   (sequential)    |  write     |          X           X
 *   ----------------+------------+--------------------------
 *   sequential      |  read      |   X            X
 *   (sequential)    |  write     |          X           X
 *                   |  rewrite   |                X
 *   ----------------+------------+--------------------------
 *   indexed         |  delete    |                X
 *   relative        |            |
 *   (sequential)    |  start     |   X            X 
 *                   |            |
 *   ----------------+------------+--------------------------
 *   indexed         |  read      |   X            X
 *   relative        |  write     |          X     X
 *   (random)        |  rewrite   |                X
 *                   |  start     |
 *                   |  delete    |                X
 *   ----------------+------------+--------------------------
 *   indexed         |  read      |   X            X
 *   relative        |  write     |          X     X
 *   (dynamic)       |  rewrite   |                X
 *                   |  start     |   X            X
 *                   |  delete    |                X
 *   ----------------+------------+--------------------------
 */

#ifndef _FILEIO_H_
#define _FILEIO_H_

#ifdef __MINGW32__
#define __USE_MINGW_FSEEK                      1
#endif /* __MINGW32__ */

#define TCB_FILE_OPEN_ERROR                 -1
#define TCB_FILE_RECORD_LOCATION_ERROR       -1
#define TCB_FILE_RECORD_LOCATION_UNDEFINED   -1

/* COBOL-85 standard:
 Exception-names and the I-O status values
 EC-I-O-AT-END              '1'
 EC-I-O-INVALID-KEY         '2'
 EC-I-O-PERMANENT-ERROR     '3'
 EC-I-O-LOGIC-ERROR         '4'
 EC-I-O-RECORD-OPERATION    '5'
 EC-I-O-FILE-SHARING        '6'
 EC-I-O-IMP                 '9'
*/
enum tcb_file_exception_status {
 TCB_EC_I_O_NONE,                  /* 0x */
 TCB_EC_I_O_AT_END,                /* 1x */
 TCB_EC_I_O_INVALID_KEY,           /* 2x */
 TCB_EC_I_O_PERMANENT_ERROR,       /* 3x */
 TCB_EC_I_O_LOGIC_ERROR,           /* 4x */
 TCB_EC_I_O_RECORD_OPERATION,      /* 5x */
 TCB_EC_I_O_FILE_SHARING,          /* 6x */
 TCB_EC_I_O_UNUSED_7,              /* unused */
 TCB_EC_I_O_UNUSED_8,              /* unused */
 TCB_EC_I_O_IMP                    /* 9x */
};

/*
#define RETURN_STATUS(x)        do { save_status (f, x); return(x); } while (0)
static void save_status (struct file_desc *f, int status);
int   tcob_save_status(char *status, int rt);
*/

typedef struct _tcb_fileio_buffers {
        unsigned int size;              /* Number of buffers allocated */ 
        char **buf;                     /* File IO buffers  */ 
} tcb_fileio_buffers;

typedef struct _tcb_fileio_handle {
        union {                        /* File handle (FILE/fileid-int) */ 
          int fi;
          FILE *fh;
        } uval;        
        int  recloc;                   /* Record location - used by rewrite  */
        /* char *rfilename;                // Resolved file name  */ 
        tcb_fileio_buffers *buf;       /* File IO buffers handle  */ 
} tcb_fileio_handle;

/* tcb_fileio_buffers *fbuf;       // File IO buffers - allocated upon file open */ 


extern struct fld_desc _generic_4binary;

void save_status (struct file_desc *f, int status);
int  tcob_save_status(char *status, int rt);

//int  tcob_read_rec(struct file_desc *f, char *record, int recpos, struct fld_desc *reclen_desc, char *reclen_buf); 
//int  tcob_write_rec(struct file_desc *f, char *record, int recpos, struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_read_rec(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, int recpos, struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_write_rec(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, int recpos, struct fld_desc *reclen_desc, char *reclen_buf); 

/*
int tcob_read_lseq(struct file_desc *f, char *record, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_lseq(struct file_desc *f, char *record, struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_write_adv_lseq(struct file_desc *f, char *record, int opt, struct fld_desc *cnt_desc, char *cnt_buf, 
                        struct fld_desc *reclen_desc, char *reclen_buf); 

int tcob_read_seq(struct file_desc *f, char *record, struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_read_next_seq(struct file_desc *f, char *record, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_seq(struct file_desc *f, char *record, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_adv_seq(struct file_desc *f, char *record, int opt, struct fld_desc *cnt_desc, char *cnt_buf, 
                       struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_rewrite_seq(struct file_desc *f, char *record, struct fld_desc *reclen_desc, char *reclen_buf);

int tcob_read_rel(struct file_desc *f, char *record, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_read_next_rel(struct file_desc *f, char *record, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_rel(struct file_desc *f, char *record, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_rewrite_rel(struct file_desc *f, char *record, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_delete_rel(struct file_desc *f, char *record, struct fld_desc *cnt_desc, char *cnt_buf);
int tcob_start_rel(struct file_desc *f, char *record, int cond, struct fld_desc *cnt_desc, char *cnt_buf); 
*/

extern int tcob_open_idx(struct file_desc *f, int mode);
extern int tcob_close_idx(struct file_desc *f);

extern int tcob_open_rel(struct file_desc *f, int mode);
extern int tcob_close_rel(struct file_desc *f);

extern char *tcob_resolve_file_name(struct file_desc *f, char *fname);

int tcob_open_real(struct file_desc *f, int mode);
int tcob_close_real(struct file_desc *f); 

tcb_fileio_buffers* tcob_allocate_fbuffers(int num, int size);
void tcob_free_fbuffers(tcb_fileio_buffers *b);

tcb_fileio_handle* tcob_allocate_fhandle(int num, int size);
void tcob_free_fhandle(tcb_fileio_handle *h);

#endif 
